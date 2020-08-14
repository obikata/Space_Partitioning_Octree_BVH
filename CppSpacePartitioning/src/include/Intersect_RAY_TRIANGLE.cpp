#include "Intersect_RAY_TRIANGLE.hpp"

float Intersect_RAY_TRIANGLE::epsilon = 0.0001f;
float* Intersect_RAY_TRIANGLE::n = new float[3];
float* Intersect_RAY_TRIANGLE::E1 = new float[3];
float* Intersect_RAY_TRIANGLE::E2 = new float[3];
float* Intersect_RAY_TRIANGLE::E_TMP = new float[3];
float* Intersect_RAY_TRIANGLE::P  = new float[3];
float* Intersect_RAY_TRIANGLE::T  = new float[3];
float* Intersect_RAY_TRIANGLE::Q  = new float[3];
float Intersect_RAY_TRIANGLE::det;
float Intersect_RAY_TRIANGLE::E1x, Intersect_RAY_TRIANGLE::E1y, Intersect_RAY_TRIANGLE::E1z;
float Intersect_RAY_TRIANGLE::E2x, Intersect_RAY_TRIANGLE::E2y, Intersect_RAY_TRIANGLE::E2z;
float Intersect_RAY_TRIANGLE::nx, Intersect_RAY_TRIANGLE::ny, Intersect_RAY_TRIANGLE::nz;
float Intersect_RAY_TRIANGLE::Px, Intersect_RAY_TRIANGLE::Py, Intersect_RAY_TRIANGLE::Pz;
float Intersect_RAY_TRIANGLE::Tx, Intersect_RAY_TRIANGLE::Ty, Intersect_RAY_TRIANGLE::Tz;
float Intersect_RAY_TRIANGLE::Qx, Intersect_RAY_TRIANGLE::Qy, Intersect_RAY_TRIANGLE::Qz;
float Intersect_RAY_TRIANGLE::u, Intersect_RAY_TRIANGLE::v;

bool Intersect_RAY_TRIANGLE::intersect2(Math::Ray3D* ray, float* A, float* B, float* C, bool two_sided, float* ptr_hit_backface, float* tuv)
{
    Math::Vec3::sub_ref(B, A, E1); // edge1: v0 -> v1
    Math::Vec3::sub_ref(C, A, E2); // edge2: v0 -> v2
    Math::Vec3::cross_ref(E1, E2, n);     // normal
    if( Math::Vec3::dot(n, ray->_d) > 0.0f)
    { // angle > 0.0
        ptr_hit_backface[0] = -1.0f;   // if there is any intersection it would be with a backface
        if( two_sided )
        {              // so if the triangle is two_sided, switch edges for further computation
            E_TMP = E1; E1 = E2; E2 = E_TMP;
        }
        else
        {
            return false;      // otherwise return "no intersection"
        }
    }
    else
    {
        ptr_hit_backface[0]= +1.0f;    // no backface, so normal direction stays the same
    }

    Math::Vec3::cross_ref(ray->_d, E2, P); // cross of ray-direction and edge2
    det = Math::Vec3::dot(E1, P);        // determinant
    if( std::abs(det) < epsilon ) return false;
    // if( det < epsilon ) return false;

    Math::Vec3::sub_ref(ray->_o, A, T);   // vector: v0 -> ray-origin
    u = Math::Vec3::dot(T, P);        // param u, + testing bounds
    if( u < 0.0f || u > det) return false;

    Math::Vec3::cross_ref(T, E1, Q); // cross of T and edge2
    v = Math::Vec3::dot(Q, ray->_d);        // param v, + testing bounds
    if( v < 0.0f || (u+v) > det) return false;

    det = 1.0f/det;
    tuv[0] = det*Math::Vec3::dot(Q, E2);
    tuv[1] = det*u;
    tuv[2] = det*v;
    return true;
}
  
bool Intersect_RAY_TRIANGLE::intersect(Math::Ray3D* ray, OBJ_Loader::OBJ_Face& face, bool two_sided, float* ptr_hit_backface, float* tuv)
{
    float* A = face.A();
    float* B = face.B();
    float* C = face.C();
    n = face.getNormal(0.33f, 0.33f);
    Math::Vec3::sub_ref(B, A, E1); // edge1: v0 -> v1
    Math::Vec3::sub_ref(C, A, E2); // edge2: v0 -> v2
    
    // Math::Vec3::cross_ref(E1, E2, n);     // normal
    if( Math::Vec3::dot(n, ray->_d) < 0.0f)
    { // angle > 0.0
        ptr_hit_backface[0] = -1.0f;   // if there is any intersection it would be with a backface
        if( two_sided )
        {              // so if the triangle is two_sided, switch edges for further computation
            E_TMP = E1; E1 = E2; E2 = E_TMP;
        }
        else
        {
            return false;      // otherwise return "no intersection"
        }
    }
    else
    {
        ptr_hit_backface[0]= +1.0f;    // no backface, so normal direction stays the same
    }

    Math::Vec3::cross_ref(ray->_d, E2, P); // cross of ray-direction and edge2
    det = Math::Vec3::dot(E1, P);        // determinant
    if( std::abs(det) < epsilon ) return false;
    // if( det < epsilon ) return false;

    Math::Vec3::sub_ref(ray->_o, A, T);   // vector: v0 -> ray-origin
    u = Math::Vec3::dot(T, P);        // param u, + testing bounds
    if( u < 0.0f || u > det) return false;

    Math::Vec3::cross_ref(T, E1, Q); // cross of T and edge2
    v = Math::Vec3::dot(Q, ray->_d);        // param v, + testing bounds
    if( v < 0.0f || (u+v) > det) return false;

    det = 1.0f/det;
    tuv[0] = det*Math::Vec3::dot(Q, E2);
    tuv[1] = det*u;
    tuv[2] = det*v;
    return true;
}

bool Intersect_RAY_TRIANGLE::intersect3(Math::Ray3D* ray, float* A, float* B, float* C, bool two_sided, float* ptr_hit_backface, float* tuv)
{

    float rdx = ray->_d[0];
    float rdy = ray->_d[1];
    float rdz = ray->_d[2];

    // edge1: v0 -> v1     // edge2: v0 -> v2
    E1x = B[0]-A[0];  E2x = C[0]-A[0];
    E1y = B[1]-A[1];  E2y = C[1]-A[1]; 
    E1z = B[2]-A[2];  E2z = C[2]-A[2];

    // normal
    nx = E1y * E2z - E1z * E2y;
    ny = E1z * E2x - E1x * E2z;
    nz = E1x * E2y - E1y * E2x;
    
    if( (nx*rdx+ny*rdy+nz*rdz) > 0.0f)
    { // angle > 0.0
        ptr_hit_backface[0] = -1.0f;   // if there is any intersection it would be with a backface
        if( two_sided )
        {              // so if the triangle is two_sided, switch edges for further computation
            swap_E1_E2();
        } 
        else
        {
            return false;      // otherwise return "no intersection"
        }
    }
    else
    {
        ptr_hit_backface[0]= +1.0f;    // no backface, so normal direction stays the same
    }

    // cross of ray-direction and edge2
    Px = rdy * E2z - rdz * E2y;
    Py = rdz * E2x - rdx * E2z;
    Pz = rdx * E2y - rdy * E2x;
    
    det = E1x*Px + E1y*Py + E1z*Pz; // determinant
    if( std::abs(det) < epsilon ) return false;
    // if( det < epsilon ) return std::numeric_limits<float>::max();
    
    // vector: v0 -> ray-origin
    Tx = ray->_o[0] - A[0];
    Ty = ray->_o[1] - A[1];
    Tz = ray->_o[2] - A[2];
    u = Tx*Px + Ty*Py + Tz*Pz; // param u, + testing bounds
    if( u < 0.0f || u > det) return false;

    // cross of T and edge2
    Qx = Ty * E1z - Tz * E1y;
    Qy = Tz * E1x - Tx * E1z;
    Qz = Tx * E1y - Ty * E1x;
    v = Qx*rdx + Qy*rdy + Qz*rdz; // param v, + testing bounds
    if( v < 0.0f || (u+v) > det) return false;

    det = 1.0f/det;
    tuv[0] = det*(Qx*E2x + Qy*E2y + Qz*E2z);
    tuv[1] = det*u;
    tuv[2] = det*v;
    return true;
}


float Intersect_RAY_TRIANGLE::intersect(Math::Ray3D* ray, float* A, float* B, float* C, bool two_sided, float* ptr_hit_backface)
{
    Math::Vec3::sub_ref(B, A, E1); // edge1: v0 -> v1
    Math::Vec3::sub_ref(C, A, E2); // edge2: v0 -> v2
    
    Math::Vec3::cross_ref(E1, E2, n);     // normal
    if( Math::Vec3::dot(n, ray->_d) > 0.0f)
    { // angle > 0.0
        ptr_hit_backface[0] = -1.0f;   // if there is any intersection it would be with a backface
        if( two_sided )
        {              // so if the triangle is two_sided, switch edges for further computation
            float* tmp = E1; E1 = E2; E2 = tmp;
        }
        else
        {
            return std::numeric_limits<float>::max();      // otherwise return "no intersection"
        }
    } 
    else
    {
        ptr_hit_backface[0]= +1.0f;    // no backface, so normal direction stays the same
    }

    
    Math::Vec3::cross_ref(ray->_d, E2, P); // cross of ray-direction and edge2
    det = Math::Vec3::dot(E1, P);       // determinant
    if( std::abs(det) < epsilon ) return std::numeric_limits<float>::max();
    // if( det < epsilon ) return std::numeric_limits<float>::max();
    
    Math::Vec3::sub_ref(ray->_o, A, T);   // vector: v0 -> ray-origin
    u = Math::Vec3::dot(T, P);        // param u, + testing bounds
    if( u < 0.0f || u > det) return std::numeric_limits<float>::max();

    Math::Vec3::cross_ref(T, E1, Q); // cross of T and edge2
    v = Math::Vec3::dot(Q, ray->_d);        // param v, + testing bounds
    if( v < 0.0f || (u+v) > det) return std::numeric_limits<float>::max();

    u/=det;
    v/=det;
    return Math::Vec3::dot(Q, E2)/det; // intersection parameter for ray: P(intersect) = o(origin) + t*d(direction);
}