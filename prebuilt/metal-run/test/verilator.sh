#!/bin/bash

################################
# suppose we are in gamma
################################

CURPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
WORKSPACE=`readlink -f $CURPATH/../`
TEST_OUTPUT=`readlink -m $CURPATH/test_output/verilator`

cd $WORKSPACE
rm -rf $TEST_OUTPUT
mkdir -p $TEST_OUTPUT

################################
# test e76d for --sim-path
################################

TEST_HEX="/work/evanl/metal-run-test/verilator-bin/e76d_hello.hex"
E76D_VERILATOR="/work/evanl/verilator/e76d/obj_dir/VTestDriver"
echo "core: e76d"
OUT_PCTRACE="$TEST_OUTPUT/e76d_hello.hex.out"
./just-run --verbose verilator $TEST_HEX --sim-path $E76D_VERILATOR --out $OUT_PCTRACE
grep "PASS" $OUT_PCTRACE &> $TEST_OUTPUT/e76d.verilator

################################
# test s76 for prebuilt verilator
################################

TEST_HEX="/work/evanl/metal-run-test/verilator-bin/s76_hello.hex"
OUT_PCTRACE="$TEST_OUTPUT/s76_hello_prebuilt.hex.out"
echo "core: latest s76"
./just-run --verbose verilator --cpu s76 $TEST_HEX --out $OUT_PCTRACE
grep "PASS" $OUT_PCTRACE &> $TEST_OUTPUT/e76d.verilator

################################
# test for standard core 
################################

# (skip e76mc, s76mc, u52, u54, u54mc, u74, and u74mc, since they take time)
for a_core in  "e20" "e21" "e24" "e31" "e34" "e76" "s21" "s51" "s54" "s76" \
               "e76mc" "s76mc" "u52" "u54" "u54mc" "u74" "u74mc" ;
do  
    OUT_PCTRACE="$TEST_OUTPUT/${a_core}_hello.hex.out"
    TEST_HEX="/work/evanl/metal-run-test/verilator-bin/${a_core}_hello.hex"
    echo "core: $a_core"
    ./just-run --verbose verilator --cpu $a_core $TEST_HEX --out $OUT_PCTRACE
    grep "PASS" $OUT_PCTRACE &> $TEST_OUTPUT/${a_core}.verilator
done

################################
# check results
################################

postfix="verilator"
keyword="PASSED"
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
