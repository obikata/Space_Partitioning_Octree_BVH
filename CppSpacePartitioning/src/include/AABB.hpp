#ifndef __AABB_HPP__
#define __AABB_HPP__

#include "Vec3.hpp"

namespace Math
{
    class AABB
    {

    protected:

    public:
        float* _min = new float[3];
        float* _max = new float[3];

        // Default Constructor without arguments
        AABB() {};

        // Constructor with pointers to min and max
        AABB(float* min, float* max)
        {
            _min[0] = min[0];
            _min[1] = min[1];
            _min[2] = min[2];
            _max[0] = max[0];
            _max[1] = max[1];
            _max[2] = max[2];
        };

        // Constructor with pointers to three vertices
        AABB(float* A, float* B, float* C) {};

        void init();

        static AABB GetInitializedAABB();

        AABB deep_copy();

        AABB* shallow_copy();

        float getVolume();

        float getSurfaceArea();

        float* getSize();

        float* getHalfSize();

        float* getCenter();

        void getHalfSizeRef(float* dst);

        void getCenterRef(float* dst);

        float** getCorners();

        bool isInside(float* v0, float* v1, float* v2);

        bool isInside(float* v);

        void grow(AABB aabb);

        bool hasSameValues(AABB aabb);

        void* malloc2d(size_t size, int row, int col);

    };
}

#endif