#include <strong_connected_components.h>
#include <topological_sort.h>

#include <limits>

using namespace std;

namespace Graph
{
    //==========================================================================
    //--------------------------------------------------------------------------
    StrongConnectedComponents::StrongConnectedComponents(const IGraph &rG, int s) :
        _count     (0),
        _marked    (rG.vertices(), false),
        _id        (rG.vertices(), numeric_limits<int>::max())
    {
        TopologicalSort ts(rG.reverse());
        
        stack<int> path;
        ts.pathTo(path);
        
        while(!path.empty())
        {
            int v = path.top();
            path.pop();
            
            if(!_marked[v])
            {
                dfs(rG, v);
                ++_count;
            }
        }        
    }

    //--------------------------------------------------------------------------
    StrongConnectedComponents::~StrongConnectedComponents()
    {}

    //--------------------------------------------------------------------------
    void StrongConnectedComponents::dfs(const IGraph &rG, int v)
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
    int StrongConnectedComponents::count() const
    {
        return _count;
    }
    

    //--------------------------------------------------------------------------
    int StrongConnectedComponents::id(int v) const
    {
        return _id[v];
    }

}
