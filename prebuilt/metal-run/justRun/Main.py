import sys
import argparse
import atexit
import signal

import utils

utils.check_package('psutil')
utils.check_package('elftools', 'pyelftools')

import psutil
import elftools.elf.elffile
import elftools.elf.sections

from . import File
from . import Simulator
from . import RISCVISAString

SUPPORTED_SIFIVE_CORE = {
  "sifive-e20": "rv32imc",
  "sifive-e21": "rv32imac",
  "sifive-e24": "rv32imafc",
  "sifive-e31": "rv32imac",
  "sifive-e34": "rv32imafc",
  "sifive-e66": "rv32imafc_zba_zbb",
  "sifive-e76": "rv32imafc",
  "sifive-e76m": "rv32imafc_zba_zbb",
  "sifive-e76n": "rv32imafc_zba_zbb",

  "sifive-s21": "rv64imac",
  "sifive-s51": "rv64imac",
  "sifive-s54": "rv64imafdc",
  "sifive-s66": "rv64imafdc_zba_zbb",
  "sifive-s76": "rv64imafdc",
  "sifive-s76m": "rv64imafdc_zba_zbb",
  "sifive-s76n": "rv64imafdc_zba_zbb",

  "sifive-u54": "rv64imafdc",
  "sifive-u64": "rv64imafdc_zba_zbb",
  "sifive-u74": "rv64imafdc",
  "sifive-u74m": "rv64imafdc_zba_zbb",
  "sifive-u74n": "rv64imafdc_zba_zbb",

  "sifive-p270": "rv64imafdcv_zfh_zba_zbb_zvfh_zvl256b",
  "sifive-p270n": "rv64imafdcv_zfh_zba_zbb_zvfh_zvl256b",
  "sifive-x280": "rv64imafdcv_zfh_zba_zbb_zvfh_zvl512b_xsfvfhbfmin_xsfvqmaccqoq",
  "sifive-x280n": "rv64imafdcv_zfh_zba_zbb_zvfh_zvl512b_xsfvfhbfmin_xsfvqmaccqoq_xsfvfnrclipxfqf_xsfvfwmaccqqq",
  "sifive-p550": "rv64imafdc_zba_zbb",
  "sifive-p650": "rv64imafdc_zba_zbb_zbs",
}

def exit_cleanup():
    parent = psutil.Process()
    children = parent.children(recursive=True)
    for p in children:
        p.terminate()
    # give children 5 secs to complete terminate process
    gone, alive = psutil.wait_procs(children, timeout=5)
    # otherwise kill them all
    for p in alive:
        p.kill()

def signal_handler():
    def handler(signum, frame):
        # redirect all death signal to normal exit
        sys.exit(-signum)

    death_sig = (signal.SIGINT, signal.SIGQUIT, signal.SIGTERM)
    for sig in death_sig:
        signal.signal(sig, handler)

def add_simulator_into_parser(sim, parser):
    parser.set_defaults(sim=sim)

    sim.add_args(parser)

    parser.add_argument('prog', type=File.fileHandler,
                        help='executable file or hex file')
    if sim.allow_inferior_args():
        parser.add_argument('args', type=str, nargs='*',
                            help='inferior arguments')

def create_parser(simulators):
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawTextHelpFormatter)
    # just-run options
    parser.add_argument('--timeout', type=int, metavar='second(s)',
                        default=None,
                        help='timeout for program execution '
                             '(no timeout in default)')
    parser.add_argument('--verbose', '-v', action='store_true', default=False,
                        help='verbose mode')
    parser.add_argument('--arch', default=None,
            help='RISC-V Arch string, parse from ELF attribute if possible ' +
                 'by default, if not present, enable all ext. by default.\n' +
                 '--arch=all is a speical value for enable all ext.\n' +
                 '--arch= also support SiFive cpu core name as arch.\n' +
                 'Supported core: %s' % ", ".join(SUPPORTED_SIFIVE_CORE.keys()) +
                 'Note: NOT all simulator target are support this feature.')

    if isinstance(simulators, Simulator.Simulator):
        add_simulator_into_parser(simulators, parser)
    else:
        # sub-command for each simulators
        subparsers = parser.add_subparsers(title='simulator', dest='sim',
                                           help='supported simulator')
        subparsers.required = True
        for sim in simulators:
            subparser = subparsers.add_parser(
                sim.name,
                formatter_class=argparse.RawTextHelpFormatter)
            add_simulator_into_parser(sim, subparser)

    return parser

def prob_arch(opts):
    arch = opts.arch
    if arch is None:
        archs = "all"
        if isinstance(opts.prog, File.ElfFile):
            attr_sec = opts.prog.elffile.get_section_by_name(".riscv.attributes")
            if attr_sec:
                xattr_section = \
                    elftools.elf.sections.ARMAttributesSection (
                        attr_sec.header,
                        attr_sec.name,
                        opts.prog.elffile)
                for subsec in xattr_section.subsections:
                    for subsubsec in subsec.subsubsections:
                        # Tag_RISCV_arch = 5 == TAG_CPU_RAW_NAME in ARM
                        for attr in subsubsec.iter_attributes(tag="TAG_CPU_RAW_NAME"):
                            # Skip rv[32|64] and there is N byte before string for
                            # recode length.
                            archs = attr.value[2:]
                            return RISCVISAString.parse(archs)
    elif arch != 'all':
        if arch.startswith('sifive-'):
            if (arch not in SUPPORTED_SIFIVE_CORE):
                raise Exception ("Unknow sifive core name : %s" % arch)
            arch = SUPPORTED_SIFIVE_CORE[arch]
        arch = RISCVISAString.parse(arch)
        if arch is None:
            raise Exception ("Arch string parse error : %s" % arch)
        return arch
    return "all"


def is_valid_args(opts):
    # Parse opts.arch to a list or 'all'
    opts.arch = prob_arch(opts)
    # Check simulator options
    return opts.sim.check_args(opts)

def run(opts):
    machine = opts.sim.create_machine(opts)
    rv = machine.run(timeout=opts.timeout,
                     verbose=opts.verbose,
                     bypass_stdin=opts.sim.can_bypass_stdin())
    opts.sim.after_sim(opts)
    return rv

def main(args, simulators=Simulator.simulators):
    atexit.register(exit_cleanup)
    signal_handler()

    argparser = create_parser(simulators)
    opts = argparser.parse_args(args[1:])
    if not is_valid_args(opts):
        sys.exit(1)
    rv = run(opts)
    sys.exit(rv)
