import os
import subprocess

from justRun import Simulator
from justRun import Machine

PROJECT_ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
GEM5_CONFIGS_PATH = 'configs/sifive'

class gem5(Simulator.Simulator):
    device_conf = {'mallard': {'arch': 'RISCV',
                               'cpu':  'mallard_o3'},
                   'e27':     {'arch': 'RISCV',
                               'cpu':  'e27_minor'}}

    @property
    def name(self):
        return 'gem5'

    @property
    def name_of_32_version(self):
        return 'build/SF_RISCV_32/gem5.opt'

    @property
    def name_of_64_version(self):
        return 'build/SF_RISCV_64/gem5.opt'

    @property
    def default_root_dir(self):
        return os.path.join(PROJECT_ROOT, 'sifive-gem5')

    def add_args(self, parser):
        # Add general simulator options
        super().add_args(parser)

        # Add gem5 options
        parser.add_argument('--config-dir', type=str,
                            default=os.path.join(self.default_root_dir,
                                                 GEM5_CONFIGS_PATH),
                            help='config folder')
        parser.add_argument('--dump-rtl-trace', action='store_true',
                            default=False,
                            help='dump rtl trace format')


    def allow_inferior_args(self):
        return True

    def cpu_support(self):
        return list(self.device_conf)

    def default_cpu(self):
        return 'mallard'

    def deploy_sim(self, build_32=False):
        print ("start to build %s" % self.name)
        if build_32:
            default_sim_name = self.name_of_32_version
        else:
            default_sim_name = self.name_of_64_version

        rv = subprocess.call(
            "cd %s && \
            git submodule update --init --recursive && \
            scons %s -j12" % (self.default_root_dir, default_sim_name),
            shell=True)

        return rv

    def check_args(self, opts):
        # Check general simulator options
        if not super().check_args(opts):
            return False

        # Check gem5 options

        return True

    def create_machine(self, opts):
        options = {'GEM5': [opts.sim_path]}
        if opts.dump_rtl_trace:
            options['DEBUG_FLAGS'] = ['--debug-flags=ExecEnable,SFExec']

        # redirect m5out directory into /tmp/
        options['GEM5_OPTIONS'] = ['--outdir=/tmp/m5out']
        if not opts.verbose:
            options['GEM5_OPTIONS'].append('--quiet')

        options['SCRIPT_PY'] = [os.path.join(opts.config_dir,
                                             "%s.py" % opts.cpu)]

        if self.device_conf[opts.cpu].get('cpu'):
            options['CPU'] = ["--cpu=%s" % self.device_conf[opts.cpu]['cpu']]

        options['COMMAND'] = ["%s %s" % (opts.prog.path, ' '.join(opts.args))]
        cmds_fmt = ('GEM5', 'GEM5_OPTIONS', 'DEBUG_FLAGS', 'SCRIPT_PY', 'CPU', 'COMMAND')

        return Machine.Machine(opts.cpu, cmds_fmt, options)
