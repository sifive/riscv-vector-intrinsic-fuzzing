// COMMAND: random_gen -r IdM8VUInt8_TA -n 1 -l 7 --has-ta --has-ma -c IdM8VUInt8_TA.c --has-policy
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
uint8_t value_0[7];
void vid_v_operator_0() {
uint8_t *placeholder0 = value_0;
int placeholder1 = 7;

unsigned placeholder2 = 0;
for (size_t vl; placeholder1 > 0; placeholder1 -= vl) {
vl = 2;
size_t tail_vl = 1;
vuint8m1_t vec_value_0_0= vid_v_u8m1_ta(tail_vl);
vec_value_0_0 = vadd_vx_u8m1_ta(vec_value_0_0, placeholder2, tail_vl);
vse8_v_u8m1(placeholder0, vec_value_0_0, vl);
placeholder2 += vl;
placeholder0 += vl;
}
}
int golden_vid_v_operator_0() {
uint8_t tmp[] = {0,255,2,255,4,255,6,};
for (int i=0; i<7;++i)
if(value_0[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vid_v_operator_0();
printf("operator_0 : %s\n", golden_vid_v_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vid_v_operator_0();
if (!ret) return 1;
return 0; }
