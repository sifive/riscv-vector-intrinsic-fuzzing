// vmacc.vx: vd[i] = +(x[rs1] * vs2[i]) + vd[i]
VI_VX_MUL_ADD_LOOP
({
  vd0 = rs1 * vs2 + vd1;
})