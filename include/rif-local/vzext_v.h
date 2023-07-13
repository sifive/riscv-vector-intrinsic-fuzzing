// vzext.vf2 vd, vs2, vm  # Zero-extend SEW/2 source to SEW destination
// vzext.vf4 vd, vs2, vm  # Zero-extend SEW/4 source to SEW destination
// vzext.vf8 vd, vs2, vm  # Zero-extend SEW/8 source to SEW destination
VI_V_LOOP({ vd = vs; })
