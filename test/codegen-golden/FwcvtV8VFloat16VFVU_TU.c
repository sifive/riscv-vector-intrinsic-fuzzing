// COMMAND: random_gen -r FwcvtV8VFloat16VFVU_TU -n 1 -l 7 --has-ta --has-ma -c FwcvtV8VFloat16VFVU_TU.c --has-policy
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
float16_t value_0[7];
uint8_t value_1[7];
float16_t value_2[7];
void vinit_rif_operator_1() {
uint16_t tmp[] = {27738,29790,29580,28721,29222,26987,27716,};
for (int i=0; i<7;++i) {union { uint16_t u16; float16_t f; } converter;
converter.u16 = tmp[i];
value_0[i] = converter.f;
}
}
void vinit_rif_operator_2() {
uint8_t tmp[] = {39,75,42,56,58,18,37,};
for (int i=0; i<7;++i) {value_1[i] = tmp[i];
}
}
void vfwcvt_f_xu_v_operator_0() {
float16_t *placeholder0 = value_0;
uint8_t *placeholder1 = value_1;
float16_t *placeholder2 = value_2;

int placeholder3 = 7;

for (size_t vl; placeholder3 > 0; placeholder3 -= vl) {
vl = 2;
size_t tail_vl = 1;
vfloat16m2_t vec_value_0_0= vle16_v_f16m2(placeholder0, vl);
vuint8m1_t vec_value_1_0= vle8_v_u8m1(placeholder1, vl);

vfloat16m2_t vec_value_2_0= vfwcvt_f_xu_v_f16m2_tu(vec_value_0_0, vec_value_1_0, tail_vl);

vse16_v_f16m2(placeholder2, vec_value_2_0, vl);

placeholder0 += vl;
placeholder1 += vl;
placeholder2 += vl;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vinit_rif_operator_2() {
return 1;
}
int golden_vfwcvt_f_xu_v_operator_0() {
uint64_t tmp[] = {20704,29790,20800,28721,21312,26987,20640,};
union { float16_t f16; uint16_t u16; } converter;
union { float16_t f16; uint16_t u16; } converter2;
for (int i=0; i<7;++i){
converter.u16 = tmp[i];
converter2.f16 = value_2[i];
if(converter.f16 != converter2.f16 && !(isNaNF16UI(converter.u16) && isNaNF16UI(converter2.u16))) {
return 0;
}
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_2();
vfwcvt_f_xu_v_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vfwcvt_f_xu_v_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vfwcvt_f_xu_v_operator_0();
if (!ret) return 1;
return 0; }
