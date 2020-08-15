#ifndef __OCTREENODE_HPP__
#define __OCTREENODE_HPP__

#include "AABB.hpp"

namespace OCT
{

    //////////////////////////////////////////////////////////////////////////////
    // GET ALL NODES IN A LIST, ... no recursion used, but a simple linked list
    //////////////////////////////////////////////////////////////////////////////

    class OctreeNode
    {
        
    public:

        int _depth;
        Math::AABB* _aabb;
        std::vector<int> IDX_triangles;
        std::vector<OctreeNode*> childs;
        int _nodeIdx = 0;

        OctreeNode() {};

        OctreeNode(int nodeIdx, int depth, Math::AABB* aabb) :  _nodeIdx(nodeIdx), _depth(depth), _aabb(aabb) {};
        
        bool isLeaf();
        
        bool isEmpty();

        bool isValid();

        int itemCount();
  
        void getNodes_recursive(std::vector<OctreeNode*>& nodes);

    };

}

#endif