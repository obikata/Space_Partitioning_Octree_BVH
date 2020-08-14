#include "include/OBJ_File.hpp"
#include "include/OBJ_Face.hpp"
#include "include/Octree.hpp"
#include "include/OctreeBuilder.hpp"
#include "include/OctreeHitResult.hpp"
#include "include/Ray3D.hpp"
#include "include/AABB.hpp"
#include <iostream>
#include <chrono>
#include <sstream>

static std::string toStr(double a, int prec) 
{
    std::ostringstream text;
    text.precision(prec);
    text << std::fixed << a;
    return text.str();
}

void* malloc2d(size_t size, int row, int col)
{

    // http://pukulab.blog.fc2.com/blog-entry-28.html
    // https://qiita.com/tanabeman/items/bb39e9d1ddb67ddf4233

    char **a, *b;
    int  t = size * col;

    // インデックスと要素を一気に確保
    a = (char**)malloc((sizeof(*a) + t) * row);
    
    if (a) {
        // [インデックス, インデックス, ..., 要素, 要素, 要素, ...]
        // と整列させるため要素の開始位置をずらす
        b = (char*)(a + row);

        // 各行の先頭アドレスを与える
        for (int i = 0; i < row; i++) {
            a[i] = b;
            b += t; // 要素のサイズ×列の長さの分だけずらす
        }

        return a;
    }
    
    return nullptr;
}

int main(int argc, char **argv)
{

    //----------------------------------------------------------------------------
    // Config.
    //----------------------------------------------------------------------------
    bool BVH_DEMO = false;
    bool OCTREE_DEMO = !BVH_DEMO;

    //----------------------------------------------------------------------------
    // Read object file
    //----------------------------------------------------------------------------
    std::cout << "Read OBJ file." << std::endl;
    OBJ_Loader::OBJ_File obj;
    std::string path = "";
    std::string filename = argv[1];
    obj.read_file(path, filename);
    // obj.display();

    // Compute AABB
    float scale = 1.0f; // Bunny
    for(int i = 0; i < obj.row_v; i++)
    {
        Math::Vec3::scale_ref_slf(obj._v[i], scale);
    }
    for(int i = 0; i < obj.row_f; i++)
    {
        obj.computeAABB(i);
    }

    obj.computeAABB();
    
    std::chrono::system_clock::time_point start, timer;
    double elapsed;
    if( OCTREE_DEMO )
    {

        //----------------------------------------------------------------------------
        // Generate octree
        //----------------------------------------------------------------------------
        std::cout << "\n-------------------------------< generating Octree >-------------------------------\n" << std::endl;
        start = std::chrono::system_clock::now();
        OCT::Octree* octree = new OCT::Octree(obj, true);
        octree->_octree_builder->MIN_DEPTH_FILL_RATIO = 1.5f; // 
        octree->_octree_builder->MAX_DEPTH = 10; //
        octree->_octree_builder->BUILD_defaultRoutine(); // build 
        timer = std::chrono::system_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timer-start).count();
        std::cout << "    building time          = " + toStr(elapsed, 3) + "ms " << std::endl;
        octree->printStatistics();
        std::cout << "\n-------------------------------<  finished Octree  >-------------------------------" << std::endl;

        //----------------------------------------------------------------------------
        // Save as static octree data structure
        //----------------------------------------------------------------------------
        

        //----------------------------------------------------------------------------
        // Raycasting
        //----------------------------------------------------------------------------

        // traverse OCTREE
        for (int i=0; i<8; i++)
        {
            int item = -1;
            float* corner = octree->_root->_aabb->getCorners()[i];
            float* center = octree->_root->_aabb->getCenter();
            float* direction(Math::Vec3::normalize_new(Math::Vec3::sub_new(corner, center)));
            float* origin = Math::Vec3::add_new(center, Math::Vec3::scale_new(Math::Vec3::negate_new(direction), 1.0f));
            std::cout << "RAY DIRECTION VECTOR: " << direction[0] << " " << direction[1] << " " << direction[2] << std::endl;
            std::cout << "RAY ORIGIN VECTOR from ROOT CENTER: " << origin[0]-center[0] << " " << origin[1]-center[1] << " " << origin[2]-center[2] << std::endl;
            // Math::Vec3::sub_ref_slf(center, origin);
            Math::Vec3::normalize_ref_slf(origin);
            Math::Ray3D* ray = new Math::Ray3D(origin, direction);
            
            OCT::OctreeHitResult* hit_result = new OCT::OctreeHitResult(ray, 0.0f, 1.0f);
            octree->_octree_traversal->traverseRayTopDown(hit_result);
            item = hit_result->_item_idx;
            if (item == -1)
            {
                std::cout << "NO HIT" << std::endl;
            }
            else
            {
                std::cout << "HIT!" << std::endl;
                hit_result->printCounters();
            }
            std::cout << std::endl;

        }
    }

    return 0;
}
