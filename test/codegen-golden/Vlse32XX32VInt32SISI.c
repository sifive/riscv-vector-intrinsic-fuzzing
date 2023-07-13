// COMMAND: random_gen -r Vlse32XX32VInt32SISI -n 1 -l 7 --has-ta --has-ma -c Vlse32XX32VInt32SISI.c --has-policy
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
int32_t value_0[7];
ptrdiff_t value_1;
int32_t value_2[7];
void vinit_rif_operator_1() {
int32_t tmp[] = {-5545814,7892207,5457874,-1416993,2596108,-7225462,-5629682,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_2() {
ptrdiff_t tmp = 3902764ll;
value_1 = tmp;
}
void vlse32_v_operator_0() {
int32_t *placeholder0 = value_0;
ptrdiff_t placeholder1 = value_1;
int32_t *placeholder2 = value_2;
int32_t *placeholder3 = value_2;
int placeholder4 = 7;

for (size_t vl; placeholder4 > 0; placeholder4 -= vl) {
vl = vsetvl_e32m1(placeholder4);
vint32m1_t placeholder5= vmv_v_x_i32m1(0, vsetvlmax_e32m1());
vse32_v_i32m1(placeholder3, placeholder5, vl);
placeholder3 += vl;
}
placeholder1 = (placeholder1 % 4) + 1;
int placeholder6 = 7;

size_t placeholder7 = 0;
for (size_t vl; placeholder6 > 0; placeholder6 -= vl) {
vl = vsetvl_e32m1(placeholder6);
if (placeholder7 < 7) {
vint32m1_t placeholder8= vmv_v_x_i32m1(0, vsetvlmax_e32m1());
vse32_v_i32m1(placeholder2, placeholder8, vl);
size_t placeholder9 = vl;
vl = vl < (7 - placeholder7 + placeholder1 - 1) / placeholder1 ? 
vl : (7 - placeholder7 + placeholder1 - 1) / placeholder1;
int32_t placeholder10 = placeholder1;
placeholder1 *= 4;
vint32m1_t vec_value_2_0= vlse32_v_i32m1(placeholder0, placeholder1, vl);
vse32_v_i32m1(placeholder2, vec_value_2_0, vl);
vl = placeholder9; // recover vl
placeholder1 = placeholder10; // recover stride
}
else {
vint32m1_t placeholder11= vmv_v_x_i32m1(0, vsetvlmax_e32m1());
vse32_v_i32m1(placeholder2, placeholder11, vl);
};
placeholder0 += vl * placeholder1;
placeholder2 += vl;
placeholder7 += vl * placeholder1;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vinit_rif_operator_2() {
return 1;
}
int golden_vlse32_v_operator_0() {
int32_t tmp[] = {-5545814,7892207,5457874,-1416993,2596108,-7225462,-5629682,};
for (int i=0; i<7;++i)
if(value_2[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_2();
vlse32_v_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vlse32_v_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vlse32_v_operator_0();
if (!ret) return 1;
return 0; }
