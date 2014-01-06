#ifndef __TOPOLOGICAL_SORT_H__
#define __TOPOLOGICAL_SORT_H__

#include <igraph.h>
#include <ipaths.h>

#include <vector>

namespace Graph
{
  //============================================================================
  class TopologicalSort : public virtual IPaths
  {
  private:
    //--------------------------------------------------------------------------
    std::vector<bool>    _marked;
    std::stack<int>      _reversePost;

    //--------------------------------------------------------------------------
    void dfs(const IGraph &rG, int v);

    //--------------------------------------------------------------------------
    TopologicalSort(const TopologicalSort &);
    TopologicalSort & operator=(const TopologicalSort &);

  public:
    //--------------------------------------------------------------------------
    TopologicalSort(const IGraph &rG);

    //--------------------------------------------------------------------------
    virtual ~TopologicalSort();

   //--------------------------------------------------------------------------
    virtual bool hasPathTo(int v);

    //--------------------------------------------------------------------------
    virtual void pathTo(std::stack<int> &rPath, int v = 0);

  };

}

#endif
