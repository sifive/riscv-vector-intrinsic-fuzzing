// vsext.vf2 vd, vs2, vm  # Sign-extend SEW/2 source to SEW destination
// vsext.vf4 vd, vs2, vm  # Sign-extend SEW/4 source to SEW destination
// vsext.vf8 vd, vs2, vm  # Sign-extend SEW/8 source to SEW destination
VI_V_LOOP({ vd = vs; })
