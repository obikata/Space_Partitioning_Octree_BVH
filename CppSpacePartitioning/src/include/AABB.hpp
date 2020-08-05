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

    public:
        float* _min;
        float* _max;

        Math::Vec3 vector3;

        // Default Constructor without arguments
        AABB() {};

        // Constructor with pointers to min and max
        AABB(float* min, float* max) : _min(min), _max(max) {};

        // Constructor with pointers to three vertices
        AABB(float* A, float* B, float* C)
        {
            float* min;
            float* max;
            min = new float[3];
            max = new float[3];

            min[0] = vector3.minComponent(A[0], B[0], C[0]);
            min[1] = vector3.minComponent(A[1], B[1], C[1]);
            min[2] = vector3.minComponent(A[2], B[2], C[2]);
            max[0] = vector3.maxComponent(A[0], B[0], C[0]);
            max[1] = vector3.maxComponent(A[1], B[1], C[1]);
            max[2] = vector3.maxComponent(A[2], B[2], C[2]);

            _min = min;
            _max = max;
        }

        void init()
        {
            float init_min_component = std::numeric_limits<float>::max();
            float init_max_component = -std::numeric_limits<float>::max();
            float* min;
            float* max;
            min = new float[3];
            max = new float[3];
            // min = (float*)malloc(3 * sizeof(float));
            // max = (float*)malloc(3 * sizeof(float));
            min[0] = init_min_component;
            min[1] = init_min_component;
            min[2] = init_min_component;
            max[0] = init_max_component;
            max[1] = init_max_component;
            max[2] = init_max_component;            
            _min = min;
            _max = max;
        }

        static AABB GetInitializedAABB()
        {
            float init_min_component = std::numeric_limits<float>::max();
            float init_max_component = -std::numeric_limits<float>::max();
            float* min;
            float* max;
            min = new float[3];
            max = new float[3];
            // min = (float*)malloc(3 * sizeof(float));
            // max = (float*)malloc(3 * sizeof(float));
            min[0] = init_min_component;
            min[1] = init_min_component;
            min[2] = init_min_component;
            max[0] = init_max_component;
            max[1] = init_max_component;
            max[2] = init_max_component;            
            return AABB(min, max);
        }

        AABB deep_copy()
        {
            return AABB(vector3.copy_new(_min), vector3.copy_new(_max));
        }

        AABB* shallow_copy()
        {
            return this;
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
            return vector3.sub_new(_max, _min);
        }

        float* getHalfSize()
        {
            return vector3.scale_new(getSize(), 0.5f);
        }

        float* getCenter()
        {
            return vector3.scale_new(vector3.add_new(_max, _min), 0.5f);
        }

        float** getCorners()
        {
            float** corners = (float**)malloc2d(sizeof(float), 8, 3);
            float c0[3] = { _min[0], _min[1], _min[2] }; // [0]
            float c1[3] = { _min[0], _min[1], _max[2] }; // [2]
            float c2[3] = { _min[0], _max[1], _min[2] }; // [1]
            float c3[3] = { _min[0], _max[1], _max[2] }; // [3]
            float c4[3] = { _max[0], _min[1], _min[2] }; // [4]
            float c5[3] = { _max[0], _min[1], _max[2] }; // [5]
            float c6[3] = { _max[0], _max[1], _min[2] }; // [6]
            float c7[3] = { _max[0], _max[1], _max[2] }; // [7]
            for (int i = 0; i < 3; i++) corners[0][i] = c0[i];
            for (int i = 0; i < 3; i++) corners[1][i] = c1[i];
            for (int i = 0; i < 3; i++) corners[2][i] = c2[i];
            for (int i = 0; i < 3; i++) corners[3][i] = c3[i];
            for (int i = 0; i < 3; i++) corners[4][i] = c4[i];
            for (int i = 0; i < 3; i++) corners[5][i] = c5[i];
            for (int i = 0; i < 3; i++) corners[6][i] = c6[i];
            for (int i = 0; i < 3; i++) corners[7][i] = c7[i];
            return corners;
        }

        bool isInside(float* v0, float* v1, float* v2)
        {
            return isInside(v0) && isInside(v1) && isInside(v2);
        }

        bool isInside(float* v)
        {
            return( (v[0]>=_min[0]) && (v[1]>=_min[1]) && (v[2]>=_min[2]) && (v[0]<=_max[0]) && (v[1]<=_max[1]) && (v[2]<=_max[2]));
        }

        void grow(AABB aabb)
        {
            vector3.min_ref_slf(this->_min, aabb._min);
            vector3.max_ref_slf(this->_max, aabb._max);
            // if( aabb.min[0] < min[0] ) min[0]=aabb.min[0];
            // if( aabb.min[1] < min[1] ) min[1]=aabb.min[1];
            // if( aabb.min[2] < min[2] ) min[2]=aabb.min[2];
            // if( aabb.max[0] > max[0] ) max[0]=aabb.max[0];
            // if( aabb.max[1] > max[1] ) max[1]=aabb.max[1];
            // if( aabb.max[2] > max[2] ) max[2]=aabb.max[2];
        }

        bool hasSameValues(AABB aabb)
        {
            if( aabb._min[0] != this->_min[0] ) return false;
            if( aabb._min[1] != this->_min[1] ) return false;
            if( aabb._min[2] != this->_min[2] ) return false;
            if( aabb._max[0] != this->_max[0] ) return false;
            if( aabb._max[1] != this->_max[1] ) return false;
            if( aabb._max[2] != this->_max[2] ) return false;
            return true;
        }

        void* malloc2d(size_t size, int row, int col)
        {

            // http://pukulab.blog.fc2.com/blog-entry-28.html
            // https://qiita.com/tanabeman/items/bb39e9d1ddb67ddf4233

            char **a, *b;
            int  t = size * col;
        
            // インデックスと要素を一気に確保
            a = (char**)malloc((sizeof(*a) + t) * row);
            
            if (a) {
                // [インデックス, インデックス, ..., 要素, 要素, 要素, ...]
                // と整列させるため要素の開始位置をずらす
                b = (char*)(a + row);
        
                // 各行の先頭アドレスを与える
                for (int i = 0; i < row; i++) {
                    a[i] = b;
                    b += t; // 要素のサイズ×列の長さの分だけずらす
                }
        
                return a;
            }
            
            return nullptr;
        }

    };
}

#endif