vxm_literal_start0 = "void compute"
vxm_literal_start1 = "Op(RIF::OperatorBase *op) {\n"
vxm_literal_body = '''
  if (op->opAttr & RIF::MergeOperation)
    assert(a->length == b->length && c->length == 1 && a->length == d->length);
  else
    assert(b->length == 1 && a->length == c->length && a->length == d->length);

  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataB = getRawPointer(b);
  auto dataC = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto sew = op->typeInfo->sew.to_int();

  for (int i = 0; i < length; ++i) {
'''

vxm_tu_literal_body = '''
  assert(c->length == 1 && a->length == b->length && a->length == d->length && a->length == e->length);

  auto length = a->length;

  auto dataPassthru = getRawPointer(a);
  auto dataA = getRawPointer(b);
  auto dataB = getRawPointer(c);
  auto dataC = getRawPointer(d);
  auto dataOut = getRawPointer(e);

  auto sew = op->typeInfo->sew.to_int();
  P.VU.vsew = sew;

  for (int i = 0; i < length; ++i) {
'''

merge_vxm_tu_literal_body = '''
  assert(a->length == b->length && a->length == c->length && d->length == 1 && a->length == e->length);

  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataPassthru = getRawPointer(b);
  auto dataB = getRawPointer(c);
  auto dataC = getRawPointer(d);
  auto dataOut = getRawPointer(e);

  auto sew = op->typeInfo->sew.to_int();
  P.VU.vsew = sew;

  for (int i = 0; i < length; ++i) {
'''

def include_literal(filename):
    return "#include\"" + filename + "\""

vxm_literal_end = '''
  }
}
'''

vxm_tu_literal_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataPassthru[i];
  }
}
'''

vxm_ta_literal_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''


def create_vxm_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += vxm_literal_start0 + op_type + vxm_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]);\n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]);\n"
  if "TailUndisturbed" in op_attr :
    if "MergeOperation" in op_attr :
      ret += merge_vxm_tu_literal_body + include_literal("v" + op_id + ".h") + vxm_tu_literal_end
    else :
      ret += vxm_tu_literal_body + include_literal("v" + op_id + ".h") + vxm_tu_literal_end
  elif "TailAgnostic" in op_attr :
    ret += vxm_literal_body + include_literal("v" + op_id + ".h") + vxm_ta_literal_end
  else:
    ret += vxm_literal_body + include_literal("v" + op_id + ".h") + vxm_literal_end
  return ret
