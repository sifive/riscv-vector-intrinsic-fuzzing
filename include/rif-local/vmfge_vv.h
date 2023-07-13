// vmfle.vv vd, vb, va, vm = vmfge.vv vd, va, vb, vm
VI_VFP_VV_LOOP_CMP
({
  res = f16_le(vs1, vs2);
},
{
  res = f32_le(vs1, vs2);
},
{
  res = f64_le(vs1, vs2);
})
