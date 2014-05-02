#include <bipartite.h>

#include <limits>

using namespace std;

namespace Graph
{
    //==========================================================================
    //--------------------------------------------------------------------------
    Bipartite::Bipartite(const IGraph &rG) :
        _bipartite (false),
        _marked    (rG.vertices(), false),
        _color     (rG.vertices(), false)
    {
        _bipartite = isBipartite(rG, 0, true);
    }

    //--------------------------------------------------------------------------
    Bipartite::~Bipartite()
    {}

    //--------------------------------------------------------------------------
    bool Bipartite::isBipartite(const IGraph &rG, int v, bool c)
    {
        _marked[v] = true;
        _color[v]  = c;
        
        const IGraph::container_t & rAdjList = rG.adjacent(v);
        
        for(IGraph::const_iterator it = rAdjList.begin(); it != rAdjList.end(); ++it)
        {
            if(!_marked[*it])
                return isBipartite(rG, *it, !c);
            else
            {
                //Previously visited, adjacent vertex of same color
                if(_color[v] == _color[*it])
                    return false;
            }
        }

        return true;
    }

    //--------------------------------------------------------------------------
    bool Bipartite::isBipartite()
    {
        return _bipartite;
    }
    
}
