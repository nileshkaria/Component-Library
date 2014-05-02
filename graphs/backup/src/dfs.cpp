#include <dfs.h>

#include <limits>

using namespace std;

namespace Graph
{
    //==========================================================================
    //--------------------------------------------------------------------------
    DepthFirstPaths::DepthFirstPaths(const IGraph &rG, int s) :
        _s(s),
        _marked(rG.vertices(), false),
        _edgeTo(rG.vertices(), numeric_limits<int>::max())
    {
        dfs(rG, s);
    }

    //--------------------------------------------------------------------------
    DepthFirstPaths::~DepthFirstPaths()
    {}

    //--------------------------------------------------------------------------
    void DepthFirstPaths::dfs(const IGraph &rG, int v)
    {
        _marked[v] = true;
        
        const IGraph::container_t & rAdjList = rG.adjacent(v);
        
        for(IGraph::const_iterator it = rAdjList.begin(); it != rAdjList.end(); ++it)
        {
            if(!_marked[*it])
            {
                dfs(rG, *it);
                _edgeTo[*it] = v;
            }            
        }
        
    }

    //--------------------------------------------------------------------------
    bool DepthFirstPaths::hasPathTo(int v)
    { 
        return _marked[v];
    }

    //--------------------------------------------------------------------------
    void DepthFirstPaths::pathTo(stack<int> &rPath, int v)
    {
        if(!_marked[v])
            return;
        
        for(int x = v; x != _s; x = _edgeTo[x])
            rPath.push(x);
        
        rPath.push(_s);        
    }

}
