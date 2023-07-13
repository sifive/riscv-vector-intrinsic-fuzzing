vv_literal_start0 = "void compute"
vv_literal_start1 = "Op(RIF::OperatorBase *op) {\n"
vv_literal_nonmask_body = '''
  assert(a->length == b->length && a->length == c->length);

  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataB = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto sew = op->typeInfo->sew.to_int();
  auto dataASew = a->typeInfo->sew.to_int(); // for index load / store only
  P.VU.vsew = sew;

  for (int i = 0; i < length; ++i) {
'''

vv_tu_literal_nonmask_body = '''
  assert(a->length == b->length && a->length == c->length && a->length == d->length);

  auto length = a->length;

  auto dataPassthru = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataB = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto sew = op->typeInfo->sew.to_int();
  auto dataASew = a->typeInfo->sew.to_int(); // for index load / store only
  P.VU.vsew = sew;

  for (int i = 0; i < length; ++i) {
'''


vv_literal_nonmask_destructive_body = '''
  assert(a->length == b->length && a->length == c->length && a->length == d->length);

  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataB = getRawPointer(b);
  auto dataC = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto sew = op->typeInfo->sew.to_int();

  #pragma push_macro("VI_VFP_VV_LOOP")
  #undef VI_VFP_VV_LOOP
  #define VI_VFP_VV_LOOP(BODY16, BODY32, BODY64)                               \\
  RIF::RawDatumOperand vd(dataA[i]);                                           \\
  RIF::RawDatumOperand vs1(dataB[i]);                                          \\
  RIF::RawDatumOperand vs2(dataC[i]);                                          \\
  switch (sew) {                                                               \\
  case e16:                                                                    \\
    BODY16;                                                                    \\
    break;                                                                     \\
  case e32:                                                                    \\
    BODY32;                                                                    \\
    break;                                                                     \\
  case e64:                                                                    \\
    BODY64;                                                                    \\
    break;                                                                     \\
  default:                                                                     \\
    assert(0);                                                                 \\
    break;                                                                     \\
  }                                                                            \\
  dataOut[i] = vd;

  #pragma push_macro("VI_VFP_VV_LOOP_WIDE")
  #undef VI_VFP_VV_LOOP_WIDE
  #define VI_VFP_VV_LOOP_WIDE(BODY16, BODY32)                                  \\
  RIF::RawDatumOperand vd(dataA[i]);                                           \\
  RIF::RawDatumOperand vs1(dataB[i]);                                          \\
  RIF::RawDatumOperand vs2(dataC[i]);                                          \\
  switch (sew) {                                                               \\
  case e16:                                                                    \\
    vs2 = f16_to_f32(vs2);                                                     \\
    vs1 = f16_to_f32(vs1);                                                     \\
    BODY16;                                                                    \\
    break;                                                                     \\
  case e32:                                                                    \\
    vs2 = f32_to_f64(vs2);                                                     \\
    vs1 = f32_to_f64(vs1);                                                     \\
    BODY32;                                                                    \\
    break;                                                                     \\
  default:                                                                     \\
    assert(0);                                                                 \\
    break;                                                                     \\
  }                                                                            \\
  dataOut[i] = vd;

  for (int i = 0; i < length; ++i) {
'''

def include_literal(filename):
    return "#include\"" + filename + "\""

vv_literal_nonmask_end = '''
  }
}
'''

vv_ta_literal_nonmask_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1)
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

vv_tu_literal_nonmask_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1)
      dataOut[i] = dataPassthru[i];
  }
}
'''

vv_literal_nonmask_destructive_end = '''
  }
  #pragma pop_macro("VI_VFP_VV_LOOP")
  #pragma pop_macro("VI_VFP_VV_LOOP_WIDE")
}
'''

vv_tu_literal_nonmask_destructive_end = '''
  }
  #pragma pop_macro("VI_VFP_VV_LOOP")
  #pragma pop_macro("VI_VFP_VV_LOOP_WIDE")
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataA[i];
  }
}
'''

vv_ta_literal_nonmask_destructive_end = '''
  }
  #pragma pop_macro("VI_VFP_VV_LOOP")
  #pragma pop_macro("VI_VFP_VV_LOOP_WIDE")
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

vv_literal_mask_body = '''
  assert(a->length == b->length && a->length == c->length &&
         a->length == e->length && a->length == d->length);

  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataMO = getRawPointer(b);
  auto dataA = getRawPointer(c);
  auto dataB = getRawPointer(d);
  auto dataOut = getRawPointer(e);

  auto sew = op->typeInfo->sew.to_int();
  auto dataASew = c->typeInfo->sew.to_int(); // for index load / store only
  P.VU.vsew = sew;

  for (int i = 0; i < length; ++i) {
    if (dataM[i]) {
'''

vv_literal_mask_body_destructive = '''
  assert(a->length == b->length && a->length == c->length &&
         a->length == e->length && a->length == d->length);

  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataMO = getRawPointer(b);
  auto dataA = getRawPointer(b);
  auto dataB = getRawPointer(c);
  auto dataC = getRawPointer(d);
  auto dataOut = getRawPointer(e);

  auto sew = op->typeInfo->sew.to_int();

  #pragma push_macro("VI_VFP_VV_LOOP")
  #undef VI_VFP_VV_LOOP
  #define VI_VFP_VV_LOOP(BODY16, BODY32, BODY64)                               \\
  RIF::RawDatumOperand vd(dataA[i]);                                           \\
  RIF::RawDatumOperand vs1(dataB[i]);                                          \\
  RIF::RawDatumOperand vs2(dataC[i]);                                          \\
  switch (sew) {                                                               \\
  case e16:                                                                    \\
    BODY16;                                                                    \\
    break;                                                                     \\
  case e32:                                                                    \\
    BODY32;                                                                    \\
    break;                                                                     \\
  case e64:                                                                    \\
    BODY64;                                                                    \\
    break;                                                                     \\
  default:                                                                     \\
    assert(0);                                                                 \\
    break;                                                                     \\
  }                                                                            \\
  dataOut[i] = vd;

  #pragma push_macro("VI_VFP_VV_LOOP_WIDE")
  #undef VI_VFP_VV_LOOP_WIDE
  #define VI_VFP_VV_LOOP_WIDE(BODY16, BODY32)                                  \\
  RIF::RawDatumOperand vd(dataA[i]);                                           \\
  RIF::RawDatumOperand vs1(dataB[i]);                                          \\
  RIF::RawDatumOperand vs2(dataC[i]);                                          \\
  switch (sew) {                                                               \\
  case e16:                                                                    \\
    vs2 = f16_to_f32(vs2);                                                     \\
    vs1 = f16_to_f32(vs1);                                                     \\
    BODY16;                                                                    \\
    break;                                                                     \\
  case e32:                                                                    \\
    vs2 = f32_to_f64(vs2);                                                     \\
    vs1 = f32_to_f64(vs1);                                                     \\
    BODY32;                                                                    \\
    break;                                                                     \\
  default:                                                                     \\
    assert(0);                                                                 \\
    break;                                                                     \\
  }                                                                            \\
  dataOut[i] = vd;

  for (int i = 0; i < length; ++i) {
    if (dataM[i]) {
'''

vv_literal_mask_end = '''
    } else
      dataOut[i] = dataMO[i];
  }
}
'''

vv_ta_literal_mask_end = '''
    } else
      dataOut[i] = dataMO[i];
  }
  auto half = length / 2;
  for (int i = half; i < length; ++i) {
    dataOut[i] = -1;
  }
}
'''

vv_tu_literal_mask_end = '''
    } else
      dataOut[i] = dataMO[i];
  }
  auto half = length / 2;
  for (int i = half; i < length; ++i) {
    dataOut[i] = dataMO[i];
  }
}
'''

vv_literal_mask_destructive_end = '''
    } else
      dataOut[i] = dataMO[i];
  }
  #pragma pop_macro("VI_VFP_VV_LOOP")
  #pragma pop_macro("VI_VFP_VV_LOOP_WIDE")
}
'''

vv_tama_literal_mask_destructive_end = '''
    } else // maskedoff element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
  #pragma pop_macro("VI_VFP_VV_LOOP")
  #pragma pop_macro("VI_VFP_VV_LOOP_WIDE")
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

vv_tamu_literal_mask_destructive_end = '''
    } else // maskedoff element is undisturbed
      dataOut[i] = dataMO[i];
  }
  #pragma pop_macro("VI_VFP_VV_LOOP")
  #pragma pop_macro("VI_VFP_VV_LOOP_WIDE")
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

vv_tuma_literal_mask_destructive_end = '''
    } else // maskedoff element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
  #pragma pop_macro("VI_VFP_VV_LOOP")
  #pragma pop_macro("VI_VFP_VV_LOOP_WIDE")
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataMO[i];
  }
}
'''

vv_tumu_literal_mask_destructive_end = '''
    } else // maskedoff element is undisturbed
      dataOut[i] = dataMO[i];
  }
  #pragma pop_macro("VI_VFP_VV_LOOP")
  #pragma pop_macro("VI_VFP_VV_LOOP_WIDE")
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataMO[i];
  }
}
'''

vv_literal_masked_no_maskedoff_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataB = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto sew = op->typeInfo->sew.to_int();
  auto dataASew = b->typeInfo->sew.to_int(); // for index load / store only
  P.VU.vsew = sew;

  for (int i = 0; i < length; ++i) {
    if (dataM[i]) {
'''

vv_mu_literal_masked_no_maskedoff_body = '''
  auto length = a->length;

  auto dataPassthru = getRawPointer(a);
  auto dataM = getRawPointer(b);
  auto dataA = getRawPointer(c);
  auto dataB = getRawPointer(d);
  auto dataOut = getRawPointer(e);

  auto sew = op->typeInfo->sew.to_int();
  auto dataASew = b->typeInfo->sew.to_int(); // for index load / store only
  P.VU.vsew = sew;

  for (int i = 0; i < length; ++i) {
    if (dataM[i]) {
'''

vv_literal_masked_no_masked_off_end = '''
    } else {

    }
  }
}
'''

vv_mask_output_ma_literal_masked_no_masked_off_end = '''
    } else { // maskedoff element is agnostic(only set one bit)
      dataOut[i] = 1;
    }
  }
}
'''

vv_ma_literal_masked_no_masked_off_end = '''
    } else { // maskedoff element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
    }
  }
}
'''

vv_mu_literal_masked_no_masked_off_end = '''
    } else { // maskedoff element is undisturbed
      dataOut[i] = dataPassthru[i];
    }
  }
}
'''

vv_tama_literal_mask_end = '''
    } else { // maskedoff element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
    }
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

vv_tamu_literal_mask_end = '''
    } else { // maskedoff element is undisturbed
      dataOut[i] = dataMO[i];
    }
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

vv_tuma_literal_mask_end = '''
    } else { // maskedoff element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
    }
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataMO[i];
  }
}
'''

vv_tumu_literal_mask_end = '''
    } else { // maskedoff element is undisturbed
      dataOut[i] = dataMO[i];
    }
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataMO[i];
  }
}
'''

def create_vv_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += vv_literal_start0 + op_type + vv_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskedOperation" in op_attr :
    if "TailAgnostic" in op_attr and "MaskAgnostic" in op_attr : # tama
      ret += vv_literal_masked_no_maskedoff_body + include_literal("v" + op_id + ".h") + vv_tama_literal_mask_end
    elif "TailAgnostic" in op_attr and "MaskUndisturbed" in op_attr : # tamu
      ret += vv_literal_mask_body + include_literal("v" + op_id + ".h") + vv_tamu_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskAgnostic" in op_attr : # tuma
      ret += vv_literal_mask_body + include_literal("v" + op_id + ".h") + vv_tuma_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskUndisturbed" in op_attr : # tumu
      ret += vv_literal_mask_body + include_literal("v" + op_id + ".h") + vv_tumu_literal_mask_end
    else : # No explicit policy specified
      ret += vv_literal_mask_body + include_literal("v" + op_id + ".h") + vv_literal_mask_end
  else :
    if "TailUndisturbed" in op_attr :
        ret += vv_tu_literal_nonmask_body + include_literal("v" + op_id + ".h") + vv_tu_literal_nonmask_end
    elif "TailAgnostic" in op_attr :
        ret += vv_literal_nonmask_body + include_literal("v" + op_id + ".h") + vv_ta_literal_nonmask_end
    else :
      ret += vv_literal_nonmask_body + include_literal("v" + op_id + ".h") + vv_literal_nonmask_end
  return ret

def create_destructive_vv_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += vv_literal_start0 + op_type + vv_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskedOperation" in op_attr :
    if "TailAgnostic" in op_attr and "MaskAgnostic" in op_attr : # tama
      ret += vv_literal_mask_body_destructive + include_literal("v" + op_id + ".h") + vv_tama_literal_mask_destructive_end
    elif "TailAgnostic" in op_attr and "MaskUndisturbed" in op_attr : # tamu
      ret += vv_literal_mask_body_destructive + include_literal("v" + op_id + ".h") + vv_tamu_literal_mask_destructive_end
    elif "TailUndisturbed" in op_attr and "MaskAgnostic" in op_attr : # tuma
      ret += vv_literal_mask_body_destructive + include_literal("v" + op_id + ".h") + vv_tuma_literal_mask_destructive_end
    elif "TailUndisturbed" in op_attr and "MaskUndisturbed" in op_attr : # tumu
      ret += vv_literal_mask_body_destructive + include_literal("v" + op_id + ".h") + vv_tumu_literal_mask_destructive_end
    else : # No explicit policy specified
      ret += vv_literal_mask_body_destructive + include_literal("v" + op_id + ".h") + vv_literal_mask_destructive_end
  else :
    if "TailUndisturbed" in op_attr :
        ret += vv_literal_nonmask_destructive_body + include_literal("v" + op_id + ".h") + vv_tu_literal_nonmask_destructive_end
    elif "TailAgnostic" in op_attr :
        ret += vv_literal_nonmask_destructive_body + include_literal("v" + op_id + ".h") + vv_ta_literal_nonmask_destructive_end
    else :
      ret += vv_literal_nonmask_destructive_body + include_literal("v" + op_id + ".h") + vv_literal_nonmask_destructive_end
  return ret

def create_masked_no_maskedoff_vv_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += vv_literal_start0 + op_type + vv_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskAgnostic" in op_attr : # ma
    ret += vv_literal_masked_no_maskedoff_body + include_literal("v" + op_id + ".h")
    if op_type[-3:] == "_MA" : # output is mask(only one bit for each element)
      ret += vv_mask_output_ma_literal_masked_no_masked_off_end
    else :
      ret += vv_ma_literal_masked_no_masked_off_end
  elif "MaskUndisturbed" in op_attr : # mu
    ret += vv_mu_literal_masked_no_maskedoff_body + include_literal("v" + op_id + ".h") + vv_mu_literal_masked_no_masked_off_end
  else :
    ret += vv_literal_masked_no_maskedoff_body + include_literal("v" + op_id + ".h") + vv_literal_masked_no_masked_off_end
  return ret
