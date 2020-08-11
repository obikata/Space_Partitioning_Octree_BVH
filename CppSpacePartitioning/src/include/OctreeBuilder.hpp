#ifndef __OCTREEBUILDER_HPP__
#define __OCTREEBUILDER_HPP__

// #include "Octree.hpp"
// #include "OctreeNode.hpp"
#include <iostream>
#include <chrono>
#include <string>
#include <algorithm>    // std::find
#include <iterator>     // std::distance
#include <bitset>
#include "AABB.hpp"
#include "Vec3.hpp"
#include "OBJ_Face.hpp"
#include "Intersect_AABB_TRIANGLE.hpp"

namespace OCT
{

    class Octree;
    class OctreeNode;

    class OctreeBuilder {

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

    private:
        Octree* _oct;

    public:

        // most important value, small values makes deep trees, especially for big scenes!!
        Math::Vec3 vector3;
        float MIN_DEPTH_FILL_RATIO = 1.5f;
        int MAX_DEPTH = 10;

        OctreeBuilder() {};

        OctreeBuilder(Octree* oct) : _oct(oct) {};

        static std::string toStr(double a, int prec);

        void BUILD_defaultRoutine();

        //////////////////////////////////////////////////////////////////////////////
        // BUILD OCTREE
        //////////////////////////////////////////////////////////////////////////////

        // save in smallest nodes, that fully contains the triangle
        bool storeAtFirstFit(OctreeNode& ot, int idx);
        
        // make sure all triangles are in leaves
        void pushToLeafes(OctreeNode& ot);
        
        void storeInLeafes(OctreeNode& ot, int idx);
    
        void optimizeSpaceCost(OctreeNode& ot);
    
        bool positiveFillRatio(OctreeNode& ot);
    
        bool cleanUp(OctreeNode& ot);

        bool fullyContains(OctreeNode& ot, OBJ_Loader::OBJ_Face& f);

        bool overlapsWithTriangle(OctreeNode& ot, OBJ_Loader::OBJ_Face& f);

        bool assureChilds(OctreeNode& ot, int max_depth);
    
        bool saveTriangleToNode(OctreeNode& ot, int idx);

    };
}

#endif