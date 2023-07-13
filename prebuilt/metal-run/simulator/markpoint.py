from justRun import Simulator
from justRun import Machine
from pathlib import Path
from shutil import copy
from subprocess import run, check_output, DEVNULL
from functools import partial
from collections import namedtuple
from argparse import SUPPRESS
import os

SIMPT_DEFAULT_PATH = Path('/nfs/teams/sw/share/compiler/simpoint-umbrella')
QEMU_PATH_REL = Path('./qemu-system-riscv64')
OPENSBI_BIN_PATH_REL = Path('../image/fw_payload_qemu.bin')
FW_JUMP_VERILATOR_PATH_REL = '../image/fw_jump_verilator'
BASEFS_PATH = Path('/work/Simpoint/rootfs/rootfs-spec2k6-20210806.ext2')
ATHENA = Path('/work/sparta/athena/v2.1.1/bin/athena')
GCC_BIN = Path('/work/sparta/jenkins/riscv-tools/bin/riscv64-unknown-elf-gcc')

MRKPT_LOG_NAME = 'markpoint.stats.log.gz'
TMP_ROOTFS_NAME = 'qemu-rootfs.img'
TMP_SCRIPT_NAME = 'qemu-guest-run.sh'
CHKPTLST_NAME = '_chkptlst'
REPLAY_MEM = 'replay.mem'
BIOS_FILE_NAME = 'coldboot.mem'
MEM_FILE1_NAME = 'mem_00.hex'
MEM_FILE2_NAME = 'mem_01.hex'
VERILATOR_ELF_NAME = Path('program.elf')

CPUConf = namedtuple('CPUConf', 'verilator_path, verilator_load_elf, mem_port_width, vlen, qemu_opts')
CPU_CONFIG = {
    'sifive-x280': CPUConf(
        verilator_path=Path('/nfs/teams/sw/share/compiler/rtlsim/x280/2022-08-22.84c3c18301d/VTestDriver'),
        verilator_load_elf=True,
        mem_port_width=32,
        vlen=512,
        qemu_opts='rv64,x-b=true,x-v=true,vlen=512'
    ),
    'sifive-p670': CPUConf(
        verilator_path=Path('/work/sparta/rtlsim/p67/latest/VTestDriver'),
        verilator_load_elf=True,
        mem_port_width=32,
        vlen=128,
        qemu_opts='rv64,x-b=true,x-v=true,vlen=128'
    )
}
ROOTFS_OFFSET_KB = 2 * 1024 * 1024

log = print

def remove_cpu_prefix(cpu): return cpu.split('-')[-1]

class markpoint(Simulator.Simulator):
    @property
    def name(self):
        return 'markpoint'

    def add_args(self, parser):
        # Add general simulator options
        super().add_args(parser)

        # Add markpoint options
        parser.add_argument('-d', '--simpt_dir', help='Override the default simpoint-umbrella path')
        parser.add_argument('--sim', choices=['athena', 'verilator'], default='verilator', help='Simulator to run the ROI, defaults to verilator', dest='mrkptsim')
        parser.add_argument('--id', required=True, type=int, help='The ID of markpoint 1 to begin the simluation', metavar='<id>')
        parser.add_argument('-M', '--maxinst', required=True, type=int, help='Maximum instruction count', metavar='<i>')
        # Suppress unused arguments in the help message
        for action in parser._actions:
            if action.dest in ['arch', 'timeout', 'sim_path']:
                action.help=SUPPRESS

    def allow_inferior_args(self):
        return True

    def can_bypass_stdin(self):
        return False

    def cpu_support(self):
        return ['sifive-x280', 'sifive-p670']

    def default_cpu(self):
        return 'sifive-x280'

    def check_args(self, opts):
        self.simpt_dir = SIMPT_DEFAULT_PATH
        if opts.simpt_dir:
            self.simpt_dir = opts.simpt_dir
        # Check if path is valid

        self.bin_dir = self.simpt_dir / 'bin'
        self.qemu = self.bin_dir/ QEMU_PATH_REL
        self.qemu_plugin = self.qemu.parent
        self.opensbi_bin = self.bin_dir / OPENSBI_BIN_PATH_REL
        self.mboot_sw_path = self.bin_dir / FW_JUMP_VERILATOR_PATH_REL
        self.veri_root = CPU_CONFIG[opts.cpu].verilator_path.parent
        self.elf = Path(opts.prog.path)
        mkptid = [opts.id]
        with open(CHKPTLST_NAME, 'w') as chkptlst:
            chkptlst.writelines(map(str, mkptid))
       
        if any(opts.args):
            self.cmdline = ' '.join(opts.args)
        else:
            self.cmdline = './' + self.elf.name
        
        return True

    def build_rootfs(self):
        log(f"Generating {TMP_SCRIPT_NAME} ...")
        with open(TMP_SCRIPT_NAME, "w",) as f:
            f.write("#!/bin/sh\nset -x\n" + self.cmdline)
        os.chmod(TMP_SCRIPT_NAME, 0o755)

        log(f"Copying {self.elf.name} and {TMP_SCRIPT_NAME} into {TMP_ROOTFS_NAME} ...")
        copy(BASEFS_PATH, TMP_ROOTFS_NAME)
        debugfs_script = f"""
        write {self.elf} {self.elf.name}
        write {TMP_SCRIPT_NAME} {TMP_SCRIPT_NAME}
        quit
        """
        run(f"echo \"{debugfs_script}\" | debugfs -w {TMP_ROOTFS_NAME}", shell=True, stderr=DEVNULL)
        os.remove(TMP_SCRIPT_NAME)

    def build_mem(self):
        run(["dd", f"if={TMP_ROOTFS_NAME}", f"of={BIOS_FILE_NAME}", f"seek={ROOTFS_OFFSET_KB}", "bs=1024", "conv=notrunc"], check=True, stderr=DEVNULL)
        run(["dd", f"if={self.opensbi_bin}", f"of={BIOS_FILE_NAME}", "conv=notrunc"], check=True, stderr=DEVNULL)

    def build_mem_from_chkpt(self, chkpt_dir):
        chkpts_mem = chkpt_dir / 'state_mem'
        chkpts_cpu = chkpt_dir / 'state_cpu'
        log('Restoring memory and register state from the checkpoint ...')
        # Maybe should check the existence of chkpts_cpu/mem

        with open(self.mboot_sw_path.with_suffix('.elf'), 'rb') as f:
            f.seek(24)
            base = int.from_bytes(f.read(8), 'little') # e_entry
        sym_lst = check_output(['nm', '-s', self.mboot_sw_path.with_suffix('.elf')])
        addr = 0

        try:
            for line in sym_lst.split(b'\n'):
                if line.find(b'rv_register_file') != -1:
                    addr = int(line.split()[0], 16)
        except ValueError:
            log('ERROR: Cannot find the symbol \'rv_register_file\'')
            exit(1)

        offset = addr - base

        if (chkpts_mem.with_suffix('.zst').is_file()):
            run([self.bin_dir / 'zstd', '-f', '-d', chkpts_mem.with_suffix('.zst'), '-o', REPLAY_MEM], check=True)
        elif (chkpts_mem.with_suffix('.gz').is_file()):
            with open(REPLAY_MEM, 'wb') as f:
                run(['gunzip', '-c', chkpts_mem.with_suffix('.gz')], stdout=f, check=True)
        else:
            copy(chkpts_mem, REPLAY_MEM)

        run(["dd", f"if={self.mboot_sw_path.with_suffix('.bin')}", f"of={REPLAY_MEM}", "conv=notrunc"], check=True, stderr=DEVNULL)
        run(["dd", f"if={chkpts_cpu}", f"of={REPLAY_MEM}", f"seek={offset}", "bs=1", "conv=notrunc"], check=True, stderr=DEVNULL)

    def _verilator_preprocess(self, opts):
        l = ROOTFS_OFFSET_KB * 1024
        run([self.bin_dir / 'bin2hex', '-w', str(CPU_CONFIG[opts.cpu].mem_port_width),
                        '-n', str(l),
                        REPLAY_MEM, MEM_FILE1_NAME], check=True)
        run([self.bin_dir / 'bin2hex', '-w', str(CPU_CONFIG[opts.cpu].mem_port_width),
                        '-s', str(l),
                        REPLAY_MEM, MEM_FILE2_NAME], check=True)

    def _verilator_with_elf_preprocess(self, opts):
        log(f'Converting {REPLAY_MEM} to {VERILATOR_ELF_NAME}')

        asm_name = VERILATOR_ELF_NAME.with_suffix('.S')
        with open(asm_name, 'w') as f:
            f.write(f"""
        .section .text;
        .global _prog_start
        _prog_start:
        .incbin "{REPLAY_MEM}"
            """)

        run([GCC_BIN, '-static', '-nostdlib', str(asm_name),
                      '-T', self.veri_root / f'linker_script/{VERILATOR_ELF_NAME}.lds',
                      '-L', self.veri_root / 'linker_script',
                      '-o', str(VERILATOR_ELF_NAME)], check=True)
        if opts.cpu == 'sifive-p670':
            run(['cp', self.veri_root / 'cosim/tgv.json', '.'], check=True)

    def verilator_preprocess(self, opts):
        self.build_mem_from_chkpt(Path('checkpoint-0'))

        if CPU_CONFIG[opts.cpu].verilator_load_elf:
            self._verilator_with_elf_preprocess(opts)
        else:
            self._verilator_preprocess(opts)


    def athena_preprocess(self, _):
        self.build_mem_from_chkpt(Path('checkpoint-0'))

    def get_qemu_fmt_and_options(self, opts):
        vlens = [int(arch[3:-1]) for arch in opts.arch if (arch.startswith('zvl') and arch[-1] == 'b')]
        if any(vlens) and max(vlens) != CPU_CONFIG[opts.cpu].vlen:
            log('CPU and ELF VLEN doest not match!')
            exit()
        options = {'QEMU': [str(self.qemu)]}
        options['CPU'] = ['-cpu', CPU_CONFIG[opts.cpu].qemu_opts]
        options['DEFAULTS'] = ['-nodefaults']
        options['SERIAL'] = ['-serial', 'mon:stdio']
        options['DEBUG'] = ['-D', 'qemu.log']
        options['GRAPHIC'] = ['-nographic']
        options['TARGET'] = ['-M', 'simple-checkpoint']
        options['MEMSIZE'] = ['-m', '4096M']
        options['BIOS'] = ['-bios', BIOS_FILE_NAME]
        options['PLUGIN'] = ['-plugin', f'{self.qemu_plugin}/libmarkpoint-rv64.so,arg=log={MRKPT_LOG_NAME},arg=M1Checkpoints={CHKPTLST_NAME}']
        options['ICOUNT'] = ['-icount', 'shift=0,sleep=off']
        options['APPEND'] = ['-append', f'\'console=hvc0 root=/dev/mtdblock0 rw slram=test1,0x100000000,+0x80000000 init=/{TMP_SCRIPT_NAME}\'']
        cmds_fmt = ('QEMU', 'CPU', 'DEFAULTS', 'SERIAL', 'DEBUG', 'GRAPHIC',
                         'TARGET', 'MEMSIZE', 'BIOS', 'PLUGIN', 'ICOUNT', 'APPEND')
        return cmds_fmt, options

    def _get_verilator_fmt_and_options(self, opts):
        fname = Path(opts.prog.path).name
        options = {'VERILATOR': [str(CPU_CONFIG[opts.cpu].verilator_path)]}
        options['RNGSEED'] = ['+random_seed=1791095845']
        options['TESTFILE'] = [f'+testfile={MEM_FILE1_NAME}']
        options['TESTFILE1'] = [f'+testfile={MEM_FILE2_NAME}']
        options['AXI4SHUF'] = ['+disable_axi4_shuffling']
        options['VERBOSITY'] = ['+verbose']
        options['INSTDUMP'] = ['+inst_dump=1']
        options['PCDUMP'] = ['+pcounter_dump=1']
        options['PCINTERVAL'] = ['+pcounter_interval=13']
        options['MAXINST'] = [f'+max_inst_num={opts.maxinst}']
        options['REDIRECT'] = [f'2>{fname}.pc.trace']
        cmds_fmt = ('VERILATOR', 'RNGSEED', 'TESTFILE', 'TESTFILE1', 'AXI4SHUF', 'VERBOSITY', 'INSTDUMP', 'PCDUMP', 'PCINTERVAL', 'MAXINST', 'REDIRECT')
        return cmds_fmt, options

    def _get_verilator_with_elf_fmt_and_options(self, opts):
        fname = Path(opts.prog.path).name
        options = {'VERILATOR': [str(CPU_CONFIG[opts.cpu].verilator_path)]}
        options['RNGSEED'] = ['+random_seed=1791095845']
        options['TESTPROG'] = [f'+test_program={VERILATOR_ELF_NAME}']
        options['ELFLOADER'] = [f'+enable_elf_loader']
        options['AXI4SHUF'] = ['+disable_axi4_shuffling']
        options['RESETVEC'] = ['+global_reset_vector=2147483648']
        options['VERBOSITY'] = ['+verbose']
        options['INSTDUMP'] = ['+inst_dump=1']
        options['PCDUMP'] = ['+pcounter_dump=1']
        options['PCINTERVAL'] = ['+pcounter_interval=8']
        options['MAXINST'] = [f'+max_inst_num={opts.maxinst}']
        options['COSIM_CFG'] = [f'+cosim_cfg_file={self.veri_root/"cosim/cosim.cfg"}']
        options['REDIRECT'] = [f'2>{fname}.pc.trace']
        cmds_fmt = ('VERILATOR', 'RNGSEED', 'TESTPROG', 'ELFLOADER', 'AXI4SHUF', 'RESETVEC', 'VERBOSITY', 'INSTDUMP', 'PCDUMP', 'PCINTERVAL', 'MAXINST', 'COSIM_CFG', 'REDIRECT')
        return cmds_fmt, options

    def get_verilator_fmt_and_options(self, opts):
        if CPU_CONFIG[opts.cpu].verilator_load_elf:
            return self._get_verilator_with_elf_fmt_and_options(opts)
        else:
            return self._get_verilator_fmt_and_options(opts)

    def get_athena_fmt_and_options(self, opts):
        fname = Path(opts.prog.path).name
        options = {'ATHENA': [str(ATHENA)]}
        options['ARCH'] = ['--arch', remove_cpu_prefix(opts.cpu)]
        options['PCTRACE'] = ['-l', f'\'top.core0 inst {fname}.pc.trace\'']
        options['MAX_INST'] = ['-i', str(opts.maxinst)]
        options['UART'] = ['-p', 'top.system.params.enable_uart true']
        options['BIN'] = ['--load-bin', f'\'{REPLAY_MEM} 0x80000000\'']
        cmds_fmt = ('ATHENA', 'ARCH', 'PCTRACE', 'MAX_INST', 'UART', 'BIN')
        return cmds_fmt, options

    def qemu_cleanup(self):
        os.remove(BIOS_FILE_NAME)
        os.remove(TMP_ROOTFS_NAME)

    def verilator_cleanup(self, opts):
        os.remove(REPLAY_MEM)
        os.remove(CHKPTLST_NAME)
        if CPU_CONFIG[opts.cpu].verilator_load_elf:
            os.remove(VERILATOR_ELF_NAME)
            os.remove(VERILATOR_ELF_NAME.with_suffix('.S'))
            if opts.cpu == 'sifive-p670':
                os.remove('tgv.json')
        else:
            os.remove(MEM_FILE1_NAME)
            os.remove(MEM_FILE2_NAME)
        
    def athena_cleanup(self, _):
        os.remove(REPLAY_MEM)
        os.remove(CHKPTLST_NAME)

    def create_machine(self, opts):
        self.build_rootfs()
        self.build_mem()

        qemu_cmds_fmt, qemu_options = self.get_qemu_fmt_and_options(opts)
        sim_preprocess = partial(getattr(self, f'{opts.mrkptsim}_preprocess'), opts)
        sim_cmds_fmt, sim_options = getattr(self, f'get_{opts.mrkptsim}_fmt_and_options')(opts)
        cleanup = partial(getattr(self, f'{opts.mrkptsim}_cleanup'), opts)

        return Machine.Machine(opts.cpu,
                [qemu_cmds_fmt, self.qemu_cleanup, sim_preprocess, sim_cmds_fmt, cleanup],
                [qemu_options, None, None, sim_options, None]
            )


    def deploy_sim(self, _):
        return
