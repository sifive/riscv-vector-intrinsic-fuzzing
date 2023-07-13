// COMMAND: random_gen -r NclipuWX8VUInt8VBVUVUSL_TUMA -n 1 -l 7 --has-ta --has-ma -c NclipuWX8VUInt8VBVUVUSL_TUMA.c --has-policy
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
uint8_t value_1[7];
uint16_t value_2[7];
size_t value_3;
uint8_t value_4[7];
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_4() {
size_t tmp = 3902764ull;
value_3 = tmp;
}
void vinit_rif_operator_2() {
uint8_t tmp[] = {75,42,56,58,18,37,65,};
for (int i=0; i<7;++i) {value_1[i] = tmp[i];
}
}
void vinit_rif_operator_3() {
uint16_t tmp[] = {9200,5979,5940,6152,1323,4633,8488,};
for (int i=0; i<7;++i) {value_2[i] = tmp[i];
}
}
void vnclipu_wx_operator_0() {
int8_t *placeholder0 = value_0;
uint8_t *placeholder1 = value_1;
uint16_t *placeholder2 = value_2;
size_t placeholder3 = value_3;
uint8_t *placeholder4 = value_4;

int placeholder5 = 7;

for (size_t vl; placeholder5 > 0; placeholder5 -= vl) {
vl = 2;
size_t tail_vl = 1;
vint8m1_t vec_value_0= vle8_v_i8m1(placeholder0, vl);
vbool8_t mask_value_0_0= vmseq_vx_i8m1_b8(vec_value_0, 1, vl);
vuint8m1_t vec_value_1_0= vle8_v_u8m1(placeholder1, vl);
vuint16m2_t vec_value_2_0= vle16_v_u16m2(placeholder2, vl);

vuint8m1_t vec_value_4_0= vnclipu_wx_u8m1_tuma(mask_value_0_0, vec_value_1_0, vec_value_2_0, placeholder3, tail_vl);

vse8_v_u8m1(placeholder4, vec_value_4_0, vl);

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
int golden_vnclipu_wx_operator_0() {
uint8_t tmp[] = {255,42,1,58,0,37,255,};
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
vnclipu_wx_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_4 : %s\n", golden_vinit_rif_operator_4() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_3 : %s\n", golden_vinit_rif_operator_3() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vnclipu_wx_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_4();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vinit_rif_operator_3();
ret &= golden_vnclipu_wx_operator_0();
if (!ret) return 1;
return 0; }