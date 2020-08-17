#ifndef __INTERSECT_AABB_TRIANGLE_HPP__
#define __INTERSECT_AABB_TRIANGLE_HPP__

#include "Vec3.hpp"
#include "AABB.hpp"

class Intersect_AABB_TRIANGLE 
{
  
  private:
    static bool AXISTEST(float rad, float p0, float p1){
      return (std::min(p0,p1) > rad || std::max(p0,p1)< -rad);
    }
      
  public:
    static bool planeBoxOverlap(float* normal, float d, float* hs);  
          
    // modified version, ... better refer to original version!
    static bool overlaps_( float* center, float* halfsize, float* A, float* B, float* C);

    static bool overlaps( Math::AABB* aabb, float* A, float* B, float* C);

    static bool directionTest(float a, float b, float c, float hs);

};

#endif