#ifndef __STRONG_CONNECTED_COMPONENTS_H__
#define __STRONG_CONNECTED_COMPONENTS_H__

#include <iconnected_components.h>

#include <vector>

namespace Graph
{
  //============================================================================
  class StrongConnectedComponents : public virtual IConnectedComponents
  {
  private:
    //--------------------------------------------------------------------------
    int                  _count;

    std::vector<bool>    _marked;
    std::vector<int>     _id;

    //--------------------------------------------------------------------------
    virtual void dfs(const IGraph &rG, int v);

    //--------------------------------------------------------------------------
    StrongConnectedComponents(const StrongConnectedComponents &);
    StrongConnectedComponents & operator=(const StrongConnectedComponents &);

  public:
    //--------------------------------------------------------------------------
    StrongConnectedComponents(const IGraph &rG, int s);

    //--------------------------------------------------------------------------
    virtual ~StrongConnectedComponents();

    //--------------------------------------------------------------------------
    virtual int count() const;

    //--------------------------------------------------------------------------
    virtual int id(int v) const;

  };

}

#endif
