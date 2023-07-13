// COMMAND: random_gen -r FwsubVF16VFloat32VFSF_TA -n 1 -l 7 --has-ta --has-ma -c FwsubVF16VFloat32VFSF_TA.c --has-policy
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
float16_t value_1;
float32_t value_2[7];
void vinit_rif_operator_1() {
uint16_t tmp[] = {27738,29790,29580,28721,29222,26987,27716,};
for (int i=0; i<7;++i) {union { uint16_t u16; float16_t f; } converter;
converter.u16 = tmp[i];
value_0[i] = converter.f;
}
}
void vinit_rif_operator_2() {
uint16_t tmp = 28575;
union { uint16_t u16; float16_t f; } converter;
converter.u16 = tmp;
value_1 = converter.f;
}
void vfwsub_vf_operator_0() {
float16_t *placeholder0 = value_0;
float16_t placeholder1 = value_1;
float32_t *placeholder2 = value_2;

int placeholder3 = 7;

for (size_t vl; placeholder3 > 0; placeholder3 -= vl) {
vl = 2;
size_t tail_vl = 1;
vfloat16m1_t vec_value_0_0= vle16_v_f16m1(placeholder0, vl);

vfloat32m2_t vec_value_2_0= vfwsub_vf_f32m2_ta(vec_value_0_0, placeholder1, tail_vl);

vse32_v_f32m2(placeholder2, vec_value_2_0, vl);

placeholder0 += vl;
placeholder2 += vl;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vinit_rif_operator_2() {
return 1;
}
int golden_vfwsub_vf_operator_0() {
uint64_t tmp[] = {3310436352u,4294967295u,1173299200u,4294967295u,1167433728u,4294967295u,3310796800u,};
union { float32_t f32; uint32_t u32; } converter;
union { float32_t f32; uint32_t u32; } converter2;
for (int i=0; i<7;++i){
converter.u32 = tmp[i];
converter2.f32 = value_2[i];
if(converter.f32 != converter2.f32 && !(isNaNF32UI(converter.u32) && isNaNF32UI(converter2.u32))) {
return 0;
}
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_2();
vfwsub_vf_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vfwsub_vf_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vfwsub_vf_operator_0();
if (!ret) return 1;
return 0; }
