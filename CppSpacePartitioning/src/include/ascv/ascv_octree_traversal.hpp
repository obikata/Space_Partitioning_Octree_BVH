#ifndef __ASCV_OCTREE_TRAVERSAL_HPP__
#define __ASCV_OCTREE_TRAVERSAL_HPP__

#include "../Ray3D.hpp"
#include "../Vec3.hpp"
#include "ascv_octree.hpp"
#include "ascv_octree_hit_result.hpp"
#include "ascv_octree_traversal_data.hpp"

namespace ascv
{
    class ascv_octree_traversal
    {
    
    private:

        static bool mirrorComponent(float* aabb_min, float* aabb_max, Math::Ray3D* ray, int id)
        {
            if(ray->_d[id] > 0.0) //TODO: handle special case: (ray->d[x] == 0.0)
            {
                return false;
            }
            ray->_o[id]     = (aabb_min[id] + aabb_max[id]) - ray->_o[id]; // mirror ray-origin at node-center
            ray->_d[id]     = -ray->_d[id];                                // mirror ray-direction
            ray->_d_rec[id] = -ray->_d_rec[id];                            // mirror ray-direction
            return true;                                           
        }

        // returns the first node, depending on the entry plane
        static int first_node(float* t0, float* tm)
        {
            float tmax = Math::Vec3::maxComponent(t0);
            if( t0[0] == tmax)
            {
                return ((tm[1]<t0[0])?2:0) | ((tm[2]<t0[0])?1:0); // YZ:tx0=max
            }
            if( t0[1] == tmax)
            {
                return ((tm[0]<t0[1])?4:0) | ((tm[2]<t0[1])?1:0); // XZ:ty0=max
            }
            return ((tm[0]<t0[2])?4:0) | ((tm[1]<t0[2])?2:0); // XY:tz0=max
        }

        // returns next node, depending on exit-plane ... YZ:tx1=min; XZ:ty1=min; XY:tz1=min; 
        static int next_node(float* t1, int YZ, int XZ, int XY)
        {
            if(t1[0] < t1[1])
            {
                return (t1[0] < t1[2]) ? YZ : XY; 
            }
            else
            {
                return (t1[1] < t1[2]) ? XZ : XY;
            }
        }

        static bool traverseOctreeRecursive(OctreeTraversalData* OTD, OctreeHitResult* hit_result, Octant* octants, int IDX_SHFT)
        {
            if(OTD->_t1[0] < 0.0 || OTD->_t1[0] < 0.0 || OTD->_t1[0] < 0.0)
            { 
        //      System.out.println("Ray origin inside AABB !"); 
                std::cout << "Ray origin inside AABB !" << std::endl;
                return false;
            }
            hit_result->COUNT_node_traversal_steps++;
            
            // if current node is is a leaf, then check the childs for intersection, and return
            if( OTD->_node->isLeaf )
            { // this presumes, that items are only located in leafes!
                std::cout << "isleaf" << std::endl;
                std::cout << "Number of IDX_triangles = " << OTD->_node->NUM_IDX_triangles << std::endl;
                for (int i=0; i<10; i++)
                {
                    if (OTD->_node->IDX_triangles[i] != -1)
                    {
                        std::cout << "IDX_triangle #" << OTD->_node->IDX_triangles[i] << " " << std::flush;
                        std::cout << "did not pass intersect2" << std::endl;
                    }
                }
                // return intersectRayObjects(OTD, hit_result);
                return false; // TODO : need to do intersect check
            }
            std::cout << "is not leaf" << std::endl;
            
            Octant* node = OTD->_node;
            float* t0      = OTD->_t0;
            float* t1      = OTD->_t1;
            float* tm      = OTD->tm();
            int curr_node   = first_node(t0, tm);
            while(curr_node < 8 )
            { // 8=indication for ray-exit    
                // std::cout << curr_node << std::endl;
                // std::cout << IDX_SHFT << std::endl;
                switch (curr_node)
                {
                    case 0:  OTD = new OctreeTraversalData(node->childs[0^IDX_SHFT], t0[0],t0[1],t0[2], tm[0],tm[1],tm[2]);  curr_node = next_node(OTD->_t1,4,2,1);  break;
                    case 1:  OTD = new OctreeTraversalData(node->childs[1^IDX_SHFT], t0[0],t0[1],tm[2], tm[0],tm[1],t1[2]);  curr_node = next_node(OTD->_t1,5,3,8);  break;
                    case 2:  OTD = new OctreeTraversalData(node->childs[2^IDX_SHFT], t0[0],tm[1],t0[2], tm[0],t1[1],tm[2]);  curr_node = next_node(OTD->_t1,6,8,3);  break;
                    case 3:  OTD = new OctreeTraversalData(node->childs[3^IDX_SHFT], t0[0],tm[1],tm[2], tm[0],t1[1],t1[2]);  curr_node = next_node(OTD->_t1,7,8,8);  break;
                    case 4:  OTD = new OctreeTraversalData(node->childs[4^IDX_SHFT], tm[0],t0[1],t0[2], t1[0],tm[1],tm[2]);  curr_node = next_node(OTD->_t1,8,6,5);  break;
                    case 5:  OTD = new OctreeTraversalData(node->childs[5^IDX_SHFT], tm[0],t0[1],tm[2], t1[0],tm[1],t1[2]);  curr_node = next_node(OTD->_t1,8,7,8);  break;
                    case 6:  OTD = new OctreeTraversalData(node->childs[6^IDX_SHFT], tm[0],tm[1],t0[2], t1[0],t1[1],tm[2]);  curr_node = next_node(OTD->_t1,8,8,7);  break;
                    case 7:  OTD = new OctreeTraversalData(node->childs[7^IDX_SHFT], tm[0],tm[1],tm[2], t1[0],t1[1],t1[2]);  curr_node = 8;                          break;
                }
                if( OTD->_node != nullptr &&  traverseOctreeRecursive(OTD, hit_result, octants, IDX_SHFT))
                {
                    return true;
                }
            } 
            return false;
        }

    
    public:

        ascv_octree_traversal();
        
        static void Traverse(Octant* octants, Math::Ray3D* ray, OctreeHitResult* hit_result, int IDX_SHFT);
    
    };

}

#endif