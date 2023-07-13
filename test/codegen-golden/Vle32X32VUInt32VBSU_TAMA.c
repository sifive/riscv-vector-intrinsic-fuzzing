// COMMAND: random_gen -r Vle32X32VUInt32VBSU_TAMA -n 1 -l 7 --has-ta --has-ma -c Vle32X32VUInt32VBSU_TAMA.c --has-policy
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
uint32_t value_2[7];
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_2() {
uint32_t tmp[] = {3902764u,7500210u,4235251u,5592077u,5806864u,1786754u,3702157u,};
for (int i=0; i<7;++i) {value_1[i] = tmp[i];
}
}
void vle32_v_operator_0() {
int8_t *placeholder0 = value_0;
uint32_t *placeholder1 = value_1;
uint32_t *placeholder2 = value_2;
int placeholder3 = 7;

size_t placeholder4 = 0;
for (size_t vl; placeholder3 > 0; placeholder3 -= vl) {
vl = 2;
size_t tail_vl = 1;
vint8mf4_t vec_value_0= vle8_v_i8mf4(placeholder0, vl);
vbool32_t mask_value_0_0= vmseq_vx_i8mf4_b32(vec_value_0, 1, vl);
vuint32m1_t vec_value_2_0= vle32_v_u32m1_tama(mask_value_0_0, placeholder1, tail_vl);
vse32_v_u32m1(placeholder2, vec_value_2_0, vl);
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
int golden_vle32_v_operator_0() {
uint32_t tmp[] = {4294967295u,4294967295u,4235251u,4294967295u,5806864u,4294967295u,4294967295u,};
for (int i=0; i<7;++i)
if(value_2[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_2();
vle32_v_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vle32_v_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vle32_v_operator_0();
if (!ret) return 1;
return 0; }
