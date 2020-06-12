#include "AABB.hpp"
#include "Vec3.hpp"
#include "OBJ_Face.hpp"

// C++ Return float/int array
// https://www.geeksforgeeks.org/return-local-array-c-function/

namespace OBJ_Loader
{
        
    float* OBJ_Face::A()
    {
        return _v[IDX_V[0]];
    }
    
    float* OBJ_Face::B()
    {
        return _v[IDX_V[1]];
    }
    
    float* OBJ_Face::C()
    {
        return _v[IDX_V[2]];
    }
                    
    float* OBJ_Face::An()
    {
        return _vn[IDX_N[0]];
    }
    
    float* OBJ_Face::Bn()
    {
        return _vn[IDX_N[1]];
    }
    
    float* OBJ_Face::Cn()
    {
        return _vn[IDX_N[2]];
    }

    void OBJ_Face::computeAABB()
    {
        _aabb = Math::AABB(A(), B(), C());
    }
    
    float* OBJ_Face::getCenter()
    {
        return Math::Vec3::triangle_midpoint_new(A(), B(), C());
    }
    
    bool OBJ_Face::isDegenerate()
    {
        float* n = getNormalUnormalized();
        return Math::Vec3::mag(n) == 0.0f;
    }
    
    float OBJ_Face::getArea()
    {
        return Math::Vec3::mag(getNormalUnormalized())*0.5f;
    }
    
    float* OBJ_Face::getNormalUnormalized()
    {
        float* E1 = Math::Vec3::sub_new(B(), A());
        float* E2 = Math::Vec3::sub_new(C(), A());
        return Math::Vec3::cross_new(E1, E2);
    }
    
    float* OBJ_Face::getNormal()
    {
        float* n = getNormalUnormalized();
        Math::Vec3::normalize_ref_slf(n);
        return n;
    }

    float* OBJ_Face::getNormal(float u, float v)
    {
        static float* n = new float[3];
        float* nA = An();
        float* nB = Bn();
        float* nC = Cn();
        float w = 1-u-v;
        n[0] = nA[0]*w + nC[0]*u + nB[0]*v;
        n[1] = nA[1]*w + nC[1]*u + nB[1]*v;
        n[2] = nA[2]*w + nC[2]*u + nB[2]*v;
        // n = {nA[0]*w + nC[0]*u + nB[0]*v, nA[1]*w + nC[1]*u + nB[1]*v, nA[2]*w + nC[2]*u + nB[2]*v};
        Math::Vec3::normalize_ref_slf(n);
        
        return n;
    }

    void OBJ_Face::getNormal_ref(float u, float v, float* n)
    {
        float* nA = An();
        float* nB = Bn();
        float* nC = Cn();
        float w = 1-u-v;
        n[0] = nA[0]*w + nC[0]*u + nB[0]*v;
        n[1] = nA[1]*w + nC[1]*u + nB[1]*v;
        n[2] = nA[2]*w + nC[2]*u + nB[2]*v;
        Math::Vec3::normalize_ref_slf(n);
    }
    
    float* OBJ_Face::getPoint(float u, float v)
    {
        static float* n = new float[3];
        float* a = A();
        float* b = B();
        float* c = C();
        float w = 1-u-v;
        n[0] = a[0]*w + c[0]*u + b[0]*v;
        n[1] = a[1]*w + c[1]*u + b[1]*v;
        n[2] = a[2]*w + c[2]*u + b[2]*v;
        return n;
    }

    float* OBJ_Face::getPoint(float u, float v, float w)
    {
        static float* p = new float[3];
        float* a = A();
        float* b = B();
        float* c = C();
        p[0] = a[0]*w + c[0]*u + b[0]*v;
        p[1] = a[1]*w + c[1]*u + b[1]*v;
        p[2] = a[2]*w + c[2]*u + b[2]*v;
        // return new float[3] {   A[0]*w + C[0]*u + B[0]*v,
        //                         A[1]*w + C[1]*u + B[1]*v,
        //                         A[2]*w + C[2]*u + B[2]*v     };
        return p;
    }
    
    float* OBJ_Face::getUniformlySampledPoint()
    {
        float u = Math::Vec3::get_random();
        float v = Math::Vec3::get_random();
        float w = std::sqrt(u);
        u = 1-w;
        v = v*w;
        return getPoint(u, v);
    }

    void OBJ_Face::getUniformlySampledUVs(float* uv)
    {
        float u = Math::Vec3::get_random();
        float v = Math::Vec3::get_random();
        float w = std::sqrt(u);
        uv[0] = (1-w);
        uv[1] = (v*w);
    }
    
    float* OBJ_Face::getCenterWeightedSampledPoint()
    {
        float r = Math::Vec3::get_random();
        float s = Math::Vec3::get_random();
        float t = Math::Vec3::get_random();
        float z = 1/(r+s+t);
        return getPoint(r*z, s*z, t*z);              
    }

}