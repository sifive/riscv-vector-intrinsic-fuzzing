// vmflt.vv vd, vb, va, vm = vmfgt.vv vd, va, vb, vm
VI_VFP_VV_LOOP_CMP
({
  res = f16_lt(vs1, vs2);
},
{
  res = f32_lt(vs1, vs2);
},
{
  res = f64_lt(vs1, vs2);
})
