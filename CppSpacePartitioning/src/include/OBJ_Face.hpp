#ifndef __OBJ_FACE_HPP__
#define __OBJ_FACE_HPP__

#include <iostream>
#include<bits/stdc++.h> 
#include "AABB.hpp"
#include "OBJ_File.hpp"
// #include "Vec3.hpp"
// #include "OBJ_Material.hpp"
// #include "OBJ_Mesh.hpp"

// C++ Return float/int array
// https://www.geeksforgeeks.org/return-local-array-c-function/

namespace OBJ_Loader
{

    class OBJ_Face : public OBJ_File
    {
    
    public:

        int* IDX_V; // indices - vertices
        int* IDX_N; // indices - normals
        int* IDX_T; // indices - texture coordinates                
        Math::AABB aabb;


        // OBJ_File* parent_obj_file;
        // OBJ_Material* MATERIAL = OBJ_Material.MAT_DEFAULT;
        // OBJ_Mesh* MESH = NULL;
        
        // bool FLAG_CHECKED = false;
        
        /**
    	Constructor 
        */
        // OBJ_Face();

        OBJ_Face() : IDX_V(new int[3] {-1, -1, -1}), IDX_N(new int[3] {-1, -1, -1}), IDX_T(new int[3] {-1, -1, -1}) {};
        
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