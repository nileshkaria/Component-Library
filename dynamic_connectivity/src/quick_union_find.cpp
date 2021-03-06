#include <quick_union_find.h>

#include <algorithm>

using namespace std;

namespace UnionFind
{
    //==========================================================================
    //--------------------------------------------------------------------------
    QuickUnionFind::QuickUnionFind(int n) :
        _id      (n, 0),
        _size    (n, 1)
    {
        for(int i = 1; i < n; ++i)
            _id[i] = i;
    }

    //--------------------------------------------------------------------------
    QuickUnionFind::~QuickUnionFind()
    {
    }

    //--------------------------------------------------------------------------
    int QuickUnionFind::root(int i)
    {
        while(i != _id[i])
        {
            //Point to the grandparent while looking up root.
            //This will halve the length of lookup branch.
            //Complexity of find is reduced to lg*n.
            _id[i] = _id[_id[i]];
            
            i = _id[i];
        }

        return i;
    }

    //--------------------------------------------------------------------------
    bool QuickUnionFind::connected(int p, int q)
    {
        return root(p) == root(q);
    }

    //If the roots are different then point the root of the smaller
    //tree to the root of the larger tree. The depth of the tree with
    //more nodes will increase by one if the size of the tree
    //doubles. This ensures that the total depth will not exceed lgn.
    //--------------------------------------------------------------------------
    void QuickUnionFind::make_union(int p, int q)
    { 
        int i = root(p);
        int j = root(q);
        
        if(i == j) 
            return;
        
        if(_size[i] < _size[j])
        {
            _id[i]    = j;
            _size[i] += _size[j];
        }
        else
        {
            _id[j]    = i;
            _size[j] += _size[i];
        }
        
    }

}

int main()
{
    return 0;
}
