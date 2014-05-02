#ifndef __EDGE_WEIGHTED_GRAPH_H__
#define __EDGE_WEIGHTED_GRAPH_H__

#include <edge.h>
#include <igraph.h>

#include <vector>

namespace Graph
{
  //============================================================================
  class EdgeWeightedGraph
  {
  public:
   //--------------------------------------------------------------------------
    typedef std::set<Edge>                               edge_container_t;
    typedef typename edge_container_t::iterator          edge_iterator;
    typedef typename edge_container_t::const_iterator    edge_const_iterator;

  private:
    //--------------------------------------------------------------------------
    int                                 _vertices;
    int                                 _edges;

    std::vector<edge_container_t *>     _adjList;
    
    //--------------------------------------------------------------------------
    EdgeWeightedGraph(const EdgeWeightedGraph &);
    EdgeWeightedGraph & operator=(const EdgeWeightedGraph &);

  public:
    //--------------------------------------------------------------------------
    EdgeWeightedGraph(int v = 0);

    //--------------------------------------------------------------------------
    ~EdgeWeightedGraph();

    //--------------------------------------------------------------------------
    void addEdge(const Edge &e);

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
