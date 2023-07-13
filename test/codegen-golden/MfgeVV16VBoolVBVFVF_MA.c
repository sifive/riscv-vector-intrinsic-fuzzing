// COMMAND: random_gen -r MfgeVV16VBoolVBVFVF_MA -n 1 -l 7 --has-ta --has-ma -c MfgeVV16VBoolVBVFVF_MA.c --has-policy
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
float16_t value_2[7];
int8_t value_3[7];
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_3() {
uint16_t tmp[] = {28575,29523,28707,29046,29100,27386,28475,};
for (int i=0; i<7;++i) {union { uint16_t u16; float16_t f; } converter;
converter.u16 = tmp[i];
value_2[i] = converter.f;
}
}
void vinit_rif_operator_2() {
uint16_t tmp[] = {29258,29822,29143,29133,29186,26923,28806,};
for (int i=0; i<7;++i) {union { uint16_t u16; float16_t f; } converter;
converter.u16 = tmp[i];
value_1[i] = converter.f;
}
}
void vmfge_vv_operator_0() {
int8_t *placeholder0 = value_0;
float16_t *placeholder1 = value_1;
float16_t *placeholder2 = value_2;
int8_t *placeholder3 = value_3;

int placeholder4 = 7;

for (size_t vl; placeholder4 > 0; placeholder4 -= vl) {
vl = vsetvl_e16m1(placeholder4);
vint8mf2_t vec_value_0= vle8_v_i8mf2(placeholder0, vl);
vbool16_t mask_value_0_0= vmseq_vx_i8mf2_b16(vec_value_0, 1, vl);
vfloat16m1_t vec_value_1_0= vle16_v_f16m1(placeholder1, vl);
vfloat16m1_t vec_value_2_0= vle16_v_f16m1(placeholder2, vl);

vbool16_t vec_value_3_0= vmfge_vv_f16m1_b16_ma(mask_value_0_0, vec_value_1_0, vec_value_2_0, vl);

{
size_t vlmax = vsetvlmax_e8mf2();
vint8mf2_t zero = vmv_v_x_i8mf2(0, vlmax);
vint8mf2_t vec_store = vmerge_vxm_i8mf2(vec_value_3_0, zero, 1, vl);
vse8_v_i8mf2(placeholder3, vec_store, vl);
}

placeholder0 += vl;
placeholder1 += vl;
placeholder2 += vl;
placeholder3 += vl;
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
int golden_vmfge_vv_operator_0() {
int8_t tmp[] = {1,1,1,1,1,1,1,};
for (int i=0; i<7;++i)
if(value_3[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_3();
vinit_rif_operator_2();
vmfge_vv_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_3 : %s\n", golden_vinit_rif_operator_3() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vmfge_vv_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_3();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vmfge_vv_operator_0();
if (!ret) return 1;
return 0; }
