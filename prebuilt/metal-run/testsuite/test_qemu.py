#!/usr/bin/env python3

import pytest
import sh
import os

def test_hello(env_sifive, qemu_run, shared_datadir):
    # Compile the hello world program
    sh.riscv64_unknown_linux_gnu_clang(shared_datadir/"hello.c", "-o",  shared_datadir/"hello", _env=env_sifive)
    # Get sysroot
    sysroot = sh.riscv64_unknown_linux_gnu_gcc("--print-sysroot", _env=env_sifive).stdout.strip().decode("utf-8")
    # Run the hello world program on qemu-run
    qemu_run("--sysroot", sysroot, shared_datadir/"hello")
