#include "Intersect_AABB_TRIANGLE.hpp"

bool Intersect_AABB_TRIANGLE::planeBoxOverlap(float* normal, float d, float* hs) {
  float vmin[3] { (normal[0]>0.0)? -hs[0]:+hs[0],
                  (normal[1]>0.0)? -hs[1]:+hs[1],
                  (normal[2]>0.0)? -hs[2]:+hs[2] };
  
  if(vector3.dot(normal, vmin) + d >  0.0) return false;
  float* vmax = vector3.negate_new(vmin);
  if(vector3.dot(normal, vmax) + d >= 0.0) return true;
  return false;
};

// modified version, ... better refer to original version!
bool Intersect_AABB_TRIANGLE::overlaps_( float* center, float* halfsize, float* A, float* B, float* C) {
  // Use separating axis theorem to test overlap between triangle and box.
  // Need to test for overlap in these directions:
  // 1) the {x,y,z}-directions (actually, since we use the AABB of the triangle we do not even need to test these)
  // 2) normal of the triangle
  // 3) crossproduct(edge from triangle, {x,y,z}-direction). This gives 3x3=9 more tests.
  
  // Move everything so that the boxcenter is in (0,0,0).
  float* hs = halfsize;
  float v0[3];
  float v1[3];
  float v2[3];
  vector3.sub_ref(A, center, v0);
  vector3.sub_ref(B, center, v1);
  vector3.sub_ref(C, center, v2);

  // Bullet 3:
  //   Test the 9 tests first (this was faster).
  
  float ea[3];
  float e_v0[3];
  float e_v1[3];
  float e_v2[3];
  
  // EDGE 0
  float e0[3];
  vector3.sub_ref(v1, v0, e0);
  vector3.abs_ref  (e0, ea);
  vector3.cross_ref(e0, v0, e_v0);
  vector3.cross_ref(e0, v1, e_v1);
  vector3.cross_ref(e0, v2, e_v2);
  
  if( AXISTEST(ea[2]*hs[1] + ea[1]*hs[2],  e_v0[0], e_v2[0]) ) return false; // X
  if( AXISTEST(ea[2]*hs[0] + ea[0]*hs[2],  e_v0[1], e_v2[1]) ) return false; // Y
  if( AXISTEST(ea[1]*hs[0] + ea[0]*hs[1],  e_v1[2], e_v2[2]) ) return false; // Z 

  // EDGE 1
  float e1[3];
  vector3.sub_ref(v2, v1, e1);
  vector3.abs_ref  (e1, ea);
  vector3.cross_ref(e1, v0, e_v0);
  vector3.cross_ref(e1, v1, e_v1);
  vector3.cross_ref(e1, v2, e_v2);
  
  if( AXISTEST(ea[2]*hs[1] + ea[1]*hs[2],  e_v0[0], e_v2[0]) ) return false;   
  if( AXISTEST(ea[2]*hs[0] + ea[0]*hs[2],  e_v0[1], e_v2[1]) ) return false;   
  if( AXISTEST(ea[1]*hs[0] + ea[0]*hs[1],  e_v0[2], e_v1[2]) ) return false; 
    
  // EDGE 2
  float e2[3];
  vector3.sub_ref(v0, v2, e2);
  vector3.abs_ref  (e2, ea);
  vector3.cross_ref(e2, v0, e_v0);
  vector3.cross_ref(e2, v1, e_v1);
  vector3.cross_ref(e2, v2, e_v2);
  
  if( AXISTEST(ea[2]*hs[1] + ea[1]*hs[2],  e_v0[0], e_v1[0]) ) return false;   
  if( AXISTEST(ea[2]*hs[0] + ea[0]*hs[2],  e_v0[1], e_v1[1]) ) return false;   
  if( AXISTEST(ea[1]*hs[0] + ea[0]*hs[1],  e_v1[2], e_v2[2]) ) return false;   

  // Bullet 1:
  //   First test overlap in the {x,y,z}-directions.
  //   Find min, max of the triangle each direction, and test for overlap in that
  //   direction -- this is equivalent to testing a minimal AABB around the triangle against the AABB.
  if(directionTest(v0[0], v1[0], v2[0], hs[0]) ) return false; // Test in X-direction.
  if(directionTest(v0[1], v1[1], v2[1], hs[1]) ) return false; // Test in Y-direction.
  if(directionTest(v0[2], v1[2], v2[2], hs[2]) ) return false; // Test in Z-direction.
  

  // Bullet 2:
  //   Test if the box intersects the plane of the triangle. Compute plane equation of triangle: normal*x+d=0.
  float* normal = vector3.cross_new(e0, e1);
  float d = -vector3.dot(normal, v0);  // plane eq: normal.x+d=0
  if(!planeBoxOverlap(normal, d, hs)) return false;
  
  // std::cout << "overlaps" << std::endl;
  return true; // box and triangle overlaps
};

bool Intersect_AABB_TRIANGLE::overlaps(Math::AABB* aabb, float* A, float* B, float* C) {
  float hs[3];
  aabb->getHalfSizeRef(hs);
  float center[3];
  vector3.add_ref(aabb->_min, hs, center);
  return overlaps_(center, hs, A, B, C);
};

bool Intersect_AABB_TRIANGLE::directionTest(float a, float b, float c, float hs) {
  return (vector3.minComponent(a,b,c) > hs || vector3.maxComponent(a,b,c) < -hs); 
};