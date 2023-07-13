// vmadd: vd[i] = (vd[i] * x[rs1]) + vs2[i]
VI_VX_MUL_ADD_LOOP
({
  vd0 = vd1 * rs1 + vs2;
})