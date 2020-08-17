#ifndef __ASCV_OCTREE_HPP__
#define __ASCV_OCTREE_HPP__

#include "../OctreeNode.hpp"

using namespace oct;
class Octree;

namespace ascv
{
        
    class Octant
    {

        public:
            int depth = 0;
            float aabb_min[3] {0.0f, 0.0f, 0.0f};
            float aabb_max[3] {0.0f, 0.0f, 0.0f};
            bool isLeaf = false; // Test against
            int NUM_IDX_triangles = 0;
            int child_node_idx[8] {-1, -1, -1, -1, -1, -1, -1, -1};
            int IDX_triangles[10] {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

            Octant() {};

    };

    class ascv_octree
    {

    public:

        int len_nodes = 0;
        int stored_items = 0;

        Octant* octants; // all octants

        ascv_octree() {};

        ascv_octree(oct::Octree* oct) : _oct(oct) {};

        void Build();

        bool isValid(Octant* octants);

    private:
        oct::Octree* _oct;

        void storeNodes_recursive(std::vector<oct::OctreeNode*>& nodes)
        {

            for (int counter = 0; counter<len_nodes; counter++)
            {

                octants[counter].depth = nodes[counter]->_depth;

                for (int j = 0; j < 3; j++)
                {
                    octants[counter].aabb_min[j] = nodes[counter]->_aabb->_min[j];
                    octants[counter].aabb_max[j] = nodes[counter]->_aabb->_max[j];
                }
            
                octants[counter].isLeaf = nodes[counter]->isLeaf();
                if (!octants[counter].isLeaf)
                { // Non-Leaf then check if childs exist because it is possible that this is an empty leaf after octree clean up
                    if (nodes[counter]->childs.size() !=0)
                    {
                        for (int i = 0; i < 8; i++)
                        {
                            if ( nodes[counter]->childs[i] != nullptr)
                            {
                                octants[counter].child_node_idx[i] = nodes[counter]->childs[i]->_nodeIdx;
                            }
                        }
                    }                        
                }
                else
                { // Leaf
                    if (!nodes[counter]->isEmpty())
                    {
                        octants[counter].NUM_IDX_triangles = nodes[counter]->IDX_triangles.size();
                        for (int j = 0; j<octants[counter].NUM_IDX_triangles; j++)
                        {
                            stored_items++;
                            octants[counter].IDX_triangles[j] = nodes[counter]->IDX_triangles[j]; // Store triangles
                        }
                    }
                }
            }

        }

    };

}

#endif