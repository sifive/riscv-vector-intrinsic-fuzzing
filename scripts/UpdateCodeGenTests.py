from TestCodeGenUtils import *
import sys

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

  output_dir = args.output_dir

  initSubProcessVars()
  ret = generateAllCCode(args, bin_path = args.random_gen, filepath = args.filepath, output_dir = args.output_dir)
  printSubprocessVerbose()

  return ret

if __name__ == "__main__":
  sys.exit(main())
