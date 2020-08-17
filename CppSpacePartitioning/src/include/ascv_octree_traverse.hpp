#ifndef __ASCV_OCTREE_TRAVERSE_HPP__
#define __ASCV_OCTREE_TRAVERSE_HPP__

#include "Ray3D.hpp"
#include "ascv_build_octree_data.hpp"
#include "ascv_octant.hpp"
#include "ascv_octree_traversal_data.hpp"
#include "ascv_octree_hit_result.hpp"

namespace ascv
{

    void OctreeTraverse(Octant* octants, Math::Ray3D* ray, OctreeHitResult* hit_result);

}

#endif