// COMMAND: random_gen -r Vlse8XX8VInt8VBVISISI_TUMA -n 1 -l 7 --has-ta --has-ma -c Vlse8XX8VInt8VBVISISI_TUMA.c --has-policy
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
int8_t value_2[7];
ptrdiff_t value_3;
int8_t value_4[7];
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_4() {
ptrdiff_t tmp = 3902764ll;
value_3 = tmp;
}
void vinit_rif_operator_2() {
int8_t tmp[] = {50,-15,12,16,-65,-26,29,};
for (int i=0; i<7;++i) {value_1[i] = tmp[i];
}
}
void vinit_rif_operator_3() {
int8_t tmp[] = {84,20,19,23,-74,-7,70,};
for (int i=0; i<7;++i) {value_2[i] = tmp[i];
}
}
void vlse8_v_operator_0() {
int8_t *placeholder0 = value_0;
int8_t *placeholder1 = value_1;
int8_t *placeholder2 = value_2;
ptrdiff_t placeholder3 = value_3;
int8_t *placeholder4 = value_4;
int8_t *placeholder5 = value_4;
int placeholder6 = 7;

for (size_t vl; placeholder6 > 0; placeholder6 -= vl) {
vl = vsetvl_e8m1(placeholder6);
vint8m1_t placeholder7= vmv_v_x_i8m1(0, vsetvlmax_e8m1());
vse8_v_i8m1(placeholder5, placeholder7, vl);
placeholder5 += vl;
}
placeholder3 = (placeholder3 % 4) + 1;
int placeholder8 = 7;

size_t placeholder9 = 0;
for (size_t vl; placeholder8 > 0; placeholder8 -= vl) {
vl = 2;
size_t tail_vl = 1;
vint8m1_t vec_value_0= vle8_v_i8m1(placeholder0, vl);
vbool8_t mask_value_0_0= vmseq_vx_i8m1_b8(vec_value_0, 1, vl);
vint8m1_t vec_value_1_0= vle8_v_i8m1(placeholder1, vl);
if (placeholder9 < 7) {
vint8m1_t placeholder10= vmv_v_x_i8m1(0, vsetvlmax_e8m1());
vse8_v_i8m1(placeholder4, placeholder10, vl);
size_t placeholder11 = vl;
vl = vl < (7 - placeholder9 + placeholder3 - 1) / placeholder3 ? 
vl : (7 - placeholder9 + placeholder3 - 1) / placeholder3;
int32_t placeholder12 = placeholder3;
placeholder3 *= 1;
vint8m1_t vec_value_4_0= vlse8_v_i8m1_tuma(mask_value_0_0, vec_value_1_0, placeholder2, placeholder3, tail_vl);
vse8_v_i8m1(placeholder4, vec_value_4_0, vl);
vl = placeholder11; // recover vl
placeholder3 = placeholder12; // recover stride
}
else {
vint8m1_t placeholder13= vmv_v_x_i8m1(0, vsetvlmax_e8m1());
vse8_v_i8m1(placeholder4, placeholder13, vl);
};
placeholder0 += vl;
placeholder1 += vl;
placeholder2 += vl * placeholder3;
placeholder4 += vl;
placeholder9 += vl * placeholder3;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vinit_rif_operator_4() {
return 1;
}
int golden_vinit_rif_operator_2() {
return 1;
}
int golden_vinit_rif_operator_3() {
return 1;
}
int golden_vlse8_v_operator_0() {
int8_t tmp[] = {-1,-15,19,16,-74,-26,-1,};
for (int i=0; i<7;++i)
if(value_4[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_4();
vinit_rif_operator_2();
vinit_rif_operator_3();
vlse8_v_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_4 : %s\n", golden_vinit_rif_operator_4() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_3 : %s\n", golden_vinit_rif_operator_3() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vlse8_v_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_4();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vinit_rif_operator_3();
ret &= golden_vlse8_v_operator_0();
if (!ret) return 1;
return 0; }