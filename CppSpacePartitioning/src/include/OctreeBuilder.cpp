#include "OctreeBuilder.hpp"
#include "Octree.hpp"

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

        for(int i = 0; i < _oct->_obj.row_f; i++)
        {
            if( _oct->_obj._f[i].isDegenerate())
            {
                continue;
            }
            // std::cout << _oct->_root._aabb._min[0] << " " << _oct->_root._aabb._min[1] << " " << _oct->_root._aabb._min[2] << std::endl;
            // std::cout << _oct->_root._aabb._max[0] << " " << _oct->_root._aabb._max[1] << " " << _oct->_root._aabb._max[2] << std::endl;
            storeAtFirstFit(_oct->_root, i);
        }

        timer = std::chrono::system_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timer-start).count();
        std::cout << "       1) storeAtFirstFit   (" + toStr(elapsed, 3) + ")   stored items: " << _oct->getNumberOfStoredItems() << std::endl;

        pushToLeafes(_oct->_root);
        timer = std::chrono::system_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timer-start).count();
        std::cout << "       2) pushToLeafes      (" + toStr(elapsed, 3) + ")   stored items: " << _oct->getNumberOfStoredItems() << std::endl;
    
        optimizeSpaceCost(_oct->_root);
        timer = std::chrono::system_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timer-start).count();
        std::cout << "       3) optimizeSpaceCost (" + toStr(elapsed, 3) + ")   stored items: " << _oct->getNumberOfStoredItems() << std::endl;

        // timer = std::chrono::system_clock::now();
        // optimizeMaxItemsPerNode(octree, obj);
        // std::cout < "  ____ octree.getNumberOfStoredItems() = " + octree.getNumberOfStoredItems() + "     optimizeMaxItemsPerNode" < std::endl;
        cleanUp(_oct->_root);
        std::cout << "    > finished building" << std::endl;

    }

    //////////////////////////////////////////////////////////////////////////////
    // BUILD OCTREE
    //////////////////////////////////////////////////////////////////////////////

    // save in smallest nodes, that fully contains the triangle
    bool OctreeBuilder::storeAtFirstFit(OctreeNode& ot, int idx)
    {
        // 1) if we reached the max depth, save the triangle and return
        if( ot._depth >= MAX_DEPTH )
        {
            std::cout << "1" << std::endl;
            saveTriangleToNode(ot, idx);
            return true;
        }
        
        // 2) generate childs, if not possible, this node is a leaf, so save the item here
        if(!assureChilds(ot, MAX_DEPTH) )
        {
            std::cout << "2" << std::endl;
            saveTriangleToNode(ot, idx);
            return true;
        }
        
        // 3)) check if one child fully contains the triangle. if so, step down to the child
        for(OctreeNode child : ot.childs)
        {
            float dst[3];
            child._aabb.getHalfSizeRef(dst);
            std::cout << dst[0] << " " << dst[1] << " " << dst[2] << std::endl; 
            if( fullyContains(child, _oct->_obj._f[idx]) )
            {
                if(storeAtFirstFit(child, idx))
                {
                    return true;
                }
            }
        }
        
        // 4) no child fully contains the triangle. so push it to the leafes
        for(OctreeNode child : ot.childs)
        {
            storeInLeafes(child, idx);
        }
        // saveTriangleToNode(ot, idx);
        return true;
    }
    
    // make sure all triangles are in leaves
    void OctreeBuilder::pushToLeafes(OctreeNode& ot)
    {
        if(ot.isLeaf())
        {
            return;
        }
        
        // since current node is no leaf, if it isn't empty either, then move its items down it childs
        if( !ot.isEmpty() )
        {
            for( int idx: ot.IDX_triangles)
            {
                for(OctreeNode child : ot.childs)
                {
                    storeInLeafes(child, idx);
                }
            }
            ot.IDX_triangles.clear();
        }

        // repeat routine for all childs
        for(OctreeNode child : ot.childs)
        {
            pushToLeafes(child);
        }
    }
    
    void OctreeBuilder::storeInLeafes(OctreeNode& ot, int idx)
    {
        // if there's no overlap between the current node and the triangle, return
        if(!overlapsWithTriangle(ot, _oct->_obj._f[idx]))
        {
            return;
        }
        
        // current node is leaf, and overlaps with the triangle, so save it here
        if(ot.isLeaf())
        {
            saveTriangleToNode(ot, idx);
            return;
        }
        
        // if the current node is no leaf, so step down the childs
        for(OctreeNode child : ot.childs)
        {
            storeInLeafes(child, idx);
        }
    }

    void OctreeBuilder::optimizeSpaceCost(OctreeNode& ot)
    {

        if( !ot.isEmpty())
        {
            if( !positiveFillRatio(ot))
            {
                assureChilds(ot, MAX_DEPTH);
                pushToLeafes(ot);
            }
        }

        if(ot.isLeaf())
        {
            return;
        }
        
        for(OctreeNode child : ot.childs)
        {
            optimizeSpaceCost(child);
        }
    }

    bool OctreeBuilder::positiveFillRatio(OctreeNode& ot)
    {
        float ratio_items_depth = ot.itemCount() / (float) (ot._depth);
        return ratio_items_depth < MIN_DEPTH_FILL_RATIO;
    }

    bool OctreeBuilder::cleanUp(OctreeNode& ot)
    {

        if(ot.isLeaf())
        {
            return ot.isEmpty(); // True if the node is an empty leaf
        }
    
        bool delete_all_childs = true;

        // for(int i = 0; i < ot.childs.size(); i++)
        // {
        //     if(ot.childs[i]==nullptr)
        //     {
        //         continue;
        //     }
        //     if(cleanUp(ot.childs[i]))
        //     {
        //         ot.childs[i]=null;
        //     }
        //     else
        //     {
        //         delete_all_childs = false; 
        //     }
        // }
        if (ot.childs.size() == 0)
        {
            delete_all_childs = false; // Already clean
        }
        
        if( delete_all_childs )
        {
            // ot.childs = null;
            ot.childs.empty();
            return ot.isEmpty();
        }
        else
        {
            return false;
        }

    }

    bool OctreeBuilder::fullyContains(OctreeNode& ot, OBJ_Loader::OBJ_Face& f)
    {
        return ot._aabb.isInside(f.A(), f.B(), f.C());
    }

    bool OctreeBuilder::overlapsWithTriangle(OctreeNode& ot, OBJ_Loader::OBJ_Face& f)
    {
        return Intersect_AABB_TRIANGLE::overlaps(ot._aabb._min, ot._aabb._max, f.A(), f.B(), f.C());
    }

    bool OctreeBuilder::assureChilds(OctreeNode& ot, int max_depth)
    {
        if( ot._depth >= max_depth )
        {
            return false;
        }

        if( ot.isLeaf() )
        {
        
            ot.childs = std::vector<OctreeNode>(8);
            // float* half_size = ot._aabb.getHalfSize();
            float half_size[3];
            ot._aabb.getHalfSizeRef(half_size);
            int child_depth = ot._depth + 1;
            for(int i = 0; i < ot.childs.size(); i++)
            {
                // std::cout << std::bitset<3>((int)(i&4)) << " " << std::bitset<3>((int)(i&2)) << " " << std::bitset<3>((int)(i&1)) << std::endl;
                float ch_bb_min[3] = { ot._aabb._min[0] + ( ( (int)(i&4) > 0 ) ? half_size[0] : 0 ) ,
                                       ot._aabb._min[1] + ( ( (int)(i&2) > 0 ) ? half_size[1] : 0 ) ,
                                       ot._aabb._min[2] + ( ( (int)(i&1) > 0 ) ? half_size[2] : 0 ) };

                static float* ch_bb_max = vector3.add_new(ch_bb_min, half_size);
                Math::AABB aabb = Math::AABB(ch_bb_min, ch_bb_max);
                ot.childs[i] = OctreeNode(child_depth, aabb);
                // std::cout << ot.childs[i]._aabb._min[0] << " " << ot.childs[i]._aabb._min[1] << " " << ot.childs[i]._aabb._min[2] << std::endl;
            }
        }
        return true;
    }

    bool OctreeBuilder::saveTriangleToNode(OctreeNode& ot, int idx)
    {   
        std::vector<int>::iterator itr = std::find(ot.IDX_triangles.begin(), ot.IDX_triangles.end(), idx);
        int index = std::distance( ot.IDX_triangles.begin(), itr);
        if( ot.IDX_triangles[index] == idx )
        { // just in case
            ot.IDX_triangles.push_back(idx);
        }
        return true;
    }

}

