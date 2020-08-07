#include "Octree.hpp"
#include "OctreeBuilder.hpp"

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

namespace OCT
{

    int Octree::getSubdivisionPlane(Math::AABB aabb)
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

    int Octree::getNumberOfNodes()
    {
        return Octree::getNodes().size();
    }

    std::vector<OctreeNode> Octree::getNodes()
    {
        std::vector<OctreeNode> nodes;
        _root.getNodes_recursive(nodes);
        return nodes;
    }

    // OctreeNode Octree::getNodeWithMaxItems()
    // {
    //     return Octree::getNodeWithMaxItems( Octree::getNodes() );
    // }
        
    // OctreeNode Octree::getNodeWithMaxItems(std::vector<OctreeNode> nodes)
    // {
    //     OctreeNode max = nodes[0];
    //     for(OctreeNode n : nodes)
    //     {
    //         if( n.isLeaf() )
    //         {
    //             if( max.itemCount() < n.itemCount() )
    //             {
    //                 max = n;
    //             }
    //         }
    //     }
    //     return max;
    // }
           
    int Octree::getNumberOfStoredItems()
    {
        return Octree::getNumberOfStoredItems( Octree::getNodes() );
    }

    int Octree::getNumberOfStoredItems(std::vector<OctreeNode> nodes)
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
        
    // int Octree::getNumberOfLeafes()
    // {
    //     return Octree::getNumberOfLeafes( Octree::getNodes() );
    // }

    // int getNumberOfLeafes(std::vector<OctreeNode> nodes)
    // {
    //     int count = 0;
    //     for(OctreeNode n : nodes)
    //     {
    //         if( n.isLeaf() )
    //         {
    //             count++;
    //         }
    //     }
    //     return count;
    // }
                
    // int Octree::sumUpLeafDepth()
    // {
    //     return Octree::sumUpLeafDepth(Octree::getNodes());
    // }

    // int Octree::sumUpLeafDepth(std::vector<OctreeNode> nodes)
    // {
    //     int count = 0;
    //     for(OctreeNode n : nodes)
    //     {
    //         if( n.isLeaf() )
    //         {
    //             count+=n._depth;
    //         }
    //     }
    //     return count;
    // }
        
    // int Octree::getMaxDepth()
    // {
    //     return Octree::getMaxDepth( Octree::getNodes() );
    // }
        
    // int Octree::getMaxDepth(std::vector<OctreeNode> nodes)
    // {
    //     int max = 0;
    //     for(OctreeNode n : nodes)
    //     {
    //         if( n._depth > max ) max = n._depth;
    //     }
    //     return max;
    // }
        
    // float Octree::getAverageLeafDepth()
    // {
    //     return Octree::getAverageLeafDepth( Octree::getNodes() );
    // }
        
    // float Octree::getAverageLeafDepth(std::vector<OctreeNode> nodes)
    // {
    //     int leaf_depth = sumUpLeafDepth(nodes);
    //     int leaf_count = getNumberOfLeafes(nodes);
    //     return leaf_depth/(float)leaf_count;
    // }
    
    // float Octree::getAverageLeafItems()
    // {
    //     return Octree::getAverageLeafDepth( Octree::getNodes() );
    // }

    // float Octree::getAverageLeafItems(std::vector<OctreeNode> nodes)
    // {
    //     int item_count = Octree::getNumberOfStoredItems(nodes);
    //     int leaf_count = Octree::getNumberOfLeafes(nodes);
    //     return item_count/(float)leaf_count;
    // }
        
    // bool Octree::isValid()
    // {
    //     return Octree::isValid( Octree::getNodes() );
    // }
        
    // bool Octree::isValid(std::vector<OctreeNode> nodes)
    // {
    //     for(OctreeNode n : nodes)
    //     {
    //         if( !n.isValid() ) return false;
    //     }
    //     return true;
    // }
            
    // void Octree::traverse(OctreeHitResult hit)
    // {
    //     _oct_traversal.traverseRayTopDown(hit);
    // }
        
    // void Octree::printStatistics()
    // {
    //     std::vector<OctreeNode> nodes  = Octree::getNodes();
    //     OctreeNode max_filled_node     = Octree::getNodeWithMaxItems();
    //     int     number_of_triangles    = _obj.row_f;
    //     bool octree_is_valid           = Octree::isValid(nodes);
    //     int     number_of_nodes        = nodes.size();       
    //     int     number_of_leafes       = Octree::getNumberOfLeafes(nodes);      
    //     int     number_of_stored_items = Octree::getNumberOfStoredItems(nodes); 
    //     int     max_depth              = Octree::getMaxDepth(nodes);            
    //     float   average_leaf_depth     = Octree::getAverageLeafDepth(nodes);   
    //     float   average_leaf_items     = Octree::getAverageLeafItems(nodes);   
        
    //     std::cout << "    octree_is_valid        = " << octree_is_valid        << std::endl;
    //     std::cout << "    number_of_triangles    = " << number_of_triangles    << std::endl;
    //     std::cout << "    number_of_nodes        = " << number_of_nodes        << std::endl;
    //     std::cout << "    number_of_leafes       = " << number_of_leafes       << std::endl;
    //     std::cout << "    number_of_stored_items = " << number_of_stored_items << std::endl;
    //     std::cout << "    max_depth              = " << max_depth              << std::endl;
    //     std::cout << "    average_leaf_depth     = " << average_leaf_depth     << std::endl;
    //     std::cout << "    average_leaf_items     = " << average_leaf_items     << std::endl;
    //     std::cout << "    max items per leaf     = " << max_filled_node.itemCount() << " (depth="+max_filled_node._depth << ")" << std::endl;
    //     std::cout << "    ratio: nodes/triangles = " << (number_of_nodes/(float)number_of_triangles) << std::endl;
    //     std::cout << "    ratio: items/triangles = " << (number_of_stored_items/(float)number_of_triangles) << std::endl;  
    // }

}
