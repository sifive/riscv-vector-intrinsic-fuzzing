// fused_gen_poc.cpp
/*
Shows the algorithm of operator fusion and how it is done from receiving a Graph
to code generation.
*/
#include "FuseGraph.hpp"
#include "Graph.hpp"
#include "RandomGenUtils.hpp"
#include "Utils.hpp"

#include <fstream>

using namespace RIF;

int main(int argc, char *argv[]) {
  parseArguments(argc, argv);
  // Note: Hard code verification mode to short in fused graph generation
  VerificationMode = "short";
  uint32_t seed = InitialSeed;
  initializeRNG(seed);

  Graph graph;
  const int length = InitialLength;
  const int maxNode = NodesToGenerate;

  initializeIndex();
  initializeGraph(graph, length);
  growUntilMaxNode(graph, maxNode, length);
  defineNonInitializedValue(graph);
  graph.generateData();

  std::ofstream GraphVizFileStream;
  GraphVizFileStream.open(RIF::GraphVizFilename,
                          std::ofstream::out | std::ofstream::trunc);
  std::ofstream CCodeFileStream;
  CCodeFileStream.open(RIF::CCodeFilename,
                       std::ofstream::out | std::ofstream::trunc);

  FuseGraphs fgs(graph);

  fgs.generateGraphviz(GraphVizFileStream);
  fgs.generateCCode(CCodeFileStream);
}
