#include "AABB.hpp"

namespace Octree
{

    //////////////////////////////////////////////////////////////////////////////
    // GET ALL NODES IN A LIST, ... no recursion used, but a simple linked list
    //////////////////////////////////////////////////////////////////////////////

    class LLNode
    {
    private:
        LLNode prev;
        OctreeNode value;
        static LLNode(OctreeNode value, LLNode prev)
        {
            this->value = value;
            this->prev = prev;
        }
    
        static LLNode push(LLNode current, OctreeNode element)
        {
            return LLNode(element, current);
        }
    
        static LLNode pop(LLNode current)
        {
            return current.prev;
        }
      
    };

    class OctreeNode
    {

    //////////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR
    //////////////////////////////////////////////////////////////////////////////

    protected:
        OctreeNode(int depth, Math::AABB aabb)
        {
            this->depth = depth;
            this->aabb  = aabb;
        }

    public:

        const Math::AABB aabb;
        const int depth;
        const IDX_triangles = new std::vector<int>;
        OctreeNode* childs;

        //////////////////////////////////////////////////////////////////////////////
        // NODE INFO
        //////////////////////////////////////////////////////////////////////////////
        
        bool isLeaf()
        {
            return childs == null;
        }
        
        bool isEmpty()
        {
            return IDX_triangles.empty();
        }
        
        // true: if node is leaf not is empty, also true if not is leaf and is empty
        bool isValid()
        {
            return isLeaf() ? !isEmpty() : isEmpty();
        }

        int itemCount()
        {
            return IDX_triangles.size();
        }
  
        void getNodes_linkedList(ArrayList<OctreeNode> nodes)
        {  // linked list version, just for testing
            LLNode llist = new LLNode(this, null);
            while ( llist != null )
            {
                OctreeNode item = llist.value;
                llist = LLNode.pop(llist);
                nodes.add(item);
                if(!item.isLeaf())
                {
                    for(OctreeNode child : item.childs)
                    {
                        if( child != null)
                        {
                            llist = LLNode.push(llist, child);
                        }
                    }
                }
            }
        }
  
  
        void getNodes_recursive(ArrayList<OctreeNode> nodes)
        {
            nodes.add(this);
            if(isLeaf())
            {
                return;
            }
            for(OctreeNode child : childs)
            {
                if( child!= null)
                {
                    child.getNodes_recursive(nodes);
                }
            }
        }

    }

}