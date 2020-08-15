#include "OctreeDataStructure.hpp"
#include "Octree.hpp"

namespace OCT 
{

    void OctreeDataStructure::Build()
    {

        // Get nodes recursively to count the total number of nodes 
        std::vector<OctreeNode*> nodes;
        _oct->_root->getNodes_recursive(nodes);
        int len = nodes.size();

        octants = (Octant*)malloc(len * sizeof(Octant));

        int counter = 0;

        storeNodeRecursively(nodes);

    }

}