#include "OBJ_Mesh.hpp"
#include "OBJ_Face.hpp"

namespace OBJ_Loader
{

    void OBJ_Mesh::computeAABB()
    {
        _aabb.init();
        for (int i = 0; i < row_f; i++)
        {
            OBJ_Face query_face = _buf_faces[i];
            query_face.computeAABB();
            _aabb.grow(query_face._aabb);
        }
    }

}