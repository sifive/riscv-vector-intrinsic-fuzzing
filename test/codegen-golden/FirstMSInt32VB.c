// COMMAND: random_gen -r FirstMSInt32VB -n 1 -l 7 --has-ta --has-ma -c FirstMSInt32VB.c --has-policy
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
int32_t value_1;
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vfirst_m_operator_0() {
int8_t *placeholder0 = value_0;
int32_t *placeholder1 = &value_1;
int placeholder2 = 7;

int32_t placeholder3 = -1;
uint32_t placeholder4 = 0;
for (size_t vl = 0; placeholder3 == -1 && placeholder2 > 0; placeholder2 -= vl) {
placeholder4 += vl;
vl = vsetvl_e8m1(placeholder2);
vint8m1_t vec_value_0= vle8_v_i8m1(placeholder0, vl);
vbool8_t mask_value_0_0= vmseq_vx_i8m1_b8(vec_value_0, 1, vl);
placeholder3 = vfirst_m_b8(mask_value_0_0, vl);
placeholder0 += vl;
}
if (placeholder3 != -1) placeholder3 += placeholder4;
*placeholder1 = placeholder3;
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vfirst_m_operator_0() {
int32_t tmp = 1;
if(value_1 != tmp) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vfirst_m_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vfirst_m_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vfirst_m_operator_0();
if (!ret) return 1;
return 0; }
