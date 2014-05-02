#include <edge_weighted_graph.h>

#include <algorithm>
#include <iterator>

using namespace std;

namespace Graph
{
    //==========================================================================
    //--------------------------------------------------------------------------
    EdgeWeightedGraph::EdgeWeightedGraph(int v) :
        _vertices    (v),
        _edges       (0),
        _adjList     (v, new edge_container_t())
    {}

    //--------------------------------------------------------------------------
    EdgeWeightedGraph::~EdgeWeightedGraph()
    {
        for_each(_adjList.begin(), _adjList.end(), delete_element<edge_container_t *>());
    }

    //--------------------------------------------------------------------------
    //NOTE : Vertex index is NOT bound checked
    //--------------------------------------------------------------------------
    void EdgeWeightedGraph::addEdge(const Edge &e)
    { 
        int v = e.either(), w = e.other(v);
        
        _adjList[v]->insert(e);
        _adjList[w]->insert(e);

        ++_edges;
    }

    //--------------------------------------------------------------------------
    const EdgeWeightedGraph::edge_container_t & EdgeWeightedGraph::adjacent(int v) const
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
    void EdgeWeightedGraph::edges(edge_container_t &rEdges) const
    { 
        //for_each(_adjList.begin(), _adjList.end());
        
        for(int v = 0; v < _vertices; ++v)
        {
            //for_each(_adjList[v]->begin(), _adjList[v]->end(),
            //         inserter(rEdges, rEdges.begin()));

            for(edge_iterator it = _adjList[v]->begin(); it != _adjList[v]->end(); ++it)
                rEdges.insert(*it);
        }
        
    }

    //--------------------------------------------------------------------------
    std::string EdgeWeightedGraph::toString()
    { 
        return "";
    }

}
