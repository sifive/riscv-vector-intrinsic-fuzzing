// vfneg.v vd,vs = vfsgnjn.vv vd,vs,vs
VI_VFP_V_LOOP
({
  vd = fsgnj16(vs.v, vs.v, true, false);
},
{
  vd = fsgnj32(vs.v, vs.v, true, false);
},
{
  vd = fsgnj64(vs.v, vs.v, true, false);
})
