#ifndef __INTERSECT_RAY_TRIANGLE_HPP__
#define __INTERSECT_RAY_TRIANGLE_HPP__

#include "Vec3.hpp"
#include "Ray3D.hpp"
#include "OBJ_Face.hpp"

class Intersect_RAY_TRIANGLE
{

private:

    static float epsilon;
    static float* n;
    static float* E1;
    static float* E2;
    static float* E_TMP;
    static float* P;
    static float* T;
    static float* Q;
    static float det;
    static float E1x, E1y, E1z;
    static float E2x, E2y, E2z;
    static float nx, ny, nz;
    static float Px, Py, Pz;
    static float Tx, Ty, Tz;
    static float Qx, Qy, Qz;

    static void swap_E1_E2()
    {
        float E_TMP_x = E1x; 
        float E_TMP_y = E1y; 
        float E_TMP_z = E1z; 
        E1x = E2x;
        E1y = E2y;
        E1z = E2z;
        E2x = E_TMP_x;
        E2y = E_TMP_y;
        E2z = E_TMP_z;
    };

public:

    static float u;
    static float v;

    static bool intersect2(Math::Ray3D* ray, float* A, float* B, float* C, bool two_sided, float* ptr_hit_backface, float* tuv);

    static bool intersect(Math::Ray3D* ray, OBJ_Loader::OBJ_Face& face, bool two_sided, float* ptr_hit_backface, float* tuv);

    static bool intersect3(Math::Ray3D* ray, float* A, float* B, float* C, bool two_sided, float* ptr_hit_backface, float* tuv);

    static float intersect(Math::Ray3D* ray, float* A, float* B, float* C, bool two_sided, float* ptr_hit_backface);

};

#endif