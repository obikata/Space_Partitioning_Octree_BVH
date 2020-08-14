#include "OctreeHitResult.hpp"

namespace OCT
{
    
    bool OctreeHitResult::checkIfCloser(float t_new, int item_idx, OctreeNode* node, float hit_backface, float u, float v)
    {
        if( _t_min < t_new && t_new < _t)
        {
            _t            = t_new;
            _u            = u;
            _v            = v;
            _item_idx     = item_idx;
            _node         = node;
            _hit_backface = hit_backface;
            _got_hit      = true;
            return true;
        }
        return false;
    }

    bool OctreeHitResult::checkIfCloser(float* tuv, int item_idx, OctreeNode* node, float hit_backface)
    {
        std::cout << "_t_min = " << _t_min << ", tuv[0] = " << tuv[0] << ", _t = " << _t << std::endl;
        if( _t_min < tuv[0] && tuv[0] < _t)
        {
            _t            = tuv[0];
            _u            = tuv[1];
            _v            = tuv[2];
            _item_idx     = item_idx;
            _node         = node;
            _hit_backface = hit_backface;
            _got_hit      = true;
            return true;
        }
        return false;
    }

    bool OctreeHitResult::gotHit()
    {
        return _got_hit;
    }

    float* OctreeHitResult::getHitPoint()
    {
        return _ray->getPoint(_t);
    }

    void OctreeHitResult::resetCounters()
    {
        COUNT_triangle_intersection_tests = 0;
        COUNT_node_intersection_tests     = 0;
        COUNT_node_traversal_steps        = 0;
    }


    void OctreeHitResult::printCounters()
    {
        std::cout << "---< HitResult: stats >---" << std::endl;
        std::cout << "   COUNT_triangle_intersection_tests = " << COUNT_triangle_intersection_tests << std::endl;
        std::cout << "   COUNT_node_intersection_tests     = " << COUNT_node_intersection_tests << std::endl;
        std::cout << "   COUNT_node_traversal_steps        = " << COUNT_node_traversal_steps << std::endl;
        std::cout << "---</ HitResult: stats >---" << std::endl;
    }
}