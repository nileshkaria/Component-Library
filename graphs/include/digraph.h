#ifndef __DIGRAPH_H__
#define __DIGRAPH_H__

#include <igraph.h>

#include <vector>

namespace Graph
{
  //============================================================================
  class Digraph : public virtual IGraph
  {
  private:
    //--------------------------------------------------------------------------
    int                              _vertices;
    int                              _edges;

    std::vector<std::set<int> *>     _adjList;
    
    Digraph                         *_pReverseGraph;

    //--------------------------------------------------------------------------
    Digraph(const Digraph &);
    Digraph & operator=(const Digraph &);

  public:
    //--------------------------------------------------------------------------
    Digraph(int v = 0);

    //--------------------------------------------------------------------------
    virtual ~Digraph();

    //--------------------------------------------------------------------------
    virtual void addEdge(int v, int w);

    //--------------------------------------------------------------------------
    virtual const container_t & adjacent(int v) const;

    //--------------------------------------------------------------------------
    virtual int vertices() const;

    //--------------------------------------------------------------------------
    virtual int edges() const;

    //--------------------------------------------------------------------------
    virtual const IGraph & reverse() const;

    //--------------------------------------------------------------------------
    virtual std::string toString();
  };

}

#endif
