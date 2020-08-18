#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

#include "include/OBJ_File.hpp"
#include "include/OBJ_Face.hpp"
#include "include/Octree.hpp"
#include "include/OctreeBuilder.hpp"
#include "include/OctreeHitResult.hpp"
#include "include/Ray3D.hpp"
#include "include/AABB.hpp"

#include "include/ascv/ascv_octree.hpp"
#include "include/ascv/ascv_octree_hit_result.hpp"
#include "include/ascv/ascv_octree_traversal.hpp"

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

float** getCorners(ascv::Octant& octant)
{

    float** corners = (float**)malloc2d(sizeof(float), 8, 3);
    float c0[3] = { octant.aabb_min[0], octant.aabb_min[1], octant.aabb_min[2] }; // [0]
    float c1[3] = { octant.aabb_min[0], octant.aabb_min[1], octant.aabb_max[2] }; // [2]
    float c2[3] = { octant.aabb_min[0], octant.aabb_max[1], octant.aabb_min[2] }; // [1]
    float c3[3] = { octant.aabb_min[0], octant.aabb_max[1], octant.aabb_max[2] }; // [3]
    float c4[3] = { octant.aabb_max[0], octant.aabb_min[1], octant.aabb_min[2] }; // [4]
    float c5[3] = { octant.aabb_max[0], octant.aabb_min[1], octant.aabb_max[2] }; // [5]
    float c6[3] = { octant.aabb_max[0], octant.aabb_max[1], octant.aabb_min[2] }; // [6]
    float c7[3] = { octant.aabb_max[0], octant.aabb_max[1], octant.aabb_max[2] }; // [7]
    for (int i = 0; i < 3; i++) corners[0][i] = c0[i];
    for (int i = 0; i < 3; i++) corners[1][i] = c1[i];
    for (int i = 0; i < 3; i++) corners[2][i] = c2[i];
    for (int i = 0; i < 3; i++) corners[3][i] = c3[i];
    for (int i = 0; i < 3; i++) corners[4][i] = c4[i];
    for (int i = 0; i < 3; i++) corners[5][i] = c5[i];
    for (int i = 0; i < 3; i++) corners[6][i] = c6[i];
    for (int i = 0; i < 3; i++) corners[7][i] = c7[i];
    return corners;
}

float* getCenter(ascv::Octant& octant)
{
    float* dst = new float[3];
    Math::Vec3::scale_ref(Math::Vec3::add_new(octant.aabb_max, octant.aabb_min), 0.5f, dst);
    return dst;
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
        oct::Octree* octree = new oct::Octree(obj, true);
        octree->_octree_builder->MIN_DEPTH_FILL_RATIO = 1.5f; // 
        octree->_octree_builder->MAX_DEPTH = 10; //
        octree->_octree_builder->BUILD_defaultRoutine(); // build 
        timer = std::chrono::system_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timer-start).count();
        std::cout << "    building time          = " + toStr(elapsed, 3) + "ms " << std::endl;
        octree->printStatistics();
        std::cout << "\n-------------------------------<  finished Octree  >-------------------------------" << std::endl;

        //----------------------------------------------------------------------------
        // Raycasting
        //----------------------------------------------------------------------------

        // traverse OCTREE
        for (int i=0; i<8; i++)
        {
            std::cout << "\n-------------------------------<  RayCast Test  >----------------------------------\n" << std::endl;
            std::cout << "RAYCAST#: " << std::setfill('0') << std::setw(5) << i << std::endl;
            int item = -1;
            float* corner = octree->_root->_aabb->getCorners()[i];
            float* center = octree->_root->_aabb->getCenter();
            float* direction(Math::Vec3::normalize_new(Math::Vec3::sub_new(corner, center)));
            float* origin = Math::Vec3::add_new(center, Math::Vec3::scale_new(Math::Vec3::negate_new(direction), 1.0f));
            std::cout << "RAY DIRECTION VECTOR: " << direction[0] << " " << direction[1] << " " << direction[2] << std::endl;
            std::cout << "RAY ORIGIN VECTOR from ROOT CENTER: " << origin[0]-center[0] << " " << origin[1]-center[1] << " " << origin[2]-center[2] << std::endl;
            Math::Vec3::normalize_ref_slf(origin);
            Math::Ray3D* ray = new Math::Ray3D(origin, direction);
            oct::OctreeHitResult* hit_result = new oct::OctreeHitResult(ray, 0.0f, 1.0f);
            octree->_octree_traversal->traverseRayTopDown(hit_result);
            item = hit_result->_item_idx;
            if (item == -1)
            {
                std::cout << "\nNO HIT" << std::endl;
            }
            else
            {
                std::cout << "\nHIT!\n" << std::endl;
                hit_result->printCounters();
            }
        }
        std::cout << "\n-------------------------------<  Finished RayCast Test  >-------------------------" << std::endl;

        //----------------------------------------------------------------------------
        // Allocate memory area for the octree and store it as a new data structure
        //----------------------------------------------------------------------------
        std::cout << "\n-------------------------------< Allocating memory for octree >--------------------\n" << std::endl;
        octree->_ascv_octree->Build();
        bool octree_Data_structure_valid = octree->_ascv_octree->isValid(octree->_ascv_octree->octants);
        std::cout << "    octree_data_structure_valid        = " << octree_Data_structure_valid         << std::endl;
        std::cout << "    octree_data_structure_nodes        = " << octree->_ascv_octree->len_nodes         << std::endl;
        std::cout << "    octree_data_structure_stored_items        = " << octree->_ascv_octree->stored_items[0]         << std::endl;
        std::cout << "\n-------------------------------<  finished storing octree data  >------------------" << std::endl;

        //----------------------------------------------------------------------------
        // RayCast against the new octree structure
        //----------------------------------------------------------------------------

        ascv::Octant* octants = octree->_ascv_octree->octants;

        // traverse OCTREE
        for (int i = 0; i < 8; i++)
        {
            std::cout << "\n-------------------------------<  RayCast Test 2 >---------------------------------\n" << std::endl;
            std::cout << "RAYCAST#: " << std::setfill('0') << std::setw(5) << i << std::endl;
            float* corner = getCorners(octants[0])[i];
            float* center = getCenter(octants[0]);
            float* direction(Math::Vec3::normalize_new(Math::Vec3::sub_new(corner, center)));
            float* origin = Math::Vec3::add_new(center, Math::Vec3::scale_new(Math::Vec3::negate_new(direction), 1.0f));
            std::cout << "RAY DIRECTION VECTOR: " << direction[0] << " " << direction[1] << " " << direction[2] << std::endl;
            std::cout << "RAY ORIGIN VECTOR from ROOT CENTER: " << origin[0]-center[0] << " " << origin[1]-center[1] << " " << origin[2]-center[2] << std::endl;
            Math::Vec3::normalize_ref_slf(origin);
            Math::Ray3D* ray = new Math::Ray3D(origin, direction);
            ascv::OctreeHitResult* hit_result = new ascv::OctreeHitResult(ray, 0.0f, 1.0f);
            int IDX_SHFT = 0;
            ascv::ascv_octree_traversal::Traverse(octants, ray, hit_result, IDX_SHFT);
        }
        std::cout << "\n-------------------------------<  Finished RayCast Test 2 >------------------------" << std::endl;

    }

    return 0;
}
