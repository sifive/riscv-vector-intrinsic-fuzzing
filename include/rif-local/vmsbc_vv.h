// vmsbc.vv vd, vs2, vs1
VI_VV_LOOP
({
  const uint64_t mmask = 1;
  const uint128_t op_mask = (UINT64_MAX >> (64 - sew));
  uint128_t res = (op_mask & vs2) - (op_mask & vs1);
  vd = (res >> sew) & mmask;
})
