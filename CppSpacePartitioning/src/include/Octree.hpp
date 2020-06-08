#include "AABB.hpp"
#include "Vec3.hpp"
#include "OBJ_File.hpp"
#include "OctreeBuilder.hpp"
#include "OctreeTraversal.hpp"
/*
//Octree: Octants numbering
//
//             +Y                        +Z
//             |                         /
//             |                        /
//             |                       /
//             |                      
//             |       o---------------o---------------o
//             |      /               /               /|
//             |     /       3       /       7       / | 
//             |    /               /               /  | 
//             |   o---------------o---------------o   | 
//             |  /               /               /|   |
//             | /       2       /       6       / | 7 |
//             /               /               /  |   o
//             o---------------o---------------o   |  /|
//             |               |               |   | / |
//             |               |               | 6 |/  |
//             |               |               |   o   |
//             |       2       |       6       |  /|   |
//             |               |               | / | 5 |
//             |               |               |/  |   o
//             o---------------o---------------o   |  /
//             |               |               |   | /
//             |               |               | 4 |/
//             |               |               |   o
//             |       0       |       4       |  / 
//             |               |               | /  
//             |               |               |/   
//             o---------------o---------------o -----------------+X
//
//
//
*/

namespace Octree
{
    class Octree
    {
    public:
        OBJLoader::OBJ_File objfile;
        OBJLoader::OctreeNode root;
        OctreeBuilder oct_builder;
        OctreeTraversal oct_traversal;
        Math::AABB aabb;
        Math::Vec3 vector3;

        Octree(objfile obj, bool cubic)
        {
            this->obj = obj;
            
            aabb = obj.aabb.copy();
            if(cubic)
            {
                float* center = aabb.getCenter();
                float* hs     = aabb.getHalfSize();
                int pl         = getSubdivisionPlane(aabb);
                vector3.add_ref(center, vector3.init(-hs[pl]), aabb.min);
                vector3.add_ref(center, vector3.init(+hs[pl]), aabb.max);
            }
            this->root = new OctreeNode(0, aabb );
            this->oct_builder = new OctreeBuilder(this);
            this->oct_traversal = new OctreeTraversal(this);
        }

        int getSubdivisionPlane(AABB aabb)
        {
            float* s = aabb.getSize();
            float max = vector3.maxComponent(s);
            if( s[0] == max )
            {
                return 0; // x-extent is max
            }
            else if( s[1] == max )
            {
              return 1; // y-extent is max
            }
            else
            {
                return 2; // z-extent is max
            }
        }
 
        void BUILD_defaultRoutine()
        {
            oct_builder.BUILD_defaultRoutine();
        }

        int getNumberOfNodes()
        {
            return getNodes().size();
        }

        std::vector<OctreeNode> getNodes()
        {
            std::vector<OctreeNode> nodes = new std::vector<OctreeNode>();
            root.getNodes_recursive(nodes);
            return nodes;
        }

        
        OctreeNode getNodeWithMaxItems()
        {
            return getNodeWithMaxItems( getNodes() );
        }
        
        OctreeNode getNodeWithMaxItems(ArrayList<OctreeNode> nodes)
        {
            OctreeNode max = nodes.get(0);
            for(OctreeNode n : nodes)
            {
                if( n.isLeaf() )
                {
                    if( max.itemCount() < n.itemCount() ) max = n;
                }
            }
            return max;
        }
           
        int getNumberOfStoredItems()
        {
            return getNumberOfStoredItems( getNodes() );
        }

        int getNumberOfStoredItems(ArrayList<OctreeNode> nodes)
        {
            int count = 0;
            for(OctreeNode n : nodes)
            {
      //      if( n.isLeaf() ){
                count += n.itemCount();
      //      }
            }
            return count;
        }
        
        int getNumberOfLeafes()
        {
            return getNumberOfLeafes( getNodes() );
        }

        int getNumberOfLeafes(ArrayList<OctreeNode> nodes)
        {
            int count = 0;
            for(OctreeNode n : nodes)
            {
                if( n.isLeaf() )
                {
                    count++;
                }
            }
            return count;
        }
                
        int sumUpLeafDepth()
        {
            return sumUpLeafDepth(getNodes());
        }

        int sumUpLeafDepth(ArrayList<OctreeNode> nodes)
        {
            int count = 0;
            for(OctreeNode n : nodes)
            {
                if( n.isLeaf() )
                {
                    count+=n.depth;
                }
            }
            return count;
        }
        
        int getMaxDepth()
        {
            return getMaxDepth( getNodes() );
        }
        
        int getMaxDepth(ArrayList<OctreeNode> nodes)
        {
            int max = 0;
            for(OctreeNode n : nodes)
            {
                if( n.depth > max ) max = n.depth;
            }
            return max;
        }
        
        
        float getAverageLeafDepth()
        {
            return getAverageLeafDepth( getNodes() );
        }
        
        float getAverageLeafDepth(ArrayList<OctreeNode> nodes)
        {
            int leaf_depth = sumUpLeafDepth(nodes);
            int leaf_count = getNumberOfLeafes(nodes);
            return leaf_depth/(float)leaf_count;
        }
        
        float getAverageLeafItems()
        {
            return getAverageLeafDepth( getNodes() );
        }

        float getAverageLeafItems(ArrayList<OctreeNode> nodes)
        {
            int item_count = getNumberOfStoredItems(nodes);
            int leaf_count = getNumberOfLeafes(nodes);
            return item_count/(float)leaf_count;
        }

        
        boolean isValid()
        {
            return isValid( getNodes() );
        }
        
        bool isValid(ArrayList<OctreeNode> nodes)
        {
            for(OctreeNode n : nodes)
            {
                if( !n.isValid() ) return false;
            }
            return true;
        }
            
        void traverse(OctreeHitResult hit)
        {
            oct_traversal.traverseRayTopDown(hit);
        }
        
        void printStatistics()
        {
            Octree octree = this;
            std::vector<OctreeNode> nodes  = octree.getNodes();
            OctreeNode max_filled_node     = octree.getNodeWithMaxItems();
            int     number_of_triangles    = obj.f.length;
            bool octree_is_valid           = octree.isValid(nodes);
            int     number_of_nodes        = nodes.size();       
            int     number_of_leafes       = octree.getNumberOfLeafes(nodes);      
            int     number_of_stored_items = octree.getNumberOfStoredItems(nodes); 
            int     max_depth              = octree.getMaxDepth(nodes);            
            float   average_leaf_depth     = octree.getAverageLeafDepth(nodes);   
            float   average_leaf_items     = octree.getAverageLeafItems(nodes);   
            
            std::cout < "    octree_is_valid        = " + octree_is_valid        < std::endl;
            std::cout < "    number_of_triangles    = " + number_of_triangles    < std::endl;
            std::cout < "    number_of_nodes        = " + number_of_nodes        < std::endl;
            std::cout < "    number_of_leafes       = " + number_of_leafes       < std::endl;
            std::cout < "    number_of_stored_items = " + number_of_stored_items < std::endl;
            std::cout < "    max_depth              = " + max_depth              < std::endl;
            std::cout < "    average_leaf_depth     = " + average_leaf_depth     < std::endl;
            std::cout < "    average_leaf_items     = " + average_leaf_items     < std::endl;
            std::cout < "    max items per leaf     = " + max_filled_node.itemCount() + " (depth="+max_filled_node.depth+")" < std::endl;
            std::cout < 
            std::cout < "    r atio: nodes/triangles = " + (number_of_nodes/(float)number_of_triangles) < std::endl;
            std::cout < "    ratio: items/triangles = " + (number_of_stored_items/(float)number_of_triangles) < std::endl;
          
        } 
              
    };
}
