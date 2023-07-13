// COMMAND: random_gen -r RedminuVS8SUInt8VU -n 1 -l 7 --has-ta --has-ma -c RedminuVS8SUInt8VU.c --has-policy
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
uint8_t value_1;
void vinit_rif_operator_1() {
uint8_t tmp[] = {22,90,78,43,63,14,22,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vredminu_vs_operator_0() {
uint8_t *placeholder0 = value_0;
uint8_t *placeholder1 = &value_1;
int placeholder2 = 7;

vuint8m1_t placeholder3= vmv_v_x_u8m1(0, vsetvlmax_e8m1());
vuint8m1_t placeholder4= vmv_v_v_u8m1(placeholder3, vsetvlmax_e8m1());
for (size_t vl; placeholder2 > 0; placeholder2 -= vl) {
vl = vsetvl_e8m1(placeholder2);
vuint8m1_t vec_value_0_0= vle8_v_u8m1(placeholder0, vl);
placeholder4 = vredminu_vs_u8m1_u8m1(placeholder4, vec_value_0_0, placeholder4, vl);
placeholder0 += vl;
}
uint8_t *placeholder5 = &value_1;
*placeholder5= vmv_x_s_u8m1_u8(placeholder4);
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vredminu_vs_operator_0() {
uint8_t tmp = 0;
if(value_1 != tmp) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vredminu_vs_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vredminu_vs_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vredminu_vs_operator_0();
if (!ret) return 1;
return 0; }
