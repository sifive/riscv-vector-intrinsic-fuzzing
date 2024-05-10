x_literal_start0 = "void compute"
x_literal_start1 = "Op(RIF::OperatorBase *op) {\n"
x_literal_nonmask_body = '''
   // script/XLiteral.py x_literal_nonmask_body
  auto length = b->length;

  auto dataA = getRawPointer(a);
  auto dataOut = getRawPointer(b);

  auto sew = op->typeInfo->sew.to_int();

  #pragma push_macro("VI_VF_MERGE_LOOP")
  #undef VI_VF_MERGE_LOOP
  #define VI_VF_MERGE_LOOP(BODY)                                               \\
  RIF::RawDatumOperand rs1(*dataA);                                            \\
  RIF::RawDatumOperand vd;                                                     \\
  BODY                                                                         \\
  dataOut[i] = vd;

  for (int i = 0; i < length; ++i) {
'''

x_literal_nonmask_mv_body = '''
   // script/XLiteral.py x_literal_nonmask_mv_body
  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataOut = getRawPointer(b);

  auto sew = op->typeInfo->sew.to_int();

  #pragma push_macro("VI_VF_MERGE_LOOP")
  #undef VI_VF_MERGE_LOOP
  #define VI_VF_MERGE_LOOP(BODY)                                               \\
  RIF::RawDatumOperand vs1(dataA[i]);                                            \\
  RIF::RawDatumOperand vd;                                                     \\
  BODY                                                                         \\
  dataOut[i] = vd;

  for (int i = 0; i < length; ++i) {
'''

x_tu_literal_nonmask_body = '''
  assert(a->length == c->length && b->length == 1);

  auto length = a->length;

  auto dataPassthru = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto sew = op->typeInfo->sew.to_int();

  #pragma push_macro("VI_VF_MERGE_LOOP")
  #undef VI_VF_MERGE_LOOP
  #define VI_VF_MERGE_LOOP(BODY)                                               \\
  RIF::RawDatumOperand rs1(*dataA);                                            \\
  RIF::RawDatumOperand vd;                                                     \\
  BODY                                                                         \\
  dataOut[i] = vd;

  for (int i = 0; i < length; ++i) {
'''

def include_literal(filename):
    return "#include\"" + filename + "\""

x_literal_nonmask_end = '''
  }
  #pragma pop_macro("VI_VF_MERGE_LOOP")
}
'''

x_tu_literal_nonmask_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataPassthru[i];
  }
  #pragma pop_macro("VI_VF_MERGE_LOOP")
}
'''

x_ta_literal_nonmask_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
  #pragma pop_macro("VI_VF_MERGE_LOOP")
}
'''

x_literal_mask_body = '''
  // scripts/XLiteral.py x_literal_mask_body
  assert(a->length == b->length && c->length == 1 &&
         a->length == d->length);

  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataMO = getRawPointer(b);
  auto dataA = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto sew = op->typeInfo->sew.to_int();

  for (int i = 0; i < length; ++i) {
    if (dataM[i]) {
'''

x_tama_literal_mask_body = '''
  // scripts/XLiteral.py x_tama_literal_mask_body
  assert(a->length == b->length && c->length == 1 &&
         a->length == d->length);

  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto sew = op->typeInfo->sew.to_int();

  for (int i = 0; i < length; ++i) {
    if (dataM[i]) {
'''

x_literal_mask_end = '''
    } else {
      dataOut[i] = dataMO[i];
    }
  }
  #pragma pop_macro("VI_VF_MERGE_LOOP")
}
'''

x_tama_literal_mask_end = '''
    } else { // maskedoff element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
    }
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
  #pragma pop_macro("VI_VF_MERGE_LOOP")
}
'''

x_tamu_literal_mask_end = '''
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

x_tuma_literal_mask_end = '''
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

x_tumu_literal_mask_end = '''
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

def create_x_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += x_literal_start0 + op_type + x_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]); // scripts/XLiteral.py create_x_op \n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]); // scripts/XLiteral.py create_x_op \n"
  if "MaskedOperation" in op_attr :
    if "TailAgnostic" in op_attr and "MaskAgnostic" in op_attr : # tama
      ret += x_tama_literal_masked_body + include_literal("v" + op_id + ".h") + x_tama_literal_mask_end
    elif "TailAgnostic" in op_attr and "MaskUndisturbed" in op_attr : # tamu
      ret += x_literal_mask_body + include_literal("v" + op_id + ".h") + x_tamu_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskAgnostic" in op_attr : # tuma
      ret += x_literal_mask_body + include_literal("v" + op_id + ".h") + x_tuma_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskUndisturbed" in op_attr : # tumu
      ret += x_literal_mask_body + include_literal("v" + op_id + ".h") + x_tumu_literal_mask_end
    else : # No explicit policy specified
      ret += x_literal_mask_body + include_literal("v" + op_id + ".h") + x_literal_mask_end
  else :
    if "TailUndisturbed" in op_attr :
      ret += x_tu_literal_nonmask_body + include_literal("v" + op_id + ".h") + x_tu_literal_nonmask_end
    elif "TailAgnostic" in op_attr :
      ret += x_literal_nonmask_body + include_literal("v" + op_id + ".h") + x_ta_literal_nonmask_end
    elif "NoVLParameter" in op_attr:
      ret += x_literal_nonmask_mv_body + include_literal("v" + op_id + ".h") + x_literal_nonmask_end
    else :
      ret += x_literal_nonmask_body + include_literal("v" + op_id + ".h") + x_literal_nonmask_end
  return ret
