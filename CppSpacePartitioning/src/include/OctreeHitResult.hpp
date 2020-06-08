#include "Ray3D.hpp"
#include "OctreeNode.hpp"
#include "OctreeTraversalData.hpp"
#include <string>

namespace Octree
{

    class OctreeHitResult
    {
    public:

        Math::Ray3D ray;
        float t_max;
        float t_min;
        float t;
        OctreeNode node;
        int item_idx = -1;
        bool two_sided_check = true;
        float hit_backface = 1.0f;
        float u, v;
        bool got_hit = false;
        int COUNT_triangle_intersection_tests = 0;
        int COUNT_node_intersection_tests     = 0;
        int COUNT_node_traversal_steps        = 0;
        
    
        std::vector<OctreeTraversalData> traversal_history;
    
        OctreeHitResult(Math::Ray3D ray, float t_min, float t_max)
        {
            set(ray, t_min, t_max);
        }
    
        OctreeHitResult set(Math::Ray3D ray, float t_min, float t_max)
        {
            this->ray = ray;
            this->t_min = t_min;
            this->t_max = t_max;
            this->t = t_max;
            this->item_idx = -1;
            this->hit_backface = 1.0f;
            this->got_hit = false;
            this->traversal_history.clear();
            return *this;
        }
    
        bool checkIfCloser(float t_new, int item_idx, OctreeNode node, float hit_backface, float u, float v)
        {
            if( t_min < t_new && t_new < t)
            {
                this->t            = t_new;
                this->u            = u;
                this->v            = v;
                this->item_idx     = item_idx;
                this->node         = node;
                this->hit_backface = hit_backface;
                this->got_hit      = true;
                return true;
            }
            return false;
        }
    
        bool checkIfCloser(float* tuv, int item_idx, OctreeNode node, float hit_backface)
        {
            if( t_min < tuv[0] && tuv[0] < t)
            {
                this->t            = tuv[0];
                this->u            = tuv[1];
                this->v            = tuv[2];
                this->item_idx     = item_idx;
                this->node         = node;
                this->hit_backface = hit_backface;
                this->got_hit      = true;
                return true;
            }
            return false;
        }

        bool gotHit()
        {
            return got_hit;
        }
    
        float* getHitPoint()
        {
            return ray.getPoint(t);
        }
    
        void resetCounters()
        {
            COUNT_triangle_intersection_tests = 0;
            COUNT_node_intersection_tests     = 0;
            COUNT_node_traversal_steps        = 0;
        }

    
        void printCounters()
        {
            std::cout < "---< HitResult: stats >---" << std::endl;
            std::cout < "   COUNT_triangle_intersection_tests = "+COUNT_triangle_intersection_tests < std::endl;
            std::cout < "   COUNT_node_intersection_tests     = "+COUNT_node_intersection_tests < std::endl;
            std::cout < "   COUNT_node_traversal_steps        = "+COUNT_node_traversal_steps < std::endl;
            std::cout < "---</ HitResult: stats >---" < std::endl;
        }
  
  };

}