#ifndef __OCTREEBUILDER_HPP__
#define __OCTREEBUILDER_HPP__

#include "Octree.hpp"

namespace OCT
{

    class OctreeBuilder: public Octree {

    //  public static float OCTANT_POS[][] =
    //  {
    //    //i&4, i&2, i&1
    //    { 0, 0, 0 },    // [0] - 000
    //    { 0, 0, 1 },    // [1] - 001
    //    { 0, 1, 0 },    // [2] - 010
    //    { 0, 1, 1 },    // [3] - 011
    //    
    //    { 1, 0, 0 },    // [4] - 100
    //    { 1, 0, 1 },    // [5] - 101
    //    { 1, 1, 0 },    // [6] - 110
    //    { 1, 1, 1 },    // [7] - 111
    //  };

    public:

        // most important value, small values makes deep trees, especially for big scenes!!
        float MIN_DEPTH_FILL_RATIO = 1.5f;
        int MAX_DEPTH = 10;

        OctreeBuilder()
        {
            initOctreeBuilder();
        };

        void initOctreeBuilder()
        {
            _octree_builder = this;
        }

        static std::string toStr(double a, int prec);

        void BUILD_defaultRoutine();

        //////////////////////////////////////////////////////////////////////////////
        // BUILD OCTREE
        //////////////////////////////////////////////////////////////////////////////

        // save in smallest nodes, that fully contains the triangle
        bool storeAtFirstFit(OctreeNode ot, int idx);
        
        // make sure all triangles are in leaves
        void pushToLeafes(OctreeNode ot);
        
        void storeInLeafes(OctreeNode ot, int idx);
    
        void optimizeSpaceCost(OctreeNode ot);
    
        bool positiveFillRatio(OctreeNode ot);
    
        bool cleanUp(OctreeNode ot);

        bool fullyContains(OctreeNode ot, OBJ_Loader::OBJ_Face f);

        bool overlapsWithTriangle(OctreeNode ot, OBJ_Loader::OBJ_Face f);

    private:
        Math::Vec3 vector3;

        bool assureChilds(OctreeNode ot, int max_depth)
        {
            if( ot._depth >= max_depth)
            {
                return false;
            }

            if( ot.isLeaf() )
            {
            
                ot.childs = std::vector<OctreeNode>(8);
                float* half_size = ot._aabb.getHalfSize();
                int child_depth = ot._depth+1;

                for(int i = 0; i < ot.childs.size(); i++)
                {
                    float ch_bb_min[3] = { ot._aabb._min[0] + ( ( i&4 > 0 ) ? half_size[0] : 0 ) ,
                                           ot._aabb._min[1] + ( ( i&2 > 0 ) ? half_size[1] : 0 ) ,
                                           ot._aabb._min[2] + ( ( i&1 > 0 ) ? half_size[2] : 0 ) };

                    static float* ch_bb_max = vector3.add_new(ch_bb_min, half_size);
                    ot.childs[i] = OctreeNode(child_depth, Math::AABB(ch_bb_min, ch_bb_max));
                }
            }
            return true;
        }
    
        bool saveTriangleToNode(OctreeNode ot, int idx)
        {   
            std::vector<int>::iterator itr = std::find(ot.IDX_triangles.begin(), ot.IDX_triangles.end(), idx);
            int index = std::distance( ot.IDX_triangles.begin(), itr);
            if( ot.IDX_triangles[index] == idx )
            { // just in case
                ot.IDX_triangles.push_back(idx);
            }
            return true;
        }

    };
}

#endif