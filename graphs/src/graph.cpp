#include <graph.h>

#include <algorithm>

using namespace std;

namespace Graph
{
    //==========================================================================
    //--------------------------------------------------------------------------
    Graph::Graph(int v) :
        _vertices   (v),
        _edges      (0),
        _adjList    (v, new set<int>())
    {}

    //--------------------------------------------------------------------------
    Graph::~Graph()
    {
        for_each(_adjList.begin(), _adjList.end(), delete_element<set<int> *>());
    }

    //--------------------------------------------------------------------------
    void Graph::addEdge(int v, int w)
    { 
        _adjList[v]->insert(w);
        _adjList[w]->insert(v);

        ++_edges;    
    }

    //--------------------------------------------------------------------------
    const IGraph::container_t & Graph::adjacent(int v) const
    { 
        return *_adjList[v];
    }

    //--------------------------------------------------------------------------
    int Graph::vertices() const
    { 
        return _vertices;        
    }

    //--------------------------------------------------------------------------
    int Graph::edges() const
    { 
        return _edges;
    }

    //--------------------------------------------------------------------------
    const IGraph & Graph::reverse() const
    { 
        return *this;        
    }

    //--------------------------------------------------------------------------
    std::string Graph::toString()
    { 
    }

}
