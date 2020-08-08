#include "OctreeNode.hpp"

namespace OCT
{
    
    //////////////////////////////////////////////////////////////////////////////
    // NODE INFO
    //////////////////////////////////////////////////////////////////////////////
    
    bool OctreeNode::isLeaf()
    {
        return (childs.size() == 0);
    }
    
    bool OctreeNode::isEmpty()
    {
        return (IDX_triangles.size() == 0);
    }
    
    // true: if node is leaf not is empty, also true if not is leaf and is empty
    bool OctreeNode::isValid()
    {
        return OctreeNode::isLeaf() ? !OctreeNode::isEmpty() : OctreeNode::isEmpty();
    }

    int OctreeNode::itemCount()
    {
        return IDX_triangles.size();
    }

    void OctreeNode::getNodes_recursive(std::vector<OctreeNode> nodes)
    {
        nodes.push_back(*this);
        if(this->isLeaf())
        // if(OctreeNode::isLeaf())
        {
            return;
        }
        for(OctreeNode child : childs)
        {
            if( &child != nullptr)
            {
                child.getNodes_recursive(nodes);
            }
        }
    }

}