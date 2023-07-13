// vfabs.v vd,vs = vfsgnjx.vv vd,vs,vs
VI_VFP_V_LOOP
({
  vd = fsgnj16(vs.v, vs.v, false, true);
},
{
  vd = fsgnj32(vs.v, vs.v, false, true);
},
{
  vd = fsgnj64(vs.v, vs.v, false, true);
})
