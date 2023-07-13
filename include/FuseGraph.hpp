#include "Graph.hpp"

#include <algorithm>
#include <stack>
#include <string>

namespace RIF {

extern int fgIndex;

struct SewDiffs {
  // Constructs sew shift lut for graph
  SewDiffs(Graph &_graph);

  // Utility to get sew shift difference between 2 values
  int getSewDiff(ValueBase *from, ValueBase *to);
  void calcSewDiff(ValueBase *from, ValueBase *to);
  void calcSewDiff(OperatorBase *op);

  Graph &graph;
  std::map<ValueBase *, int> lut;
};

struct FuseGraph {
  FuseGraph(Graph &graph);

  void assignLmul(SewDiffs &sd);
  void add(OperatorBase *op);
  std::vector<OperatorBase *> getOperatorsInTopologicalOrder();
  void generateGraphviz(std::ostream &os);
  void generateCCode(std::ostream &os);

  const std::string id;
  Graph &graph;
  std::set<OperatorBase *> operators;
  std::set<ValueBase *> values;
};

struct FuseGraphs {
  FuseGraphs(Graph &graph);

  std::vector<int> getFuseGraphsInTopologicalOrder();
  void generateGraphviz(std::ostream &os);
  void generateCCode(std::ostream &os, uint32_t seed = 0xdeadbeef);

  Graph &graph;
  SewDiffs sd;
  std::vector<FuseGraph> subgraphs;
  std::map<OperatorBase *, int> operatorLUT;
};

} // namespace RIF
