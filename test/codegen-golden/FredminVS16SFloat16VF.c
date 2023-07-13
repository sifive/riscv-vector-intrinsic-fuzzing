// COMMAND: random_gen -r FredminVS16SFloat16VF -n 1 -l 7 --has-ta --has-ma -c FredminVS16SFloat16VF.c --has-policy
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
void vinit_rif_operator_1() {
uint16_t tmp[] = {27738,29790,29580,28721,29222,26987,27716,};
for (int i=0; i<7;++i) {union { uint16_t u16; float16_t f; } converter;
converter.u16 = tmp[i];
value_0[i] = converter.f;
}
}
void vfredmin_vs_operator_0() {
float16_t *placeholder0 = value_0;
float16_t *placeholder1 = &value_1;
int placeholder2 = 7;

vfloat16m1_t placeholder3= vfmv_v_f_f16m1(0, vsetvlmax_e16m1());
vfloat16m1_t placeholder4= vmv_v_v_f16m1(placeholder3, vsetvlmax_e16m1());
for (size_t vl; placeholder2 > 0; placeholder2 -= vl) {
vl = vsetvl_e16m1(placeholder2);
vfloat16m1_t vec_value_0_0= vle16_v_f16m1(placeholder0, vl);
placeholder4 = vfredmin_vs_f16m1_f16m1(placeholder4, vec_value_0_0, placeholder4, vl);
placeholder0 += vl;
}
float16_t *placeholder5 = &value_1;
*placeholder5= vfmv_f_s_f16m1_f16(placeholder4);
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vfredmin_vs_operator_0() {
uint16_t tmp = 0;
union { float16_t f16; uint16_t u16; } converter, converter2;
converter.u16 = tmp;
converter2.f16 = value_1;
if(converter.f16 != value_1 && !(isNaNF16UI(converter.u16) && isNaNF16UI(converter2.u16))) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vfredmin_vs_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vfredmin_vs_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vfredmin_vs_operator_0();
if (!ret) return 1;
return 0; }
