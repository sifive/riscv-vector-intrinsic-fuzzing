#!/bin/bash

################################
# suppose we are in gamma
################################

CURPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
WORKSPACE=`readlink -f $CURPATH/../`
TEST_OUTPUT=`readlink -f $CURPATH/test_output/qemu`

# suppose we are in gamma
CC="/sifive/tools/riscv-tools/riscv64-unknown-elf-gcc-8.3.0-2020.04.0-x86_64-linux-ubuntu14/bin/riscv64-unknown-elf-gcc"
CFLAGS="-march=rv32imac -mabi=ilp32 --specs=nano.specs"

cd $WORKSPACE
rm -rf $TEST_OUTPUT
mkdir -p $TEST_OUTPUT

################################
# test hello with qemu user mode
################################

# create simple hello
echo "int main(){printf(\"hello\\n\");}" >> $TEST_OUTPUT/hello.c
$CC $CFLAGS $TEST_OUTPUT/hello.c -o $TEST_OUTPUT/hello &> /dev/null
./just-run qemu $TEST_OUTPUT/hello &> $TEST_OUTPUT/rv32imac.qemu
echo $? >> $TEST_OUTPUT/rv32imac.qemu

################################
# check results
################################

postfix="qemu"
keyword="hello"
for a_test in `cd $TEST_OUTPUT && find . -name "*.$postfix" |xargs`
do
    a_test=`basename $a_test`
    echo -n "for case: $a_test ... "
    grep $keyword "$TEST_OUTPUT/$a_test" &> /dev/null
    if [ "$?" == "0" ];then
        echo "pass !"
    else
        echo "fail !"
    fi
done
