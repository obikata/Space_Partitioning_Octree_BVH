#include "AABB.hpp"

namespace Math
{

        void AABB::init()
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

        AABB AABB::GetInitializedAABB()
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

        AABB AABB::deep_copy()
        {
            return AABB(vector3.copy_new(_min), vector3.copy_new(_max));
        }

        AABB* AABB::shallow_copy()
        {
            return this;
        }

        float AABB::getVolume()
        {
            float* s = getSize();
            return s[0]*s[1]*s[2];
        }

        float AABB::getSurfaceArea()
        {
            float* s = getSize();
            return (s[0]*s[1] + s[0]*s[2] + s[1]*s[2]) * 2;
        }

        float* AABB::getSize()
        {
            return vector3.sub_new(_max, _min);
        }

        // float* getHalfSize()
        // {
        //     float* dst = new float[3];
        //     vector3.scale_ref(getSize(), 0.5f, dst);
        //     return dst;
        // }

        float* AABB::getCenter()
        {
            float* dst = new float[3];
            vector3.scale_ref(vector3.add_new(_max, _min), 0.5f, dst);
            return dst;
        }

        void AABB::getHalfSizeRef(float* dst)
        {
            dst[0] = (_max[0] - _min[0]) * 0.5f;
            dst[1] = (_max[1] - _min[1]) * 0.5f;
            dst[2] = (_max[2] - _min[2]) * 0.5f;
        }

        void AABB::getCenterRef(float* dst)
        {
            vector3.scale_ref(vector3.add_new(_max, _min), 0.5f, dst);
        }

        float** AABB::getCorners()
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

        bool AABB::isInside(float* v0, float* v1, float* v2)
        {
            return isInside(v0) && isInside(v1) && isInside(v2);
        }

        bool AABB::isInside(float* v)
        {
            return( (v[0]>=_min[0]) && (v[1]>=_min[1]) && (v[2]>=_min[2]) && (v[0]<=_max[0]) && (v[1]<=_max[1]) && (v[2]<=_max[2]));
        }

        void AABB::grow(AABB aabb)
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

        bool AABB::hasSameValues(AABB aabb)
        {
            if( aabb._min[0] != this->_min[0] ) return false;
            if( aabb._min[1] != this->_min[1] ) return false;
            if( aabb._min[2] != this->_min[2] ) return false;
            if( aabb._max[0] != this->_max[0] ) return false;
            if( aabb._max[1] != this->_max[1] ) return false;
            if( aabb._max[2] != this->_max[2] ) return false;
            return true;
        }

        void* AABB::malloc2d(size_t size, int row, int col)
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
}