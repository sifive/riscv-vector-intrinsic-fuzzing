vx_literal_start0 = "void compute"
vx_literal_start1 = "Op(RIF::OperatorBase *op) {\n"
vx_literal_nonmask_body = '''
  assert(a->length == c->length && b->length == 1);

  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataB = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto sew = op->typeInfo->sew.to_int();
  P.VU.vsew = sew;

  for (int i = 0; i < length; ++i) {
'''

vx_tu_literal_nonmask_body = '''
  assert(a->length == b->length && c->length == 1 && a->length == d->length);

  auto length = a->length;

  auto dataPassthru = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataB = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto sew = op->typeInfo->sew.to_int();
  P.VU.vsew = sew;

  for (int i = 0; i < length; ++i) {
'''

vx_literal_nonmask_destructive_body = '''
  assert(a->length == c->length && a->length == d->length && b->length == 1);

  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataB = getRawPointer(b);
  auto dataC = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto sew = op->typeInfo->sew.to_int();

  #pragma push_macro("VI_VFP_VF_LOOP")
  #undef VI_VFP_VF_LOOP
  #define VI_VFP_VF_LOOP(BODY16, BODY32, BODY64)                               \\
  RIF::RawDatumOperand vd(dataA[i]);                                           \\
  RIF::RawDatumOperand rs1(*dataB);                                            \\
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

  #pragma push_macro("VI_VFP_VF_LOOP_WIDE")
  #undef VI_VFP_VF_LOOP_WIDE
  #define VI_VFP_VF_LOOP_WIDE(BODY16, BODY32)                                  \\
  RIF::RawDatumOperand vd(dataA[i]);                                           \\
  RIF::RawDatumOperand rs1(*dataB);                                            \\
  RIF::RawDatumOperand vs2(dataC[i]);                                          \\
  switch (sew) {                                                               \\
  case e16:                                                                    \\
    vs2 = f16_to_f32(vs2);                                                     \\
    rs1 = f16_to_f32(rs1);                                                     \\
    BODY16;                                                                    \\
    break;                                                                     \\
  case e32:                                                                    \\
    vs2 = f32_to_f64(vs2);                                                     \\
    rs1 = f32_to_f64(rs1);                                                     \\
    BODY32;                                                                    \\
    break;                                                                     \\
  default:                                                                     \\
    assert(0);                                                                 \\
    break;                                                                     \\
  }                                                                            \\
  dataOut[i] = vd;

  for (int i = 0; i < length; ++i) {
'''

vx_literal_nonmask_end = '''
  }
}
'''

vx_ta_literal_nonmask_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1)
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

vx_tu_literal_nonmask_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1)
      dataOut[i] = dataPassthru[i];
  }
}
'''

vx_literal_nonmask_destructive_end = '''
  }
  #pragma pop_macro("VI_VFP_VF_LOOP")
  #pragma pop_macro("VI_VFP_VF_LOOP_WIDE")
}
'''

vx_tu_literal_nonmask_destructive_end = '''
  }
  #pragma pop_macro("VI_VFP_VF_LOOP")
  #pragma pop_macro("VI_VFP_VF_LOOP_WIDE")
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataA[i];
  }
}
'''

vx_ta_literal_nonmask_destructive_end = '''
  }
  #pragma pop_macro("VI_VFP_VF_LOOP")
  #pragma pop_macro("VI_VFP_VF_LOOP_WIDE")
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

vx_literal_mask_body = '''
  assert(a->length == b->length && a->length == c->length &&
         a->length == e->length && d->length == 1);

  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataMO = getRawPointer(b);
  auto dataA = getRawPointer(c);
  auto dataB = getRawPointer(d);
  auto dataOut = getRawPointer(e);

  auto sew = op->typeInfo->sew.to_int();
  P.VU.vsew = sew;

  for (int i = 0; i < length; ++i) {
    if (dataM[i]) {
'''

vx_literal_mask_destructive_body = '''
  assert(a->length == b->length && a->length == d->length &&
          a->length == e->length && c->length == 1);

  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataMO = getRawPointer(b);
  auto dataA = getRawPointer(b);
  auto dataB = getRawPointer(c);
  auto dataC = getRawPointer(d);
  auto dataOut = getRawPointer(e);

  auto sew = op->typeInfo->sew.to_int();

  #pragma push_macro("VI_VFP_VF_LOOP")
  #undef VI_VFP_VF_LOOP
  #define VI_VFP_VF_LOOP(BODY16, BODY32, BODY64)                               \\
  RIF::RawDatumOperand vd(dataA[i]);                                           \\
  RIF::RawDatumOperand rs1(*dataB);                                            \\
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

  #pragma push_macro("VI_VFP_VF_LOOP_WIDE")
  #undef VI_VFP_VF_LOOP_WIDE
  #define VI_VFP_VF_LOOP_WIDE(BODY16, BODY32)                                  \\
  RIF::RawDatumOperand vd(dataA[i]);                                           \\
  RIF::RawDatumOperand rs1(*dataB);                                            \\
  RIF::RawDatumOperand vs2(dataC[i]);                                          \\
  switch (sew) {                                                               \\
  case e16:                                                                    \\
    vs2 = f16_to_f32(vs2);                                                     \\
    rs1 = f16_to_f32(rs1);                                                     \\
    BODY16;                                                                    \\
    break;                                                                     \\
  case e32:                                                                    \\
    vs2 = f32_to_f64(vs2);                                                     \\
    rs1 = f32_to_f64(rs1);                                                     \\
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

vx_literal_mask_end = '''
    } else
      dataOut[i] = dataMO[i];
  }
}
'''

vx_ta_literal_mask_end = '''
    } else
      dataOut[i] = dataMO[i];
  }
  auto half = length / 2;
  for (int i = half; i < length; ++i) {
    dataOut[i] = -1;
  }
}
'''

vx_tu_literal_mask_end = '''
    } else
      dataOut[i] = dataMO[i];
  }
  auto half = length / 2;
  for (int i = half; i < length; ++i) {
    dataOut[i] = dataMO[i];
  }
}
'''

vx_literal_mask_destructive_end = '''
    } else
      dataOut[i] = dataMO[i];
  }
  #pragma pop_macro("VI_VFP_VF_LOOP")
  #pragma pop_macro("VI_VFP_VF_LOOP_WIDE")
}
'''

vx_literal_masked_no_maskedoff_body = '''
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

vx_literal_masked_no_masked_off_end = '''
    } else {

    }
  }
}
'''

vx_tama_literal_mask_end = '''
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

vx_tamu_literal_mask_end = '''
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

vx_tuma_literal_mask_end = '''
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

vx_tumu_literal_mask_end = '''
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

vx_tama_literal_mask_destructive_end = '''
    } else // maskedoff element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
  #pragma pop_macro("VI_VFP_VF_LOOP")
  #pragma pop_macro("VI_VFP_VF_LOOP_WIDE")
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

vx_tamu_literal_mask_destructive_end = '''
    } else // maskedoff element is undisturbed
      dataOut[i] = dataMO[i];
  }
  #pragma pop_macro("VI_VFP_VF_LOOP")
  #pragma pop_macro("VI_VFP_VF_LOOP_WIDE")
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

vx_tuma_literal_mask_destructive_end = '''
    } else // maskedoff element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
  #pragma pop_macro("VI_VFP_VF_LOOP")
  #pragma pop_macro("VI_VFP_VF_LOOP_WIDE")
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataMO[i];
  }
}
'''

vx_tumu_literal_mask_destructive_end = '''
    } else // maskedoff element is undisturbed
      dataOut[i] = dataMO[i];
  }
  #pragma pop_macro("VI_VFP_VF_LOOP")
  #pragma pop_macro("VI_VFP_VF_LOOP_WIDE")
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataMO[i];
  }
}
'''

vx_mu_literal_masked_no_maskedoff_body = '''
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

vx_ma_literal_masked_no_masked_off_end = '''
    } else { // maskedoff element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
    }
  }
}
'''

vx_mask_output_ma_literal_masked_no_masked_off_end = '''
    } else { // maskedoff element is agnostic(only set one bit)
      dataOut[i] = 1;
    }
  }
}
'''

vx_mu_literal_masked_no_masked_off_end = '''
    } else { // maskedoff element is undisturbed
      dataOut[i] = dataPassthru[i];
    }
  }
}
'''


def include_literal(filename):
    return "#include\"" + filename + "\""

def create_vx_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += vx_literal_start0 + op_type + vx_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskedOperation" in op_attr :
    if "TailAgnostic" in op_attr and "MaskAgnostic" in op_attr : # tama
      ret += vx_literal_masked_no_maskedoff_body + include_literal("v" + op_id + ".h") + vx_tama_literal_mask_end
    elif "TailAgnostic" in op_attr and "MaskUndisturbed" in op_attr : # tamu
      ret += vx_literal_mask_body + include_literal("v" + op_id + ".h") + vx_tamu_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskAgnostic" in op_attr : # tuma
      ret += vx_literal_mask_body + include_literal("v" + op_id + ".h") + vx_tuma_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskUndisturbed" in op_attr : # tumu
      ret += vx_literal_mask_body + include_literal("v" + op_id + ".h") + vx_tumu_literal_mask_end
    else : # No explicit policy specified
      ret += vx_literal_mask_body + include_literal("v" + op_id + ".h") + vx_literal_mask_end
  else :
    if "TailUndisturbed" in op_attr :
      ret += vx_tu_literal_nonmask_body + include_literal("v" + op_id + ".h") + vx_tu_literal_nonmask_end
    elif "TailAgnostic" in op_attr :
      ret += vx_literal_nonmask_body + include_literal("v" + op_id + ".h") + vx_ta_literal_nonmask_end
    else :
      ret += vx_literal_nonmask_body + include_literal("v" + op_id + ".h") + vx_literal_nonmask_end
  return ret

def create_destructive_vx_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += vx_literal_start0 + op_type + vx_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskedOperation" in op_attr :
    if "TailAgnostic" in op_attr and "MaskAgnostic" in op_attr : # tama
      ret += vx_literal_mask_destructive_body  + include_literal("v" + op_id + ".h") + vx_tama_literal_mask_destructive_end
    elif "TailAgnostic" in op_attr and "MaskUndisturbed" in op_attr : # tamu
      ret += vx_literal_mask_destructive_body + include_literal("v" + op_id + ".h") + vx_tamu_literal_mask_destructive_end
    elif "TailUndisturbed" in op_attr and "MaskAgnostic" in op_attr : # tuma
      ret += vx_literal_mask_destructive_body + include_literal("v" + op_id + ".h") + vx_tuma_literal_mask_destructive_end
    elif "TailUndisturbed" in op_attr and "MaskUndisturbed" in op_attr : # tumu
      ret += vx_literal_mask_destructive_body + include_literal("v" + op_id + ".h") + vx_tumu_literal_mask_destructive_end
    else : # No explicit policy specified
      ret += vx_literal_mask_destructive_body + include_literal("v" + op_id + ".h") + vx_literal_mask_destructive_end
  else :
    if "TailUndisturbed" in op_attr :
      ret += vx_literal_nonmask_destructive_body + include_literal("v" + op_id + ".h") + vx_tu_literal_nonmask_destructive_end
    elif "TailAgnostic" in op_attr :
      ret += vx_literal_nonmask_destructive_body + include_literal("v" + op_id + ".h") + vx_ta_literal_nonmask_destructive_end
    else :
      ret += vx_literal_nonmask_destructive_body + include_literal("v" + op_id + ".h") + vx_literal_nonmask_destructive_end
  return ret

def create_masked_no_maskedoff_vx_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += vx_literal_start0 + op_type + vx_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskAgnostic" in op_attr : # ma
    ret += vx_literal_masked_no_maskedoff_body  + include_literal("v" + op_id + ".h")
    if op_type[-3:] == "_MA" : # output is mask(only one bit for each element)
      ret += vx_mask_output_ma_literal_masked_no_masked_off_end
    else :
      ret += vx_ma_literal_masked_no_masked_off_end
  elif "MaskUndisturbed" in op_attr : # mu
    ret += vx_mu_literal_masked_no_maskedoff_body + include_literal("v" + op_id + ".h") + vx_mu_literal_masked_no_masked_off_end
  else :
    ret += vx_literal_masked_no_maskedoff_body + include_literal("v" + op_id + ".h") + vx_literal_masked_no_masked_off_end
  return ret
