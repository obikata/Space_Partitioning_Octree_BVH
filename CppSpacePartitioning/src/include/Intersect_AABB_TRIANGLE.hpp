#ifndef __INTERSECT_AABB_TRIANGLE_HPP__
#define __INTERSECT_AABB_TRIANGLE_HPP__

/**
 * 
 *   author: (c)thomas diewald, http://thomasdiewald.com/
 *   date: 12.09.2012
 *   
 *
 * This source is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * A copy of the GNU General Public License is available on the World
 * Wide Web at <http://www.gnu.org/copyleft/gpl.html>. You can also
 * obtain it by writing to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "Vec3.hpp"

// adapted from:
// http://fileadmin.cs.lth.se/cs/personal/tomas_akenine-moller/pubs/tribox.pdf
// http://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/code/tribox3.txt
// http://www.toxicengine.org/developers/reference/triboxoverlap_8cpp-source.html
// http://www.koders.com/cpp/fid17736F013E5860D198107D9B7D494AF15ABB6A79.aspx?s=ray
//
// other: 
// http://www.geometrictools.com/LibMathematics/Distance/Distance.html
// http://tog.acm.org/resources/GraphicsGems/gemsiii/triangleCube.c
// http://clb.demon.fi/MathGeoLib/docs/Triangle.cpp_code.html#459

class Intersect_AABB_TRIANGLE 
{
  
  private:
    static Math::Vec3 vector3;
    static bool AXISTEST(float rad, float p0, float p1){
      return (std::min(p0,p1) > rad || std::max(p0,p1)< -rad);
    }
    
    static bool directionTest(float a, float b, float c, float hs){
      return (vector3.minComponent(a,b,c) > hs ||vector3.maxComponent(a,b,c) < -hs); 
    }
  
  public:
    static bool planeBoxOverlap(float* normal, float d, float* hs);  
          
    // modified version, ... better refer to original version!
    static bool overlaps_( float* center, float* halfsize, float* A, float* B, float* C);

    static bool overlaps( float* aabb_min, float* aabb_max, float* A, float* B, float* C);

};

#endif