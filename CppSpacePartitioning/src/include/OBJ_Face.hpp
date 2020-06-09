#ifndef __OBJ_FACE_HPP__
#define __OBJ_FACE_HPP__

#include "AABB.hpp"
#include "Vec3.hpp"
#include "OBJ_File.hpp"
#include "OBJ_Material.hpp"
#include "OBJ_Mesh.hpp"

namespace OBJ_Loader
{
    class OBJ_Face
    {
    public:
        OBJ_File parent_obj_file;
        OBJ_Material MATERIAL = OBJ_Material.MAT_DEFAULT;
        OBJ_Mesh MESH = null;
        Math::AABB aabb;
        Math::Vec3 vector3;

        int IDX_V[3]; // indices - vertices
        int IDX_N[3]; // indices - normals
        int IDX_T[3]; // indices - texture coordinates
                
        bool FLAG_CHECKED = false;
        
        OBJ_Face(OBJ_File parent_obj_file)
        {
            this.parent_obj_file = parent_obj_file;
        }
        
        float* A() 
        {
            return parent_obj_file.v[IDX_V[0]];
        }
        
        float* B() 
        {
            return parent_obj_file.v[IDX_V[1]];
        }
        
        float* C()
        {
            return parent_obj_file.v[IDX_V[2]];
        }
                        
        float* An()
        {
            return parent_obj_file.n[IDX_N[0]];
        }
        
        float* Bn()
        {
            return parent_obj_file.n[IDX_N[1]];
        }
        
        float* Cn()
        {
            return parent_obj_file.n[IDX_N[2]];
        }

        void computeAABB()
        {
            aabb = new AABB(A(), B(), C());
        }
        
        float* getCenter()
        {
            return vector3.triangle_midpoint_new(A(), B(), C());
        }
        
        bool isDegenerate()
        {
            float* n = getNormalUnormalized();
            return vector3.mag(n) == 0.0f;
        }
        
        float getArea()
        {
            return vector3.mag(getNormalUnormalized())*0.5f;
        }
        
        float* getNormalUnormalized()
        {
            float* E1 = vector3.sub_new(B(), A());
            float* E2 = vector3.sub_new(C(), A());
            return vector3.cross_new(E1, E2);
        }
        
        float* getNormal()
        {
            float* n = getNormalUnormalized();
            vector3.normalize_ref_slf(n);
            return n;
        }

        float* getNormal(float u, float v)
        {
            float* nA = An(), nB = Bn(),  nC = Cn();
            float w = 1-u-v;
            float* n = {   nA[0]*w + nC[0]*u + nB[0]*v,
                            nA[1]*w + nC[1]*u + nB[1]*v,
                            nA[2]*w + nC[2]*u + nB[2]*v     };
            vector3.normalize_ref_slf(n);
            return n;
        }

        void getNormal_ref(float u, float v, float* dst)
        {
            float* nA = An(), nB = Bn(),  nC = Cn();
            float w = 1-u-v;
            dst[0] = nA[0]*w + nC[0]*u + nB[0]*v;
            dst[1] = nA[1]*w + nC[1]*u + nB[1]*v;
            dst[2] = nA[2]*w + nC[2]*u + nB[2]*v;
            vector3.normalize_ref_slf(dst);
        }
        
        float* getPoint(float u, float v)
        {
            float* A = A(), B = B(),  C = C();
            float w = 1-u-v;
            return new float* {   A[0]*w + C[0]*u + B[0]*v,
                                    A[1]*w + C[1]*u + B[1]*v,
                                    A[2]*w + C[2]*u + B[2]*v     };
        }

        float* getPoint(float u, float v, float w)
        {
            float* A = A(), B = B(),  C = C();
            return new float* {   A[0]*w + C[0]*u + B[0]*v,
                                    A[1]*w + C[1]*u + B[1]*v,
                                    A[2]*w + C[2]*u + B[2]*v     };
        }
        
        float* getUniformlySampledPoint()
        {
            float u = vector3.get_random();
            float v = vector3.get_random();
            float w = std::sqrt(u);
            u = 1-w;
            v = v*w;
            return getPoint(u, v);
        }

        static void getUniformlySampledUVs(float* uv)
        {
            float u = vector3.get_random();
            float v = vector3.get_random();
            float w = std::sqrt(u);
            uv[0] = (1-w);
            uv[1] = (v*w);
        }
        
        float* getCenterWeightedSampledPoint()
        {
            float r = vector3.get_random();
            float s = vector3.get_random();
            float t = vector3.get_random();
            float z = 1/(r+s+t);
            return getPoint(r*z, s*z, t*z);              
        }
    };
}

#endif