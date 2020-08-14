#include "OctreeDataStructure.hpp"
#include "Octree.hpp"

namespace OCT {

    void OctreeDataStructure::Build()
    {

        // Get nodes recursively
        std::vector<OctreeNode*> nodes;
        _oct->_root->getNodes_recursive(nodes);

        root_idx = 0;


    }

}