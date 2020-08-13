#ifndef __OCTREE_HPP__
#define __OCTREE_HPP__

#include "AABB.hpp"
#include "Vec3.hpp"
#include "OBJ_File.hpp"
#include "OctreeNode.hpp"
#include "OctreeBuilder.hpp"
#include "OctreeTraversal.hpp"

namespace OCT
{

    class Octree
    {
    
    public:
        int _NUM_ITEMS = 0;
        OBJ_Loader::OBJ_File _obj;
        Math::Vec3 vector3;
        OctreeNode* _root;
        OctreeBuilder* _octree_builder;
        OctreeTraversal* _octree_traversal;

        Octree() {};
        
        Octree(OBJ_Loader::OBJ_File& obj, bool cubic) : _obj(obj), _root(nullptr), _octree_builder(nullptr), _octree_traversal(nullptr)
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
            _octree_builder = new OctreeBuilder(this);
            _octree_traversal = new OctreeTraversal(this);

        };

        int getSubdivisionPlane(Math::AABB& aabb);
 
        int getNumberOfNodes();

        std::vector<OctreeNode*> getNodes();
        
        OctreeNode* getNodeWithMaxItems();
        
        OctreeNode* getNodeWithMaxItems(const std::vector<OctreeNode*>& nodes);
           
        void getNumberOfStoredItems();

        int getNumberOfStoredItems(const std::vector<OctreeNode*>& nodes);
        
        int getNumberOfLeaves();

        int getNumberOfLeaves(const std::vector<OctreeNode*>& nodes);
                
        int sumUpLeafDepth();

        int sumUpLeafDepth(const std::vector<OctreeNode*>& nodes);
        
        int getMaxDepth();
        
        int getMaxDepth(const std::vector<OctreeNode*>& nodes);
        
        float getAverageLeafDepth();
        
        float getAverageLeafDepth(const std::vector<OctreeNode*>& nodes);
        
        float getAverageLeafItems();

        float getAverageLeafItems(const std::vector<OctreeNode*>& nodes);
        
        bool isValid();
        
        bool isValid(const std::vector<OctreeNode*>& nodes);

        // void traverse(OctreeHitResult* hit);
        
        void printStatistics();
              
    };
}

#endif