#include "AABB.hpp"
#include "OBJ_Face.hpp"

namespace OBJ_Loader
{
    class OBJ_Mesh
    {
    public:
        OBJ_File parenet_obj_file;
        std::string name;
        std::vector<OBJ_Face> faces;
        Math::AABB aabb;

        OBJ_Mesh(OBJ_File parent_obj_file, std::string name)
        {
            //abcdefg
            this.parent_obj_file = parent_obj_file;
            this.name = name;
        }

        void computeAABB()
        {
            aabb = AABB.init();
            for (OBJ_Face face : faces)
            {
                face.computeAABB();
                aabb.grow(face.aabb);
            }
        }

    };
}