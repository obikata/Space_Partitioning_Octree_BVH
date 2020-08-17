#include "OctreeDataStructure.hpp"
#include "Octree.hpp"

namespace OCT 
{

    void OctreeDataStructure::Build()
    {

        // Get nodes recursively to count the total number of nodes 
        std::vector<OctreeNode*> nodes;
        _oct->_root->getNodes_recursive(nodes);
        len_nodes = nodes.size();

        octants = (Octant*)malloc(len_nodes * sizeof(Octant));

        // Store nodes
        storeNodes_recursive(nodes);

    }

    bool OctreeDataStructure::isValid(Octant* octants)
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