// COMMAND: random_gen -r NclipuWX8VUInt8VUSU -n 1 -l 7 --has-ta --has-ma -c NclipuWX8VUInt8VUSU.c --has-policy
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
uint32_t value_1;
uint8_t value_2[7];
void vinit_rif_operator_1() {
uint16_t tmp[] = {2227,8946,7729,4291,6298,1387,2185,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_2() {
uint32_t tmp = 3902764u;
value_1 = tmp;
}
void vnclipu_wx_operator_0() {
uint16_t *placeholder0 = value_0;
uint32_t placeholder1 = value_1;
uint8_t *placeholder2 = value_2;

int placeholder3 = 7;

for (size_t vl; placeholder3 > 0; placeholder3 -= vl) {
vl = vsetvl_e16m2(placeholder3);
vuint16m2_t vec_value_0_0= vle16_v_u16m2(placeholder0, vl);

vuint8m1_t vec_value_2_0= vnclipu_wx_u8m1(vec_value_0_0, placeholder1, vl);

vse8_v_u8m1(placeholder2, vec_value_2_0, vl);

placeholder0 += vl;
placeholder2 += vl;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vinit_rif_operator_2() {
return 1;
}
int golden_vnclipu_wx_operator_0() {
uint8_t tmp[] = {1,2,2,1,2,0,1,};
for (int i=0; i<7;++i)
if(value_2[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_2();
vnclipu_wx_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vnclipu_wx_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vnclipu_wx_operator_0();
if (!ret) return 1;
return 0; }
