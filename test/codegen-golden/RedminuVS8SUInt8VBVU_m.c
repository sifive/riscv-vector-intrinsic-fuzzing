// COMMAND: random_gen -r RedminuVS8SUInt8VBVU_m -n 1 -l 7 --has-ta --has-ma -c RedminuVS8SUInt8VBVU_m.c --has-policy
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
uint8_t value_1[7];
uint8_t value_2;
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_2() {
uint8_t tmp[] = {39,75,42,56,58,18,37,};
for (int i=0; i<7;++i) {value_1[i] = tmp[i];
}
}
void vredminu_vs_operator_0() {
int8_t *placeholder0 = value_0;
uint8_t *placeholder1 = value_1;
uint8_t *placeholder2 = &value_2;
int placeholder3 = 7;

vuint8m1_t placeholder4= vmv_v_x_u8m1(0, vsetvlmax_e8m1());
vuint8m1_t placeholder5= vmv_v_v_u8m1(placeholder4, vsetvlmax_e8m1());
for (size_t vl; placeholder3 > 0; placeholder3 -= vl) {
vl = vsetvl_e8m1(placeholder3);
vint8m1_t vec_value_0= vle8_v_i8m1(placeholder0, vl);
vbool8_t mask_value_0_0= vmseq_vx_i8m1_b8(vec_value_0, 1, vl);
vuint8m1_t vec_value_1_0= vle8_v_u8m1(placeholder1, vl);
placeholder5 = vredminu_vs_u8m1_u8m1_m (mask_value_0_0, placeholder5, vec_value_1_0, placeholder5, vl);
placeholder0 += vl;
placeholder1 += vl;
}
uint8_t *placeholder6 = &value_2;
*placeholder6= vmv_x_s_u8m1_u8(placeholder5);
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vinit_rif_operator_2() {
return 1;
}
int golden_vredminu_vs_operator_0() {
uint8_t tmp = 0;
if(value_2 != tmp) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_2();
vredminu_vs_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vredminu_vs_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vredminu_vs_operator_0();
if (!ret) return 1;
return 0; }
