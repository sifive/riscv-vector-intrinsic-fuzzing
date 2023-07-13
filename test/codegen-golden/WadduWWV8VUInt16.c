// COMMAND: random_gen -r WadduWWV8VUInt16 -n 1 -l 7 --has-ta --has-ma -c WadduWWV8VUInt16.c --has-policy
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
uint16_t value_0[7];
uint8_t value_1[7];
uint16_t value_2[7];
void vinit_rif_operator_1() {
uint16_t tmp[] = {2227,8946,7729,4291,6298,1387,2185,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_2() {
uint8_t tmp[] = {39,75,42,56,58,18,37,};
for (int i=0; i<7;++i) {value_1[i] = tmp[i];
}
}
void vwaddu_wv_operator_0() {
uint16_t *placeholder0 = value_0;
uint8_t *placeholder1 = value_1;
uint16_t *placeholder2 = value_2;

int placeholder3 = 7;

for (size_t vl; placeholder3 > 0; placeholder3 -= vl) {
vl = vsetvl_e16m2(placeholder3);
vuint16m2_t vec_value_0_0= vle16_v_u16m2(placeholder0, vl);
vuint8m1_t vec_value_1_0= vle8_v_u8m1(placeholder1, vl);

vuint16m2_t vec_value_2_0= vwaddu_wv_u16m2(vec_value_0_0, vec_value_1_0, vl);

vse16_v_u16m2(placeholder2, vec_value_2_0, vl);

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
int golden_vwaddu_wv_operator_0() {
uint16_t tmp[] = {2266,9021,7771,4347,6356,1405,2222,};
for (int i=0; i<7;++i)
if(value_2[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_2();
vwaddu_wv_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vwaddu_wv_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vwaddu_wv_operator_0();
if (!ret) return 1;
return 0; }
