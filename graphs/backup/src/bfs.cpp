#include <bfs.h>

#include <limits>
#include <queue>

using namespace std;

namespace Graph
{
    //==========================================================================
    //--------------------------------------------------------------------------
    BreadthFirstPaths::BreadthFirstPaths(const IGraph &rG, int s) :
        _s(s),
        _marked(rG.vertices(), false),
        _edgeTo(rG.vertices(), numeric_limits<int>::max())
    {
        bfs(rG, s);
    }

    //--------------------------------------------------------------------------
    BreadthFirstPaths::~BreadthFirstPaths()
    {}

    //--------------------------------------------------------------------------
    void BreadthFirstPaths::bfs(const IGraph &rG, int v)
    {
        _marked[v] = true;

        queue<int> q;
        q.push(v);
                
        while(!q.empty())
        {
            v = q.front();
            q.pop();

            const IGraph::container_t & rAdjList = rG.adjacent(v);
        
            for(IGraph::const_iterator it = rAdjList.begin(); it != rAdjList.end(); ++it)
            {
                if(!_marked[*it])
                {
                    q.push(*it);
                    
                    _marked[*it] = true;
                    _edgeTo[*it] = v;
                }
                
            }
        }
    }

    //--------------------------------------------------------------------------
    bool BreadthFirstPaths::hasPathTo(int v)
    { 
        return _marked[v];
    }

    //--------------------------------------------------------------------------
    void BreadthFirstPaths::pathTo(std::stack<int> &rPath, int v)
    {
        if(!_marked[v])
            return;
        
        for(int x = v; x != _s; x = _edgeTo[x])
            rPath.push(x);
        
        rPath.push(_s);        
    }

}
