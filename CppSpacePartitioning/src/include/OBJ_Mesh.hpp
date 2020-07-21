#ifndef __OBJ_MESH_HPP__
#define __OBJ_MESH_HPP__

#include "AABB.hpp"
#include "OBJ_File.hpp"

namespace OBJ_Loader
{
    class OBJ_Face;
    class OBJ_Mesh : public OBJ_File
    {

    public:

        Math::AABB _aabb;
        std::string _name;
        std::vector<OBJ_Face> _buf_faces;

    	/**
    	Constructor 
        */
        OBJ_Mesh(std::string name) : _name(name) {};

        void computeAABB();

    };
}

#endif