// poc.cpp
/*
Proof-Of-Concept of the graph structure and how it works
*/
#include "Graph.hpp"
#include "Utils.hpp"
#include "Value.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace RIF;

Graph::Value *getInitializeValue(CustomValType type, Graph &graph,
                                 const std::string &id, const int &length) {
  auto init = graph.getNewOperator(CustomValType::Initialize, "init_" + id);
  auto value = graph.getNewValue(type, "value_" + id, length);
  init->addOutput(value);
  return value;
}

int main(int argc, char **argv) {
  RIF::parseArguments(argc, argv);

  Graph graph;

  const int length = 15;

  auto a = getInitializeValue(OneDInt32, graph, "A", length);
  auto b = getInitializeValue(OneDInt32, graph, "B", length);
  auto c = graph.getNewValue(OneDInt32, "value_C", length);

  auto op1 = graph.getNewOperator(CustomValType::AddVV32VInt32VIVI, "op1");

  op1->addInput(0, a);
  op1->addInput(1, b);
  op1->addOutput(c);

  std::ofstream GraphVizFileStream;
  GraphVizFileStream.open(RIF::GraphVizFilename,
                          std::ofstream::out | std::ofstream::trunc);
  std::ofstream CCodeFileStream;
  CCodeFileStream.open(RIF::CCodeFilename,
                       std::ofstream::out | std::ofstream::trunc);

  graph.generateData();

  graph.generateGraphViz(std::cout);
  graph.generateGraphViz(GraphVizFileStream);

  graph.generateCCode(std::cout);
  graph.generateCCode(CCodeFileStream);

  GraphVizFileStream.close();
  CCodeFileStream.close();
}