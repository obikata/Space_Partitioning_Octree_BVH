#ifndef __OCTREE_HPP__
#define __OCTREE_HPP__

#include "AABB.hpp"
#include "Vec3.hpp"
#include "OBJ_File.hpp"
#include "OctreeNode.hpp"
#include "OctreeBuilder.hpp"
// #include "OctreeTraversal.hpp"

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

            if(cubic)
            {
                float center[3];
                _obj._aabb.getCenterRef(center);
                float hs[3];
                _obj._aabb.getHalfSizeRef(hs);
                int pl         = getSubdivisionPlane(_obj._aabb);
                float hspl_min[3] {-hs[pl], -hs[pl], -hs[pl]};
                float hspl_max[3] {hs[pl], hs[pl], hs[pl]};
                vector3.add_ref(center, hspl_min, _obj._aabb._min);
                vector3.add_ref(center, hspl_max, _obj._aabb._max);
            }

            float min[3] {_obj._aabb._min[0], _obj._aabb._min[1], _obj._aabb._min[2]};
            float max[3] {_obj._aabb._max[0], _obj._aabb._max[1], _obj._aabb._max[2]};
            Math::AABB* aabb = new Math::AABB(min, max);
            _root = new OctreeNode(0, aabb);
            _octree_builder = OctreeBuilder(this);
            // _oct_traversal = OctreeTraversal(this);

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