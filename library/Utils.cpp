#include "Utils.hpp"

#include <cstdint>
#include <cstring>
#include <iostream>
#include <ostream>
#include <random>
#include <sstream>
#include <string>

#include <argp.h>

using namespace std;

namespace RIF {

std::string GraphVizFilename;
std::string CCodeFilename;
std::string InitialRootName = "AddVV32VInt32VIVI";
uint32_t InitialLength = 500;
uint32_t InitialSeed = 0xdeadbeef;
uint32_t NodesToGenerate = 5;
std::mt19937 rng;
bool VerboseMode = false;
std::string TargetArch = "rv64gcv";
std::string VerificationMode = "long";
bool VerifyTailPolicy = true;
bool VerifyMaskPolicy = true;
bool HasPolicy = false;
bool HasTA = false;
bool HasMA = false;
static char *Progname = nullptr;

/* The options we understand. */
static struct argp_option options[] = {
    {"verbose", 'v', 0, 0, "Produce verbose output"},
    {"disable-tail-policy", 't', "VERIFY_TAIL", 0,
     "Disable verification for tail policy"},
    {"disable-mask-policy", 'a', "VERIFY_MASK", 0,
     "Disable verification for mask policy"},
    {"code", 'c', "FILE", 0, "C code file, default filename: 'output.c'"},
    {"dot", 'd', "FILE", 0,
     "Graphviz visualization file, default filename is 'output.dot'"},
    {"length", 'l', "DATA_LENGTH", 0,
     "Data length for the initial node (root)"},
    {"march", 'm', "ARCH_STRING", 0,
     "Arch string for testing, default is rv64gcv"},
    {"seed", 's', "RANDOM_SEED", 0,
     "Seed for random number generator, default seed is '0xdeadbeef'"},
    {"root", 'r', "OPERATOR_ENUM", 0,
     "Initial node for the graph generation, default root is 'AddVV32'"},
    {"nodes-to-gen", 'n', "NODES_TO_GEN", 0,
     "The number of nodes to generate for the graph."},
    {"verification-mode", 'f', "VERIFICATION_MODE", 0,
     "'short' lets RIF generate verification only to result nodes, 'long' lets "
     "RIF generate verification to all nodes. Default to 'long'."},
    {"has-policy", 'p', 0, 0,
     "The flag that specifies whether to enable policy intrinsics or not"},
    {"has-ta", 'z', 0, 0,
     "The flag that specifies whether to enable ta intrinsics or not"},
    {"has-ma", 'x', 0, 0,
     "The flag that specifies whether to enable ma intrinsics or not"},
    {0, 'h', 0, 0, "Give this help list"},
    {0}};

static error_t parse_opt(int key, char *arg, struct argp_state *state);
// Our argp parser.
static struct argp argp = {options, parse_opt, "", ""};

// Parse a single option.
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  switch (key) {
  case 'v':
    VerboseMode = true;
    break;
  case 't':
    VerifyTailPolicy = false;
    break;
  case 'a':
    VerifyMaskPolicy = false;
    break;
  case 'p':
    HasPolicy = true;
    break;
  case 'z':
    HasTA = true;
    break;
  case 'x':
    HasMA = true;
    break;
  case 'c':
    CCodeFilename = arg;
    break;
  case 'd':
    GraphVizFilename = arg;
    break;
  case 'l':
    InitialLength = std::stoul(std::string(arg), nullptr, 10);
  case 'm':
    // TODO: Verify the arch string and parse the capability.
    TargetArch = arg;
    break;
  case 's':
    InitialSeed = std::stoul(std::string(arg), nullptr, 16);
    break;
  case 'r':
    InitialRootName = arg;
    break;
  case 'n':
    NodesToGenerate = std::stoul(std::string(arg), nullptr, 10);
    break;
  case 'f':
    VerificationMode = std::string(arg);
  case 'h':
    argp_help(&argp, stdout, ARGP_HELP_STD_HELP, Progname);
    exit(0);
    break;

  case ARGP_KEY_ARG:
    // Too many arguments.
    if (state->arg_num >= 0) {
      std::cerr << "Receive unknown argument " << arg << "\n";
      argp_usage(state);
    }
    break;

  case ARGP_KEY_END:
    break;

  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

void parseArguments(int argc, char **argv) {
  Progname = argv[0];
  // default filename
  GraphVizFilename = "output.dot";
  CCodeFilename = "output.c";

  // Parse our arguments; every option seen by parse_opt will
  // be reflected in arguments.
  argp_parse(&argp, argc, argv, 0, 0, nullptr);
}

void initializeRNG(uint32_t seed) { rng = std::mt19937(seed); }

// Simple linear transformation from generator 'rng'
template <>
float16_t getRandomNumber(int minValue, int maxValue, uint64_t *raw) {
  uint64_t x = getRandomNumber<uint64_t>(minValue, maxValue, nullptr);
  float16_t ret = ui64_to_f16(x);
  if (raw != nullptr)
    *raw = ret.v;
  return ret;
}
template <>
float32_t getRandomNumber(int minValue, int maxValue, uint64_t *raw) {
  uint64_t x = getRandomNumber<uint64_t>(minValue, maxValue, nullptr);
  float32_t ret = ui64_to_f32(x);
  if (raw != nullptr)
    *raw = ret.v;
  return ret;
}
template <>
float64_t getRandomNumber(int minValue, int maxValue, uint64_t *raw) {
  uint64_t x = getRandomNumber<uint64_t>(minValue, maxValue, nullptr);
  float64_t ret = ui64_to_f64(x);
  if (raw != nullptr)
    *raw = ret.v;
  return ret;
}

} // namespace RIF
