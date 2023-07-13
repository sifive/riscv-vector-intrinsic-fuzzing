// COMMAND: random_gen -r NsraWX8VInt8VBVIVISL_TAMU -n 1 -l 7 --has-ta --has-ma -c NsraWX8VInt8VBVIVISL_TAMU.c --has-policy
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
int16_t value_2[7];
size_t value_3;
int8_t value_4[7];
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_4() {
size_t tmp = 3902764ull;
value_3 = tmp;
}
void vinit_rif_operator_2() {
int8_t tmp[] = {50,-15,12,16,-65,-26,29,};
for (int i=0; i<7;++i) {value_1[i] = tmp[i];
}
}
void vinit_rif_operator_3() {
int16_t tmp[] = {8399,1958,1879,2303,-7354,-734,6976,};
for (int i=0; i<7;++i) {value_2[i] = tmp[i];
}
}
void vnsra_wx_operator_0() {
int8_t *placeholder0 = value_0;
int8_t *placeholder1 = value_1;
int16_t *placeholder2 = value_2;
size_t placeholder3 = value_3;
int8_t *placeholder4 = value_4;

int placeholder5 = 7;

for (size_t vl; placeholder5 > 0; placeholder5 -= vl) {
vl = 2;
size_t tail_vl = 1;
vint8m1_t vec_value_0= vle8_v_i8m1(placeholder0, vl);
vbool8_t mask_value_0_0= vmseq_vx_i8m1_b8(vec_value_0, 1, vl);
vint8m1_t vec_value_1_0= vle8_v_i8m1(placeholder1, vl);
vint16m2_t vec_value_2_0= vle16_v_i16m2(placeholder2, vl);

vint8m1_t vec_value_4_0= vnsra_wx_i8m1_tamu(mask_value_0_0, vec_value_1_0, vec_value_2_0, placeholder3, tail_vl);

vse8_v_i8m1(placeholder4, vec_value_4_0, vl);

placeholder0 += vl;
placeholder1 += vl;
placeholder2 += vl;
placeholder4 += vl;
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
int golden_vnsra_wx_operator_0() {
int8_t tmp[] = {50,-1,0,-1,-2,-1,29,};
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
vnsra_wx_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_4 : %s\n", golden_vinit_rif_operator_4() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_3 : %s\n", golden_vinit_rif_operator_3() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vnsra_wx_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_4();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vinit_rif_operator_3();
ret &= golden_vnsra_wx_operator_0();
if (!ret) return 1;
return 0; }
