#ifndef __VEC3_HPP__
#define __VEC3_HPP__

// #include <algorithm>
// #include <cmath>
#include <random>
#include <sstream>
#include <iostream>

namespace Math
{
    class Vec3
    {        
    public:
        static float* init(float v)
        {
            static float dst[3] {v,v,v};
            return dst;
        }

        static float* nullvector()
        {
            static float dst[3] {0.0f, 0.0f, 0.0f};
            return dst;
        }

       static void nullvector_slf(float* dst)
        {
            dst[0] = 0;
            dst[1] = 0;
            dst[2] = 0;
        }

        static void set_Ref(float x, float y, float z, float* dst)
        {
            dst[0] = x;
            dst[1] = y;
            dst[2] = z;
        }

        static float* set_new(float x, float y, float z)
        {
            static float dst[3] {x, y, z};
            return dst;
        }

        static void copy_ref(float* a, float* dst) 
        {
            dst[0] = a[0];
            dst[1] = a[1];
            dst[2] = a[2];
        }

        static float* copy_new(float* a)
        {
            float* dst;
            dst = new float[3] {a[0], a[1], a[2]};
            return dst;
        }

        static float* min_new(float* a, float* b)
        {
            static float dst[3]
            {
                (float)std::min(a[0], b[0]),
                (float)std::min(a[1], b[1]),
                (float)std::min(a[2], b[2]),
            };
            return dst;
        }

        static float* max_new(float* a, float* b)
        {
            static float dst[3]
            {
                (float)std::max(a[0], b[0]),
                (float)std::max(a[1], b[1]),
                (float)std::max(a[2], b[2]),
            };
            return dst;
        }

        static void min_ref(float* a, float* b, float* dst)
        {
            dst[0] = std::min(a[0], b[0]);
            dst[1] = std::min(a[1], b[1]);
            dst[2] = std::min(a[2], b[2]);
        }
   
        static void max_ref(float* a, float* b, float* dst)
        {
            dst[0] = std::max(a[0], b[0]);
            dst[1] = std::max(a[1], b[1]);
            dst[2] = std::max(a[2], b[2]);
        }

        static void min_ref_slf(float* dst, float* b)
        {
            dst[0] = std::min(dst[0], b[0]);
            dst[1] = std::min(dst[1], b[1]);
            dst[2] = std::min(dst[2], b[2]);
        }
     
        static void max_ref_slf(float* dst, float* b)
        {
            dst[0] = std::max(dst[0], b[0]);
            dst[1] = std::max(dst[1], b[1]);
            dst[2] = std::max(dst[2], b[2]);
        }

        static bool equals(float* a, float* b)
        {
            return (a[0] == b[0] && a[1] == b[1] && a[2] == b[2]);
        }

        static void add_ref_slf(float* a, float* dst)
        {
            dst[0] += a[0];  dst[1] += a[1];   dst[2] += a[2];
        }

        static void add_ref(float* a, float* b, float* dst) 
        {
            dst[0] = a[0]+b[0];  dst[1] = a[1]+b[1];   dst[2] = a[2]+b[2];
        }

        static float* add_new(float* a, float* b)
        {
            static float dst[3] {(a[0]+b[0]),  (a[1]+b[1]),   (a[2]+b[2])};
            return dst;
        }

        static void sub_ref_slf(float* a, float* dst)
        {

            dst[0] -= a[0];  dst[1] -= a[1];   dst[2] -= a[2];
        }

        static void sub_ref(float* a, float* b, float* dst)
        {
            dst[0] = a[0]-b[0];   dst[1] = a[1]-b[1];  dst[2] = a[2]-b[2];
        }
        static float* sub_new(float* a, float* b)
        {
            static float dst[3] {(a[0]-b[0]),  (a[1]-b[1]),  (a[2]-b[2])};
            return dst;
        }

        static void line_midpoint_ref(float* a, float* b, float* dst)
        {
            dst[0] = (a[0] + b[0]) * 0.5f;
            dst[1] = (a[1] + b[1]) * 0.5f;
            dst[2] = (a[2] + b[2]) * 0.5f;
        }

        static float* line_midpoint_new(float* a, float* b)
        {
            static float dst[3] {(a[0]+b[0])*0.5f, (a[1]+b[1])*0.5f, (a[2]+b[2])*0.5f};
            return dst;
        }

        static void triangle_midpoint_ref(float* a, float* b, float* c, float* dst) 
        {
            float f = 1.0f/3.0f;
            dst[0] = (a[0]+b[0]+c[0]) * f;
            dst[1] = (a[1]+b[1]+c[1]) * f;
            dst[2] = (a[2]+b[2]+c[2]) * f;
        }

        static float* triangle_midpoint_new(float* a, float* b, float* c) 
        {
            float f = 1.0f/3.0f;
            static float dst[3] {(a[0]+b[0]+c[0]) * f, (a[1]+b[1]+c[1]) * f, (a[2]+b[2]+c[2]) * f};
            return dst;
        }

        static void sum_ref(float* a, float* b, float* c, float* dst)
        {
            dst[0] = a[0]+b[0]+c[0];
            dst[1] = a[1]+b[1]+c[1];
            dst[2] = a[2]+b[2]+c[2];
        }

        static float* sum_new(float* a, float* b, float* c)
        {
            static float dst[3] {a[0]+b[0]+c[0],  a[1]+b[1]+c[1], a[2]+b[2]+c[2]};
            return  dst;
        }

        static void sumlist_ref(float** arr, float* dst)
        {
            int len = sizeof(arr) / sizeof(arr[0]);
            for(int i = 0; i < len; i++)
            {
                dst[0] += arr[i][0];
                dst[1] += arr[i][1];
                dst[2] += arr[i][2];
            }
        }

        static float* sumlist_new(float** arr)
        {
            // static float dst[3];
            float* dst = new float[3];
            int len = sizeof(arr) / sizeof(arr[0]);
            for(int i = 0; i < len; i++)
            {
                dst[0] += arr[i][0];
                dst[1] += arr[i][1];
                dst[2] += arr[i][2];
            }
            return dst;
        }
        
        static void multiply_ref_slf(float* a, float* dst)
        {
            dst[0] *= a[0];
            dst[1] *= a[1];
            dst[2] *= a[2];
        }

        static void multiply_ref(float* a, float* b, float* dst)
        {
            dst[0] = a[0] * b[0];
            dst[1] = a[1] * b[1];
            dst[2] = a[2] * b[2];
        }
        
        static float* multiply_new(float* a, float* b)
        {
            static float dst[3] {a[0]*b[0], a[1]*b[1], a[2]*b[2]};
            return dst;
        }

        static void negate_ref(float* a, float* dst)
        {
            dst[0] = -a[0];
            dst[1] = -a[1];
            dst[2] = -a[2];
        }

        static void negate_ref_slf(float* a)
        {
            a[0] = -a[0];
            a[1] = -a[1];
            a[2] = -a[2];
        }

        static float* negate_new(float* a)
        {
            static float dst[3] {-a[0], -a[1], -a[2]};
            return dst;
        }
  
        static float* abs_new(float* a)
        {
            static float dst[3] {std::abs(a[0]), std::abs(a[1]), std::abs(a[2]) };
            return dst;
        }
        static void abs_ref(float* a, float* dst)
        {
            dst[0] = std::abs(a[0]);
            dst[1] = std::abs(a[1]);
            dst[2] = std::abs(a[2]);
        }  
        
        static void abs_ref_slf(float* a)
        {
            a[0] = std::abs(a[0]);
            a[1] = std::abs(a[1]);
            a[2] = std::abs(a[2]);
        }
        
        static float minComponent(float* a)
        {
            return std::min(std::min(a[0], a[1]), a[2]);
        }
        
        static float maxComponent(float* a)
        {
            return std::max(std::max(a[0], a[1]), a[2]);
        }
        
        static float minComponent(float a, float b, float c)
        {
            return std::min(std::min(a, b), c);
        }
        
        static float maxComponent(float a, float b, float c)
        {
            return std::max(std::max(a, b), c);
        }
                
        static void scale_ref(float* a, float val, float* dst) 
        {
            dst[0] = a[0] * val;
            dst[1] = a[1] * val;
            dst[2] = a[2] * val;
        }
  
        static void scale_ref_slf(float* a, float val) 
        {
            a[0] *= val;
            a[1] *= val;
            a[2] *= val;
        }

        static float* scale_new(float* a, float val) 
        {
            static float dst[3] {a[0]*val, a[1]*val, a[2]*val};
            return dst;
        }
            
        static float* reciprocal_new(float* a)
        {
            static float dst[3] {1.0f/a[0], 1.0f/a[1], 1.0f/a[2]};
            return dst;
        }

        static void reciprocal_ref(float* a, float* dst)
        {
            dst[0] = 1.0f/a[0];
            dst[1] = 1.0f/a[1];
            dst[2] = 1.0f/a[2];
        }

        static void reciprocal_ref_slf(float* a)
        {
            a[0] = 1.0f/a[0];
            a[1] = 1.0f/a[1];
            a[2] = 1.0f/a[2];
        }

        static void normalize_ref_slf  (float* a)
        {
            float x = a[0], y = a[1], z = a[2];
            float len = (float) std::sqrt(x*x + y*y + z*z);
            if (len != 1.0f)
            {
                a[0] /= len;
                a[1] /= len;
                a[2] /= len;
            }
        }

        static void normalize_ref(float* a, float* dst)
        {
            float x = a[0], y = a[1], z = a[2];
            float len = (float) std::sqrt(x * x + y * y + z * z);
            if (len == 0.0f)
            {
                dst[0] = 0;
                dst[1] = 0;
                dst[2] = 0;
            } 
            else if (len == 1.0f)
            {
                dst[0] = x;
                dst[1] = y;
                dst[2] = z;
            } 
            else 
            {
                dst[0] = x / len;
                dst[1] = y / len;
                dst[2] = z / len;
            }
        }

        static float* normalize_new(float* a) 
        {
            float x = a[0], y = a[1], z = a[2];
            float len = (float) std::sqrt(x * x + y * y + z * z);
            if (len == 0.0f)
            {
                return set_new(0.0f, 0.0f, 0.0f);
            }
            else if (len == 1.0f)
            {
                return set_new(x, y, z);
            }
            else 
            {
                return set_new(x/len, y/len, z/len);
            }
        }
                
        static void cross_ref(float* a, float* b, float* dst) 
        {
            float ax = a[0], ay = a[1], az = a[2];
            float bx = b[0], by = b[1], bz = b[2];

            dst[0] = ay * bz - az * by;
            dst[1] = az * bx - ax * bz;
            dst[2] = ax * by - ay * bx;
        }

        static float* cross_new(float* a, float* b)
        {
            float ax = a[0], ay = a[1], az = a[2];
            float bx = b[0], by = b[1], bz = b[2];

            return set_new(ay*bz - az*by, az*bx - ax*bz, ax*by - ay*bx);
        }

        static float dot(float* a, float* b) 
        {
            return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
        }

        static float angleBetween(float* a, float* b)
        {
            return (float) std::acos( dot(a,b)/(mag(a)*mag(b)) );
        }

        static float angleBetween_unit(float* a, float* b)
        {
            return (float) std::acos( dot(a,b) );
        }

        static float mag(float* a) 
        {
            float x = a[0], y = a[1], z = a[2];
            return (float) std::sqrt(x*x + y*y + z*z);
        }

        static float mag_sq (float* a)
        {
            float x = a[0], y = a[1], z = a[2];
            return x*x + y*y + z*z;
        }

        static void dir_unit_ref(float* a, float* b, float* dst)
        {
            sub_ref(a, b, dst);
            normalize_ref_slf(dst);
        }

        static float* dir_unit_new(float* a, float* b)
        {
            // static float* dst;
            // dst = sub_new(a, b);
            // normalize_ref_slf(dst);
            // return dst;
            return normalize_new( sub_new(a, b) );
        }

        static void lerp_ref(float* a, float* b, float val, float* dst) 
        {
            dst[0] = a[0] + val * (b[0] - a[0]);
            dst[1] = a[1] + val * (b[1] - a[1]);
            dst[2] = a[2] + val * (b[2] - a[2]);
        }

        static float* lerp_new(float* a, float* b, float val) 
        {
            static float dst[3] {a[0]+val*(b[0]-a[0]), a[1]+val*(b[1]-a[1]), a[2]+val*(b[2]-a[2])};
            return dst;
        }

        static float dist(float* a, float* b)
        {
            return mag(sub_new(a, b));
        }

        static float* randF3_new(float size)
        {
            static float dst[3]
            {
                (float) (get_random()-0.5f) * 2.0f * size,
                (float) (get_random()-0.5f) * 2.0f * size,
                (float) (get_random()-0.5f) * 2.0f * size
            };

            return dst;
        }

        static void randF3_ref(float* dst, float size)
        {
            dst[0] = (float) (get_random()-0.5f) * 2.0f * size;
            dst[1] = (float) (get_random()-0.5f) * 2.0f * size;
            dst[2] = (float) (get_random()-0.5f) * 2.0f * size;
        }

        static float* reflect_new(float* V, float* N)
        {
            float c = 2.0f * dot(V, N);
            return set_new(V[0]-c*N[0], V[1]-c*N[1], V[2]-c*N[2]);
        }

        static void reflect_ref(float* V, float* N, float* dst)
        {
            float c = 2.0f * dot(V, N);
            dst[0] = V[0]-c*N[0];
            dst[1] = V[1]-c*N[1];
            dst[2] = V[2]-c*N[2];
        }
  
        static void reflect_ref_slf(float* V, float* N)
        {
            float c = 2.0f * dot(V, N);
            V[0] -= c*N[0];
            V[1] -= c*N[1];
            V[2] -= c*N[2];
        }

        static bool refract_new(float* I, float* N, float eta, float* R)
        {
            float cosNI = dot( N, I );
            float k = 1.0f - eta*eta*(1.0f - cosNI*cosNI);
            if( k > 0.0 )
            {
                R[0] = (eta*I[0]) - (eta*cosNI + (float)std::sqrt(k)) * N[0]; 
                R[1] = (eta*I[1]) - (eta*cosNI + (float)std::sqrt(k)) * N[1]; 
                R[2] = (eta*I[2]) - (eta*cosNI + (float)std::sqrt(k)) * N[2]; 
                return true;
            }
            else
            {
                reflect_ref(I, N, R);
                return false;
            }
        }

        static std::string toStr(float* a, int prec) 
        {
            std::ostringstream a0, a1, a2;
            a0.precision(prec);
            a0 << std::fixed << a[0];
            a1.precision(prec);
            a1 << std::fixed << a[1];
            a2.precision(prec);
            a2 << std::fixed << a[2];
            return (a0.str() + ", " + a1.str() + ", " + a2.str());
            // return (std::to_string(a[0]) + ", " + std::to_string(a[1]) + ", " + std::to_string(a[2]));
        }

        static void print(float* a, int prec) 
        {
            std::cout << toStr(a, prec) << std::endl;
        }

        static float get_random()
        {
            //https://stackoverflow.com/questions/686353/random-float-number-generation
            static std::default_random_engine e;
            static std::uniform_real_distribution<> dis(0, 1); // rage 0 - 1
            return dis(e);
        }

    };
}


#endif