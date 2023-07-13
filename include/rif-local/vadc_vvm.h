// vadc.vvm vd, vs2, vs1, carry
VI_VV_LOOP_WITH_CARRY
({
  const uint128_t op_mask = (UINT64_MAX >> (64 - sew));
  uint128_t res = (op_mask & vs1) + (op_mask & vs2) + carry;
  vd = res;
})
