import os
import subprocess
import signal
import sys
from collections.abc import Sequence

class Machine:
    def __init__(self, name, cmds_fmt, options):
        if isinstance(cmds_fmt[0], Sequence) and not isinstance(cmds_fmt[0], (str, bytes, bytearray)):
            self.cmd_count = len(cmds_fmt)
            self.cmds_fmt = cmds_fmt
            self.options = options
        else:
            self.cmd_count = 1
            self.cmds_fmt = [cmds_fmt]
            self.options = [options]
        self.name = name
        self.machine = None

    def cmd_generate(self, idx):
        cmds = []
        for opt_name in self.cmds_fmt[idx]:
            opt = self.options[idx].get(opt_name)
            if opt:
                cmds += opt

        return cmds

    def expand_arg(self, arg):
        if isinstance(arg, Sequence):
            if len(arg) != self.cmd_count:
                print('Number of arguments and commands do not match')
                exit(-1)
            return arg
        else:
            return [arg] * self.cmd_count


    def run(self, timeout=None, verbose=False, wait=True, bypass_stdin=True):
        # Args have to be primitive type or a iterable collection which has len == self.cmd_count
        # Expand arg into [arg, arg, ...] if it is a primitive type
        timeout = self.expand_arg(timeout)
        verbose = self.expand_arg(verbose)
        wait = self.expand_arg(wait)
        bypass_stdin = self.expand_arg(bypass_stdin)
        for i in range(self.cmd_count):
            if callable(self.cmds_fmt[i]):
                # Maybe we could pass the last rv to the next function
                rv = self.cmds_fmt[i]()
            else:
                cmds = ' '.join(self.cmd_generate(i))

                if verbose[i]:
                    print(cmds)

                if bypass_stdin[i]:
                    self.machine = subprocess.Popen(cmds, shell=True,
                                                    # create a new session
                                                    # group processes
                                                    stderr=subprocess.STDOUT,
                                                    preexec_fn=os.setpgrp)
                else:
                    self.machine = subprocess.Popen(cmds, shell=True,
                                                    stdin=subprocess.DEVNULL,
                                                    # create a new session
                                                    # group processes
                                                    stderr=subprocess.STDOUT,
                                                    preexec_fn=os.setpgrp)

                try:
                    if wait[i]:
                        self.machine.wait(timeout=timeout[i])
                except subprocess.TimeoutExpired as e:
                    print ("%s: program timeout" % e.__class__.__name__)
                    self.shutdown()
                    rv = -1
                    # Shall we break and return if any of the commands failed?
                else:
                    rv = self.machine.returncode
                    if rv < 0:
                        signal_num = -rv
                        if signal_num <= signal.NSIG:
                            # Try to convert to signal name.
                            try:
                                if sys.version_info >= (3,8):
                                    sys.stderr.write("%s\n" % signal.strsignal(signal_num))
                                elif sys.version_info >= (3,5):
                                    sys.stderr.write("Terminated by signal %s\n" % signal.Signals(signal_num).name)
                                else:
                                    SIGNALS_TO_NAMES_DICT = dict((getattr(signal, n), n) \
                                        for n in dir(signal) if n.startswith('SIG') and '_' not in n )
                                    sys.stderr.write("Terminated by signal %s\n" % SIGNALS_TO_NAMES_DICT[signal_num])
                            except:
                                pass

        return rv

    def shutdown(self):
        self.machine.kill()
