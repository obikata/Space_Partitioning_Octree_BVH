#include "OctreeBuilder.hpp"

namespace OCT
{

    //  public static float OCTANT_POS[][] =
    //  {
    //    //i&4, i&2, i&1
    //    { 0, 0, 0 },    // [0] - 000
    //    { 0, 0, 1 },    // [1] - 001
    //    { 0, 1, 0 },    // [2] - 010
    //    { 0, 1, 1 },    // [3] - 011
    //    
    //    { 1, 0, 0 },    // [4] - 100
    //    { 1, 0, 1 },    // [5] - 101
    //    { 1, 1, 0 },    // [6] - 110
    //    { 1, 1, 1 },    // [7] - 111
    //  };

    std::string OctreeBuilder::toStr(double a, int prec) 
    {
        std::ostringstream text;
        text.precision(prec);
        text << std::fixed << a;
        return text.str();
    }

    void OctreeBuilder::BUILD_defaultRoutine()
    {
        
        std::chrono::system_clock::time_point start, timer;
        // auto start, end;
        double elapsed;
        std::string txt_time;

        std::cout << "    > start building" << std::endl;

        start = std::chrono::system_clock::now();

        std::cout << __obj->row_f << std::endl;
        for(int i = 0; i < __obj->row_f; i++)
        {
            if( __obj->_f[i].isDegenerate())
            {
                continue;
            }
            std::cout << _root.itemCount() << std::endl;
            storeAtFirstFit(&_root, i);
        }
        // std::cout << _root.itemCount() << std::endl;

        timer = std::chrono::system_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timer-start).count();
        std::cout << Octree::getNumberOfStoredItems() << std::endl;
        std::cout << "       1) storeAtFirstFit   (" + toStr(elapsed, 3) + ")   stored items: " << Octree::getNumberOfStoredItems() << std::endl;

        pushToLeafes(&_root);
        timer = std::chrono::system_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timer-start).count();
        std::cout << "       2) pushToLeafes      (" + toStr(elapsed, 3) + ")   stored items: " << Octree::getNumberOfStoredItems() << std::endl;
    
        optimizeSpaceCost(&_root);
        timer = std::chrono::system_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timer-start).count();
        std::cout << "       3) optimizeSpaceCost (" + toStr(elapsed, 3) + ")   stored items: " << Octree::getNumberOfStoredItems() << std::endl;

        // timer = std::chrono::system_clock::now();
        // optimizeMaxItemsPerNode(octree, obj);
        // std::cout < "  ____ octree.getNumberOfStoredItems() = " + octree.getNumberOfStoredItems() + "     optimizeMaxItemsPerNode" < std::endl;
        cleanUp(&_root);
        std::cout << "    > finished building" << std::endl;

    }

    //////////////////////////////////////////////////////////////////////////////
    // BUILD OCTREE
    //////////////////////////////////////////////////////////////////////////////

    // save in smallest nodes, that fully contains the triangle
    bool OctreeBuilder::storeAtFirstFit(OctreeNode* ot, int idx)
    {
        // 1) if we reached the max depth, save the triangle and return
        std::cout << ot->_depth << std::endl;
        std::cout << MAX_DEPTH << std::endl;
        if( ot->_depth >= MAX_DEPTH )
        {
            saveTriangleToNode(ot, idx);
            return true;
        }
        
        // 2) generate childs, if not possible, this node is a leaf, so save the item here
        if(!assureChilds(ot, MAX_DEPTH) )
        {
            saveTriangleToNode(ot, idx);
            return true;
        }
        
        // 3)) check if one child fully contains the triangle. if so, step down to the child
        for(OctreeNode child : ot->childs)
        {
            if( fullyContains(&child, __obj->_f[idx]) )
            {
                if(storeAtFirstFit(&child, idx))
                {
                    return true;
                }
            }
        }
        
        // 4) no child fully contains the triangle. so push it to the leafes
        for(OctreeNode child : ot->childs)
        {
            storeInLeafes(&child, idx);
        }
        // saveTriangleToNode(ot, idx);
        return true;
    }
    
    // make sure all triangles are in leaves
    void OctreeBuilder::pushToLeafes(OctreeNode* ot)
    {
        if(ot->isLeaf())
        {
            return;
        }
        
        // since current node is no leaf, if it isn't empty either, then move its items down it childs
        if( !ot->isEmpty() )
        {
            for( int idx: ot->IDX_triangles)
            {
                for(OctreeNode child : ot->childs)
                {
                    storeInLeafes(&child, idx);
                }
            }
            ot->IDX_triangles.clear();
        }

        // repeat routine for all childs
        for(OctreeNode child : ot->childs)
        {
            pushToLeafes(&child);
        }
    }
    
    void OctreeBuilder::storeInLeafes(OctreeNode* ot, int idx)
    {
        // if there's no overlap between the current node and the triangle, return
        if(!overlapsWithTriangle(ot, __obj->_f[idx]))
        {
            return;
        }
        
        // current node is leaf, and overlaps with the triangle, so save it here
        if(ot->isLeaf())
        {
            saveTriangleToNode(ot, idx);
            return;
        }
        
        // if the current node is no leaf, so step down the childs
        for(OctreeNode child : ot->childs)
        {
            storeInLeafes(&child, idx);
        }
    }

    void OctreeBuilder::optimizeSpaceCost(OctreeNode* ot)
    {

        if( !ot->isEmpty())
        {
            if( !positiveFillRatio(ot))
            {
                assureChilds(ot, MAX_DEPTH);
                pushToLeafes(ot);
            }
        }

        if(ot->isLeaf())
        {
            return;
        }
        
        for(OctreeNode child : ot->childs)
        {
            optimizeSpaceCost(&child);
        }
    }

    bool OctreeBuilder::positiveFillRatio(OctreeNode* ot)
    {
        float ratio_items_depth = ot->itemCount() / (float) (ot->_depth);
        return ratio_items_depth < MIN_DEPTH_FILL_RATIO;
    }

    bool OctreeBuilder::cleanUp(OctreeNode* ot)
    {

        if(ot->isLeaf())
        {
            return ot->isEmpty(); // True if the node is an empty leaf
        }
    
        bool delete_all_childs = true;

        // for(int i = 0; i < ot->childs.size(); i++)
        // {
        //     if(ot->childs[i]==nullptr)
        //     {
        //         continue;
        //     }
        //     if(cleanUp(ot->childs[i]))
        //     {
        //         ot->childs[i]=null;
        //     }
        //     else
        //     {
        //         delete_all_childs = false; 
        //     }
        // }
        if (ot->childs.size() == 0)
        {
            delete_all_childs = false; // Already clean
        }
        
        if( delete_all_childs )
        {
            // ot->childs = null;
            ot->childs.empty();
            return ot->isEmpty();
        }
        else
        {
            return false;
        }

    }

    bool OctreeBuilder::fullyContains(OctreeNode* ot, OBJ_Loader::OBJ_Face f)
    {
        return ot->_aabb.isInside(f.A(), f.B(), f.C());
    }

    bool OctreeBuilder::overlapsWithTriangle(OctreeNode* ot, OBJ_Loader::OBJ_Face f)
    {
        return Intersect_AABB_TRIANGLE::overlaps(ot->_aabb._min, ot->_aabb._max, f.A(), f.B(), f.C());
    }

}

