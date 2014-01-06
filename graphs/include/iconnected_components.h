#ifndef __ICONNECTED_COMPONENTS_H__
#define __ICONNECTED_COMPONENTS_H__

#include <igraph.h>

namespace Graph
{
  //============================================================================
  class IConnectedComponents
  {
  private:
    //--------------------------------------------------------------------------
    virtual void dfs(const IGraph &rG, int v) = 0;

  public:
    //--------------------------------------------------------------------------
    virtual ~IConnectedComponents() {}

    //--------------------------------------------------------------------------
    virtual int count() const = 0;

    //--------------------------------------------------------------------------
    virtual int id(int v) const = 0;

  };

}

#endif
