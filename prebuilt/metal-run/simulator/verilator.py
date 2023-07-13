import os, re
import subprocess

from justRun import Simulator
from justRun import Machine
from justRun import File

'''
Only support run simulator without --sim-path on gamma machine since
we need wit and wake to build verilator.

For machines without wit and wake, users should tell us prebuilt verilator by
--sim-path option.
'''

PROJECT_ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
COREIP_ROOT = "/work/coreplex"

# This should be updated periodly.
# 20G1
PCS_PATH_FOR_VER = "tarballs_20G1.03.00_rc1/full"
PCS_BASIC_PATH = "%s/%s"%(COREIP_ROOT, PCS_PATH_FOR_VER)
E20_path = "sifive_E20_rtl_full_20G1.03.00.tar.gz"
E21_path = "sifive_E21_rtl_full_20G1.03.00.tar.gz"
E24_path = "sifive_E24_rtl_full_20G1.03.00.tar.gz"
E31_path = "sifive_E31_rtl_full_20G1.03.00.tar.gz"
E34_path = "sifive_E34_rtl_full_20G1.03.00.tar.gz"
E76MC_path = "sifive_E76MC_rtl_full_20G1.03.00.tar.gz"
E76_path = "sifive_E76_rtl_full_20G1.03.00.tar.gz"
S21_path = "sifive_S21_rtl_full_20G1.03.00.tar.gz"
S51_path = "sifive_S51_rtl_full_20G1.03.00.tar.gz"
S54_path = "sifive_S54_rtl_full_20G1.03.00.tar.gz"
S76MC_path = "sifive_S76MC_rtl_full_20G1.03.00.tar.gz"
S76_path = "sifive_S76_rtl_full_20G1.03.00.tar.gz"
U52_path = "sifive_U52_rtl_full_20G1.03.00.tar.gz"
U54MC_path = "sifive_U54MC_rtl_full_20G1.03.00.tar.gz"
U54_path = "sifive_U54_rtl_full_20G1.03.00.tar.gz"
U74MC_path = "sifive_U74MC_rtl_full_20G1.03.00.tar.gz"
U74_path = "sifive_U74_rtl_full_20G1.03.00.tar.gz"
'''
We already provide --sim-path,
and default verilator in /work/evanl/verilator/latest
Do we really need to rebuild the verilator for users ?
'''

VERILATOR_VERSION="4.028" # each pcs version need corresponding verilator.
PREBUILT_VERI_BASE="/work/evanl/verilator/latest"

class verilator(Simulator.Simulator):

    std_pcs_table = { "e20": E20_path,
                      "e21": E21_path,
                      "e24": E24_path,
                      "e31": E31_path,
                      "e34": E34_path,
                      "e76mc": E76MC_path,
                      "e76": E76_path,
                      "s21": S21_path,
                      "s51": S51_path,
                      "s54": S51_path,
                      "s76mc": S76MC_path,
                      "s76": S76_path,
                      "u52": U52_path,
                      "u54mc": U54MC_path,
                      "u54": U52_path,
                      "u74mc": U74MC_path,
                      "u74": U74_path }

    core_name = None

    @property
    def name(self):
        return 'verilator'

    @property
    def name_of_verilator(self):
        return '%s/sifive_coreip/obj_dir/VTestDriver'%self.core_name

    @property
    def default_root_dir(self):
        return os.path.join("%s"%PREBUILT_VERI_BASE)

    @property
    def deploy_root_dir(self):
        return os.path.join(PROJECT_ROOT, 'sifive-verilator')

    def get_tarball_path(self, core_name):
        '''
        Get PCS tarball path here.

        Input: core_name. Currently we're consindering about standard core.
               See /work/coreplex/tarballs_20G1.03.00_rc1/full for all
               standard cores.
        '''
        tarball_path = "%s/%s"%(PCS_BASIC_PATH,
                                self.std_pcs_table.get(core_name))
        return tarball_path

    def add_args(self, parser):
        '''
        You choosed the cpu core when sim-path is given.
        Which means the --sim-path, and --cpu are excluded in verilator.
        So we will ignore --cpu when --sim-path appear.
        '''
        # Add general simulator options
        super().add_args(parser)

        # Add verilator options here
        parser.add_argument('--max-cycles', type=str,
                            default=20000000,
                            help='max cycles be executed in verilator')
        parser.add_argument('--custom-cmd', required=False, type=str,
                            help='cmd to verilator instead of default')
        parser.add_argument('--out', required=False, type=str,
                            help='path to PC trace')


    def allow_inferior_args(self):
        return True

    def cpu_support(self):
        return list(self.std_pcs_table.keys())

    def default_cpu(self):
        return 'e76'

    def set_core_name(self, core):
        self.core_name = core

    def deploy_sim(self, core_name):
        print ("start to deploy verilator for %s" % core_name)
        self.set_core_name(core_name)
        tarball_path = self.get_tarball_path(core_name)
        folder_name = os.path.basename(tarball_path).replace(".tar.gz", "")
        null_out = open(os.devnull, 'w')

        # decompress
        cmd1 = "mkdir -p {0} && tar xvf {1} --xform 's/{2}/{3}/' -C {0}".format(
                                                        self.deploy_root_dir,
                                                        tarball_path,
                                                        folder_name,
                                                        core_name)
        print ("decompress from: %s"%tarball_path)
        subprocess.call( cmd1,
                         shell=True,
                         stdout=null_out,
                         stderr=subprocess.STDOUT)

        # build verilator
        path_to_verilator = "%s/%s"%(self.deploy_root_dir, core_name)
        ml_cmd = "module load verilator/%s"%VERILATOR_VERSION
        cmd2 = "cd %s && %s && make obj_dir/VTestDriver"%( path_to_verilator,
                                                           ml_cmd)
        print ("building %s verilator"%core_name)
        rv = subprocess.call( cmd2,
                         shell=True,
                         stdout=null_out,
                         stderr=subprocess.STDOUT)

        null_out.close()
        if rv == 0:
            print ("build successfully")
        else:
            print ("build failed")
        return rv

    def check_args(self, opts):
        if isinstance( opts.prog, File.ElfFile):
            print ("please input hex file")
            return False
        if opts.sim_path is None: # Does not specfic any simulator
            # Check simulator path
            '''
            TODO: This is workaround.
            verilator need value of "--cpu" to initialize,
            But this module was initilized in very first stage.
            '''
            opts.sim.set_core_name(opts.cpu)

            default_sim_name = self.name_of_verilator
            opts.sim_path = os.path.join(self.default_root_dir,
                                         default_sim_name)
            if not os.path.isfile(opts.sim_path):
                if opts.verbose:
                    print ("default simulater %s does not exist" % opts.sim_path)
                deployed_veri = "%s/%s/obj_dir/VTestDriver"%(\
                                                          self.deploy_root_dir,
                                                          opts.cpu)
                rv = None
                if os.path.exists(deployed_veri) == False:
                    opts.sim_path = deployed_veri
                    rv = self.deploy_sim(opts.cpu)
                else:
                    if opts.verbose:
                        print ("use deployed verilator: %s"%deployed_veri)
                    opts.sim_path = deployed_veri
                if rv:
                    print ("deploy %s failed"%self.name)
                    return False
        else: #  Check specfic simulator
            if not os.path.isfile(opts.sim_path):
                print ("specfic simulater %s not found" % opts.sim_path)
                return False

        return True

    def after_sim(self, opts):
        output_path = "%s.out"%opts.prog.path
        if opts.out:
            output_path = opts.out
        print ("please get PC trace in %s"%output_path)

    def create_machine(self, opts):
        options = None
        '''
        # get lunch cmd.
          1. if custom_cmd, then use it directly
          2. if no custom_cmd, get default cmd by make --dry-run.
        '''
        if opts.custom_cmd:
            # using custom_cmd instead of default way
            cmd = "%s %s"%(opts.sim_path, opts.custom_cmd)
            options = {'VERILATOR_AND_OPTIONS': [cmd]}
        else:
            # using custom_cmd by default way

            verilator_base = "%s/.."%os.path.dirname(opts.sim_path)

            # get verilator cmd
            dry_run_cmd = "cd %s && "%verilator_base + \
                          "make hello.verilator.out --dry-run |grep VTest"
            try:
                default_cmd = subprocess.check_output(dry_run_cmd,
                                                      stderr=subprocess.STDOUT,
                                                      shell=True).decode()
            except subprocess.CalledProcessError as e:
                guess_cmd = 'bash -o pipefail -c "./obj_dir/VTestDriver '\
                          + '+random_seed=1 +tilelink_timeout=16000 '\
                          + '+disable_ahb_fuzzing=1 +disable_axi4_shuffling=1 '\
                          + '+max-cycles=20000000 +verbose '\
                          + '+inst_dump=1 +pcounter_dump=1 +pcounter_interval=8 '\
                          + '+testfile=hello.hex >hello.verilator.out 2>&1"'
                default_cmd = guess_cmd

            default_cmd = re.sub( "\+max-cycles=[0-9]* ",
                                  "+max-cycles=%s "%opts.max_cycles,
                                  default_cmd)
            default_cmd = re.sub( "\+testfile=.*\.hex",
                                  "+testfile=%s"%opts.prog.path,
                                  default_cmd)
            default_cmd = re.sub( "./obj_dir/VTestDriver ",
                                  "%s "%opts.sim_path,
                                  default_cmd)
            default_cmd = default_cmd.replace("tail -100 |", "")
            if opts.out:
                default_cmd = default_cmd.replace("hello.verilator.out",
                                                  opts.out)
            else:
                default_cmd = default_cmd.replace("hello.verilator.out",
                                              "%s.out"%opts.prog.path)
            if opts.verbose == False:
                default_cmd = re.sub("2>\&1\s*\|\s*tee", "&>", default_cmd)
            options = {'VERILATOR_AND_OPTIONS': [default_cmd]}

        # need an additional comma when only one element in a tuple
        cmds_fmt = ('VERILATOR_AND_OPTIONS', )

        return Machine.Machine(opts.cpu, cmds_fmt, options)
