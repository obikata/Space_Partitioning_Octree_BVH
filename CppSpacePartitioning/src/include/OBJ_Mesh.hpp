#ifndef __OBJ_MESH_HPP__
#define __OBJ_MESH_HPP__

#include "AABB.hpp"
#include "OBJ_File.hpp"
#include "OBJ_Face.hpp"
// #include "OBJ_File.hpp"

namespace OBJ_Loader
{

    class OBJ_File;
    class OBJ_Face;

    class OBJ_Mesh
    {

    public:

        OBJ_File* parent_obj_file;
        std::string name;
        std::vector<OBJ_Face> faces;
        Math::AABB* aabb;

        OBJ_Mesh(OBJ_File* parent_obj_file, std::string name)
        {
            //abcdefg
            this->parent_obj_file = parent_obj_file;
            this->name = name;
        }

        void computeAABB()
        {
            aabb->init();
            for (int i = 0; i < faces.size(); i++)
            {
                faces[i].computeAABB();
                aabb->grow(faces[i].aabb);
            }
        }

    };
}

#endif