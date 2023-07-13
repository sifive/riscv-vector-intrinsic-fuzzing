# metal-run: wrapper for running program from freedom-mental on qemu

## Step by step demo

### Program built with freedom-mental

```
$ make TARGET=sifive-hifive1 PROGRAM=hello software
```

### And you want to run with qemu.

```
./mental-run software/hello/debug/hello.elf
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
