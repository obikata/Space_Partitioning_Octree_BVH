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
        std::vector<int> IDX_triangles = std::vector<int>();
        std::vector<OctreeNode*> childs = std::vector<OctreeNode*>();

        OctreeNode() {};

        OctreeNode(int depth, Math::AABB* aabb) : _depth(depth), _aabb(aabb) {};
        
        bool isLeaf();
        
        bool isEmpty();

        bool isValid();

        int itemCount();
  
        void getNodes_recursive(std::vector<OctreeNode*>& nodes);

    };

}

#endif