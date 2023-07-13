// vneg.v vd,vs
// (vneg.v vd,vs = vrsub.vx vd,vs,x0)
VI_V_LOOP({ vd = -vs; })
