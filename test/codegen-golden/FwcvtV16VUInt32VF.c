// COMMAND: random_gen -r FwcvtV16VUInt32VF -n 1 -l 7 --has-ta --has-ma -c FwcvtV16VUInt32VF.c --has-policy
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
float16_t value_0[7];
uint32_t value_1[7];
void vinit_rif_operator_1() {
uint16_t tmp[] = {27738,29790,29580,28721,29222,26987,27716,};
for (int i=0; i<7;++i) {union { uint16_t u16; float16_t f; } converter;
converter.u16 = tmp[i];
value_0[i] = converter.f;
}
}
void vfwcvt_xu_f_v_operator_0() {
float16_t *placeholder0 = value_0;
uint32_t *placeholder1 = value_1;

int placeholder2 = 7;

for (size_t vl; placeholder2 > 0; placeholder2 -= vl) {
vl = vsetvl_e16m1(placeholder2);
vfloat16m1_t vec_value_0_0= vle16_v_f16m1(placeholder0, vl);

vuint32m2_t vec_value_1_0= vfwcvt_xu_f_v_u32m2(vec_value_0_0, vl);

vse32_v_u32m2(placeholder1, vec_value_1_0, vl);

placeholder0 += vl;
placeholder1 += vl;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vfwcvt_xu_f_v_operator_0() {
uint32_t tmp[] = {4456u,17888u,15456u,8584u,12592u,2774u,4368u,};
for (int i=0; i<7;++i)
if(value_1[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vfwcvt_xu_f_v_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vfwcvt_xu_f_v_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vfwcvt_xu_f_v_operator_0();
if (!ret) return 1;
return 0; }
