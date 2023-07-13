// COMMAND: random_gen -r Fwcvt_rtzV16VUInt32VBVUVF_TUMU -n 1 -l 7 --has-ta --has-ma -c Fwcvt_rtzV16VUInt32VBVUVF_TUMU.c --has-policy
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
uint32_t value_1[7];
float16_t value_2[7];
uint32_t value_3[7];
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
uint32_t tmp[] = {6442165u,9199407u,5979199u,5939507u,6151593u,1323058u,4632843u,};
for (int i=0; i<7;++i) {value_1[i] = tmp[i];
}
}
void vfwcvt_rtz_xu_f_v_operator_0() {
int8_t *placeholder0 = value_0;
uint32_t *placeholder1 = value_1;
float16_t *placeholder2 = value_2;
uint32_t *placeholder3 = value_3;

int placeholder4 = 7;

for (size_t vl; placeholder4 > 0; placeholder4 -= vl) {
vl = 2;
size_t tail_vl = 1;
vint8mf2_t vec_value_0= vle8_v_i8mf2(placeholder0, vl);
vbool16_t mask_value_0_0= vmseq_vx_i8mf2_b16(vec_value_0, 1, vl);
vuint32m2_t vec_value_1_0= vle32_v_u32m2(placeholder1, vl);
vfloat16m1_t vec_value_2_0= vle16_v_f16m1(placeholder2, vl);

vuint32m2_t vec_value_3_0= vfwcvt_rtz_xu_f_v_u32m2_tumu(mask_value_0_0, vec_value_1_0, vec_value_2_0, tail_vl);

vse32_v_u32m2(placeholder3, vec_value_3_0, vl);

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
int golden_vfwcvt_rtz_xu_f_v_operator_0() {
uint32_t tmp[] = {6442165u,9199407u,8472u,5939507u,11616u,1323058u,4632843u,};
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
vfwcvt_rtz_xu_f_v_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_3 : %s\n", golden_vinit_rif_operator_3() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vfwcvt_rtz_xu_f_v_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_3();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vfwcvt_rtz_xu_f_v_operator_0();
if (!ret) return 1;
return 0; }
