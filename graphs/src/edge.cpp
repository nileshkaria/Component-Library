#include <edge.h>

using namespace std;

namespace Graph
{
    //==========================================================================
    //Edge is saved with lower vertex first to avoid duplicates.    
    //--------------------------------------------------------------------------
    /*
    Edge::Edge(int v, int w, double weight) :
        _v      (v < w ? v : w),
        _w      (w == _v ? v : w),
        _weight (weight)
    {}
    */

    //--------------------------------------------------------------------------
    //Allow self loops and parallel edges
    //--------------------------------------------------------------------------
    Edge::Edge(int v, int w, double weight) :
        _v      (v < w ? v : w),
        _w      (w == _v ? v : w),
        _weight (weight)
    {}

    //--------------------------------------------------------------------------
    Edge::~Edge()
    {}

    //--------------------------------------------------------------------------
    int Edge::either() const
    { 
        return _v;
    }

    //--------------------------------------------------------------------------
    int Edge::other(int v) const
    { 
        return v == _v ? _w : _v;
    }

    //--------------------------------------------------------------------------
    bool Edge::operator<(const Edge &rhs) const
    { 
        return _weight < rhs._weight ? true : false;
    }

   //--------------------------------------------------------------------------
    bool Edge::operator>(const Edge &rhs) const
    { 
        return _weight > rhs._weight ? true : false;
    }

    //--------------------------------------------------------------------------
    std::string Edge::toString()
    { 
        return "";
    }

}
