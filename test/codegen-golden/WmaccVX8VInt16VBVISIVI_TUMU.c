// COMMAND: random_gen -r WmaccVX8VInt16VBVISIVI_TUMU -n 1 -l 7 --has-ta --has-ma -c WmaccVX8VInt16VBVISIVI_TUMU.c --has-policy
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
int8_t value_2;
int8_t value_3[7];
int16_t value_4[7];
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_4() {
int8_t tmp[] = {-22,50,-15,12,16,-65,-26,};
for (int i=0; i<7;++i) {value_3[i] = tmp[i];
}
}
void vinit_rif_operator_2() {
int16_t tmp[] = {2884,8399,1958,1879,2303,-7354,-734,};
for (int i=0; i<7;++i) {value_1[i] = tmp[i];
}
}
void vinit_rif_operator_3() {
int8_t tmp = 70;
value_2 = tmp;
}
void vwmacc_vx_operator_0() {
int8_t *placeholder0 = value_0;
int16_t *placeholder1 = value_1;
int8_t placeholder2 = value_2;
int8_t *placeholder3 = value_3;
int16_t *placeholder4 = value_4;

int placeholder5 = 7;

for (size_t vl; placeholder5 > 0; placeholder5 -= vl) {
vl = 2;
size_t tail_vl = 1;
vint8m1_t vec_value_0= vle8_v_i8m1(placeholder0, vl);
vbool8_t mask_value_0_0= vmseq_vx_i8m1_b8(vec_value_0, 1, vl);
vint16m2_t vec_value_1_0= vle16_v_i16m2(placeholder1, vl);
vint8m1_t vec_value_3_0= vle8_v_i8m1(placeholder3, vl);

vint16m2_t vec_value_4_0= vwmacc_vx_i16m2_tumu(mask_value_0_0, vec_value_1_0, placeholder2, vec_value_3_0, tail_vl);

vse16_v_i16m2(placeholder4, vec_value_4_0, vl);

placeholder0 += vl;
placeholder1 += vl;
placeholder3 += vl;
placeholder4 += vl;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vinit_rif_operator_4() {
return 1;
}
int golden_vinit_rif_operator_2() {
return 1;
}
int golden_vinit_rif_operator_3() {
return 1;
}
int golden_vwmacc_vx_operator_0() {
int16_t tmp[] = {2884,8399,908,1879,3423,-7354,-734,};
for (int i=0; i<7;++i)
if(value_4[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_4();
vinit_rif_operator_2();
vinit_rif_operator_3();
vwmacc_vx_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_4 : %s\n", golden_vinit_rif_operator_4() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_3 : %s\n", golden_vinit_rif_operator_3() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vwmacc_vx_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_4();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vinit_rif_operator_3();
ret &= golden_vwmacc_vx_operator_0();
if (!ret) return 1;
return 0; }
