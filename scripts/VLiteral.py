v_literal_start0 = "void compute"
v_literal_start1 = "Op(RIF::OperatorBase *op) {\n"
v_literal_nonmask_body = '''
  assert(a->length == b->length);

  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataOut = getRawPointer(b);

  auto sew = op->typeInfo->sew.to_int();

  for (int i = 0; i < length; ++i) {
'''

v_tu_literal_nonmask_body = '''
  assert(a->length == b->length && a->length == c->length);

  auto length = a->length;

  auto dataPassthru = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto sew = op->typeInfo->sew.to_int();

  for (int i = 0; i < length; ++i) {
'''

v_literal_nonmask_no_input_body = '''

  auto length = a->length;

  auto dataOut = getRawPointer(a);

  auto sew = op->typeInfo->sew.to_int();

  for (int i = 0; i < length; ++i) {
'''

v_literal_mask_body = '''
  assert(a->length == b->length && a->length == c->length &&
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

def include_literal(filename):
    return "#include\"" + filename + "\""

v_literal_nonmask_end = '''
  }
}
'''

v_ta_literal_nonmask_end = '''
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

v_tu_literal_nonmask_end = '''
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataPassthru[i];
  }
}
'''


v_literal_mask_end = '''
    } else
      dataOut[i] = dataMO[i];
  }
}
'''

v_tama_literal_mask_end = '''
    } else { // maskedoff element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
    }
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

v_tamu_literal_mask_end = '''
    } else { // maskedoff element is undisturbed
      dataOut[i] = dataMO[i];
    }
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''

v_tuma_literal_mask_end = '''
    } else { // maskedoff element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
    }
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataMO[i];
  }
}
'''

v_tumu_literal_mask_end = '''
    } else { // maskedoff element is undisturbed
      dataOut[i] = dataMO[i];
    }
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataMO[i];
  }
}
'''


v_literal_masked_no_maskedoff_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto sew = op->typeInfo->sew.to_int();

  for (int i = 0; i < length; ++i) {
    if (dataM[i]) {
'''

v_literal_masked_no_maskedoff_end = '''
    } else {

    }
  }
}
'''

v_literal_strided_load_nonmask_body = '''
  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataStride = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto stride = *dataStride;
  stride = stride % 4 + 1; // lets deal with stride = [1, 4] or [-1, -4]

  auto sew = op->typeInfo->sew.to_int();

  memset(dataOut, 0, length * sew / 8);

  if (stride < 0)
    dataA += length - 1;

  for (int i = 0; i < length && abs(i * stride) < length; ++i) {
'''

v_literal_strided_load_nonmask_end = '''
  }
}
'''

v_tu_literal_strided_load_nonmask_body = '''
  auto length = a->length;

  auto dataPassthru = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataStride = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto stride = *dataStride;
  stride = stride % 4 + 1; // lets deal with stride = [1, 4] or [-1, -4]

  auto sew = op->typeInfo->sew.to_int();

  memset(dataOut, 0, length * sew / 8);

  if (stride < 0)
    dataA += length - 1;

  for (int i = 0; i < length && abs(i * stride) < length; ++i) {
'''

v_literal_strided_load_mask_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataMO = getRawPointer(b);
  auto dataA = getRawPointer(c);
  auto dataStride = getRawPointer(d);
  auto dataOut = getRawPointer(e);

  auto stride = *dataStride;
  stride = stride % 4 + 1; // lets deal with stride = [1, 4] or [-1, -4]

  auto sew = op->typeInfo->sew.to_int();

  memset(dataOut, 0, length * sew / 8);

  if (stride < 0)
    dataA += length - 1;

  for (int i = 0; i < length && abs(i * stride) < length; ++i) {
    if (dataM[i]) {
'''

v_literal_strided_load_mask_end = '''
    } else {
      dataOut[i] = dataMO[i];
    }
  }
}
'''

v_literal_strided_load_masked_no_maskedoff_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataStride = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto stride = *dataStride;
  stride = stride % 4 + 1; // lets deal with stride = [1, 4] or [-1, -4]

  auto sew = op->typeInfo->sew.to_int();

  memset(dataOut, 0, length * sew / 8);

  if (stride < 0)
    dataA += length - 1;

  for (int i = 0; i < length && abs(i * stride) < length; ++i) {
    if (dataM[i]) {
'''

v_literal_strided_store_nonmask_body = '''
  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataStride = getRawPointer(b);
  auto dataOut = getRawPointer(c);

  auto stride = *dataStride;
  stride = stride % 4 + 1; // lets deal with stride = [1, 4] or [-1, -4]

  auto sew = op->typeInfo->sew.to_int();

  memset(dataOut, 0, length * sew / 8);

  if (stride < 0)
    dataOut += length - 1;

  for (int i = 0; i < length && abs(i * stride) < length; ++i) {
'''

v_literal_strided_store_nonmask_end = '''
  }
}
'''

v_literal_strided_store_mask_body = '''
  auto length = a->length;

  auto dataM = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataStride = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto stride = *dataStride;
  stride = stride % 4 + 1; // lets deal with stride = [1, 4] or [-1, -4]

  auto sew = op->typeInfo->sew.to_int();

  memset(dataOut, 0, length * sew / 8);

  if (stride < 0)
    dataOut += length - 1;

  for (int i = 0; i < length && abs(i * stride) < length; ++i) {
    if (dataM[i]) {
'''

v_literal_strided_store_mask_end = '''
    }
  }
}
'''

def create_v_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += v_literal_start0 + op_type + v_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskedOperation" in op_attr :
    if "TailAgnostic" in op_attr and "MaskAgnostic" in op_attr : # tama
      ret += v_literal_masked_no_maskedoff_body + include_literal("v" + op_id + ".h") + v_tama_literal_mask_end
    elif "TailAgnostic" in op_attr and "MaskUndisturbed" in op_attr : # tamu
      ret += v_literal_mask_body + include_literal("v" + op_id + ".h") + v_tamu_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskAgnostic" in op_attr : # tuma
      ret += v_literal_mask_body + include_literal("v" + op_id + ".h") + v_tuma_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskUndisturbed" in op_attr : # tumu
      ret += v_literal_mask_body + include_literal("v" + op_id + ".h") + v_tumu_literal_mask_end
    else : # No explicit policy specified
      ret += v_literal_mask_body + include_literal("v" + op_id + ".h") + v_literal_mask_end
  else :
    if "TailUndisturbed" in op_attr :
        ret += v_tu_literal_nonmask_body + include_literal("v" + op_id + ".h") + v_tu_literal_nonmask_end
    elif "TailAgnostic" in op_attr :
        ret += v_literal_nonmask_body + include_literal("v" + op_id + ".h") + v_ta_literal_nonmask_end
    else :
      ret += v_literal_nonmask_body + include_literal("v" + op_id + ".h") + v_literal_nonmask_end
  return ret

def create_no_input_v_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += v_literal_start0 + op_type + v_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  ret += v_literal_nonmask_no_input_body + include_literal("v" + op_id + ".h") + v_literal_nonmask_end
  return ret

def create_masked_no_maskedoff_v_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += v_literal_start0 + op_type + v_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  ret += v_literal_masked_no_maskedoff_body + include_literal("v" + op_id + ".h") + v_literal_masked_no_maskedoff_end
  return ret

def create_strided_load_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += v_literal_start0 + op_type + v_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskedOperation" in op_attr :
    if "TailAgnostic" in op_attr and "MaskAgnostic" in op_attr : # tama
      ret += v_literal_strided_load_masked_no_maskedoff_body + include_literal("v" + op_id + ".h") + v_tama_literal_mask_end
    elif "TailAgnostic" in op_attr and "MaskUndisturbed" in op_attr : # tamu
      ret += v_literal_strided_load_mask_body + include_literal("v" + op_id + ".h") + v_tamu_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskAgnostic" in op_attr : # tuma
      ret += v_literal_strided_load_mask_body + include_literal("v" + op_id + ".h") + v_tuma_literal_mask_end
    elif "TailUndisturbed" in op_attr and "MaskUndisturbed" in op_attr : # tumu
      ret += v_literal_strided_load_mask_body + include_literal("v" + op_id + ".h") + v_tumu_literal_mask_end
    else : # No explicit policy specified
      ret += v_literal_strided_load_mask_body + include_literal("v" + op_id + ".h") + v_literal_mask_end
  else :
    if "TailUndisturbed" in op_attr :
      ret += v_tu_literal_strided_load_nonmask_body + include_literal("v" + op_id + ".h") + v_tu_literal_nonmask_end
    elif "TailAgnostic" in op_attr :
      ret += v_literal_strided_load_nonmask_body + include_literal("v" + op_id + ".h") + v_ta_literal_nonmask_end
    else :
      ret += v_literal_strided_load_nonmask_body + include_literal("v" + op_id + ".h") + v_literal_nonmask_end
  return ret

def create_strided_store_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += v_literal_start0 + op_type + v_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "MaskedOperation" in op_attr :
    ret += v_literal_strided_store_mask_body + include_literal("v" + op_id + ".h") + v_literal_strided_store_mask_end
  else :
    ret += v_literal_strided_store_nonmask_body + include_literal("v" + op_id + ".h") + v_literal_strided_store_nonmask_end
  return ret
