# metal-run: wrapper for running program from freedom-metal on qemu

## Step by step demo

### Program built with freedom-metal

```
$ make TARGET=sifive-hifive1 PROGRAM=hello software
```

### And you want to run with qemu.

```
./metal-run software/hello/debug/hello.elf
Hello, World!
```

Exit with out `ctrl+a x` or `kill`! and get correct return code from main/exit/abort!

## Usage:

```
$ ./metal-run -h
usage: metal-run [-h] [--qemu QEMU] [--machine MACHINE] [--gdb GDB]
                 [--port PORT]
                 prog

positional arguments:
  prog                  executable file

optional arguments:
  -h, --help            show this help message and exit
  --qemu QEMU           path for qemu
  --machine MACHINE, -m MACHINE
                        machine type used in qemu, default is sifive_e
  --gdb GDB             path for gdb
  --port PORT           port for communicate between gdb and qemu (auto detect
                        if not given)
```
# arty-run:
  wrapper for running program from freedom-mental on arty. see [README](docs/README.arty_run.md)

# Testing metal-run

## Prerequisites

Install python packages

```
$ pip3 install --user -r requirements.txt
```

Have functional in-house toolchain in `PATH`

```
module load sifive/freedom-tools/toolsuite-linux/2022.08.1
```

## Run pytest in top-level dir

```
$ pytest -sv ./testsuite
```

The expected output should be as follows

```
❯ pytest -sv  ./testsuite
============ test session starts ============
platform linux -- Python 3.9.2, pytest-7.1.2, pluggy-1.0.0 -- /sifive/tools/python/python/rhel8/3.9.2b/bin/python3.9
cachedir: .pytest_cache
rootdir: /ssdscratch/jzhangjian/metal-run
plugins: datadir-1.3.1
collected 1 item

testsuite/test_qemu.py::test_hello PASSED

============ 1 passed in 0.25s ============
```
