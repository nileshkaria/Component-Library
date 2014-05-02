#ifndef __IGRAPH_H__
#define __IGRAPH_H__

#include <set>
#include <string>

namespace Graph
{
  //============================================================================
  //----------------------------------------------------------------------------
  template <typename T>
    struct delete_element
    {
      void operator()(T t) const
      {
        delete t;
      }
    };

  //============================================================================
  class IGraph
  {
  public:
    //--------------------------------------------------------------------------
    typedef std::set<int>                           container_t;
    typedef typename container_t::iterator          iterator;
    typedef typename container_t::const_iterator    const_iterator;

  public:
    //--------------------------------------------------------------------------
    virtual ~IGraph() {}

    //--------------------------------------------------------------------------
    virtual void addEdge(int v, int w) = 0;

    //--------------------------------------------------------------------------
    virtual const container_t & adjacent(int v) const = 0;

    //--------------------------------------------------------------------------
    virtual int vertices() const = 0;

    //--------------------------------------------------------------------------
    virtual int edges() const = 0;

    //--------------------------------------------------------------------------
    virtual const IGraph & reverse() const = 0;

    //--------------------------------------------------------------------------
    virtual std::string toString() = 0;
  };

}

#endif
