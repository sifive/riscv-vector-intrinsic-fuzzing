// COMMAND: random_gen -r MsifMVBoolVB -n 1 -l 7 --has-ta --has-ma -c MsifMVBoolVB.c --has-policy
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
int8_t value_1[7];
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vmsif_m_operator_0() {
int8_t *placeholder0 = value_0;
int8_t *placeholder1 = value_1;
int placeholder2 = 7;

int32_t placeholder3 = -1;
for (size_t vl = 0; placeholder2 > 0 && placeholder3 == -1; placeholder2 -= vl) {
vl = vsetvl_e8m1(placeholder2);
vint8m1_t vec_value_0= vle8_v_i8m1(placeholder0, vl);
vbool8_t mask_value_0_0= vmseq_vx_i8m1_b8(vec_value_0, 1, vl);
vbool8_t vec_value_1_0= vmsif_m_b8(mask_value_0_0, vl);
{
size_t vlmax = vsetvlmax_e8m1();
vint8m1_t zero = vmv_v_x_i8m1(0, vlmax);
vint8m1_t vec_store = vmerge_vxm_i8m1(vec_value_1_0, zero, 1, vl);
vse8_v_i8m1(placeholder1, vec_store, vl);
}
placeholder0 += vl;
placeholder1 += vl;
placeholder3 = vfirst_m_b8(mask_value_0_0, vl);
}
for (size_t vl;placeholder2 > 0; placeholder2 -= vl) {
vl = vsetvl_e8m1(placeholder2);
vbool8_t placeholder4 = vmclr_m_b8(vsetvlmax_e8m1());
{
size_t vlmax = vsetvlmax_e8m1();
vint8m1_t zero = vmv_v_x_i8m1(0, vlmax);
vint8m1_t vec_store = vmerge_vxm_i8m1(placeholder4, zero, 1, vl);
vse8_v_i8m1(placeholder1, vec_store, vl);
}
placeholder0 += vl;
placeholder1 += vl;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vmsif_m_operator_0() {
int8_t tmp[] = {1,1,0,0,0,0,0,};
for (int i=0; i<7;++i)
if(value_1[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vmsif_m_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vmsif_m_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vmsif_m_operator_0();
if (!ret) return 1;
return 0; }
