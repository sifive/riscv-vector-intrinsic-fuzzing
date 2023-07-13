// COMMAND: random_gen -r Vse32X32VoidSFVF -n 1 -l 7 --has-ta --has-ma -c Vse32X32VoidSFVF.c --has-policy
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
void vinit_rif_operator_1() {
uint32_t tmp[] = {1250422356u,1267237304u,1265360466u,1258485599u,1262498700u,1244223528u,1250254620u,};
for (int i=0; i<7;++i) {union { uint32_t u32; float32_t f; } converter;
converter.u32 = tmp[i];
value_0[i] = converter.f;
}
}
void vse32_v_operator_0() {
float32_t *placeholder0 = value_0;
float32_t *placeholder1 = value_1;
float32_t *placeholder2 = value_1;
int placeholder3 = 7;

for (size_t vl; placeholder3 > 0; placeholder3 -= vl) {
vl = vsetvl_e32m1(placeholder3);
vfloat32m1_t placeholder4= vfmv_v_f_f32m1(0, vsetvlmax_e32m1());
vse32_v_f32m1(placeholder2, placeholder4, vl);
placeholder2 += vl;
}
int placeholder5 = 7;

size_t placeholder6 = 0;
for (size_t vl; placeholder5 > 0; placeholder5 -= vl) {
vl = vsetvl_e32m1(placeholder5);
vfloat32m1_t vec_value_0_0= vle32_v_f32m1(placeholder0, vl);
vse32_v_f32m1(placeholder1, vec_value_0_0, vl);
placeholder0 += vl;
placeholder1 += vl;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vse32_v_operator_0() {
uint64_t tmp[] = {1250422356u,1267237304u,1265360466u,1258485599u,1262498700u,1244223528u,1250254620u,};
union { float32_t f32; uint32_t u32; } converter;
union { float32_t f32; uint32_t u32; } converter2;
for (int i=0; i<7;++i){
converter.u32 = tmp[i];
converter2.f32 = value_1[i];
if(converter.f32 != converter2.f32 && !(isNaNF32UI(converter.u32) && isNaNF32UI(converter2.u32))) {
return 0;
}
}
return 1;
}
int main () {
vinit_rif_operator_1();
vse32_v_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vse32_v_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vse32_v_operator_0();
if (!ret) return 1;
return 0; }
