// vmacc.vv: vd[i] = +(vs1[i] * vs2[i]) + vd[i]
VI_VV_MUL_ADD_LOOP
({
  vd0 = vs1 * vs2 + vd1;
})