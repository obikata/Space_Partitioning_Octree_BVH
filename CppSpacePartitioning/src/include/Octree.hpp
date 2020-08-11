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
#include "OBJ_Face.hpp"
#include "OctreeNode.hpp"
// #include "OctreeBuilder.hpp"
// #include "OctreeTraversal.hpp"
#include "Intersect_AABB_TRIANGLE.hpp"

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

    class OctreeBuilder;

    class Octree
    {
    
    public:
        Math::Vec3 vector3;
        OBJ_Loader::OBJ_File* _obj;
        OctreeNode _root;
        OctreeBuilder* _octree_builder;
        // Octree::OctreeTraversal _oct_traversal;

        Octree() {};
        
        Octree(OBJ_Loader::OBJ_File *obj, bool cubic) : _obj(obj)
        {
            Math::AABB aabb = _obj->_aabb.deep_copy();
            if(cubic)
            {
                float* center  = aabb.getCenter();
                float* hs      = aabb.getHalfSize();
                int pl         = getSubdivisionPlane(aabb);
                vector3.add_ref(center, vector3.init(-hs[pl]), aabb._min);
                vector3.add_ref(center, vector3.init(+hs[pl]), aabb._max);
            }
            _root = OctreeNode(0, aabb);
            // this->_oct_traversal = OctreeTraversal(this);
        };

        int getSubdivisionPlane(Math::AABB aabb);
 
        int getNumberOfNodes();

        std::vector<OctreeNode> getNodes();
        
        // OctreeNode getNodeWithMaxItems();
        
        // OctreeNode getNodeWithMaxItems(std::vector<OctreeNode> nodes);
           
        int getNumberOfStoredItems();

        int getNumberOfStoredItemsWithGetNodes(const std::vector<OctreeNode>& nodes);
        
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