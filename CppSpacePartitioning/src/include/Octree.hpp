#ifndef __OCTREE_HPP__
#define __OCTREE_HPP__

#include "AABB.hpp"
#include "Vec3.hpp"
#include "OBJ_File.hpp"
// #include "OctreeNode.hpp"
// #include "OctreeBuilder.hpp"
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

namespace Octree
{
    class Octree

    {

    public:
        Math::Vec3 vector3;
        OBJ_Loader::OBJ_File _obj;
        Math::AABB _aabb;
        // OctreeNode _root;
        // Octree::OctreeBuilder _oct_builder;
        // Octree::OctreeTraversal _oct_traversal;

        Octree(OBJ_Loader::OBJ_File obj, bool cubic) : _obj(obj)
        {
            std::cout << "TEST" << std::endl;
            Math::AABB aabb = _obj._aabb.copy();
            if(cubic)
            {
                float* center  = aabb.getCenter();
                float* hs      = aabb.getHalfSize();
                // int pl         = getSubdivisionPlane(aabb);
                // vector3.add_ref(center, vector3.init(-hs[pl]), aabb._min);
                // vector3.add_ref(center, vector3.init(+hs[pl]), aabb._max);
            }
            // this->_root = OctreeNode(0, aabb);
            // this->_oct_builder = OctreeBuilder(this);
            // this->_oct_traversal = OctreeTraversal(this);

        };

        // int getSubdivisionPlane(Math::AABB aabb);
 
        // void BUILD_defaultRoutine();

        // int getNumberOfNodes();

        // std::vector<OctreeNode> getNodes();
        
        // OctreeNode getNodeWithMaxItems();
        
        // OctreeNode getNodeWithMaxItems(std::vector<OctreeNode> nodes);
           
        // int getNumberOfStoredItems();

        // int getNumberOfStoredItems(std::vector<OctreeNode> nodes);
        
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