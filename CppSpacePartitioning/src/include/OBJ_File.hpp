#ifndef __OBJ_FILE_HPP__
#define __OBJ_FILE_HPP__

#include <iostream>

namespace OBJ_Loader
{

    class OBJ_Face;

    class OBJ_File
    {

    protected:
        // OBJ_Material* materials;
        // OBJ_Mesh* m; // meshes
        float** _v; // vertices
        float** _vt; // texture coordinates (normalized)
        float** _vn; // vertex-normals
        OBJ_Face* _f; // faces
        // Math::AABB aabb; // Axis Aligned Bounding Box
        
        int row_v = 0, col_v = 0;
        int row_vt = 0, col_vt = 0;
        int row_vn = 0, col_vn = 0;
        int row_f = 0;

    public:

        // Math::Vec3 vector3;

    	/**
    	Constructor 
        */
        OBJ_File() : _v(nullptr), _vt(nullptr), _vn(nullptr), _f(nullptr) {};
        
        void read_file(const char *filename);

        void* malloc2d(size_t size, int row, int col);

        void display();

    };

}

#endif