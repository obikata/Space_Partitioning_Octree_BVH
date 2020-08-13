#ifndef __OCTREEBUILDER_HPP__
#define __OCTREEBUILDER_HPP__

// #include <iostream>
#include <chrono>
#include <algorithm>
#include <iterator>
#include "AABB.hpp"
#include "Vec3.hpp"
#include "OBJ_Face.hpp"
#include "Intersect_AABB_TRIANGLE.hpp"

namespace OCT
{

    class Octree;
    class OctreeNode;

    class OctreeBuilder {

    private:

        static std::string toStr(double a, int prec)
        {
        std::ostringstream text;
        text.precision(prec);
        text << std::fixed << a;
        return text.str();
        }

    public:

        Octree* _oct;
        Math::Vec3 vector3;
        float MIN_DEPTH_FILL_RATIO = 1.5f; // most important value, small values makes deep trees, especially for big scenes
        int MAX_DEPTH = 10;

        OctreeBuilder() {};

        OctreeBuilder(Octree* oct) : _oct(oct) {};

        void BUILD_defaultRoutine();

        bool storeAtFirstFit(OctreeNode* ot, int idx);
        
        void pushToLeaves(OctreeNode* ot);
        
        void storeInLeaves(OctreeNode* ot, int idx);
    
        void optimizeSpaceCost(OctreeNode* ot);
    
        bool positiveFillRatio(OctreeNode* ot);
    
        bool cleanUp(OctreeNode* ot);

        bool fullyContains(OctreeNode* ot, OBJ_Loader::OBJ_Face& f);

        bool overlapsWithTriangle(OctreeNode* ot, OBJ_Loader::OBJ_Face& f);

        bool assureChilds(OctreeNode* ot, int max_depth);
    
        bool saveTriangleToNode(OctreeNode* ot, int idx);

    };
}

#endif