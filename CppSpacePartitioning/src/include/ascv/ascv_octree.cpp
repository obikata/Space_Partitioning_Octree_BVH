#include <vector>

#include "../AABB.hpp"
#include "../Octree.hpp"
#include "../OctreeNode.hpp"
#include "ascv_octree.hpp"

namespace ascv
{

    void ascv_octree::Build()
    {

        // Get nodes recursively to count the total number of nodes 
        std::vector<oct::OctreeNode*> nodes;
        _oct->_root->getNodes_recursive(nodes);
        len_nodes = nodes.size();

        octants = (Octant*)malloc(len_nodes * sizeof(Octant));

        // Store nodes
        storeNodes_recursive(nodes);

    }

    bool ascv_octree::isValid(Octant* octants)
    {
        for (int i = 0; i<len_nodes; i++)
        {
            if (!octants[i].isLeaf)
            { // non-leaf
                if( octants[i].NUM_IDX_triangles != 0 )
                {
                    return false; // non-leaf contains zero triangle
                }
            }
        }
        return true;
    }

}