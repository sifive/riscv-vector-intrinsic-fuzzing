#!/usr/bin/env bash

# Load python
if ! command -v python3; then
    module load python/python
fi
# Load SiFive in-house toolchain
if ! command -v riscv64-unknown-linux-gnu-clang; then
    module load sifive/freedom-tools/toolsuite-linux/2022.08.1
fi
# Install python packages
pip3 install --user --no-cache -r requirements.txt
# Make sure submodules are ready
git submodule update --recursive
# Run test
pytest -sv ./testsuite
