// COMMAND: random_gen -r WredsumVS8SInt16VI -n 1 -l 7 --has-ta --has-ma -c WredsumVS8SInt16VI.c --has-policy
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
int16_t value_1;
void vinit_rif_operator_1() {
int8_t tmp[] = {-56,79,55,-14,26,-73,-57,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vwredsum_vs_operator_0() {
int8_t *placeholder0 = value_0;
int16_t *placeholder1 = &value_1;
int placeholder2 = 7;

vint16m1_t placeholder3= vmv_v_x_i16m1(0, vsetvlmax_e16m1());
vint16m1_t placeholder4= vmv_v_v_i16m1(placeholder3, vsetvlmax_e16m1());
for (size_t vl; placeholder2 > 0; placeholder2 -= vl) {
vl = vsetvl_e8m1(placeholder2);
vint8m1_t vec_value_0_0= vle8_v_i8m1(placeholder0, vl);
placeholder4 = vwredsum_vs_i8m1_i16m1(placeholder4, vec_value_0_0, placeholder4, vl);
placeholder0 += vl;
}
int16_t *placeholder5 = &value_1;
*placeholder5= vmv_x_s_i16m1_i16(placeholder4);
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vwredsum_vs_operator_0() {
int16_t tmp = -40;
if(value_1 != tmp) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vwredsum_vs_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vwredsum_vs_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vwredsum_vs_operator_0();
if (!ret) return 1;
return 0; }
