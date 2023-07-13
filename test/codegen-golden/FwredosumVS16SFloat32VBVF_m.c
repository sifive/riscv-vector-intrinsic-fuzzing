// COMMAND: random_gen -r FwredosumVS16SFloat32VBVF_m -n 1 -l 7 --has-ta --has-ma -c FwredosumVS16SFloat32VBVF_m.c --has-policy
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
float16_t value_1[7];
float32_t value_2;
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_2() {
uint16_t tmp[] = {28575,29523,28707,29046,29100,27386,28475,};
for (int i=0; i<7;++i) {union { uint16_t u16; float16_t f; } converter;
converter.u16 = tmp[i];
value_1[i] = converter.f;
}
}
void vfwredosum_vs_operator_0() {
int8_t *placeholder0 = value_0;
float16_t *placeholder1 = value_1;
float32_t *placeholder2 = &value_2;
int placeholder3 = 7;

vfloat32m1_t placeholder4= vfmv_v_f_f32m1(0, vsetvlmax_e32m1());
vfloat32m1_t placeholder5= vmv_v_v_f32m1(placeholder4, vsetvlmax_e32m1());
for (size_t vl; placeholder3 > 0; placeholder3 -= vl) {
vl = vsetvl_e16m1(placeholder3);
vint8mf2_t vec_value_0= vle8_v_i8mf2(placeholder0, vl);
vbool16_t mask_value_0_0= vmseq_vx_i8mf2_b16(vec_value_0, 1, vl);
vfloat16m1_t vec_value_1_0= vle16_v_f16m1(placeholder1, vl);
placeholder5 = vfwredosum_vs_f16m1_f32m1_m (mask_value_0_0, placeholder5, vec_value_1_0, placeholder5, vl);
placeholder0 += vl;
placeholder1 += vl;
}
float32_t *placeholder6 = &value_2;
*placeholder6= vfmv_f_s_f32m1_f32(placeholder5);
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vinit_rif_operator_2() {
return 1;
}
int golden_vfwredosum_vs_operator_0() {
uint32_t tmp = 1191776256u;
union { float32_t f32; uint32_t u32; } converter, converter2;
converter.u32 = tmp;
converter2.f32 = value_2;
if(converter.f32 != value_2 && !(isNaNF32UI(converter.u32) && isNaNF32UI(converter2.u32))) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_2();
vfwredosum_vs_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vfwredosum_vs_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vfwredosum_vs_operator_0();
if (!ret) return 1;
return 0; }