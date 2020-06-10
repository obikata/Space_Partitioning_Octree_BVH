#ifndef __AABB_HPP__
#define __AABB_HPP__

// #include <cstddef>
// #include <iostream>
// #include <limits>
#include "Vec3.hpp"

namespace Math
{
    class AABB
    {

    protected:
        float* _min;
        float* _max;

    public:

        Math::Vec3 vector3;

        AABB() : _min(vector3.nullvector()), _max(vector3.nullvector()) {};
        
        AABB(float* min, float* max) : _min(min), _max(max) {};

        AABB(float* A, float* B, float* C)
        {
            float min[3]
            {
                vector3.minComponent(A[0], B[0], C[0]),
                vector3.minComponent(A[1], B[1], C[1]),
                vector3.minComponent(A[2], B[2], C[2])
            };
            float max[3]
            {
                vector3.maxComponent(A[0], B[0], C[0]),
                vector3.maxComponent(A[1], B[1], C[1]),
                vector3.maxComponent(A[2], B[2], C[2])
            };
            this->min = min;
            this->max = max;
        }

        static AABB init()
        {
            float numeric_limits_min = std::numeric_limits<float>::min();
            float numeric_limits_max = std::numeric_limits<float>::max();
            float min[3] {numeric_limits_min, numeric_limits_min, numeric_limits_min};
            float max[3] {numeric_limits_max, numeric_limits_max, numeric_limits_max};
            return AABB(min, max);
        }

        AABB copy()
        {
            return AABB(vector3.copy_new(min), vector3.copy_new(max));
        }

        float getVolume()
        {
            float* s = getSize();
            return s[0]*s[1]*s[2];
        }

        float getSurfaceArea()
        {
            float* s = getSize();
            return (s[0]*s[1] + s[0]*s[2] + s[1]*s[2]) * 2;
        }

        float* getSize()
        {
            return vector3.sub_new(max, min);
        }

        float* getHalfSize()
        {
            return vector3.scale_new(getSize(), 0.5f);
        }

        float* getCenter()
        {
            return vector3.scale_new(vector3.add_new(max, min), 0.5f);
        }

        float** getCorners()
        {
            float** multiArr = new float*[8];
            multiArr[0] = new float[3] { min[0], min[1],min[2] }; // [0]
            multiArr[1] = new float[3] { min[0], min[1],max[2] }; // [1]
            multiArr[2] = new float[3] { min[0], max[1],min[2] }; // [2]
            multiArr[3] = new float[3] { min[0], max[1],max[2] }; // [3]
            multiArr[4] = new float[3] { max[0], min[1],min[2] }; // [4]
            multiArr[5] = new float[3] { max[0], min[1],max[2] }; // [5]
            multiArr[6] = new float[3] { max[0], max[1],min[2] }; // [6]
            multiArr[7] = new float[3] { max[0], max[1],max[2] }; // [7]
            return multiArr;
        }

        bool isInside(float* v0, float* v1, float* v2)
        {
            return isInside(v0) && isInside(v1) && isInside(v2);
        }

        bool isInside(float* v)
        {
            return( (v[0]>=min[0]) && (v[1]>=min[1]) && (v[2]>=min[2]) && (v[0]<=max[0]) && (v[1]<=max[1]) && (v[2]<=max[2]));
        }

        AABB grow(AABB& aabb)
        {
            vector3.min_ref_slf(this->min, aabb.min);
            vector3.max_ref_slf(this->max, aabb.max);
            // if( aabb.min[0] < min[0] ) min[0]=aabb.min[0];
            // if( aabb.min[1] < min[1] ) min[1]=aabb.min[1];
            // if( aabb.min[2] < min[2] ) min[2]=aabb.min[2];
            // if( aabb.max[0] > max[0] ) max[0]=aabb.max[0];
            // if( aabb.max[1] > max[1] ) max[1]=aabb.max[1];
            // if( aabb.max[2] > max[2] ) max[2]=aabb.max[2];
            return *this;
        }

        bool hasSameValues(AABB& aabb)
        {
            if( aabb.min[0] != min[0] ) return false;
            if( aabb.min[1] != min[1] ) return false;
            if( aabb.min[2] != min[2] ) return false;
            if( aabb.max[0] != max[0] ) return false;
            if( aabb.max[1] != max[1] ) return false;
            if( aabb.max[2] != max[2] ) return false;
            return true;
        }
    };
}

#endif