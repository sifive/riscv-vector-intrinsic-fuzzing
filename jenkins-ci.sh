#!/bin/bash

set -e

source /sifive/tools/Modules/init-chooser

if module is-loaded kitware/cmake
then
  module unload kitware/cmake
fi
if module is-loaded python/python
then
  module unload python/python
fi
if module is-loaded clang
then
  module unload clang
fi
if module is-loaded gcc/gcc
then
  module unload gcc/gcc
fi
module load kitware/cmake/3.18.4
module load python/python/3.9.2
module load clang/12.0.1.1
module load gcc/gcc/11.2.0

hostname

mkdir build && cd build
cmake ..
make -j$(nproc)
make test ARGS=-V
