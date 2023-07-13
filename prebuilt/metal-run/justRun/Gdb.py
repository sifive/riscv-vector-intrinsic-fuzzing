import os
import sys
import subprocess
import tempfile
import pty

import utils
utils.check_package('pexpect')

import pexpect

class Gdb:
    break_funcs = ['exit', 'metal_shutdown', 'early_trap_vector']

    def __init__(self, port, debug, cmds_fmt, options, machine):
        self.port = port
        self.debug = debug
        self.cmds_fmt = cmds_fmt
        self.options = options
        self.machine = machine

    def cmd_generate(self):
        cmds = []
        for opt_name in self.cmds_fmt:
            opt = self.options.get(opt_name)
            if opt:
                cmds += opt

        return cmds

    def create_init_script(self, style=False):
        f = tempfile.NamedTemporaryFile(mode="w")
        # disable gdb style
        # this is done for the convenience of the parser
        f.write("set style enabled %s\n" % ("on" if style else "off"))
        # set gdb port
        f.write("target remote :%d\n" % self.port)
        # set breakpoints
        for break_func in self.break_funcs:
            f.write("b *%s\n" % break_func)
        f.flush()
        return f

    def run(self, timeout=None, verbose=False, bypass_stdin=False):
        self.machine.run(verbose=verbose, wait=False, bypass_stdin=False)

        # generate init gdb script & add into options
        gdb_script = self.create_init_script(style=True if self.debug else False)
        self.options['GDB_SCRIPT'] = ['-x', gdb_script.name]

        cmds = self.cmd_generate()

        if verbose:
            print (' '.join(cmds))

        # start to run with gdb
        try:
            if self.debug:
                rv = self.debug_with_gdb(cmds)
            else:
                rv = self.run_with_gdb(cmds, timeout, verbose)
        except Exception as e:
            print(e)
            rv = -1
        finally:
            # clear all processes whatever happens
            self.machine.shutdown()

        return rv

    def run_with_gdb(self, cmds, timeout, verbose):
        gdb = pexpect.spawn(' '.join(cmds), encoding='utf-8')

        if verbose:
            gdb.logfile = sys.stdout

        # continue
        gdb.expect("(gdb)")
        gdb.sendline("c")

        # start to run program
        gdb.expect("Breakpoint \\d*, .*\)", timeout=timeout)

        # get register value
        def get_val(reg_name):
            gdb.sendline("p %s" % reg_name)
            gdb.expect("\$\\d* = .*\r")
            val = parse_val(gdb.after)
            return val

        # get result
        break_line = gdb.after.split(" ")
        assert len(break_line) == 6, "Parser error on breakpoint line"
        hit_func = break_line[4]
        assert hit_func in self.break_funcs, \
            "break function %s is not in the breakpoint list" % hit_func

        # TODO: breakpoint handler will implemented by architecture class
        if "early_trap_vector" in hit_func:
            print("Hit early_trap_vector, something went wrong.")
            mcause = get_val("$mcause")
            mepc = get_val("$mepc")
            mtval = get_val("$mtval")
            print ("$mcause = %d" % mcause)
            print ("$mepc = 0x%x" % mepc)
            print ("$mtval = 0x%x" % mtval)
            rv = -1
        elif "metal_shutdown" in hit_func:
            print("metal_shutdown!")
            rv = -1
        else:
            rv = get_val("$a0")

        gdb.sendline("quit")

        return rv

    def debug_with_gdb(self, cmds):
        gdb = pty.spawn(cmds)

        # return status from pty process
        return gdb

def parse_val(line):
    raw_rv = line.strip()
    val = raw_rv.split("=")[1].strip()
    rv = int(val)
    return rv
