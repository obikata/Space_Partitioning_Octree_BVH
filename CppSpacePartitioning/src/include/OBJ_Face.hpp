#ifndef __OBJ_FACE_HPP__
#define __OBJ_FACE_HPP__

#include "AABB.hpp"
#include "OBJ_File.hpp"

namespace OBJ_Loader
{
    class OBJ_File;

    class OBJ_Face : public OBJ_File
    {

    private:

        OBJ_File* ptr_obj;
    
    public:

        int* IDX_V; // indices - vertices
        int* IDX_N; // indices - normals
        int* IDX_T; // indices - texture coordinates                
        Math::AABB _aabb;

        /*
        The OBJ file references materials by name with the "usemtl" keyword. 
        All faces that follow are given the attributes of this material 
        until the next "usemtl" command is encountered.
        Faces and surfaces can be assigned into named groups with the "g" keyword.
        */
        
        int MeshGroupIdx; // Mesh group index
        int MaterialIdx; // Mesh group material index
        
        // bool FLAG_CHECKED = false;
        
        /**
    	Constructor 
        */
        // OBJ_Face() : IDX_V(new int[3] {-1, -1, -1}), IDX_N(new int[3] {-1, -1, -1}), IDX_T(new int[3] {-1, -1, -1}), MeshGroupIdx(0) {};
        OBJ_Face(OBJ_File* obj) : ptr_obj(obj), IDX_V(new int[3] {-1, -1, -1}), IDX_N(new int[3] {-1, -1, -1}), IDX_T(new int[3] {-1, -1, -1}), MeshGroupIdx(0), MaterialIdx(0) {};
        // OBJ_Face() : IDX_V(new int[3] {-1, -1, -1}), IDX_N(new int[3] {-1, -1, -1}), IDX_T(new int[3] {-1, -1, -1}), MeshGroupIdx(0), MaterialIdx(0) {};
        
        float* A();

        float* B(); 
        
        float* C();
                        
        float* An();
        
        float* Bn();
        
        float* Cn();

        void computeAABB();
        
        float* getCenter();
        
        bool isDegenerate();
        
        float getArea();
        
        float* getNormalUnormalized();
        
        float* getNormal();

        float* getNormal(float u, float v);

        void getNormal_ref(float u, float v, float* n);
        
        float* getPoint(float u, float v);

        float* getPoint(float u, float v, float w);
        
        float* getUniformlySampledPoint();

        void getUniformlySampledUVs(float* uv);
        
        float* getCenterWeightedSampledPoint();

    };
}

#endif