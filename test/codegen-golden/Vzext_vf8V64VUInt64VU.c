// COMMAND: random_gen -r Vzext_vf8V64VUInt64VU -n 1 -l 7 --has-ta --has-ma -c Vzext_vf8V64VUInt64VU.c --has-policy
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
uint64_t value_1[7];
void vinit_rif_operator_1() {
uint8_t tmp[] = {22,90,78,43,63,14,22,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vzext_vf8_operator_0() {
uint8_t *placeholder0 = value_0;
uint64_t *placeholder1 = value_1;

int placeholder2 = 7;

for (size_t vl; placeholder2 > 0; placeholder2 -= vl) {
vl = vsetvl_e64m1(placeholder2);
vuint8mf8_t vec_value_0_0= vle8_v_u8mf8(placeholder0, vl);

vuint64m1_t vec_value_1_0= vzext_vf8_u64m1(vec_value_0_0, vl);

vse64_v_u64m1(placeholder1, vec_value_1_0, vl);

placeholder0 += vl;
placeholder1 += vl;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vzext_vf8_operator_0() {
uint64_t tmp[] = {22ull,90ull,78ull,43ull,63ull,14ull,22ull,};
for (int i=0; i<7;++i)
if(value_1[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vzext_vf8_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vzext_vf8_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vzext_vf8_operator_0();
if (!ret) return 1;
return 0; }
