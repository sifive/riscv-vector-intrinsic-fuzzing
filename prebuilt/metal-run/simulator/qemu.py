import os
import subprocess
import utils

from justRun import Simulator
from justRun import Machine
from justRun import PrebuiltUtils

EXT_OPTS = {
  "zba":             "zba=true",
  "zbb":             "zbb=true",
  "zbc":             "zbc=true",
  "zbs":             "zbs=true",
  "v":               "v=true",
  "zve32f":          "Zve32f=true",
  "zve64f":          "Zve64f=true",
  "zfh":             "Zfh=true",
  "zvamo":           "x-Zvamo=true",
  "zvfh":            "x-Zvfh=true",
  "xsfvqmaccqoq":    "x-xsfvqmaccqoq=true",
  "xsfvqmaccdod":    "x-xsfvqmaccdod=true",
  "xsfvfhbfmin":     "x-xsfvfhbfmin=true",
  "xsfvfnrclipxfqf": "x-xsfvfnrclipxfqf=true",
  "xsfvfwmaccqqq":   "x-xsfvfwmaccqqq=true",
  "xsfvcp":   "x-xsfvcp=true",
}

class qemu(Simulator.Simulator):
    @property
    def name(self):
        return 'qemu'

    @property
    def name_of_32_version(self):
        return PrebuiltUtils.get_qemu_prog_name(rv32_p=True, full_system_mode=False)

    @property
    def name_of_64_version(self):
        return PrebuiltUtils.get_qemu_prog_name(rv32_p=False, full_system_mode=False)

    @property
    def default_root_dir(self):
        return PrebuiltUtils.qemu_default_root_dir()

    def add_args(self, parser):
        # Add general simulator options
        super().add_args(parser)

        qemu_env_message = '''
You can use -E and -U options or the --set-env and --unset-env options to set and unset environment variables for the QEMU process.
It is possible to provide several variables by separating themby commas in getsubopt(3) style.
Additionally it is possible to provide the -E and -U options multiple times.
The following lines are equivalent:
    -E var1=val2 -E var2=val2 -U LD_PRELOAD -U LD_DEBUG
    -E var1=val2,var2=val2 -U LD_PRELOAD,LD_DEBUG
Note that if you provide several changes to a single variable
the last change will stay in effect
'''

        # Add qemu options
        parser.add_argument('--gdb-port', type=int,
                            default=None,
                            help='Specify gdb port and wait gdb connection to that port')
        parser.add_argument('--env', '-E', action='append', default=[],
                            help="Set environment variable for qemu." + qemu_env_message)
        parser.add_argument('--unset-env', '-U', action='append', default=[]
                            , help="Unset environment variable for qemu" + qemu_env_message)
        parser.add_argument('--sysroot', type=str, default="",
                            help="Path for sysroot, must set if running "
                                 "linux user program with dynamic link")
        parser.add_argument('--hist-trace', action='store_true',
                            help="Generate trace log")
        parser.add_argument('--in-asm', action='store_true',
                            help="Pass -d in_asm to qemu")
        parser.add_argument('--dump-reg', action='store_true',
                            help="Pass -d cpu to qemu")
        parser.add_argument('--hist-trace-output', type=str,
                            help="Output file name for trace log, default is executable name + \".qhist\"")
        parser.add_argument('--in-asm-output', type=str, default="",
                            help="Output file name for in_asm log, default is stdout")
        parser.add_argument('--strace', '-strace', action='store_true',
                            help="Enable strace for qemu")
        parser.add_argument('--fill-vector-agnostic-to-1', action='store_true',
                            help="Fill tha inactive and tail element to all 1 ")


    def allow_inferior_args(self):
        return True

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

    def check_args(self, opts):
        # Check general simulator options
        if not super().check_args(opts):
            return False

        # Check qemu options

        return True

    def create_machine(self, opts):
        options = {'QEMU': [opts.sim_path]}
        if opts.cpu == 'any':
            is_32 = (opts.prog.fileClass == 32)
            if is_32:
                opts.cpu = 'rv32'
            else:
                opts.cpu = 'rv64'

        if opts.arch == 'all':
            # default to zvl512b for arch=all
            max_vlen = 512
            ext_opts = list(set(EXT_OPTS.values())) + ['vlen=512', 'vext_spec=v1.0']
        else:
            max_vlen = 0
            ext_opts = ['vext_spec=v1.0']
            for arch in opts.arch:
                if arch in EXT_OPTS:
                    ext_opts.append(EXT_OPTS[arch])
                if (arch.startswith('zvl') and arch[-1] == 'b'):
                    vlen = int(arch[3:-1])
                    max_vlen = max(vlen, max_vlen)
            if max_vlen != 0:
                ext_opts.append('vlen=%d'%max_vlen)
        if max_vlen != 0:
            ta_ma_fill_1 = False
            if (opts.fill_vector_agnostic_to_1):
                ta_ma_fill_1 = True
            # TODO: Default ta_ma_fill_1 = True for those CPU really did that
            #       like P670.
            if ta_ma_fill_1:
                ext_opts += ["rvv_ta_all_1s=true", "rvv_ma_all_1s=true"]
            else:
                ext_opts += ["rvv_ta_all_1s=false", "rvv_ma_all_1s=false"]

        elen = 0
        for arch in opts.arch:
          if (arch.startswith("zve32")):
            elen = max(elen, 32)
          if (arch.startswith("zve64") or arch == 'v'):
            elen = max(elen, 64)

        if elen != 0:
          ext_opts.append("elen=%d" % elen)

        if opts.in_asm:
            dash_d = ["in_asm"]
            if opts.dump_reg:
              dash_d.append("cpu")
            options['DIN_ASM'] = ["-d", ",".join(dash_d)]
            options['DIN_ASM'] += ["-singlestep"]

            if opts.in_asm_output != '':
                options['DIN_ASM'] += ["-D", opts.in_asm_output]


        cpu_opts = ['-cpu']

        # TODO: Disable unused EXT.
        if len(ext_opts) != 0:
            cpu_opts.append(opts.cpu + "," + ",".join(ext_opts))
        else:
            cpu_opts.append(opts.cpu)

        options['CPU'] = cpu_opts
        options['PROGRAM'] = [opts.prog.path]

        if opts.args:
            options['ARGUMENT'] = [' '.join(map(utils.escape_shell_arg, opts.args))]

        if opts.sysroot:
            options['SYSROOT'] = ['-L', opts.sysroot]

        if opts.hist_trace or opts.hist_trace_output is not None:
            trace_output = opts.hist_trace_output
            if trace_output is None:
                trace_output = os.path.basename(opts.prog.path) + ".qhist"

            options['HIST'] = ['-plugin', PrebuiltUtils.get_qemu_hist_plugin(), '-D', trace_output, '-d', 'plugin']

        if opts.strace:
            options['STRACE'] = ['-strace']

        if opts.gdb_port:
            options['GDB_PORT'] = ['-g', str(opts.gdb_port)]

        if opts.env:
            options['ENV'] = ['-E', ','.join(opts.env)]

        if opts.unset_env:
            options['UNSET_ENV'] = ['-U', ','.join(opts.unset_env)]

        # RHEL 8 work-around...
        # RHEL 8 will got following error when running rv32 program, and -B
        # option can resolve that.
        # qemu-riscv32: Unable to reserve 0xfffff000 bytes of virtual address
        # space at 0x1000 (Success) for use as guest address space (check
        # yourvirtual memory ulimit setting, min_mmap_addr or reserve less using -R option)
        if os.path.exists("/etc/redhat-release"):
            options['B'] = ['-B', '0x100000']

        cmds_fmt = ('QEMU', 'GDB_PORT', 'CPU', 'DIN_ASM', 'B', 'STRACE', 'HIST', 'ENV', 'UNSET_ENV', 'SYSROOT', 'PROGRAM', 'ARGUMENT')

        return Machine.Machine(opts.cpu, cmds_fmt, options)

    def deploy_sim(self, build_32=False):
        PrebuiltUtils.init(PrebuiltUtils.QEMU)
        return 0
