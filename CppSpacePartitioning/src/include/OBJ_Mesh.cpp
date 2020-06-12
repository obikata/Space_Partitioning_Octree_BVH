#include "OBJ_Mesh.hpp"

namespace OBJ_Loader
{

    void OBJ_Mesh::computeAABB()
    {
        _aabb.init();
        for (int i = 0; i < row_f; i++)
        {
            OBJ_Face query_face = buf_faces[i];
            query_face.computeAABB();
            _aabb.grow(query_face._aabb);
        }
    }

}