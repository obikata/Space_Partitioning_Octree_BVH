#ifndef __OBJ_FILE_HPP__
#define __OBJ_FILE_HPP__

#include "AABB.hpp"

namespace OBJ_Loader
{

    class OBJ_Face;
    class OBJ_Mesh;
    class OBJ_Material;

    class OBJ_File
    {

    public:

        float** _v; // vertices
        float** _vt; // texture coordinates (normalized)
        float** _vn; // vertex-normals
        OBJ_Face* _f; // faces
        OBJ_Mesh* _m; // meshes
        OBJ_Material* _mat; // materials
        
        int row_v = 0, col_v = 0;
        int row_vt = 0, col_vt = 0;
        int row_vn = 0, col_vn = 0;
        int row_f = 0;
        int row_m = 0;
        int row_mat = 0;

        Math::AABB _aabb = Math::AABB(); // Axis Aligned Bounding Box
        Math::Vec3 vector3;

    	/**
    	Constructor 
        */
        // OBJ_File() : _v(nullptr), _vt(nullptr), _vn(nullptr), _f(nullptr), _m(nullptr) {};
        OBJ_File() : _v(nullptr), _vt(nullptr), _vn(nullptr), _f(nullptr), _m(nullptr), _mat(nullptr) {};
        
        void read_file(std::string path, std::string filename);

        void* malloc2d(size_t size, int row, int col);

        void display();

        void computeAABB();

        void computeAABB(int face_id);

    };

}

#endif