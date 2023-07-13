import abc
import os
import importlib

simulators = []
sim_config_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                              '../simulator')

class Simulator(metaclass=abc.ABCMeta):
    @property
    @abc.abstractmethod
    def name(self):
        raise NotImplementedError

    @property
    def name_of_32_version(self):
        raise NotImplementedError

    @property
    def name_of_64_version(self):
        raise NotImplementedError

    @property
    def default_root_dir(self):
        raise NotImplementedError

    def add_args(self, parser):
        parser.add_argument('--sim-path', type=str,
                            help='simulator path')
        parser.add_argument('--cpu', type=str,
                            default=self.default_cpu(),
                            help='cpu core name (default: %(default)s) \n'
                                 'recommend: \n\t'
                                  + '\n\t'.join(self.cpu_support()))

    @abc.abstractmethod
    def allow_inferior_args(self):
        raise NotImplementedError

    @abc.abstractmethod
    def cpu_support(self):
        raise NotImplementedError

    @abc.abstractmethod
    def default_cpu(self):
        raise NotImplementedError

    def deploy_sim(self, build_32=False):
        return 1

    def check_args(self, opts):
        # Check simulator path
        if opts.sim_path is None: # Did not specified any simulator
            is_32 = (opts.prog.fileClass == 32)
            if is_32:
                default_sim_name = self.name_of_32_version
            else:
                default_sim_name = self.name_of_64_version
            opts.sim_path = os.path.join(self.default_root_dir,
                                         default_sim_name)
            if not os.path.isfile(opts.sim_path):
                print ("Default simulator %s did not exist." % opts.sim_path)
                rv = self.deploy_sim(is_32)
                if rv:
                    return False
        else: #  Check for specific simulator
            if not os.path.isfile(opts.sim_path):
                print ("Specified simulator %s not found." % opts.sim_path)
                return False

        return True

    @abc.abstractmethod
    def create_machine(self, opts):
        raise NotImplementedError

    def after_sim(self, opts):
        pass

    def can_bypass_stdin(self):
        return True

for sim in os.listdir(sim_config_dir):
    if os.path.isfile(os.path.join(sim_config_dir, sim)):
        if sim.startswith('.'): # Skip hidden files
            continue
        sim = os.path.splitext(sim)[0]
        simulators.append(
            getattr(importlib.import_module('.'.join(['simulator', sim])),
                    sim)()
        )
