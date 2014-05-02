#include <directed_edge.h>

using namespace std;

namespace Graph
{
    //==========================================================================
    //DirectedEdge is saved with lower vertex first to avoid duplicates.    
    //--------------------------------------------------------------------------
    /*
    DirectedEdge::DirectedEdge(int v, int w, double weight) :
        _v      (v < w ? v : w),
        _w      (w == _v ? v : w),
        _weight (weight)
    {}
    */

    //--------------------------------------------------------------------------
    //Allow self loops and parallel edges
    //--------------------------------------------------------------------------
    DirectedEdge::DirectedEdge(int v, int w, double weight) :
        _v      (v < w ? v : w),
        _w      (w == _v ? v : w),
        _weight (weight)
    {}

    //--------------------------------------------------------------------------
    DirectedEdge::~DirectedEdge()
    {}

    //--------------------------------------------------------------------------
    int DirectedEdge::from() const
    { 
        return _v;
    }

    //--------------------------------------------------------------------------
    int DirectedEdge::to() const
    { 
        return _w;
    }

    //--------------------------------------------------------------------------
    bool DirectedEdge::operator<(const DirectedEdge &rhs) const
    { 
        return _weight < rhs._weight ? true : false;
    }

   //--------------------------------------------------------------------------
    bool DirectedEdge::operator>(const DirectedEdge &rhs) const
    { 
        return _weight > rhs._weight ? true : false;
    }

    //--------------------------------------------------------------------------
    std::string DirectedEdge::toString()
    { 
        return "";
    }

}
