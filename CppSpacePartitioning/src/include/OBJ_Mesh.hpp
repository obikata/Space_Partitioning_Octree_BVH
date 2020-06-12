#ifndef __OBJ_MESH_HPP__
#define __OBJ_MESH_HPP__

#include "AABB.hpp"
#include "OBJ_File.hpp"

namespace OBJ_Loader
{

    class OBJ_Mesh : public OBJ_File
    {

    public:

        Math::AABB _aabb;
        std::string _name;
        std::vector<OBJ_Face> buf_faces;

        OBJ_Mesh(std::string name) : _name(name) {};

        void computeAABB() {};

    };
}

#endif