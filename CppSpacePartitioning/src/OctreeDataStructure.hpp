#ifndef __STATIC_OCTREE_HPP__
#define __STATIC_OCTREE_HPP__

#include <vector>

/*

Octree Structure

octants = (Octant*)malloc(num_nodes * sizeof(Octant))
int root_idx : Index of root node
Octant root = octants[root_idx]

*/

namespace OCT {

    class Octree;
    class OctreeNode;

    class Octant
    {
        
    };

    class OctreeDataStructure
    {

        private:
            Octree* _oct;
            std::vector<OctreeNode*> nodes;

        public:

            int root_idx = 0;
            OctreeNode* nodes; // All nodes

            OctreeDataStructure() {};

            OctreeDataStructure(Octree* oct) : _oct(oct) {};

            void Build();

    };

}

#endif