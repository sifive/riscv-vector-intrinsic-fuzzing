// COMMAND: random_gen -r Vsoxei32V32VoidVBVUVF_m -n 1 -l 7 --has-ta --has-ma -c Vsoxei32V32VoidVBVUVF_m.c --has-policy
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
uint32_t value_2[7];
float32_t value_3[7];
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_3() {
uint32_t tmp[] = {3902764u,7500210u,4235251u,5592077u,5806864u,1786754u,3702157u,};
for (int i=0; i<7;++i) {value_2[i] = tmp[i];
}
}
void vinit_rif_operator_2() {
uint32_t tmp[] = {1262786923u,1267490606u,1261860990u,1261781606u,1262205779u,1243709844u,1259168278u,};
for (int i=0; i<7;++i) {union { uint32_t u32; float32_t f; } converter;
converter.u32 = tmp[i];
value_1[i] = converter.f;
}
}
void vsoxei32_v_operator_0() {
int8_t *placeholder0 = value_0;
float32_t *placeholder1 = value_1;
uint32_t *placeholder2 = value_2;
float32_t *placeholder3 = value_3;
float32_t *placeholder4 = value_3;
int placeholder5 = 7;

for (size_t vl; placeholder5 > 0; placeholder5 -= vl) {
vl = vsetvl_e32m1(placeholder5);
vfloat32m1_t placeholder6= vfmv_v_f_f32m1(0, vsetvlmax_e32m1());
vse32_v_f32m1(placeholder4, placeholder6, vl);
placeholder4 += vl;
}
int placeholder7 = 7;

size_t placeholder8 = 0;
for (size_t vl; placeholder7 > 0; placeholder7 -= vl) {
vl = vsetvl_e32m1(placeholder7);
vint8mf4_t vec_value_0= vle8_v_i8mf4(placeholder0, vl);
vbool32_t mask_value_0_0= vmseq_vx_i8mf4_b32(vec_value_0, 1, vl);
vuint32m1_t vec_value_2_0= vle32_v_u32m1(placeholder2, vl);
vfloat32m1_t vec_value_1_0= vle32_v_f32m1(placeholder1, vl);
if (7 < 4294967295) {
vuint32m1_t placeholder9= vmv_v_x_u32m1(0, vsetvlmax_e32m1());
vec_value_2_0 = vremu_vx_u32m1_m(mask_value_0_0, placeholder9, vec_value_2_0, 7, vl);
}
vec_value_2_0 = vmul_vx_u32m1(vec_value_2_0, 4, vl);
vsoxei32_v_f32m1_m (mask_value_0_0, placeholder3, vec_value_2_0, vec_value_1_0, vl);
placeholder0 += vl;
placeholder1 += vl;
placeholder2 += vl;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vinit_rif_operator_3() {
return 1;
}
int golden_vinit_rif_operator_2() {
return 1;
}
int golden_vsoxei32_v_operator_0() {
uint64_t tmp[] = {1262205779u,0u,0u,0u,1267490606u,0u,1261860990u,};
union { float32_t f32; uint32_t u32; } converter;
union { float32_t f32; uint32_t u32; } converter2;
for (int i=0; i<7;++i){
converter.u32 = tmp[i];
converter2.f32 = value_3[i];
if(converter.f32 != converter2.f32 && !(isNaNF32UI(converter.u32) && isNaNF32UI(converter2.u32))) {
return 0;
}
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_3();
vinit_rif_operator_2();
vsoxei32_v_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_3 : %s\n", golden_vinit_rif_operator_3() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vsoxei32_v_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_3();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vsoxei32_v_operator_0();
if (!ret) return 1;
return 0; }
