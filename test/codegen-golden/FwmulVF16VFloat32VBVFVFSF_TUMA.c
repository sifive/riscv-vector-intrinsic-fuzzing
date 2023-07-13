// COMMAND: random_gen -r FwmulVF16VFloat32VBVFVFSF_TUMA -n 1 -l 7 --has-ta --has-ma -c FwmulVF16VFloat32VBVFVFSF_TUMA.c --has-policy
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
float32_t value_1[7];
float16_t value_2[7];
float16_t value_3;
float32_t value_4[7];
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_4() {
uint16_t tmp = 28575;
union { uint16_t u16; float16_t f; } converter;
converter.u16 = tmp;
value_3 = converter.f;
}
void vinit_rif_operator_2() {
uint32_t tmp[] = {1264903012u,1258373094u,1261086746u,1261516319u,1247419408u,1256322614u,1262786923u,};
for (int i=0; i<7;++i) {union { uint32_t u32; float32_t f; } converter;
converter.u32 = tmp[i];
value_1[i] = converter.f;
}
}
void vinit_rif_operator_3() {
uint16_t tmp[] = {29822,29143,29133,29186,26923,28806,29733,};
for (int i=0; i<7;++i) {union { uint16_t u16; float16_t f; } converter;
converter.u16 = tmp[i];
value_2[i] = converter.f;
}
}
void vfwmul_vf_operator_0() {
int8_t *placeholder0 = value_0;
float32_t *placeholder1 = value_1;
float16_t *placeholder2 = value_2;
float16_t placeholder3 = value_3;
float32_t *placeholder4 = value_4;

int placeholder5 = 7;

for (size_t vl; placeholder5 > 0; placeholder5 -= vl) {
vl = 2;
size_t tail_vl = 1;
vint8mf2_t vec_value_0= vle8_v_i8mf2(placeholder0, vl);
vbool16_t mask_value_0_0= vmseq_vx_i8mf2_b16(vec_value_0, 1, vl);
vfloat32m2_t vec_value_1_0= vle32_v_f32m2(placeholder1, vl);
vfloat16m1_t vec_value_2_0= vle16_v_f16m1(placeholder2, vl);

vfloat32m2_t vec_value_4_0= vfwmul_vf_f32m2_tuma(mask_value_0_0, vec_value_1_0, vec_value_2_0, placeholder3, tail_vl);

vse32_v_f32m2(placeholder4, vec_value_4_0, vl);

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
int golden_vfwmul_vf_operator_0() {
uint64_t tmp[] = {4294967295u,1258373094u,1286657356u,1261516319u,1268615892u,1256322614u,4294967295u,};
union { float32_t f32; uint32_t u32; } converter;
union { float32_t f32; uint32_t u32; } converter2;
for (int i=0; i<7;++i){
converter.u32 = tmp[i];
converter2.f32 = value_4[i];
if(converter.f32 != converter2.f32 && !(isNaNF32UI(converter.u32) && isNaNF32UI(converter2.u32))) {
return 0;
}
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_4();
vinit_rif_operator_2();
vinit_rif_operator_3();
vfwmul_vf_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_4 : %s\n", golden_vinit_rif_operator_4() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_3 : %s\n", golden_vinit_rif_operator_3() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vfwmul_vf_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_4();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vinit_rif_operator_3();
ret &= golden_vfwmul_vf_operator_0();
if (!ret) return 1;
return 0; }
