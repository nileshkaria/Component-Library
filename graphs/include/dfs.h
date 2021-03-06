#ifndef __DFS_H__
#define __DFS_H__

#include <igraph.h>
#include <ipaths.h>

#include <vector>

namespace Graph
{
  //============================================================================
  //In a graph G represented using the adjacency-lists representation, dfs
  //marks all vertices connected to s in time proportional to the sum of the 
  //degrees of each vertex in the connected component containing s.
  //This is because each edge is visited twice and each vertex is visited once.
  //Running time : O(E + V)
  class DepthFirstPaths : public virtual IPaths
  {
  private:
    //--------------------------------------------------------------------------
    int                  _s;

    std::vector<bool>    _marked;
    std::vector<int>     _edgeTo;

    //--------------------------------------------------------------------------
    void dfs(const IGraph &rG, int v);

    //--------------------------------------------------------------------------
    DepthFirstPaths(const DepthFirstPaths &);
    DepthFirstPaths & operator=(const DepthFirstPaths &);

  public:
    //--------------------------------------------------------------------------
    DepthFirstPaths(const IGraph &rG, int s);

    //--------------------------------------------------------------------------
    virtual ~DepthFirstPaths();

    //--------------------------------------------------------------------------
    virtual bool hasPathTo(int v);

    //--------------------------------------------------------------------------
    virtual void pathTo(std::stack<int> &rPath, int v = 0);

  };

}

#endif
