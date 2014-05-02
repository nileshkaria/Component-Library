#ifndef __MINIMUM_SPANNING_TREE_
#define __MINIMUM_SPANNING_TREE_

#include <edge_weighted_graph.h>

#include <functional>
#include <queue>
#include <vector>

namespace Graph
{
  //============================================================================
  class MinimumSpanningTree
  {
  private:
    //--------------------------------------------------------------------------
    const EdgeWeightedGraph    &_rG;

    std::queue<Edge>            _kruskalMST;
    std::queue<Edge>            _primMST;

    //--------------------------------------------------------------------------
    MinimumSpanningTree(const MinimumSpanningTree &);
    MinimumSpanningTree & operator=(const MinimumSpanningTree &);

    //--------------------------------------------------------------------------
    void kruskalMST();

    //--------------------------------------------------------------------------
    void primMST();

    //--------------------------------------------------------------------------
    void visit(std::vector<bool> &rMarked, int v,
	       std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge> > &rPQ);

  public:
    //--------------------------------------------------------------------------
    MinimumSpanningTree(const EdgeWeightedGraph &rG);

    //--------------------------------------------------------------------------
    ~MinimumSpanningTree();

    //--------------------------------------------------------------------------
    const EdgeWeightedGraph & graph();

    //--------------------------------------------------------------------------
    const std::queue<Edge> & KruskalMST();

    //--------------------------------------------------------------------------
    const std::queue<Edge> & PrimMST();

  };

}

#endif
