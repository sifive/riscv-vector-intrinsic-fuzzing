#!/bin/bash

################################
# suppose we are in gamma
################################

CURPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
WORKSPACE=`readlink -f $CURPATH/../`
TEST_OUTPUT=`readlink -f $CURPATH/test_output/qemu-sys`
TEST_BIN="/work/evanl/metal-run-test/qemu-sys-bin/hello.elf"

cd $WORKSPACE
rm -rf $TEST_OUTPUT
mkdir -p $TEST_OUTPUT

./just-run qemu-sys $TEST_BIN &> $TEST_OUTPUT/e31.qemu-sys

################################
# check results
################################

postfix="qemu-sys"
keyword="Hello"
for a_test in `cd $TEST_OUTPUT && find . -name "*\.$postfix" |xargs`
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
