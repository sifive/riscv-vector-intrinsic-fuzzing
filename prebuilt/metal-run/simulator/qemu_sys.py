import os
import subprocess

import utils

from justRun import Simulator
from justRun import Machine
from justRun import Gdb
from justRun import PrebuiltUtils

class qemu_sys(Simulator.Simulator):
    @property
    def name(self):
        return 'qemu-sys'

    @property
    def name_of_32_version(self):
        return PrebuiltUtils.get_qemu_prog_name(rv32_p=True, full_system_mode=True)

    @property
    def name_of_64_version(self):
        return PrebuiltUtils.get_qemu_prog_name(rv32_p=False, full_system_mode=True)

    @property
    def default_root_dir(self):
        return PrebuiltUtils.qemu_default_root_dir()

    def add_args(self, parser):
        # Add general simulator options
        super().add_args(parser)
        PrebuiltUtils.init(PrebuiltUtils.GDB)

        # Add qemu options
        parser.add_argument('--port', type=int,
                            default=utils.grab_available_port(),
                            help='port for communicate between gdb and qemu '
                                 '(auto detect if not given)')
        parser.add_argument('--machine', '-m', type=str,
                            default=self.default_machine(),
                            help='machine type used in qemu '
                                 '(default: %(default)s)\n'
                                 'recommend:\n\t'
                                 + '\n\t'.join(self.machine_support()))
        parser.add_argument('--gdb', type=str, default=PrebuiltUtils.get_gdb(),
                            help='path for gdb')
        parser.add_argument('--trace', action='store_true', default=False,
                            help='print out detail trace from qemu')
        parser.add_argument('--debug', action='store_true', default=False,
                            help='using gdb to debug program')


    def allow_inferior_args(self):
        return False

    def cpu_support(self):
        PrebuiltUtils.init(PrebuiltUtils.QEMU)
        cpus = subprocess.run([os.path.join(self.default_root_dir,
                                            self.name_of_64_version),
                               '-cpu', 'help'],
                               stdin=open(os.devnull),
                               stdout=subprocess.PIPE).stdout.decode()
        return cpus.splitlines()

    def default_cpu(self):
        return 'any'

    def machine_support(self):
        md = subprocess.run([os.path.join(self.default_root_dir,
                                          self.name_of_64_version),
                             '-machine', 'help'],
                            stdin=open(os.devnull),
                            stdout=subprocess.PIPE).stdout.decode()
        md_lines = md.splitlines()

        return [l.split()[0] for l in md_lines[1:]]

    def default_machine(self):
        return 'sifive_e'

    def check_args(self, opts):
        # Check general simulator options
        if not super().check_args(opts):
            return False

        # Check qemu options

        return True

    def create_machine(self, opts):
        options = {'QEMU': [opts.sim_path]}
        options['STARTUP'] = ['-S']
        if opts.cpu:
            options['CPU'] = ['-cpu', opts.cpu]
        options['GDB'] = ['-gdb', "tcp::%d" % opts.port]
        options['GRAPHIC'] = ['-nographic']
        options['MACHINE'] = ['-machine', opts.machine]
        options['KERNEL'] = ['-kernel', opts.prog.path]
        if opts.trace:
            options['TRACE'] = ['-d', 'in_asm,cpu', '-singlestep']
        cmds_fmt = ('QEMU', 'STARTUP', 'CPU', 'GDB', 'GRAPHIC',
                    'MACHINE', 'KERNEL', 'TRACE')
        machine = Machine.Machine(opts.cpu, cmds_fmt, options)

        gdb_options = {'GDB': [opts.gdb]}
        gdb_options['OPTIONS'] = ['-q']
        gdb_options['PROG'] = [opts.prog.path]
        gdb_cmds_fmt = ('GDB', 'OPTIONS', 'GDB_SCRIPT','PROG')

        return Gdb.Gdb(opts.port, opts.debug,
                       gdb_cmds_fmt, gdb_options, machine)

    def deploy_sim(self, build_32=False):
        PrebuiltUtils.init(PrebuiltUtils.QEMU)
        PrebuiltUtils.init(PrebuiltUtils.GDB)
        return 0
