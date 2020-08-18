#ifndef __ASCV_OCTREE_HIT_RESULT_DATA_HPP__
#define __ASCV_OCTREE_HIT_RESULT_DATA_HPP__


#include "../Vec3.hpp"
#include "../Ray3D.hpp"
#include "ascv_octree.hpp"

namespace ascv
{

    class OctreeHitResult
    {
    public:

        Math::Ray3D* _ray;
        float _t_max;
        float _t_min;
        float _t;
        Octant* _node;
        int _item_idx = -1;
        bool _two_sided_check = true;
        float _hit_backface = 1.0f;
        float _u, _v;
        bool _got_hit = false;
        int COUNT_triangle_intersection_tests = 0;
        int COUNT_node_intersection_tests     = 0;
        int COUNT_node_traversal_steps        = 0;    

        OctreeHitResult(Math::Ray3D* ray, float t_min, float t_max) : _ray(ray), _t_min(t_min), _t_max(t_max), _t(t_max), _item_idx(-1), _hit_backface(1.0f), _got_hit(false) {}; 

        bool checkIfCloser(float t_new, int item_idx, Octant* node, float hit_backface, float u, float v)
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


        bool checkIfCloser(float* tuv, int item_idx, Octant* node, float hit_backface)
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

        bool gotHit()
        {
            return _got_hit;
        }

        float* getHitPoint()
        {
            return _ray->getPoint(_t);
        }

        void resetCounters()
        {
            COUNT_triangle_intersection_tests = 0;
            COUNT_node_intersection_tests     = 0;
            COUNT_node_traversal_steps        = 0;
        }


        void printCounters()
        {
            std::cout << "---< HitResult: stats >---" << std::endl;
            std::cout << "   COUNT_triangle_intersection_tests = " << COUNT_triangle_intersection_tests << std::endl;
            std::cout << "   COUNT_node_intersection_tests     = " << COUNT_node_intersection_tests << std::endl;
            std::cout << "   COUNT_node_traversal_steps        = " << COUNT_node_traversal_steps << std::endl;
            std::cout << "---</ HitResult: stats >---" << std::endl;
        }

    };

}

#endif