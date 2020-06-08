#include "Octree.hpp"
#include "OctreeNode.hpp"
#include "OBJ_File.hpp"
#include "Vec3.hpp"
#include <iostream>
#include <chrono>
#include <string>

namespace Octree
{

    class OctreeBuilder
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

    private:
        Octree octree;
        OctreeNode root;
        OBJ_File obj;
        Vec3 vector3;

        bool assureChilds(OctreeNode ot, int max_depth)
        {
            if( ot.depth >= max_depth)
            {
                return false;
            }

            if( ot.isLeaf() )
            {
            
                ot.childs = new OctreeNode[8];
                float* half_size = ot.aabb.getHalfSize();
                int child_depth = ot.depth+1;

                for(int i = 0; i < ot.childs.length; i++)
                {
            //        float[] ch_bb_min = DwVec3.add_new(ot.aabb.min, DwVec3.multiply_new(half_size, OCTANT_POS[i]));                
                    float ch_bb_min[3] = { ot.aabb.min[0] + (((i&4)>0)?half_size[0]:0),
                                        ot.aabb.min[1] + (((i&2)>0)?half_size[1]:0),
                                        ot.aabb.min[2] + (((i&1)>0)?half_size[2]:0) };

                    float ch_bb_max[3] = vector3.add_new(ch_bb_min, half_size);
                    ot.childs[i] = new OctreeNode(child_depth, new AABB(ch_bb_min, ch_bb_max));
                }
            }
            return true;
        }
    
        bool saveTriangleToNode(OctreeNode ot, int idx)
        {   
            if( !ot.IDX_triangles.contains(idx))
            { // just in case
                ot.IDX_triangles.add(idx);
            }
            return true;
        }

    public:
        // most important value, small values makes deep trees, especially for big scenes!!
        float MIN_DEPTH_FILL_RATIO = 1.5f;
        int MAX_DEPTH = 10;

        OctreeBuilder(Octree octree)
        {
            this->octree = octree;
            this->root = octree.root;
            this->obj = octree.obj;
        }

        static std::string toStr(double a, int prec) 
        {
            std::ostringstream text;
            text.precision(prec);
            text << std::fixed << a;
            return text.str(); 
        }

        void BUILD_defaultRoutine()
        {
            std::chrono::system_clock::time_point start, timer;
            // auto start, end;
            double elapsed;
            std::string txt_time;

            std::cout << "    > start building" << std::endl;

            start = std::chrono::system_clock::now();

            for(int i = 0; i < obj.f.length; i++)
            {
                if( obj.f[i].isDegenerate())
                {
                    continue;
                }
                storeAtFirstFit(root, i);
            }

            timer = std::chrono::system_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timer-start).count();
            txt_time = toStr(elapsed, 3);
            std::cout < "       1) storeAtFirstFit   (" + txt_time + ")   stored items: " + octree.getNumberOfStoredItems() << std::endl;

            timer = std::chrono::system_clock::now();
            pushToLeafes(root);
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timer-start).count();
            std::cout < "       2) pushToLeafes      (" + txt_time + ")   stored items: " + octree.getNumberOfStoredItems() < std::endl;
        
            timer = std::chrono::system_clock::now();
            optimizeSpaceCost(root);
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timer-start).count();
            std::cout < "       3) optimizeSpaceCost (" + txt_time + ")   stored items: " + octree.getNumberOfStoredItems() < std::endl;

            // timer = std::chrono::system_clock::now();
            // optimizeMaxItemsPerNode(octree, obj);
            // std::cout < "  ____ octree.getNumberOfStoredItems() = " + octree.getNumberOfStoredItems() + "     optimizeMaxItemsPerNode" < std::endl;
            cleanUp(root);
            std::cout << "    > finished building" << std::endl;

        }

        //////////////////////////////////////////////////////////////////////////////
        // BUILD OCTREE
        //////////////////////////////////////////////////////////////////////////////

        // save in smallest nodes, that fully contains the triangle
        bool storeAtFirstFit(OctreeNode ot, int idx)
        {
            // 1) if we reached the max depth, save the triangle and return
            if( ot.depth >= MAX_DEPTH ){
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
            for(OctreeNode child : ot.childs)
            {
                if( fullyContains(child, obj.f[idx]) )
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
        void pushToLeafes(OctreeNode ot)
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
        
        void storeInLeafes(OctreeNode ot, int idx)
        {
            // if there's no overlap between the current node and the triangle, return
            if(!overlapsWithTriangle(ot, obj.f[idx]))
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
    
        void optimizeSpaceCost(OctreeNode ot)
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
    
        bool positiveFillRatio(OctreeNode ot)
        {
            float ratio_items_depth = ot.itemCount() / (float) (ot.depth);
            return ratio_items_depth < MIN_DEPTH_FILL_RATIO;
        }
    
        bool cleanUp(OctreeNode ot)
        {

            if(ot.isLeaf())
            {
                return ot.isEmpty();
            }
        
            bool delete_all_childs = true;

            for(int i = 0; i < ot.childs.length; i++)
            {
                if(ot.childs[i]==null)
                {
                    continue;
                }
                if(cleanUp(ot.childs[i]))
                {
                    ot.childs[i] = null;
                }
                else
                {
                    delete_all_childs = false; 
                }
            }
            
            if( delete_all_childs )
            {
                ot.childs = null;
                return ot.isEmpty();
            }
            else
            {
                return false;
            }

        }
    
        bool fullyContains(OctreeNode ot, OBJ_Face f)
        {
            return ot.aabb.isInside(f.A(), f.B(), f.C());
        }

        bool overlapsWithTriangle(OctreeNode ot, OBJ_Face f)
        {
            return Intersect_AABB_TRIANGLE.overlaps(ot.aabb.min, ot.aabb.max, f.A(), f.B(), f.C());
        }

    };
}

