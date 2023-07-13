// COMMAND: random_gen -r Sext_vf2V16VInt16VI_TA -n 1 -l 7 --has-ta --has-ma -c Sext_vf2V16VInt16VI_TA.c --has-policy
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <riscv_vector.h>
typedef _Float16 float16_t;
typedef float float32_t;
typedef double float64_t;
#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & 0x03FF))
#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & 0x007FFFFF))
#define isNaNF64UI( a ) (((~(a) & UINT64_C( 0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF )))
int8_t value_0[7];
int16_t value_1[7];
void vinit_rif_operator_1() {
int8_t tmp[] = {-56,79,55,-14,26,-73,-57,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vsext_vf2_operator_0() {
int8_t *placeholder0 = value_0;
int16_t *placeholder1 = value_1;

int placeholder2 = 7;

for (size_t vl; placeholder2 > 0; placeholder2 -= vl) {
vl = 2;
size_t tail_vl = 1;
vint8mf2_t vec_value_0_0= vle8_v_i8mf2(placeholder0, vl);

vint16m1_t vec_value_1_0= vsext_vf2_i16m1_ta(vec_value_0_0, tail_vl);

vse16_v_i16m1(placeholder1, vec_value_1_0, vl);

placeholder0 += vl;
placeholder1 += vl;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vsext_vf2_operator_0() {
int16_t tmp[] = {-56,-1,55,-1,26,-1,-57,};
for (int i=0; i<7;++i)
if(value_1[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vsext_vf2_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vsext_vf2_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vsext_vf2_operator_0();
if (!ret) return 1;
return 0; }
