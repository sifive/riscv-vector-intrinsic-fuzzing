import os
import subprocess

PROJECT_ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')

QEMU = 0
GDB  = 1
SPIKE = 2

PREBUILT_PATH = {
    QEMU : os.path.join(PROJECT_ROOT, 'prebuilt', 'prebuilt-qemu'),
    GDB : os.path.join(PROJECT_ROOT, 'prebuilt', 'prebuilt-gdb'),
    SPIKE : os.path.join(PROJECT_ROOT, 'prebuilt', 'prebuilt-spike'),
}

def cmdrun(cmd, cwd=None):
    rv = subprocess.run([cmd], shell=True, cwd=cwd)
    return rv.returncode

def get_qemu_hist_plugin():
    return os.path.join(PREBUILT_PATH[QEMU], 'plugins', 'insn_hist.so')

def get_qemu_prog_name(rv32_p, full_system_mode):
    prog_name = "qemu-"
    if full_system_mode:
        prog_name += "system-"
    if rv32_p:
        prog_name += "riscv32"
    else:
        prog_name += "riscv64"
    return prog_name

def qemu_default_root_dir():
    return os.path.join(PREBUILT_PATH[QEMU], 'bin')

def spike_default_root_dir():
    return os.path.join(PREBUILT_PATH[SPIKE], 'bin')

def get_gdb():
    return os.path.join(PREBUILT_PATH[GDB], 'riscv64-unknown-elf-gdb')

def get_spike():
    return os.path.join(PREBUILT_PATH[SPIKE], 'bin', 'spike')

def get_pk(xlen):
    return os.path.join(PREBUILT_PATH[SPIKE], 'bin', 'riscv%s-unknown-elf'%xlen, 'pk')

def init(comp):
    path = PREBUILT_PATH[comp]
    dir_name = os.path.dirname(path)

    if not os.path.exists(os.path.join(path, '.git')):
         cmdrun("flock .lock git submodule update --init %s" % dir_name,
                cwd=os.path.join(PROJECT_ROOT, 'prebuilt'))
    # Don't update if it's already there.
    # Checking every time will hurt the performance under a highly parallel case.
    #else:
    #     cmdrun("flock .lock git submodule update %s" % dir_name,
    #            cwd=os.path.join(PROJECT_ROOT, 'prebuilt'))
