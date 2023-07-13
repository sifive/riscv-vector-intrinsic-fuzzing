import OpDefParser

import argparse
import os
import subprocess
import threading
import sys
import pathlib


class Color :
	HEADER = '\033[95m'
	OKBLUE = '\033[94m'
	OKCYAN = '\033[96m'
	OKGREEN = '\033[92m'
	WARNING = '\033[93m'
	FAIL = '\033[91m'
	ENDC = '\033[0m'
	BOLD = '\033[1m'
	UNDERLINE = '\033[4m'

def config() :
  parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawTextHelpFormatter)
  parser.add_argument('--random-gen', help='Path to random-gen binary')
  parser.add_argument('--filepath', help='Path to CustomOperator.def')
  parser.add_argument('--output-dir', help='Path to output directory')
  parser.add_argument('--codegen-golden', help='Path to codegen golden directory')
  parser.add_argument('--has-policy', help='Enable policy if set', action='store_true')
  args = parser.parse_args()

  return args

def parseCustomOperatorDefinitions(filepath) :
  return OpDefParser.parse(filepath)


def policyFilter(options, op_def) :
  policy_attrs = ["TailAgnostic", "TailUndisturbed", "MaskAgnostic", "MaskUndisturbed"]
  valid = True
  if not options.has_policy:
    for attr in op_def.op_attr:
      if attr in policy_attrs:
        valid = False
  return valid

# The getOpTypesToGen function extracts the effective op_types following
# the rules below:
#   1. For load and store operations(Simply those that in exceptions list),
#      it collects the op_type contains either '32V32' or '32' depending on
#      whether it's indexed load/store or not.
#   2. Otherwise, it collects the operations with uniqie op_id with non-masked
#      version, masked version as well as policies(ta, tu, tama, tamu, tuma, tumu)
exceptions = ["Vle", "Vse", "Vloxei", "Vluxei", "Vsoxei", "Vsuxei", "Vlse", "Vsse"]
def getOpTypesToGen(options, filepath, exceptions = exceptions) :
  filters = [policyFilter]
  op_types = []
  count = dict()
  op_defs = parseCustomOperatorDefinitions(filepath)
  for op_def in op_defs :
    valid = True
    for filter in filters:
      if not filter(options, op_def):
        valid = False
    if not valid:
      continue

    op_type = op_def.op_type
    op_id = op_def.op_id
    for e in exceptions :
      if op_type.startswith(e) :
        if op_type.startswith(e + "32V32"):
          op_types.append(op_type)
        elif op_type.startswith(e + "32") and not (op_type.startswith("Vloxei") or
                                                   op_type.startswith("Vluxei") or
                                                   op_type.startswith("Vsoxei") or
                                                   op_type.startswith("Vsuxei")) :
          op_types.append(op_type)
        count[op_id] = 1

    if op_type.endswith("_m") :
      op_id = op_id + "m"

    if op_type.endswith("TA") :
      op_id = op_id + "ta"
    elif op_type.endswith("TU") :
      op_id = op_id + "tu"
    elif op_type.endswith("TAMA") :
      op_id = op_id + "tama"
    elif op_type.endswith("TAMU") :
      op_id = op_id + "tamu"
    elif op_type.endswith("TUMA") :
      op_id = op_id + "tuma"
    elif op_type.endswith("TUMU") :
      op_id = op_id + "tumu"
    elif op_type.endswith("MA") :
      op_id = op_id + "ma"
    elif op_type.endswith("MU") :
      op_id = op_id + "mu"
    elif op_type.endswith("TAM") :
      op_id = op_id + "tam"
    elif op_type.endswith("TUM") :
      op_id = op_id + "tum"

    if op_id in count :
      continue

    op_types.append(op_type)
    count[op_id] = 1

  return op_types


def runSubProcess(args, testing = False) :
  output = ""
  ret = -1
  if testing :
    output = "Running " + args[2] + ": "
  runSubProcess.total += 1
  try:
    ret = subprocess.check_call(args, stdout = subprocess.DEVNULL, stderr = subprocess.DEVNULL, timeout = 100)
    if not ret :
      runSubProcess.passed += 1
    else :
      runSubProcess.failed += 1
      failedCases.append(args[2])
  except subprocess.TimeoutExpired:
    runSubProcess.timeout += 1
    runSubProcess.timeoutCases.append(args[2])
  except:
    runSubProcess.failed += 1
    runSubProcess.failedCases.append(args[2])
  if testing :
    if not ret :
      print(output, f"{Color.OKGREEN}PASS{Color.ENDC}")
    else :
      print(output, f"{Color.FAIL}FAIL{Color.ENDC}")

def initSubProcessVars() :
  runSubProcess.total = 0
  runSubProcess.timeout = 0
  runSubProcess.timeoutCases = []
  runSubProcess.passed = 0
  runSubProcess.failed = 0
  runSubProcess.failedCases = []

def generateAllCCode(options, bin_path, filepath, output_dir, data_len = "7") :
  print("Generating C Code", flush = True)
  if not os.path.exists(output_dir) :
    try :
      os.makedirs(output_dir)
    except :
      print("Failed on makedirs", file=sys.stderr)
      sys.exit(1)
  op_types = getOpTypesToGen(options, filepath)

  run_list = []
  for op_type in op_types:
    args = [bin_path, "-r", op_type, "-n", "1", "-l", data_len, "--has-ta", "--has-ma", "-c", output_dir + "/" + op_type + ".c"]
    if options.has_policy:
      args.append("--has-policy")
    task = threading.Thread(target=runSubProcess, args=(args,))
    task.start()
    run_list.append(task)

  for task in run_list:
    task.join()

  if runSubProcess.timeout or runSubProcess.failed :
    return 1
  else :
    return 0

def printSubprocessVerbose(runSubProcess = runSubProcess) :
  total_tasks = runSubProcess.total
  passed_tasks = runSubProcess.passed
  timeout_tasks = runSubProcess.timeout
  failed_tasks = runSubProcess.failed
  timeout_list = runSubProcess.timeoutCases
  failed_list = runSubProcess.failedCases

  print(f"{Color.OKGREEN}Total Cases{Color.ENDC}: ", total_tasks)
  print(f"{Color.OKGREEN}Pass{Color.ENDC}: ", passed_tasks)
  if timeout_tasks :
    print(f"{Color.FAIL}Timeout{Color.ENDC}: ", timeout_tasks)
  if failed_tasks :
    print(f"{Color.FAIL}Fail{Color.ENDC}: ", failed_tasks)
  if timeout_list != [] :
    print(f"{Color.FAIL}Timeout Cases{Color.ENDC}: ", timeout_list)
  if failed_list != [] :
    print(f"{Color.FAIL}Failed Cases{Color.ENDC}: ", failed_list)
