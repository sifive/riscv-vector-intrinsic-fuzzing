// vmnot.m vd, vs => vmnand.mm vd, vs, vs  # Invert bits
VI_LOOP_PSUEDO_MASK(~(vs & vs));
