#include <edge_weighted_digraph.h>

#include <algorithm>
#include <iterator>

using namespace std;

namespace Graph
{
    //==========================================================================
    //--------------------------------------------------------------------------
    EdgeWeightedDigraph::EdgeWeightedDigraph(int v) :
        _vertices    (v),
        _edges       (0),
        _adjList     (v, new edge_container_t())
    {}

    //--------------------------------------------------------------------------
    EdgeWeightedDigraph::~EdgeWeightedDigraph()
    {
        for_each(_adjList.begin(), _adjList.end(), delete_element<edge_container_t *>());
    }

    //--------------------------------------------------------------------------
    //NOTE : Vertex index is NOT bound checked
    //--------------------------------------------------------------------------
    void EdgeWeightedDigraph::addEdge(const DirectedEdge &e)
    { 
        int v = e.from();

        _adjList[v]->insert(e);

        ++_edges;
    }

    //--------------------------------------------------------------------------
    const EdgeWeightedDigraph::edge_container_t & EdgeWeightedDigraph::adjacent(int v) const
    { 
        return *_adjList[v];
    }

    //--------------------------------------------------------------------------
    int EdgeWeightedDigraph::vertices() const
    { 
        return _vertices;        
    }

    //--------------------------------------------------------------------------
    int EdgeWeightedDigraph::edges() const
    { 
        return _edges;
    }

    //--------------------------------------------------------------------------
    void EdgeWeightedDigraph::edges(edge_container_t &rEdges) const
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
    std::string EdgeWeightedDigraph::toString()
    { 
        return "";
    }

}
