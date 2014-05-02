#include <connected_components.h>

#include <limits>

using namespace std;

namespace Graph
{
    //==========================================================================
    //--------------------------------------------------------------------------
    ConnectedComponents::ConnectedComponents(const IGraph &rG, int s) :
        _count     (0),
        _marked    (rG.vertices(), false),
        _id        (rG.vertices(), numeric_limits<int>::max())
    {
        for(size_t v = 0; v < rG.vertices(); ++v)
        {
            if(!_marked[v])
            {
                dfs(rG, v);
                ++_count;
            }
        }        
    }

    //--------------------------------------------------------------------------
    ConnectedComponents::~ConnectedComponents()
    {}

    //--------------------------------------------------------------------------
    void ConnectedComponents::dfs(const IGraph &rG, int v)
    {
        _marked[v] = true;
        _id[v]     = _count;
        
        const IGraph::container_t & rAdjList = rG.adjacent(v);
        
        for(IGraph::const_iterator it = rAdjList.begin(); it != rAdjList.end(); ++it)
        {
            if(!_marked[*it])
                dfs(rG, *it);
        }
        
    }

    //--------------------------------------------------------------------------
    int ConnectedComponents::count() const
    {
        return _count;
    }
    

    //--------------------------------------------------------------------------
    int ConnectedComponents::id(int v) const
    {
        return _id[v];
    }

}
