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
    float scale = 1000.0f; // Bunny
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
            // for (int i =0; i < 8 ; i++)
            // {
            //     corner = octree->_root->_aabb->getCorners()[i];
            //     std::cout << corner[0] << " " << corner[1] << " " << corner[2] << std::endl;
            // }
            float* center = octree->_root->_aabb->getCenter();
            float direction[3];
            Math::Vec3::sub_ref(corner, center, direction);
            Math::Vec3::normalize_ref_slf(direction);
            std::cout << "RAY DIRECTION: " << direction[0] << " " << direction[1] << " " << direction[2] << std::endl;
            float origin[3];
            Math::Vec3::add_ref(center,Math::Vec3::scale_new(Math::Vec3::negate_new(direction), 10.0f), origin);
            std::cout << "RAY ORIGIN: " << origin[0]-center[0] << " " << origin[1]-center[1] << " " << origin[2]-center[2] << std::endl;
            Math::Ray3D* ray = new Math::Ray3D(origin, direction);
            // std::cout << "RAY_DIR = " << ray->d[0] << " " << ray->d[1] << " " << ray->d[2] << std::endl;
            // std::cout << "RAY_ORIGIN = " << ray->o[0] << " " << ray->o[1] << " " << ray->o[2] << std::endl;
            // std::cout << "OCT_ROOT_CENTER = " << center[0] << " " << center[1] << " " << center[2] << std::endl;
            OCT::OctreeHitResult* hit_result = new OCT::OctreeHitResult(ray, 0.0f, 1.0f);
            octree->_octree_traversal->traverseRayTopDown(hit_result);
            item = hit_result->_item_idx;
            std::cout << item << std::endl;
        }
    }

    return 0;
}
