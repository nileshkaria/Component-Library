#include <edge_weighted_graph.h>

#include <algorithm>

using namespace std;

namespace Graph
{
    //==========================================================================
    //--------------------------------------------------------------------------
    EdgeWeightedGraph::EdgeWeightedGraph(int v) :
        _vertices        (v),
        _edges           (0),
        _adjList         (v, new set<Edge>())
    {}

    //--------------------------------------------------------------------------
    EdgeWeightedGraph::~EdgeWeightedGraph()
    {
        for_each(_adjList.begin(), _adjList.end(), delete_element<set<Edge> *>());
    }

    //--------------------------------------------------------------------------
    void EdgeWeightedGraph::addEdge(const Edge &e)
    { 
        int v = e.either(), w = e.other(v);
        
        _adjList[v]->insert(e);
        _adjList[w]->insert(e);

        ++_edges;
    }
aaa
    //--------------------------------------------------------------------------
    const IGraph::container_t & EdgeWeightedGraph::adjacent(int v) const
    { 
        return *_adjList[v];
    }

    //--------------------------------------------------------------------------
    int EdgeWeightedGraph::vertices() const
    { 
        return _vertices;        
    }

    //--------------------------------------------------------------------------
    int EdgeWeightedGraph::edges() const
    { 
        return _edges;
    }

    //--------------------------------------------------------------------------
    std::string EdgeWeightedGraph::toString()
    { 
    }

}
