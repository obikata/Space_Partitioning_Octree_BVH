#include "include/OBJ_File.hpp"
#include "include/OBJ_Face.hpp"
#include "include/Octree.hpp"
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

int main(int argc, char **argv)
{

    //----------------------------------------------------------------------------
    // Config.
    //----------------------------------------------------------------------------
    bool BVH_DEMO = false;
    bool OCTREE_DEMO = !BVH_DEMO;
    // bool FILL = true;
    // bool VISUALSIZE = !false;
    // Camera cam;

    //----------------------------------------------------------------------------
    // Read object file
    //----------------------------------------------------------------------------
    std::cout << "Read OBJ file." << std::endl;
    OBJ_Loader::OBJ_File obj;
    std::string path = "";
    std::string filename = argv[1];
    // std::string filename = "buddha.obj";
    obj.read_file(path, filename);

    // Debug: Check OBJ_Loader functionality
    // obj.display();

    // Compute AABB
    float scale = 0.0f; // Bunny
    for(int i = 0; i < obj.row_v; i++)
    {
        Math::Vec3::scale_ref_slf(obj._v[i], scale);
    }
    for(int i = 0; i < obj.row_f; i++)
    {
        obj.computeAABB(i);
    }

    // Check AABB
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MIN = " << obj._aabb._min[i] << std::endl;
    }
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MAX = " << obj._aabb._max[i] << std::endl;
    }

    obj.computeAABB();

    // Check AABB
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MIN = " << obj._aabb._min[i] << std::endl;
    }
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MAX = " << obj._aabb._max[i] << std::endl;
    }

    //----------------------------------------------------------------------------
    // Generate octree
    //----------------------------------------------------------------------------
    std::chrono::system_clock::time_point start, timer;
    double elapsed;
    if( OCTREE_DEMO )
    {
        std::cout << "\n-------------------------------< generating Octree >-------------------------------\n" << std::endl;
        start = std::chrono::system_clock::now();
        Octree::Octree octree(obj, true);
    //     octree.oct_builder.MIN_DEPTH_FILL_RATIO = 1.2f; // 
    //     octree.oct_builder.MAX_DEPTH            = 11; // 
    //     octree.BUILD_defaultRoutine(); // build 
        timer = std::chrono::system_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timer-start).count();
        std::cout << "    building time          = " + toStr(elapsed, 3) + "ms " << std::endl;
    //     octree.printStatistics();
        std::cout << "\n-------------------------------<  finished Octree  >-------------------------------" << std::endl;
    }

    //----------------------------------------------------------------------------
    // Raycasting
    //----------------------------------------------------------------------------

    // traverse OCTREE
    // int item = -1;
    // Ray3D ray = new Camera(this).getSceenRay(width-mouseX, height-mouseY);

    // if( OCTREE_DEMO ){
    //     OctreeHitResult hit_result = new OctreeHitResult(ray, 0, 1);
    //     octree.traverse(hit_result);
    //     item = hit_result.item_idx;
    // }

    return 0;
}
