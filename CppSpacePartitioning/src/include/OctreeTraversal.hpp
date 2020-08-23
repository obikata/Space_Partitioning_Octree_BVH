#ifndef __OCTREETRAVERSAL_HPP__
#define __OCTREETRAVERSAL_HPP__

#include "AABB.hpp"
#include "Vec3.hpp"
#include "Ray3D.hpp"
#include "OBJ_Face.hpp"
#include "OBJ_File.hpp"
#include "Intersect_RAY_TRIANGLE.hpp"
#include "OctreeHitResult.hpp"
#include "OctreeTraversalData.hpp"

namespace oct
{

    class Octree;

    class OctreeTraversal
    {

    private:

        int IDX_SHFT = 0;
        float* ptr_hit_backface = new float[1];
        float* tuv = new float[3];

        bool mirrorComponent(Math::AABB* aabb, Math::Ray3D* ray, int id)
        {
            if(ray->_d[id] > 0.0) //TODO: handle special case: (ray->d[x] == 0.0)
            {
                return false;
            }
            ray->_o[id]     = (aabb->_min[id] + aabb->_max[id]) - ray->_o[id]; // mirror ray-origin at node-center
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
        
        bool traverseOctreeRecursive(OctreeTraversalData* OTD, OctreeHitResult* hit_result)
        {
            if(OTD->_t1[0] < 0.0 || OTD->_t1[0] < 0.0 || OTD->_t1[0] < 0.0)
            { 
        //      System.out.println("Ray origin inside AABB !"); 
                std::cout << "Ray origin inside AABB !" << std::endl;
                return false;
            }
            hit_result->COUNT_node_traversal_steps++;
            
            // if current node is is a leaf, then check the childs for intersection, and return
            if( OTD->_node->isLeaf())
            { // this presumes, that items are only located in leafes!
                std::cout << "isleaf" << std::endl;
                // ALSO THE PLACE TO SUBDIVIDE THE OCTREE AT THE CURRENT NODE AND MOVE ON TRAVERSION
                return intersectRayObjects(OTD, hit_result);
            }
            std::cout << "is not leaf" << std::endl;
          
            OctreeNode* node = OTD->_node;
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
                if( OTD->_node != nullptr &&  traverseOctreeRecursive(OTD, hit_result))
                {
                    return true;
                }
            } 
            return false;
        }
      
        // // traverse the octree (linkedListversion)
        // void traverseOctree(OctreeTraversalData* OTD, OctreeHitResult* hit_result)
        // {
        //     while( OTD != null) 
        //     {
        //         hit_result->COUNT_node_traversal_steps++;
        //         OctreeTraversalData OTD_CUR = OTD;
        //         OTD = OTD->prev; // pop() last element
              
        //         if(OTD_CUR->t1[0] < 0.0 || OTD_CUR->t1[0] < 0.0 || OTD_CUR->t1[0] < 0.0)
        //         { 
        //             // System.out.println("Ray origin inside AABB !"); 
        //             continue;   
        //         }

        //         if( OTD_CUR.node->isLeaf() )
        //         {
        //             // if( !OTD_CUR.node->isLeaf()) System.out.println("TRAVERSING: a not empty node, which is NOT a leaf");
        //             if( intersectRayObjects(OTD_CUR, hit_result)) return;
        //             continue;
        //         }
                

            
        //         // if current node is NOT a leaf, then check the childs for intersection
        //         OctreeNode node = OTD_CUR.node;
        //         float* t0 = OTD_CUR.t0;
        //         float* t1 = OTD_CUR.t1;
        //         float* tm = OTD_CUR.tm();
        //         int curr_node = first_node(t0,tm); 
                
        //         OctreeTraversalData OTD_FIRST=null, OTD_LAST=null; // temp stacks
                
        //         while(curr_node < 8 ) // 8=indication for ray-exit
        //         {     
        //             switch (curr_node)
        //             {     
        //                 case 0:  OTD_CUR = new OctreeTraversalData(node->childs[0^IDX_SHFT], t0[0],t0[1],t0[2],   tm[0],tm[1],tm[2]);  curr_node = next_node(OTD_CUR.t1,4,2,1);  break;
        //                 case 1:  OTD_CUR = new OctreeTraversalData(node->childs[1^IDX_SHFT], t0[0],t0[1],tm[2],   tm[0],tm[1],t1[2]);  curr_node = next_node(OTD_CUR.t1,5,3,8);  break;
        //                 case 2:  OTD_CUR = new OctreeTraversalData(node->childs[2^IDX_SHFT], t0[0],tm[1],t0[2],   tm[0],t1[1],tm[2]);  curr_node = next_node(OTD_CUR.t1,6,8,3);  break;
        //                 case 3:  OTD_CUR = new OctreeTraversalData(node->childs[3^IDX_SHFT], t0[0],tm[1],tm[2],   tm[0],t1[1],t1[2]);  curr_node = next_node(OTD_CUR.t1,7,8,8);  break;
        //                 case 4:  OTD_CUR = new OctreeTraversalData(node->childs[4^IDX_SHFT], tm[0],t0[1],t0[2],   t1[0],tm[1],tm[2]);  curr_node = next_node(OTD_CUR.t1,8,6,5);  break;
        //                 case 5:  OTD_CUR = new OctreeTraversalData(node->childs[5^IDX_SHFT], tm[0],t0[1],tm[2],   t1[0],tm[1],t1[2]);  curr_node = next_node(OTD_CUR.t1,8,7,8);  break;
        //                 case 6:  OTD_CUR = new OctreeTraversalData(node->childs[6^IDX_SHFT], tm[0],tm[1],t0[2],   t1[0],t1[1],tm[2]);  curr_node = next_node(OTD_CUR.t1,8,8,7);  break;
        //                 case 7:  OTD_CUR = new OctreeTraversalData(node->childs[7^IDX_SHFT], tm[0],tm[1],tm[2],   t1[0],t1[1],t1[2]);  curr_node = 8;                            break;
        //             }
                    
        //             // create reversed stack
        //             // add element to stack, only when the node is not null, otherwise continue traversing the childs.
        //             if(OTD_CUR.node != null)
        //             {
        //                 if (OTD_FIRST == null )
        //                 {
        //                     OTD_FIRST = (OTD_LAST = OTD_CUR); // init new temp. stack, keep pointers to start and end
        //                 }
        //                 else
        //                 {
        //                   OTD_FIRST = (OTD_FIRST.prev = OTD_CUR);       // add new element at begin of stack--> reversed building + update start pointer
        //                 }
        //             }
        //         } 
          
        //         if( OTD_FIRST != null)
        //         {
        //             OTD_FIRST.prev = OTD; // add new (reversed) stack at end of = combination of current and reversed stack
        //             OTD = OTD_LAST;       // set pointer to last element
        //         } 
        //     }
        // }

    public:
  
        Octree* _oct;

        OctreeTraversal() {};

        OctreeTraversal(Octree* oct) : _oct(oct) {};

        // intersection tests for items in current node
        bool intersectRayObjects(OctreeTraversalData* OTD, OctreeHitResult* hit_result);

        // traversing preparations
        void traverseRayTopDown(OctreeHitResult* hit_result);
    };
}

#endif