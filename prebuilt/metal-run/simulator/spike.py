import os
import subprocess
import utils

from justRun import Simulator
from justRun import Machine
from justRun import PrebuiltUtils

class spike(Simulator.Simulator):
    @property
    def name(self):
        return 'spike'

    @property
    def name_of_32_version(self):
        return "spike"

    @property
    def name_of_64_version(self):
        return "spike"

    @property
    def default_root_dir(self):
        return PrebuiltUtils.spike_default_root_dir()

    def add_args(self, parser):
        # Add general simulator options
        super().add_args(parser)

        parser.add_argument('--spike-isa', type=str, default="",
                            help="spike option")

    def allow_inferior_args(self):
        return True

    def cpu_support(self):
        return ['no cpu for spike']

    def default_cpu(self):
        return 'no cpu for spike'

    def check_args(self, opts):
        # Check general simulator options
        if not super().check_args(opts):
            return False
        return True

    def create_machine(self, opts):
        # It seems like spike can not bypass stdin
        opts.bypass_stdin=False

        options = {'SPIKE': [opts.sim_path]}

        is_32 = (opts.prog.fileClass == 32)
        if is_32:
            xlen = 32
        else:
            xlen = 64

        if not opts.spike_isa:
          opts.spike_isa = 'rv%sgcv_zfh_xsfvqmaccdod_xsfvqmaccqoq' % xlen

        options['ISA'] = ['--isa=%s'%opts.spike_isa]
        options['CONFIG'] = ['--varch=vlen:256,elen:64,slen:256']
        options['PK'] = [PrebuiltUtils.get_pk(xlen)]
        options['PROGRAM'] = [opts.prog.path]

        if opts.args:
            options['ARGUMENT'] = [' '.join(map(utils.escape_shell_arg, opts.args))]

        cmds_fmt = ('SPIKE', 'CONFIG', 'ISA', 'PK', 'PROGRAM', 'ARGUMENT')

        return Machine.Machine(opts.cpu, cmds_fmt, options)

    def deploy_sim(self, build_32=False):
        PrebuiltUtils.init(PrebuiltUtils.SPIKE)
        return 0

    def can_bypass_stdin(self):
        return False
