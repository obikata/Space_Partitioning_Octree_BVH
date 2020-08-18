
#include "ascv_octree_traversal.hpp"

namespace ascv
{
    
    void ascv_octree_traversal::Traverse(Octant* octants, Math::Ray3D* ray, OctreeHitResult* hit_result, int IDX_SHFT)
    {
        if( hit_result == nullptr )
        {
            return;
        }

        Math::Ray3D* ray_mod = hit_result->_ray->copy();  // copy ray
        if(mirrorComponent(octants[0].aabb_min, octants[0].aabb_max, ray_mod, 0)) IDX_SHFT |= 4;
        if(mirrorComponent(octants[0].aabb_min, octants[0].aabb_max, ray_mod, 1)) IDX_SHFT |= 2;
        if(mirrorComponent(octants[0].aabb_min, octants[0].aabb_max, ray_mod, 2)) IDX_SHFT |= 1;
        // std::cout << IDX_SHFT << std::endl;
        
        // get intersection intervals
        float* t0 = Math::Vec3::multiply_new(Math::Vec3::sub_new(octants[0].aabb_min, ray_mod->_o), ray_mod->_d_rec);
        float* t1 = Math::Vec3::multiply_new(Math::Vec3::sub_new(octants[0].aabb_max, ray_mod->_o), ray_mod->_d_rec);
        OctreeTraversalData* otd = new OctreeTraversalData(&octants[0], t0, t1);

        // if ray hits octree (root), traverse childs
        if( otd->tNear() < otd->tFar() )
        {
            // std::cout << otd->tNear() << " " << otd->tFar() << std::endl;
        
            traverseOctreeRecursive(otd, hit_result, octants, IDX_SHFT);
        }

    };

}
