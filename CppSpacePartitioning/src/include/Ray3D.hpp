
#ifndef __RAY3D_HPP__
#define __RAY3D_HPP__
#include "Vec3.hpp"

namespace Math
{

    class Ray3D 
    {
    public:
        float* o;
        float* d;
        float* d_rec;

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
        
        Ray3D() {}
        
        Ray3D copy()
        {
        return Ray3D(Math::Vec3::copy_new(o), Math::Vec3::copy_new(d));
        }

        void normalize()
        {
            Math::Vec3::normalize_ref_slf(d);
            setDirection(d);
        }
        
        float* getPoint(float t)
        {
            return Math::Vec3::add_new(o, Math::Vec3::scale_new(d, t) );
        }
        
        void getPoint_ref(float t, float* dst)
        {
            Math::Vec3::add_ref(o, Math::Vec3::scale_new(d, t), dst);
        }
        
        void setEndpoint(float* endpoint)
        {
            d = Math::Vec3::sub_new(endpoint, o);
            d_rec = new float[3]{1.0f/d[0], 1.0f/d[1], 1.0f/d[2]};
        }
    
        void setStartpoint(float* startpoint)
        {
            o = startpoint;
        }

        void setDirection(float* direction)
        {
            this->d = direction;
            this->d_rec = new float[3]{1.0f/d[0], 1.0f/d[1], 1.0f/d[2]};
        }
    };
}

#endif