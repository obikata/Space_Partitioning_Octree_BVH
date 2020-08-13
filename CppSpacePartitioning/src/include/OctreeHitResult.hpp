#ifndef __OCTREEHITRESULT_HPP__
#define __OCTREEHITRESULT_HPP__

#include "Ray3D.hpp"
#include "OctreeNode.hpp"
#include "OctreeTraversalData.hpp"
#include <string>

namespace OCT
{

    class OctreeHitResult
    {
    public:

        Math::Ray3D* _ray;
        float _t_max;
        float _t_min;
        float _t;
        OctreeNode* _node;
        int _item_idx = -1;
        bool _two_sided_check = true;
        float _hit_backface = 1.0f;
        float _u, _v;
        bool _got_hit = false;
        int COUNT_triangle_intersection_tests = 0;
        int COUNT_node_intersection_tests     = 0;
        int COUNT_node_traversal_steps        = 0;    
        std::vector<OctreeTraversalData*> _traversal_history;

        OctreeHitResult(Math::Ray3D* ray, float t_min, float t_max) : _ray(ray), _t_min(t_min), _t_max(t_max), _t(t_max), _item_idx(-1), _hit_backface(1.0f), _got_hit(false), _traversal_history(std::vector<OctreeTraversalData*>()) {}; 
    
        bool checkIfCloser(float t_new, int item_idx, OctreeNode* node, float hit_backface, float u, float v);
    
        bool checkIfCloser(float* tuv, int item_idx, OctreeNode* node, float hit_backface);

        bool gotHit();
    
        float* getHitPoint();
    
        void resetCounters();
    
        void printCounters();

  };

}

#endif