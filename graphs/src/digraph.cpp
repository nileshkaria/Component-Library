#include <digraph.h>

#include <algorithm>

using namespace std;

namespace Graph
{
    //==========================================================================
    //--------------------------------------------------------------------------
    Digraph::Digraph(int v) :
        _vertices        (v),
        _edges           (0),
        _adjList         (v, new set<int>()),
        _pReverseGraph   (0)
    {}

    //--------------------------------------------------------------------------
    Digraph::~Digraph()
    {
        for_each(_adjList.begin(), _adjList.end(), delete_element<set<int> *>());
        
        if(_pReverseGraph)
        {
            delete _pReverseGraph;
            _pReverseGraph = 0;
        }
    }

    //--------------------------------------------------------------------------
    void Digraph::addEdge(int v, int w)
    { 
        _adjList[v]->insert(w);

        ++_edges;
        
        if(_pReverseGraph)
        {
            delete _pReverseGraph;
            _pReverseGraph = 0;
        }
    }

    //--------------------------------------------------------------------------
    const IGraph::container_t & Digraph::adjacent(int v) const
    { 
        return *_adjList[v];
    }

    //--------------------------------------------------------------------------
    int Digraph::vertices() const
    { 
        return _vertices;        
    }

    //--------------------------------------------------------------------------
    int Digraph::edges() const
    { 
        return _edges;
    }

    //--------------------------------------------------------------------------
    const IGraph & Digraph::reverse() const
    { 
        if(!_pReverseGraph)
        {
            IGraph *pTemp = _pReverseGraph;
            
            pTemp = new Digraph(_vertices);
            
            for(size_t v = 0; v < _vertices; ++v)
            {
                for(set<int>::iterator it = _adjList[v]->begin(); it != _adjList[v]->end(); ++it)
                    pTemp->addEdge(*it, v);
            }
        }
        
        return *_pReverseGraph;
    }

    //--------------------------------------------------------------------------
    std::string Digraph::toString()
    { 
    }

}
