#ifndef __OCTREEDATASTRUCTURE_HPP__
#define __OCTREEDATASTRUCTURE_HPP__

#include <vector>
#include "AABB.hpp"
#include "OctreeNode.hpp"

/*

Octree Structure

octants = (Octant*)malloc(num_nodes * sizeof(Octant))
int root_idx : Index of root nodes[counter]
Octant root = octants[root_idx]

*/

namespace OCT {

    class Octree;
    class OctreeNode;

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
            // float aabb_min[3] {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
            // float aabb_max[3] {-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max()};

            Octant();
    
    };

    class OctreeDataStructure
    {

        private:
            Octree* _oct;

            void storeNodeRecursively(std::vector<OctreeNode*>& nodes)
            {

                for (int counter = 0; counter<nodes.size(); counter++)
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
                                octants[counter].child_node_idx[i] = 0; //TODO
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
                                octants[counter].IDX_triangles[j] = nodes[counter]->IDX_triangles[j]; // Store triangles
                            }
                        }
                    }

                }

            }

        public:

            Octant* octants; // all octants
            int no_leaf_count = 0;

            OctreeDataStructure() {};

            OctreeDataStructure(Octree* oct) : _oct(oct) {};

            void Build();

    };

}

#endif