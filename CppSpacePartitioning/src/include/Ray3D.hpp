
#ifndef __RAY3D_HPP__
#define __RAY3D_HPP__
#include "Vec3.hpp"

namespace Math
{

    class Ray3D 
    {
    public:
        float* _o;
        float* _d;
        float* _d_rec;

        Ray3D(float* o, float* d)
        {
            setStartpoint(o);
            setDirection(d);
        }

        void set(float* o, float* d)
        {
            setStartpoint(o);
            setDirection(d);
        }
        
        // Ray3D() {}
        
        Ray3D* copy()
        {
        return new Ray3D(Math::Vec3::copy_new(_o), Math::Vec3::copy_new(_d));
        }

        void normalize()
        {
            Math::Vec3::normalize_ref_slf(_d);
            setDirection(_d);
        }
        
        float* getPoint(float t)
        {
            return Math::Vec3::add_new(_o, Math::Vec3::scale_new(_d, t) );
        }
        
        void getPoint_ref(float t, float* dst)
        {
            Math::Vec3::add_ref(_o, Math::Vec3::scale_new(_d, t), dst);
        }
        
        void setEndpoint(float* endpoint)
        {
            _d = Math::Vec3::sub_new(endpoint, _o);
            float* d_rec = Math::Vec3::set_new(1.0f/_d[0], 1.0f/_d[1], 1.0f/_d[2]);
        }
    
        void setStartpoint(float* startpoint)
        {
            _o = startpoint;
        }

        void setDirection(float* direction)
        {
            _d = direction;
            _d_rec = Math::Vec3::set_new(1.0f/_d[0], 1.0f/_d[1], 1.0f/_d[2]);
        }
    };
}

#endif