# Literals covered in this file includes vcpop, vfirst, vmsbf, vmsif, vmsof, viota
cpop_literal_start0 = "void compute"
cpop_literal_start1 = "Op(RIF::OperatorBase *op) {\n"
cpop_literal_nonmask_body = '''
  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataOut = getRawPointer(b);

  auto sew = op->typeInfo->sew;

  unsigned long pop_count = 0;

  for (int i = 0; i < length; ++i) {
'''

cpop_literal_nonmask_end = '''
  }
  *dataOut = pop_count;
}
'''

cpop_literal_mask_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto sew = op->typeInfo->sew;

  unsigned long pop_count = 0;

  for (int i = 0; i < length; ++i) {
    if (dataM[i]) {
'''

cpop_literal_mask_end = '''
    }
  }
  *dataOut = pop_count;
}
'''

def include_literal(filename):
    return "#include\"" + filename + "\""

def create_cpop_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += cpop_literal_start0 + op_type + cpop_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskedOperation" in op_attr :
    ret += cpop_literal_mask_body + include_literal("v" + op_id + ".h") + cpop_literal_mask_end  
  else :
    ret += cpop_literal_nonmask_body + include_literal("v" + op_id + ".h") + cpop_literal_nonmask_end
  return ret

vfirst_literal_start0 = "void compute"
vfirst_literal_start1 = "Op(RIF::OperatorBase *op) {\n"
vfirst_literal_nonmask_body = '''
  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataOut = getRawPointer(b);

  auto sew = op->typeInfo->sew;

  int first = -1;
  int i = 0;
  while (i < length && first == -1) {
'''

vfirst_literal_nonmask_end = '''
    ++i;
  }
  *dataOut = first;
}
'''

vfirst_literal_mask_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto sew = op->typeInfo->sew;

  int first = -1;
  int i = 0;
  while (i < length && first == -1) {
    if (dataM[i]) {
'''

vfirst_literal_mask_end = '''
    }
    ++i;
  }
  *dataOut = first;
}
'''

def create_vfirst_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += vfirst_literal_start0 + op_type + vfirst_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskedOperation" in op_attr :
    ret += vfirst_literal_mask_body + include_literal("v" + op_id + ".h") + vfirst_literal_mask_end  
  else :
    ret += vfirst_literal_nonmask_body + include_literal("v" + op_id + ".h") + vfirst_literal_nonmask_end
  return ret

msbf_msif_msof_literal_start0 = "void compute"
msbf_msif_msof_literal_start1 = "Op(RIF::OperatorBase *op) {\n"
msbf_msif_msof_literal_nonmask_body = '''
  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataOut = getRawPointer(b);

  auto sew = op->typeInfo->sew;

  int i = 0;
  while (i < length) {
'''

msbf_msif_msof_literal_nonmask_end = '''
    ++i;
  }
  while (i < length) {
    dataOut[i] = 0;
    ++i;
  }
}
'''

msbf_msif_msof_literal_mask_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataMO = getRawPointer(b);
  auto dataA = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto sew = op->typeInfo->sew;

  int i = 0;
  while (i < length) {
    if (dataM[i]) {
'''

msbf_msif_msof_ma_literal_mask_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto sew = op->typeInfo->sew;

  int i = 0;
  while (i < length) {
    if (dataM[i]) {
'''

msbf_msif_msof_literal_mask_end = '''
    } else {
      dataOut[i] = dataMO[i];
    }
    ++i;
  }
  while (i < length) {
    if (dataM[i]) {
      dataOut[i] = 0;
    } else {
      dataOut[i] = dataMO[i];
    }
    ++i;
  }
}
'''

msbf_msif_msof_ma_literal_mask_end = '''
    } else { // maskedoff is 1 for vector mask agnostic
      dataOut[i] = 1;
    }
    ++i;
  }
  while (i < length) {
    if (dataM[i]) {
      dataOut[i] = 0;
    } else {
      dataOut[i] = 1;
    }
    ++i;
  }
}
'''

def create_msbf_msif_msof_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += msbf_msif_msof_literal_start0 + op_type + msbf_msif_msof_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskedOperation" in op_attr :
    if "MaskAgnostic" in op_attr :
      ret += msbf_msif_msof_ma_literal_mask_body + include_literal("v" + op_id + ".h") + msbf_msif_msof_ma_literal_mask_end
    else :
      ret += msbf_msif_msof_literal_mask_body + include_literal("v" + op_id + ".h") + msbf_msif_msof_literal_mask_end
  else :
    ret += msbf_msif_msof_literal_nonmask_body + include_literal("v" + op_id + ".h") + msbf_msif_msof_literal_nonmask_end
  return ret

iota_literal_start0 = "void compute"
iota_literal_start1 = "Op(RIF::OperatorBase *op) {\n"
iota_literal_nonmask_body = '''
  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataOut = getRawPointer(b);

  auto sew = op->typeInfo->sew;

  unsigned acculateMask = 0;
  for (int i = 0; i < length; ++i) {
'''

iota_ta_literal_nonmask_body = '''
  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataOut = getRawPointer(b);

  auto sew = op->typeInfo->sew;

  unsigned acculateMask = 0;
  for (int i = 0; i < length; i += 2) {
'''

iota_tu_literal_nonmask_body = '''
  auto length = a->length;

  auto dataPassthru = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto sew = op->typeInfo->sew;

  unsigned acculateMask = 0;
  for (int i = 0; i < length; i += 2) {
'''

iota_literal_nonmask_end = '''
  }
}
'''

iota_tu_literal_nonmask_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataPassthru[i];
  }
}
'''

iota_ta_literal_nonmask_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

iota_literal_mask_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataMO = getRawPointer(b);
  auto dataA = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto sew = op->typeInfo->sew;

  unsigned acculateMask = 0;
  for (int i = 0; i < length; ++i) {
    if (dataM[i]) {
'''

iota_tail_policy_literal_mask_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataMO = getRawPointer(b);
  auto dataA = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto sew = op->typeInfo->sew;

  unsigned acculateMask = 0;
  for (int i = 0; i < length; i += 2) {
    if (dataM[i]) {
'''

iota_tama_literal_mask_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto sew = op->typeInfo->sew;

  unsigned acculateMask = 0;
  for (int i = 0; i < length; i += 2) {
    if (dataM[i]) {
'''

iota_literal_mask_end = '''
    } else {
      dataOut[i] = dataMO[i];
    }
  }
}
'''

iota_tama_literal_mask_end = '''
    } else {
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
    }
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

iota_tamu_literal_mask_end = '''
    } else {
      dataOut[i] = dataMO[i];
    }
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

iota_tuma_literal_mask_end = '''
    } else {
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
    }
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataMO[i];
  }
}
'''

iota_tumu_literal_mask_end = '''
    } else {
      dataOut[i] = dataMO[i];
    }
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataMO[i];
  }
}
'''

def create_iota_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += iota_literal_start0 + op_type + iota_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskedOperation" in op_attr :
    if "TailAgnostic" in op_attr and "MaskAgnostic" in op_attr : # tama
      ret += iota_tama_literal_mask_body + include_literal("v" + op_id + ".h") + iota_tama_literal_mask_end
    elif "TailAgnostic" in op_attr and "MaskUndisturbed" in op_attr : # tamu
      ret += iota_tail_policy_literal_mask_body + include_literal("v" + op_id + ".h") + iota_tamu_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskAgnostic" in op_attr : # tuma
      ret += iota_tail_policy_literal_mask_body + include_literal("v" + op_id + ".h") + iota_tuma_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskUndisturbed" in op_attr : # tumu
      ret += iota_tail_policy_literal_mask_body + include_literal("v" + op_id + ".h") + iota_tumu_literal_mask_end
    else : # No explicit policy specified
      ret += iota_literal_mask_body + include_literal("v" + op_id + ".h") + iota_literal_mask_end
  else :
    if "TailUndisturbed" in op_attr :
      ret += iota_tu_literal_nonmask_body + include_literal("v" + op_id + ".h") + iota_tu_literal_nonmask_end
    elif "TailAgnostic" in op_attr :
      ret += iota_ta_literal_nonmask_body + include_literal("v" + op_id + ".h") + iota_ta_literal_nonmask_end
    else :
      ret += iota_literal_nonmask_body + include_literal("v" + op_id + ".h") + iota_literal_nonmask_end
  return ret

id_literal_start0 = "void compute"
id_literal_start1 = "Op(RIF::OperatorBase *op) {\n"
id_literal_nonmask_body = '''
  auto length = a->length;

  auto dataOut = getRawPointer(a);

  auto sew = op->typeInfo->sew;

  for (int i = 0; i < length; ++i) {
'''

id_tu_literal_nonmask_body = '''
  auto length = a->length;

  auto dataPassthru = getRawPointer(a);
  auto dataOut = getRawPointer(b);

  auto sew = op->typeInfo->sew;

  for (int i = 0; i < length; ++i) {
'''

id_literal_nonmask_end = '''
  }
}
'''

id_ta_literal_nonmask_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

id_tu_literal_nonmask_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataPassthru[i];
  }
}
'''

id_literal_mask_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataMO = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto sew = op->typeInfo->sew;

  for (int i = 0; i < length; ++i) {
    if (dataM[i]) {
'''

id_tama_literal_mask_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataOut = getRawPointer(b);

  auto sew = op->typeInfo->sew;

  for (int i = 0; i < length; ++i) {
    if (dataM[i]) {
'''

id_literal_mask_end = '''
    } else {
      dataOut[i] = dataMO[i];
    }
  }
}
'''

id_tama_literal_mask_end = '''
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

id_tamu_literal_mask_end = '''
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

id_tuma_literal_mask_end = '''
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

id_tumu_literal_mask_end = '''
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

def create_id_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += id_literal_start0 + op_type + id_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskedOperation" in op_attr :
    if "TailAgnostic" in op_attr and "MaskAgnostic" in op_attr : # tama
      ret += id_tama_literal_mask_body + include_literal("v" + op_id + ".h") + id_tama_literal_mask_end
    elif "TailAgnostic" in op_attr and "MaskUndisturbed" in op_attr : # tamu
      ret += id_literal_mask_body + include_literal("v" + op_id + ".h") + id_tamu_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskAgnostic" in op_attr : # tuma
      ret += id_literal_mask_body + include_literal("v" + op_id + ".h") + id_tuma_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskUndisturbed" in op_attr : # tumu
      ret += id_literal_mask_body + include_literal("v" + op_id + ".h") + id_tumu_literal_mask_end
    else : # No explicit policy specified
      ret += id_literal_mask_body + include_literal("v" + op_id + ".h") + id_literal_mask_end
  else :
    if "TailUndisturbed" in op_attr :
      ret += id_tu_literal_nonmask_body + include_literal("v" + op_id + ".h") + id_tu_literal_nonmask_end
    elif "TailAgnostic" in op_attr :
      ret += id_literal_nonmask_body + include_literal("v" + op_id + ".h") + id_ta_literal_nonmask_end
    else :
      ret += id_literal_nonmask_body + include_literal("v" + op_id + ".h") + id_literal_nonmask_end
  return ret
