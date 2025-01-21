# RVV Intrinsic Fuzzing (RIF)

This repository aims to create fuzz testing for the RVV C intrinsic.

## Usage

### How To Build?

```
$ git clone https://github.com/sifive/riscv-vector-intrinsic-fuzzing
$ cd riscv-vector-intrinsic-fuzzing
$ cd test/build
$ cmake ../..
$ make
$ ./tool/random_gen --help
Usage: random_gen [OPTION...]

  -c, --code=FILE            C code file, default filename: 'output.c'
  -d, --dot=FILE             Graphviz visualization file, default filename is
                             'output.dot'
  -h                         Give this help list
  -m, --march=ARCH_STRING    Arch string for testing, default is rv64gcv
  -n, --nodes-to-gen=NODES_TO_GEN
                             The number of nodes to generate for the graph.
  -r, --root=OPERATOR_ENUM   Initial node for the graph generation, default
                             root is 'AddVV32'
  -s, --seed=RANDOM_SEED     Seed for random number generator, default seed is
                             '0xdeadbeef'
  -v, --verbose              Produce verbose output
  -?, --help                 Give this help list
      --usage                Give a short usage message

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.
```

### How To Use?

`rif-test` is the current driver to fuzz all existing intrinsics in `include/CustomOperator.def`.

```
./rif-test --help
usage: rif-test [-h] [--gen {random_gen,fused_gen}] [--sim SIM] [--cc CC] 
                [--mode {full,fast}] [--node NODE] [--arch ARCH] [--abi ABI]
                [--cflags CFLAGS] [--seed SEED] [--random {on,off}] [--has-policy]

optional arguments:
  -h, --help            show this help message and exit
  --gen {random_gen,fused_gen}
                        Random gen pattern
  --sim SIM             Path to simulator
  --cc CC               Path to compiler
  --mode {full,fast}    Testing mode
  --node NODE           Minimal # of node
  --arch ARCH           Target arch config, default is rv64gcv_zvfh
  --abi ABI             Target ABI config, default is lp64d
  --cflags CFLAGS       Default compilation flag
  --seed SEED           Fixed random seed
  --random {on,off}     Feed random seed
  --has-policy          Enable policy if set
```

RIF already have linked a pre-built simulator from [metal-run](https://github.com/sifive/metal-run). So the minimum
requirement for testing it to specify a compiler that is able to compile RISC-V vector intrinsics. To specify your
own simulator (QEMU), please add `${PATH_TO_QEMU_BINARY} ${CPU_CONFIGS}` of how you wish to run
`${PATH_TO_QEMU_BINARY} ${CPU_CONFIGS} ${PATH_TO_ELF}` under --sim.


```
$ git clone https://github.com/sifive/riscv-vector-intrinsic-fuzzing
$ mkdir test
$ cd test
$ ../rif-test --cc=<YOUR-COMPILER-PATH>
$ make
```



### How To Build?

```
$ git clone https://github.com/sifive/riscv-vector-intrinsic-fuzzing
$ cd riscv-vector-intrinsic-fuzzing
$ mkdir build; cd build
$ cmake ..
$ make
$ ./tool/random_gen --help
Usage: random_gen [OPTION...]

  -c, --code=FILE            C code file, default filename: 'output.c'
  -d, --dot=FILE             Graphviz visualization file, default filename is
                             'output.dot'
  -h                         Give this help list
  -m, --march=ARCH_STRING    Arch string for testing, default is rv64gcv
  -n, --nodes-to-gen=NODES_TO_GEN
                             The number of nodes to generate for the graph.
  -r, --root=OPERATOR_ENUM   Initial node for the graph generation, default
                             root is 'AddVV32'
  -s, --seed=RANDOM_SEED     Seed for random number generator, default seed is
                             '0xdeadbeef'
  -v, --verbose              Produce verbose output
  -?, --help                 Give this help list
      --usage                Give a short usage message

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.