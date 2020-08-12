#ifndef __OCTREE_HPP__
#define __OCTREE_HPP__

#include <iostream>
#include <chrono>
#include <string>
#include <algorithm>    // std::find
#include <iterator>     // std::distance
#include "AABB.hpp"
#include "Vec3.hpp"
#include "OBJ_File.hpp"
#include "OctreeNode.hpp"
#include "OctreeBuilder.hpp"
// #include "OctreeTraversal.hpp"

/*
//Octree: Octants numbering
//
//             +Y                        +Z
//             |                         /
//             |                        /
//             |                       /
//             |                      
//             |       o---------------o---------------o
//             |      /               /               /|
//             |     /       3       /       7       / | 
//             |    /               /               /  | 
//             |   o---------------o---------------o   | 
//             |  /               /               /|   |
//             | /       2       /       6       / | 7 |
//             /               /               /  |   o
//             o---------------o---------------o   |  /|
//             |               |               |   | / |
//             |               |               | 6 |/  |
//             |               |               |   o   |
//             |       2       |       6       |  /|   |
//             |               |               | / | 5 |
//             |               |               |/  |   o
//             o---------------o---------------o   |  /
//             |               |               |   | /
//             |               |               | 4 |/
//             |               |               |   o
//             |       0       |       4       |  / 
//             |               |               | /  
//             |               |               |/   
//             o---------------o---------------o -----------------+X
//
//
//
*/

namespace OCT
{

    class Octree
    {
    
    public:
        // OBJ_Loader::OBJ_File _obj;
        int _NUM_ITEMS = 0;
        OBJ_Loader::OBJ_File _obj;
        Math::Vec3 vector3;
        OctreeNode* _root;
        OctreeBuilder _octree_builder;
        // Octree::OctreeTraversal _oct_traversal;

        // Octree() {};
        
        Octree(OBJ_Loader::OBJ_File& obj, bool cubic) : _obj(obj)
        {
            // std::cout << _obj._aabb._min[0] << " " << _obj._aabb._min[1] << " " << _obj._aabb._min[2] << std::endl;
            // std::cout << _obj._aabb._max[0] << " " << _obj._aabb._max[1] << " " << _obj._aabb._max[2] << std::endl;
            if(cubic)
            {
                float* center = _obj._aabb.getCenter();
                // std::cout << center[0] << " " << center[1] << " " << center[2] << std::endl;
                // float* hs = _obj._aabb.getHalfSize();
                float hs[3];
                _obj._aabb.getHalfSizeRef(hs);
                // std::cout << hs[0] << " " << hs[1] << " " << hs[2] << std::endl;
                int pl         = getSubdivisionPlane(_obj._aabb);
                // std::cout << pl << std::endl;
                // std::cout << _obj._aabb._min[0] << " " << _obj._aabb._min[1] << " " << _obj._aabb._min[2] << std::endl;
                // std::cout << _obj._aabb._max[0] << " " << _obj._aabb._max[1] << " " << _obj._aabb._max[2] << std::endl;
                // float* hspl_min, hspl_max; 
                float hspl_min[3] {-hs[pl], -hs[pl], -hs[pl]};
                float hspl_max[3] {hs[pl], hs[pl], hs[pl]};
                vector3.add_ref(center, hspl_min, _obj._aabb._min);
                vector3.add_ref(center, hspl_max, _obj._aabb._max);
                // std::cout << _obj._aabb._max[0]-_obj._aabb._min[0] << " " << _obj._aabb._max[1]-_obj._aabb._min[1] << " " << _obj._aabb._max[2]-_obj._aabb._min[2] << std::endl;
            }
            // std::cout << _obj._aabb._min[0] << " " << _obj._aabb._min[1] << " " << _obj._aabb._min[2] << std::endl;
            // std::cout << _obj._aabb._max[0] << " " << _obj._aabb._max[1] << " " << _obj._aabb._max[2] << std::endl;
            float min[3] {_obj._aabb._min[0], _obj._aabb._min[1], _obj._aabb._min[2]};
            float max[3] {_obj._aabb._max[0], _obj._aabb._max[1], _obj._aabb._max[2]};
            Math::AABB* aabb = new Math::AABB(min, max);
            _root = new OctreeNode(0, aabb);
            // std::cout << _root._aabb._min[0] << " " << _root._aabb._min[1] << " " << _root._aabb._min[2] << std::endl;
            // std::cout << _root._aabb._max[0] << " " << _root._aabb._max[1] << " " << _root._aabb._max[2] << std::endl;

            _octree_builder = OctreeBuilder(this);
            // this->_oct_traversal = OctreeTraversal(this);
        };

        int getSubdivisionPlane(Math::AABB& aabb);
 
        int getNumberOfNodes();

        std::vector<OctreeNode*> getNodes();
        
        // OctreeNode getNodeWithMaxItems();
        
        // OctreeNode getNodeWithMaxItems(std::vector<OctreeNode> nodes);
           
        void getNumberOfStoredItems();

        void getNumberOfStoredItemsWithGetNodes(const std::vector<OctreeNode*>& nodes);
        
        // int getNumberOfLeafes();

        // int getNumberOfLeafes(std::vector<OctreeNode> nodes);
                
        // int sumUpLeafDepth();

        // int sumUpLeafDepth(std::vector<OctreeNode> nodes);
        
        // int getMaxDepth();
        
        // int getMaxDepth(std::vector<OctreeNode> nodes);
        
        // float getAverageLeafDepth();
        
        // float getAverageLeafDepth(std::vector<OctreeNode> nodes);
        
        // float getAverageLeafItems();

        // float getAverageLeafItems(std::vector<OctreeNode> nodes);
        
        // bool isValid();
        
        // bool isValid(std::vector<OctreeNode> nodes);

        // // void traverse(OctreeHitResult hit);
        
        // void printStatistics();
              
    };
}

#endif