// random_gen.cpp
/*
Shows the algorithm of graph random generation.
*/
#include "Graph.hpp"
#include "RandomGenUtils.hpp"
#include "Utils.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace RIF;

static void printCommand(std::ofstream &file_stream, int argc, char *argv[]) {
  auto processArgs = [&]() {
    std::vector<std::string> args;
    for (int i = 0; i < argc; ++i) {
      args.push_back(argv[i]);
    }
    // Trim the filepath(if exists) to get the filename-only argument
    for (auto &arg : args) {
      int index = 0;
      for (index = arg.size() - 1; index >= 0; --index) {
        if (arg[index] == '/') {
          break;
        }
      }
      if (index >= 0) {
        arg = arg.substr(index + 1);
      }
    }
    return args;
  };

  file_stream << "// COMMAND: ";
  auto args = processArgs();
  for (int i = 0; i < args.size(); ++i) {
    file_stream << args[i];
    if (i != args.size() - 1) {
      file_stream << ' ';
    }
  }
  file_stream << '\n';
}

int main(int argc, char *argv[]) {
  parseArguments(argc, argv);
  uint32_t seed = InitialSeed;
  initializeRNG(seed);

  Graph graph;
  const int length = InitialLength;
  const int maxNode = NodesToGenerate;

  initializeIndex();
  initializeGraph(graph, length);
  growUntilMaxNode(graph, maxNode, length);
  defineNonInitializedValue(graph);

  std::ofstream GraphVizFileStream;
  GraphVizFileStream.open(RIF::GraphVizFilename,
                          std::ofstream::out | std::ofstream::trunc);
  std::ofstream CCodeFileStream;
  CCodeFileStream.open(RIF::CCodeFilename,
                       std::ofstream::out | std::ofstream::trunc);

  graph.generateData();

  // graph.generateGraphViz(std::cout);
  graph.generateGraphViz(GraphVizFileStream);

  printCommand(CCodeFileStream, argc, argv);
  // graph.generateCCode(std::cout);
  graph.generateCCode(CCodeFileStream);

  GraphVizFileStream.close();
  CCodeFileStream.close();
}
