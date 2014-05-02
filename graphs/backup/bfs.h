#ifndef __BFS_H__
#define __BFS_H__

#include <igraph.h>
#include <ipaths.h>

#include <vector>

namespace Graph
{
  //============================================================================
  //The shortest path between the source and any vertex in the connected set of 
  //s is found using bfs. This is because vertices at a fixed length away from 
  //s are all processed before the next set of vertices an additional level away.
  class BreadthFirstPaths : public virtual IPaths
  {
  private:
    //--------------------------------------------------------------------------
    int                  _s;

    std::vector<bool>    _marked;
    std::vector<int>     _edgeTo;

    //--------------------------------------------------------------------------
    void bfs(const IGraph &rG, int v);

    //--------------------------------------------------------------------------
    BreadthFirstPaths(const BreadthFirstPaths &);
    BreadthFirstPaths & operator=(const BreadthFirstPaths &);

  public:
    //--------------------------------------------------------------------------
    BreadthFirstPaths(const IGraph &rG, int s);

    //--------------------------------------------------------------------------
    virtual ~BreadthFirstPaths();

    //--------------------------------------------------------------------------
    virtual bool hasPathTo(int v);

    //--------------------------------------------------------------------------
    virtual void pathTo(std::stack<int> &rPath, int v);

  };

}

#endif
