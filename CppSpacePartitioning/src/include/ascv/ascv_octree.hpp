#ifndef __ASCV_OCTREE_HPP__
#define __ASCV_OCTREE_HPP__

#include "../OctreeNode.hpp"

namespace oct
{
    class Octree;
}

namespace ascv
{
        
    class Octant
    {

    public:
        int depth;
        int NUM_IDX_triangles;
        float aabb_min[3];
        float aabb_max[3];
        bool isLeaf = false; // Test against
        int IDX_triangles[10];
        Octant** childs;

        Octant()
        {
            depth = 0;
            NUM_IDX_triangles = 0;
            for(int i = 0; i<3; i++) aabb_min[i] = 0.0f;
            for(int i = 0; i<3; i++) aabb_max[i] = 0.0f;
            for(int i = 0; i<10; i++) IDX_triangles[i] = -1;
            childs = (Octant**)malloc(8 * sizeof(Octant*));
        };

        int ptr_storeNodes_recursive(std::vector<oct::OctreeNode*>& nodes, int counter, int* stored_items, Octant** ptr_octants)
        {

            this->depth = nodes[counter]->_depth;

            for (int j = 0; j < 3; j++)
            {
                this->aabb_min[j] = nodes[counter]->_aabb->_min[j];
                this->aabb_max[j] = nodes[counter]->_aabb->_max[j];
            }
        
            // std::cout << counter << std::endl;
            this->isLeaf = nodes[counter]->isLeaf();
            int cnt = counter;
            if (!this->isLeaf)
            { // Non-Leaf then check if childs exist because it is possible that this is an empty leaf after octree clean up
                if (nodes[counter]->childs.size() !=0)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        if ( nodes[cnt]->childs[i] != nullptr )
                        {
                            this->childs[i] = ptr_octants[counter+1];
                            counter = ptr_octants[counter+1]->ptr_storeNodes_recursive(nodes, (counter+1), stored_items, ptr_octants);
                        }
                    }
                }                         
            }
            else
            { // Leaf
                if (!nodes[counter]->isEmpty())
                {
                    this->NUM_IDX_triangles = nodes[counter]->IDX_triangles.size();
                    for (int j = 0; j<this->NUM_IDX_triangles; j++)
                    {
                        stored_items[0]++;
                        this->IDX_triangles[j] = nodes[counter]->IDX_triangles[j]; // Store triangles
                    }
                }                
            }
            // std::cout << stored_items[0] << std::endl;
            return counter;
        }
    };

    class ascv_octree
    {

    public:

        int len_nodes = 0;
        int counter = 0;
        int* stored_items = new int[1] {0};
        Octant* octants; // all octants
        Octant** ptr_octants;

        ascv_octree() {};

        ascv_octree(oct::Octree* oct) : _oct(oct) {};

        void Build();

        bool isValid(Octant* octants);

    private:
        oct::Octree* _oct;

        // void storeNodes_recursive(std::vector<oct::OctreeNode*>& nodes)
        // {

        //     for (int counter = 0; counter<len_nodes; counter++)
        //     {

        //         octants[counter].depth = nodes[counter]->_depth;

        //         for (int j = 0; j < 3; j++)
        //         {
        //             octants[counter].aabb_min[j] = nodes[counter]->_aabb->_min[j];
        //             octants[counter].aabb_max[j] = nodes[counter]->_aabb->_max[j];
        //         }
            
        //         octants[counter].isLeaf = nodes[counter]->isLeaf();
        //         if (!octants[counter].isLeaf)
        //         { // Non-Leaf then check if childs exist because it is possible that this is an empty leaf after octree clean up
        //             if (nodes[counter]->childs.size() !=0)
        //             {
        //                 for (int i = 0; i < 8; i++)
        //                 {
        //                     if ( nodes[counter]->childs[i] != nullptr)
        //                     {
        //                         octants[counter].child_node_idx[i] = nodes[counter]->childs[i]->_nodeIdx; //TODO
        //                     }
        //                 }
        //             }                        
        //         }
        //         else
        //         { // Leaf
        //             if (!nodes[counter]->isEmpty())
        //             {
        //                 octants[counter].NUM_IDX_triangles = nodes[counter]->IDX_triangles.size();
        //                 for (int j = 0; j<octants[counter].NUM_IDX_triangles; j++)
        //                 {
        //                     stored_items++;
        //                     octants[counter].IDX_triangles[j] = nodes[counter]->IDX_triangles[j]; // Store triangles
        //                 }
        //             }
        //         }
        //     }

        // }

    };

}

#endif