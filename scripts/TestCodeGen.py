from TestCodeGenUtils import *

def runDiffTest(options, path1, path2, filepath) :
  op_types = getOpTypesToGen(options, filepath)
  run_list = []
  for op_type in op_types:
    test_case = op_type + ".c"
    task = threading.Thread(target = runSubProcess, args = (["diff", path1 + "/" + test_case, path2 + "/" + test_case], True,))
    task.start()
    run_list.append(task)

  for task in run_list:
    task.join()

  if runSubProcess.timeout or runSubProcess.failed :
    return 1
  else :
    return 0

def main() :
  args = config()
  if not args.random_gen :
    print('Please specify the random-gen argument', file = sys.stderr)
    sys.exit(1)
  if not args.filepath :
    print('Please specify the filepath argument', file = sys.stderr)
    sys.exit(1)
  if not args.output_dir :
    print('Please specify the output-dir argument', file = sys.stderr)
    sys.exit(1)
  if not args.codegen_golden :
    print('Please specify the codegen-golden argument', file = sys.stderr)
    sys.exit(1)

  initSubProcessVars()
  generateAllCCode(args, args.random_gen, args.filepath, args.output_dir)
  initSubProcessVars()
  ret = runDiffTest(args, args.codegen_golden, args.output_dir, args.filepath)
  printSubprocessVerbose()

  return ret

if __name__ == "__main__":
  sys.exit(main())
