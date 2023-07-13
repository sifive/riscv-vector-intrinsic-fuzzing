from typing import Dict


class OpDefInfo:
  op_type     = None
  op_id       = None
  sew         = None
  type_class  = None
  op_attr     = {}
  output_type = None
  input_num   = None
  input_types = []

  def __str__(self):
    return "CUSTOM_OP_TYPE({op_type}, {op_id}, {type_class}, {op_attr}, {output_type}, {input_num}, {input_types})".format_map(self.__dict__)

# format:
# CUSTOM_OP_TYPE(OP_TYPE, OP_ID, SEW, TYPE_CLASS, OP_ATTR, OUTPUT_TYPE,
# NUM_OF_INPUTS, INPUT_TYPE(S)...)
def parse(path):
  op_def_infos = []
  with open(path, "r") as f:
    for line in f.readlines() :
      if line.startswith("CUSTOM_OP_TYPE(") == False :
        continue
      args = line[15:-2].split(",")
      args = list(map(lambda x: x.strip(), args))
      op_def_info = OpDefInfo()

      op_def_info.op_type = args[0]
      op_def_info.op_id = args[1]
      op_def_info.sew = args[2]
      op_def_info.type_class = args[3]
      op_def_info.op_attr = set(map(lambda x: x.strip(), args[4].split('|')))
      op_def_info.output_type = args[5]
      op_def_info.input_num = int(args[6])
      op_def_info.input_types = args[7:]

      op_def_infos.append(op_def_info)

  return op_def_infos
