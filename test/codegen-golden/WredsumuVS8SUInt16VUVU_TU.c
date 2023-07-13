// COMMAND: random_gen -r WredsumuVS8SUInt16VUVU_TU -n 1 -l 7 --has-ta --has-ma -c WredsumuVS8SUInt16VUVU_TU.c --has-policy
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
void vwredsumu_vs_operator_0() {
uint16_t *placeholder0 = value_0;
uint8_t *placeholder1 = value_1;
uint16_t *placeholder2 = value_2;
int placeholder3 = 7;

vuint16m1_t placeholder4= vmv_v_x_u16m1(0, vsetvlmax_e16m1());
vuint16m1_t placeholder5= vmv_v_v_u16m1(placeholder4, vsetvlmax_e16m1());
// This function initializes the output elements according to
// its
// tail policy and
// the reason doing so is to maintain VLA style.
// For ta policy, it initializes the value to all 1's, for tu it
// initializes to values of merge instead. E.g.
// in[5]:  [1, 1, 2, 2, 3]
// out[5]: [0, 0, 0, 0, 0] (global value is initialized to 0)
// vl:     4
// If we apply redsum_ta(out, in, vl), We want the result to be:
// [9, -1, -1, -1, -1].
// However, the vl is only 4, so it might result in something
// like:
// [6, -1, -1, -1, 3],
// but we want to maintain the output consistent as it's in VLA
// style,
// so one of the most convinent way to do so is to initialize
// the
// tail value in the beginning
// before performing actual computing, namely, getting into the
// loop.
memcpy(value_2, value_0, sizeof(value_2));
for (size_t vl; placeholder3 > 0; placeholder3 -= vl) {
vl = vsetvl_e8m1(placeholder3);
vuint16m1_t vec_value_0_0= vle16_v_u16m1(placeholder0, vl);
vuint8m1_t vec_value_1_0= vle8_v_u8m1(placeholder1, vl);
placeholder5 = vwredsumu_vs_u8m1_u16m1_tu(vec_value_0_0, vec_value_1_0, placeholder5, vl);
placeholder0 += vl;
placeholder1 += vl;
placeholder2 += vl;
}
uint16_t *placeholder6 = value_2;
*placeholder6= vmv_x_s_u16m1_u16(placeholder5);
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vinit_rif_operator_2() {
return 1;
}
int golden_vwredsumu_vs_operator_0() {
uint16_t tmp[] = {325,8946,7729,4291,6298,1387,2185,};
for (int i=0; i<7;++i)
if(value_2[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_2();
vwredsumu_vs_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vwredsumu_vs_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vwredsumu_vs_operator_0();
if (!ret) return 1;
return 0; }
