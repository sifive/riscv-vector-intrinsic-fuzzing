// COMMAND: random_gen -r Vlse32XX32VFloat32VFSFSI_TU -n 1 -l 7 --has-ta --has-ma -c Vlse32XX32VFloat32VFSFSI_TU.c --has-policy
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
float32_t value_0[7];
float32_t value_1[7];
ptrdiff_t value_2;
float32_t value_3[7];
void vinit_rif_operator_1() {
uint32_t tmp[] = {1250422356u,1267237304u,1265360466u,1258485599u,1262498700u,1244223528u,1250254620u,};
for (int i=0; i<7;++i) {union { uint32_t u32; float32_t f; } converter;
converter.u32 = tmp[i];
value_0[i] = converter.f;
}
}
void vinit_rif_operator_3() {
ptrdiff_t tmp = 3902764ll;
value_2 = tmp;
}
void vinit_rif_operator_2() {
uint32_t tmp[] = {1264903012u,1258373094u,1261086746u,1261516319u,1247419408u,1256322614u,1262786923u,};
for (int i=0; i<7;++i) {union { uint32_t u32; float32_t f; } converter;
converter.u32 = tmp[i];
value_1[i] = converter.f;
}
}
void vlse32_v_operator_0() {
float32_t *placeholder0 = value_0;
float32_t *placeholder1 = value_1;
ptrdiff_t placeholder2 = value_2;
float32_t *placeholder3 = value_3;
float32_t *placeholder4 = value_3;
int placeholder5 = 7;

for (size_t vl; placeholder5 > 0; placeholder5 -= vl) {
vl = vsetvl_e32m1(placeholder5);
vfloat32m1_t placeholder6= vfmv_v_f_f32m1(0, vsetvlmax_e32m1());
vse32_v_f32m1(placeholder4, placeholder6, vl);
placeholder4 += vl;
}
placeholder2 = (placeholder2 % 4) + 1;
int placeholder7 = 7;

size_t placeholder8 = 0;
for (size_t vl; placeholder7 > 0; placeholder7 -= vl) {
vl = 2;
size_t tail_vl = 1;
vfloat32m1_t vec_value_0_0= vle32_v_f32m1(placeholder0, vl);
if (placeholder8 < 7) {
vfloat32m1_t placeholder9= vfmv_v_f_f32m1(0, vsetvlmax_e32m1());
vse32_v_f32m1(placeholder3, placeholder9, vl);
size_t placeholder10 = vl;
vl = vl < (7 - placeholder8 + placeholder2 - 1) / placeholder2 ? 
vl : (7 - placeholder8 + placeholder2 - 1) / placeholder2;
int32_t placeholder11 = placeholder2;
placeholder2 *= 4;
vfloat32m1_t vec_value_3_0= vlse32_v_f32m1_tu(vec_value_0_0, placeholder1, placeholder2, tail_vl);
vse32_v_f32m1(placeholder3, vec_value_3_0, vl);
vl = placeholder10; // recover vl
placeholder2 = placeholder11; // recover stride
}
else {
vfloat32m1_t placeholder12= vfmv_v_f_f32m1(0, vsetvlmax_e32m1());
vse32_v_f32m1(placeholder3, placeholder12, vl);
};
placeholder0 += vl;
placeholder1 += vl * placeholder2;
placeholder3 += vl;
placeholder8 += vl * placeholder2;
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
int golden_vlse32_v_operator_0() {
uint64_t tmp[] = {1264903012u,1267237304u,1261086746u,1258485599u,1247419408u,1244223528u,1262786923u,};
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
vlse32_v_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_3 : %s\n", golden_vinit_rif_operator_3() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vlse32_v_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_3();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vlse32_v_operator_0();
if (!ret) return 1;
return 0; }
