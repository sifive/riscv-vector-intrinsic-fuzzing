// RandomGenUtils.hpp
/*
Utility used for random graph generation.
*/

#include "Graph.hpp"
#include <string>

namespace RIF {

extern int valueIndex;
extern int opIndex;

void initializeIndex();
std::string getNewValueName();
std::string getNewOperatorName();
void fillOperatorWithUninitializedValue(Graph &graph, Graph::Operator *op,
                                        const int length);
void initializeGraph(Graph &graph, const int length);
void growOnExistingValue(Graph &graph, const int length);
void createRandomOp(Graph &graph, const int length);
void growUntilMaxNode(Graph &graph, const int maxNode, const int length);
void defineNonInitializedValue(Graph &graph);

template <typename S> typename S::iterator select_random(S &s, size_t n) {
  n %= s.size();
  typename S::iterator it = std::begin(s);
  std::advance(it, n);
  return it;
}

} // namespace RIF
