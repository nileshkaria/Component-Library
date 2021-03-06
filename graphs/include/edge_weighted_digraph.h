#ifndef __EDGE_WEIGHTED_DIGRAPH_H__
#define __EDGE_WEIGHTED_DIGRAPH_H__

#include <directed_edge.h>
#include <igraph.h>

#include <vector>

namespace Graph
{
  //============================================================================
  class EdgeWeightedDigraph
  {
  public:
   //--------------------------------------------------------------------------
    typedef std::set<DirectedEdge>                       edge_container_t;
    typedef typename edge_container_t::iterator          edge_iterator;
    typedef typename edge_container_t::const_iterator    edge_const_iterator;

  private:
    //--------------------------------------------------------------------------
    int                                 _vertices;
    int                                 _edges;

    std::vector<edge_container_t *>     _adjList;
    
    //--------------------------------------------------------------------------
    EdgeWeightedDigraph(const EdgeWeightedDigraph &);
    EdgeWeightedDigraph & operator=(const EdgeWeightedDigraph &);

  public:
    //--------------------------------------------------------------------------
    EdgeWeightedDigraph(int v = 0);

    //--------------------------------------------------------------------------
    ~EdgeWeightedDigraph();

    //--------------------------------------------------------------------------
    void addEdge(const DirectedEdge &e);

    //--------------------------------------------------------------------------
    const edge_container_t & adjacent(int v) const;

    //--------------------------------------------------------------------------
    int vertices() const;

    //--------------------------------------------------------------------------
    int edges() const;

    //--------------------------------------------------------------------------
    void edges(edge_container_t &rEdges) const;

    //--------------------------------------------------------------------------
    std::string toString();
  };

}

#endif
