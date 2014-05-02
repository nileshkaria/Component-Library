#ifndef __BIPARTITE_H__
#define __BIPARTITE_H__

#include <igraph.h>

#include <vector>

namespace Graph
{
  //============================================================================
  //Linear time DFS based algorithm to find if the graph is bipartite, ie. each
  //vertex is connected to a node of the opposite color.
  //Running time: O(E + V)
  class Bipartite
  {
  private:
    //--------------------------------------------------------------------------
    bool                 _bipartite;

    std::vector<bool>    _marked;
    std::vector<bool>    _color;

    //--------------------------------------------------------------------------
    bool isBipartite(const IGraph &rG, int v, bool c);

    //--------------------------------------------------------------------------
    Bipartite(const Bipartite &);
    Bipartite & operator=(const Bipartite &);

  public:
    //--------------------------------------------------------------------------
    Bipartite(const IGraph &rG);

    //--------------------------------------------------------------------------
    ~Bipartite();

    //--------------------------------------------------------------------------
    bool isBipartite();

  };

}

#endif
