#!/bin/bash

CURPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
WORKSPACE=`readlink -f $CURPATH/../`
OUTPUT_BASE="$CURPATH/test_output"
mkdir -p $OUTPUT_BASE

echo "#### test qemu ####"
bash $WORKSPACE/test/qemu.sh  

echo "#### test qemu-sys ####"
bash $WORKSPACE/test/qemu-sys.sh

echo "#### test verilator ####"
bash $WORKSPACE/test/verilator.sh

