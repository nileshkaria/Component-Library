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
  private:
    //--------------------------------------------------------------------------
    int                              _vertices;
    int                              _edges;

    std::vector<std::set<Edge> *>     _adjList;
    
    //--------------------------------------------------------------------------
    EdgeWeightedGraph(const EdgeWeightedGraph &);
    EdgeWeightedGraph & operator=(const EdgeWeightedGraph &);

  public:
   //--------------------------------------------------------------------------
    typedef std::set<int>                           edge_container_t;
    typedef typename container_t::iterator          edge_iterator;
    typedef typename container_t::const_iterator    edge_const_iterator;

  public:
    //--------------------------------------------------------------------------
    EdgeWeightedGraph(int v = 0);

    //--------------------------------------------------------------------------
    virtual ~EdgeWeightedGraph();

    //--------------------------------------------------------------------------
    virtual void addEdge(const Edge &e);

    //--------------------------------------------------------------------------
    virtual const edge_container_t & adjacent(int v) const;

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
