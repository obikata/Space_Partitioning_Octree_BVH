
#include "OctreeTraversal.hpp"
#include "OctreeHitResult.hpp"
#include "Octree.hpp"

namespace oct
{

    // traversing preparations
    void OctreeTraversal::traverseRayTopDown(OctreeHitResult* hit_result)
    {
        if( hit_result == nullptr )
        {
            return;
        }

        IDX_SHFT = 0;
        Math::Ray3D* ray_mod = hit_result->_ray->copy();  // copy ray
        if(mirrorComponent(_oct->_root->_aabb, ray_mod, 0)) IDX_SHFT |= 4;
        if(mirrorComponent(_oct->_root->_aabb, ray_mod, 1)) IDX_SHFT |= 2;
        if(mirrorComponent(_oct->_root->_aabb, ray_mod, 2)) IDX_SHFT |= 1;

        // get intersection intervals
        float* t0 = Math::Vec3::multiply_new(Math::Vec3::sub_new(_oct->_root->_aabb->_min, ray_mod->_o), ray_mod->_d_rec);
        float* t1 = Math::Vec3::multiply_new(Math::Vec3::sub_new(_oct->_root->_aabb->_max, ray_mod->_o), ray_mod->_d_rec);
        OctreeTraversalData* otd = new OctreeTraversalData(_oct->_root, t0, t1);

        // if ray hits octree (root), traverse childs
        if( otd->tNear() < otd->tFar() )
        {
            std::cout << otd->tNear() << " " << otd->tFar() << std::endl;
        
            traverseOctreeRecursive(otd, hit_result);
            for( OctreeTraversalData* td_checked : hit_result->_traversal_history)
            {
                for(int id : td_checked->_node->IDX_triangles)
                {
                    _oct->_obj._f[id].FLAG_CHECKED = false; // reset flags!
                }
            }
        }
    }

    // intersection tests for items in current node
    bool OctreeTraversal::intersectRayObjects(OctreeTraversalData* OTD, OctreeHitResult* hit_result)
    {

        hit_result->_traversal_history.push_back(OTD);
        hit_result->COUNT_node_intersection_tests++;
        
        std::cout << "Number of IDX_triangles = " << OTD->_node->IDX_triangles.size() << std::endl;
        for(int id : OTD->_node->IDX_triangles)
        {
            OBJ_Loader::OBJ_Face f = _oct->_obj._f[id];
            if( f.FLAG_CHECKED )
            {
                continue;
            }
            f.FLAG_CHECKED = true;

            std::cout << "IDX_triangle = " << id << std::endl;
            
            if(Intersect_RAY_TRIANGLE::intersect2(hit_result->_ray, f.A(), f.B(), f.C(), hit_result->_two_sided_check, ptr_hit_backface, tuv))
            {
                std::cout << "Passed intersect2" << std::endl;
                hit_result->checkIfCloser(tuv, id, OTD->_node, ptr_hit_backface[0]);
                hit_result->COUNT_triangle_intersection_tests++;
            }
        }

        // because some objects exceed the nodes aabb, an intersection (at t) can 
        // be outside the current abbb and, the next node may contains a closer
        // object with a smaller t!!!
        // in the end, ONLY if a hit(at t) is INSIDE the current node, 
        // there cant be any smaller values for t in any subsequent nodes.
        return (hit_result->_t <= OTD->tFar());
    }
}