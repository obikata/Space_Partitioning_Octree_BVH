#ifndef __ASCV_OCTREE_TRAVERSAL_DATA_HPP__
#define __ASCV_OCTREE_TRAVERSAL_DATA_HPP__

#include "../Vec3.hpp"
#include "../Ray3D.hpp"
#include "ascv_octree.hpp"

namespace ascv 
{

    class OctreeTraversalData
    {
        private:

        public:

            // OctreeTraversalData* prev;
            Octant* _node;
            float* _t0;
            float* _t1;
            
            OctreeTraversalData(Octant* node, float* t0, float* t1) : _node(node), _t0(t0), _t1(t1) {};
            
            OctreeTraversalData(Octant* node, float t0x, float t0y, float t0z, float t1x, float t1y, float t1z) : _node(node), _t0(new float[3] {t0x, t0y, t0z}), _t1(new float[3] {t1x, t1y, t1z}) {};
            
            float* tm()
            {
                return Math::Vec3::scale_new( Math::Vec3::add_new(_t0, _t1), 0.5f);
            }

            float tNear()
            {
                return Math::Vec3::maxComponent(_t0);
            }

            float tFar ()
            {
                return Math::Vec3::minComponent(_t1);
            }
    };
   
}

#endif