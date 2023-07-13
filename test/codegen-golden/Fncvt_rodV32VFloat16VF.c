// COMMAND: random_gen -r Fncvt_rodV32VFloat16VF -n 1 -l 7 --has-ta --has-ma -c Fncvt_rodV32VFloat16VF.c --has-policy
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
float16_t value_1[7];
void vinit_rif_operator_1() {
uint32_t tmp[] = {1250422356u,1267237304u,1265360466u,1258485599u,1262498700u,1244223528u,1250254620u,};
for (int i=0; i<7;++i) {union { uint32_t u32; float32_t f; } converter;
converter.u32 = tmp[i];
value_0[i] = converter.f;
}
}
void vfncvt_rod_f_f_w_operator_0() {
float32_t *placeholder0 = value_0;
float16_t *placeholder1 = value_1;

int placeholder2 = 7;

for (size_t vl; placeholder2 > 0; placeholder2 -= vl) {
vl = vsetvl_e32m1(placeholder2);
vfloat32m1_t vec_value_0_0= vle32_v_f32m1(placeholder0, vl);

vfloat16mf2_t vec_value_1_0= vfncvt_rod_f_f_w_f16mf2(vec_value_0_0, vl);

vse16_v_f16mf2(placeholder1, vec_value_1_0, vl);

placeholder0 += vl;
placeholder1 += vl;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vfncvt_rod_f_f_w_operator_0() {
uint64_t tmp[] = {31743,31743,31743,31743,31743,31743,31743,};
union { float16_t f16; uint16_t u16; } converter;
union { float16_t f16; uint16_t u16; } converter2;
for (int i=0; i<7;++i){
converter.u16 = tmp[i];
converter2.f16 = value_1[i];
if(converter.f16 != converter2.f16 && !(isNaNF16UI(converter.u16) && isNaNF16UI(converter2.u16))) {
return 0;
}
}
return 1;
}
int main () {
vinit_rif_operator_1();
vfncvt_rod_f_f_w_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vfncvt_rod_f_f_w_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vfncvt_rod_f_f_w_operator_0();
if (!ret) return 1;
return 0; }
