// COMMAND: random_gen -r RedmaxVS8SInt8VBVIVI_TUM -n 1 -l 7 --has-ta --has-ma -c RedmaxVS8SInt8VBVIVI_TUM.c --has-policy
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
int8_t value_2[7];
int8_t value_3[7];
void vinit_rif_operator_1() {
int8_t tmp[] = {0,1,1,0,1,0,0,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_3() {
int8_t tmp[] = {-22,50,-15,12,16,-65,-26,};
for (int i=0; i<7;++i) {value_2[i] = tmp[i];
}
}
void vinit_rif_operator_2() {
int8_t tmp[] = {29,84,20,19,23,-74,-7,};
for (int i=0; i<7;++i) {value_1[i] = tmp[i];
}
}
void vredmax_vs_operator_0() {
int8_t *placeholder0 = value_0;
int8_t *placeholder1 = value_1;
int8_t *placeholder2 = value_2;
int8_t *placeholder3 = value_3;
int placeholder4 = 7;

vint8m1_t placeholder5= vmv_v_x_i8m1(0, vsetvlmax_e8m1());
vint8m1_t placeholder6= vmv_v_v_i8m1(placeholder5, vsetvlmax_e8m1());
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
memcpy(value_3, value_1, sizeof(value_3));
for (size_t vl; placeholder4 > 0; placeholder4 -= vl) {
vl = vsetvl_e8m1(placeholder4);
vint8m1_t vec_value_0= vle8_v_i8m1(placeholder0, vl);
vbool8_t mask_value_0_0= vmseq_vx_i8m1_b8(vec_value_0, 1, vl);
vint8m1_t vec_value_1_0= vle8_v_i8m1(placeholder1, vl);
vint8m1_t vec_value_2_0= vle8_v_i8m1(placeholder2, vl);
placeholder6 = vredmax_vs_i8m1_i8m1_tum(mask_value_0_0, vec_value_1_0, vec_value_2_0, placeholder6, vl);
placeholder0 += vl;
placeholder1 += vl;
placeholder2 += vl;
placeholder3 += vl;
}
int8_t *placeholder7 = value_3;
*placeholder7= vmv_x_s_i8m1_i8(placeholder6);
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
int golden_vredmax_vs_operator_0() {
int8_t tmp[] = {50,84,20,19,23,-74,-7,};
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
vredmax_vs_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_3 : %s\n", golden_vinit_rif_operator_3() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vredmax_vs_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_3();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vredmax_vs_operator_0();
if (!ret) return 1;
return 0; }
