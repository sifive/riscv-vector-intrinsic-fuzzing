# arty-run: wrapper for running program from freedom-mental on arty.

## Please note that
   
1. arty-run will NOT flahs FPGA to specific core ip.

    You should specify correct core ip when building from freedom-e-sdk with TARGET,

    and speicfy correct openocd config in bsp.

    Maybe support flashing in the future with arty-run or other utility.


2. Things to do if you connect multiple arty at the same Linux PC:
    a. add ftdi_location in openocd.cfg
    b. specify tty number in arty-run
    
   These are something that can't be handled automatically, sorry.

   Please see the [reference](https://sifive.atlassian.net/wiki/spaces/~561831029/pages/425427398/Play+Arty)


## Step by step demo on hsinchu lab server

Assume that you flashed e31 on arty.

### Program built with benchmark repo

```
$ git clone git@github.com:sifive/benchmarks.git --recursive

$ cd benchmarks && source ./sourceme

$ python ./scripts/evaluate_benchmark.py --benchmark-list coremark_esdk_p10100 --freedom-target e31-arty --coremark-float 1 --toolchain /scratch/sifive-tw-lab/tool/riscv64-unknown-elf-gcc-8.2.0-2019.02.0-x86_64-linux-ubuntu14/bin/riscv64-unknown-elf-gcc --qemu-path ~/scratch/tools/qemu-system-riscv/bin/qemu-system-riscv32

```


### And you want to run with arty.

```
/home/evanli/scratch/work/metal-run/arty-run --openocd /scratch/sifive-tw-lab/tool/riscv-openocd-0.10.0-2019.02.0-x86_64-linux-ubuntu14/bin/openocd --gdb /scratch/sifive-tw-lab/tool/riscv64-unknown-elf-gcc-8.2.0-2019.02.0-x86_64-linux-ubuntu14/bin/riscv64-unknown-elf-gdb --openocd-config /scratch/sifive-tw-lab/freedom-e-sdk/bsp/coreip-e31-arty/openocd1.cfg --timeout 50 --executable benchmarks/binary/tasks/$task_id/coremark_esdk_p10100.-Os.plain --tty /dev/ttyUSB2

# need to wait for 30s for coremark running
```

## Usage: 
```
usage: arty-run [-h] [--timeout TIMEOUT] --tty TTY --executable EXECUTABLE
                --gdb GDB --openocd OPENOCD --openocd-config OPENOCD_CONFIG

optional arguments:
  -h, --help            show this help message and exit
  --timeout TIMEOUT     timeout
  --tty TTY             tty string, ex: /dev/ttyUSB1
  --executable EXECUTABLE
                        executable file
  --gdb GDB             path to gdb
  --openocd OPENOCD     path to openocd
  --openocd-config OPENOCD_CONFIG
                        config of openocd

```
