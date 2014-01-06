#ifndef __CONNECTED_COMPONENTS_H__
#define __CONNECTED_COMPONENTS_H__

#include <iconnected_components.h>

#include <vector>

namespace Graph
{
  //============================================================================
  class ConnectedComponents : public virtual IConnectedComponents
  {
  private:
    //--------------------------------------------------------------------------
    int                  _count;

    std::vector<bool>    _marked;
    std::vector<int>     _id;

    //--------------------------------------------------------------------------
    virtual void dfs(const IGraph &rG, int v);

    //--------------------------------------------------------------------------
    ConnectedComponents(const ConnectedComponents &);
    ConnectedComponents & operator=(const ConnectedComponents &);

  public:
    //--------------------------------------------------------------------------
    ConnectedComponents(const IGraph &rG, int s);

    //--------------------------------------------------------------------------
    virtual ~ConnectedComponents();

    //--------------------------------------------------------------------------
    virtual int count() const;

    //--------------------------------------------------------------------------
    virtual int id(int v) const;

  };

}

#endif
