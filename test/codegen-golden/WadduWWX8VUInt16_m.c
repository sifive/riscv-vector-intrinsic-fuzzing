// COMMAND: random_gen -r WadduWWX8VUInt16_m -n 1 -l 7 --has-ta --has-ma -c WadduWWX8VUInt16_m.c --has-policy
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
uint16_t value_1[7];
uint16_t value_2[7];
uint8_t value_3;
uint16_t value_4[7];
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_4() {
uint8_t tmp = 39;
value_3 = tmp;
}
void vinit_rif_operator_2() {
uint16_t tmp[] = {7500,4235,5592,5807,1786,3702,6442,};
for (int i=0; i<7;++i) {value_1[i] = tmp[i];
}
}
void vinit_rif_operator_3() {
uint16_t tmp[] = {9200,5979,5940,6152,1323,4633,8488,};
for (int i=0; i<7;++i) {value_2[i] = tmp[i];
}
}
void vwaddu_wx_operator_0() {
int8_t *placeholder0 = value_0;
uint16_t *placeholder1 = value_1;
uint16_t *placeholder2 = value_2;
uint8_t placeholder3 = value_3;
uint16_t *placeholder4 = value_4;

int placeholder5 = 7;

for (size_t vl; placeholder5 > 0; placeholder5 -= vl) {
vl = vsetvl_e16m2(placeholder5);
vint8m1_t vec_value_0= vle8_v_i8m1(placeholder0, vl);
vbool8_t mask_value_0_0= vmseq_vx_i8m1_b8(vec_value_0, 1, vl);
vuint16m2_t vec_value_1_0= vle16_v_u16m2(placeholder1, vl);
vuint16m2_t vec_value_2_0= vle16_v_u16m2(placeholder2, vl);

vuint16m2_t vec_value_4_0= vwaddu_wx_u16m2_m (mask_value_0_0, vec_value_1_0, vec_value_2_0, placeholder3, vl);

vse16_v_u16m2(placeholder4, vec_value_4_0, vl);

placeholder0 += vl;
placeholder1 += vl;
placeholder2 += vl;
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
int golden_vwaddu_wx_operator_0() {
uint16_t tmp[] = {7500,6018,5979,5807,1362,3702,6442,};
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
vwaddu_wx_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_4 : %s\n", golden_vinit_rif_operator_4() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_3 : %s\n", golden_vinit_rif_operator_3() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vwaddu_wx_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_4();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vinit_rif_operator_3();
ret &= golden_vwaddu_wx_operator_0();
if (!ret) return 1;
return 0; }
