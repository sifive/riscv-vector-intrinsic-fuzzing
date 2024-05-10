vvm_literal_start0 = "void compute"
vvm_literal_start1 = "Op(RIF::OperatorBase *op) {\n"
vvm_literal_body = '''
  //scripts/VVMLiteral.py vvm_literal_body
  assert(a->length == b->length && a->length == c->length && a->length == d->length);

  auto length = a->length;

  auto dataA = getRawPointer(a);
  auto dataB = getRawPointer(b);
  auto dataC = getRawPointer(c);
  auto dataOut = getRawPointer(d);

  auto sew = op->typeInfo->sew.to_int();

  for (int i = 0; i < length; ++i) {
'''

vvm_tu_literal_body = '''
  assert(a->length == b->length && a->length == c->length && a->length == d->length && a->length == e->length);

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

merge_vvm_tu_literal_body = '''
  assert(a->length == b->length && a->length == c->length && a->length == d->length && a->length == e->length);

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

vvm_literal_end = '''
  }
}
'''

vvm_tu_literal_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is undisturbed
      dataOut[i] = dataPassthru[i];
  }
}
'''

vvm_ta_literal_end = '''
  }
  for (int i = 0; i < length; ++i) {
    if (i & 1) // tail element is agnostic
      memset(&dataOut[i], 0xff, sizeof(dataOut[i]));
  }
}
'''


def create_vvm_op(op_type, op_id, op_attr, output_type, input_num, input_types) :
  ret = ""
  ret += vvm_literal_start0 + op_type + vvm_literal_start1
  for i in range(input_num) :
    var = chr(ord('a') + i)
    ret += "  auto " + var + " = static_cast<RIF::" + input_types[i] + "Val *>(op->inputs[" + str(i) + "]); // scripts/VVMLiteral.py create_vvm_op \n"
  var = chr(ord('a') + input_num)
  ret += "  auto " + var + " = static_cast<RIF::" + output_type + "Val *>(op->outputs[0]); // scripts/VVMLiteral.py create_vvm_op \n"
  if "TailUndisturbed" in op_attr :
    if "MergeOperation" in op_attr :
      ret += merge_vvm_tu_literal_body + include_literal("v" + op_id + ".h") + vvm_tu_literal_end
    else :
      ret += vvm_tu_literal_body + include_literal("v" + op_id + ".h") + vvm_tu_literal_end
  elif "TailAgnostic" in op_attr :
    ret += vvm_literal_body + include_literal("v" + op_id + ".h") + vvm_ta_literal_end
  else :
    ret += vvm_literal_body + include_literal("v" + op_id + ".h") + vvm_literal_end
  return ret
