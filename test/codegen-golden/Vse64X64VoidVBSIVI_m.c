// COMMAND: random_gen -r Vse64X64VoidVBSIVI_m -n 1 -l 7 --has-ta --has-ma -c Vse64X64VoidVBSIVI_m.c --has-policy
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
int64_t value_1[7];
int64_t value_2[7];
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_2() {
int64_t tmp[] = {-2194472ll,5000420ll,-1529498ll,1184154ll,1613727ll,-6426492ll,-2595685ll,};
for (int i=0; i<7;++i) {value_1[i] = tmp[i];
}
}
void vse64_v_operator_0() {
int8_t *placeholder0 = value_0;
int64_t *placeholder1 = value_1;
int64_t *placeholder2 = value_2;
int64_t *placeholder3 = value_2;
int placeholder4 = 7;

for (size_t vl; placeholder4 > 0; placeholder4 -= vl) {
vl = vsetvl_e64m1(placeholder4);
vint64m1_t placeholder5= vmv_v_x_i64m1(0, vsetvlmax_e64m1());
vse64_v_i64m1(placeholder3, placeholder5, vl);
placeholder3 += vl;
}
int placeholder6 = 7;

size_t placeholder7 = 0;
for (size_t vl; placeholder6 > 0; placeholder6 -= vl) {
vl = vsetvl_e64m1(placeholder6);
vint8mf8_t vec_value_0= vle8_v_i8mf8(placeholder0, vl);
vbool64_t mask_value_0_0= vmseq_vx_i8mf8_b64(vec_value_0, 1, vl);
vint64m1_t vec_value_1_0= vle64_v_i64m1(placeholder1, vl);
vse64_v_i64m1_m (mask_value_0_0, placeholder2, vec_value_1_0, vl);
placeholder0 += vl;
placeholder1 += vl;
placeholder2 += vl;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vinit_rif_operator_2() {
return 1;
}
int golden_vse64_v_operator_0() {
int64_t tmp[] = {0ll,5000420ll,-1529498ll,0ll,1613727ll,0ll,0ll,};
for (int i=0; i<7;++i)
if(value_2[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_2();
vse64_v_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vse64_v_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vse64_v_operator_0();
if (!ret) return 1;
return 0; }
