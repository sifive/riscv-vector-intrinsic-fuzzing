// vmadc.vv vd, vs2, vs1
VI_VV_LOOP
({
  const uint64_t mmask = 1;
  const uint128_t op_mask = (UINT64_MAX >> (64 - sew));
  uint128_t res = (op_mask & vs1) + (op_mask & vs2);
  vd = (res >> sew) & mmask;
})
