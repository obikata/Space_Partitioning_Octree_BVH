#include "Vec3.hpp"

namespace Math
{

    Math::Vec3 vector3;

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
    
    Ray3D(){}
    
    Ray3D copy()
    {
       return Ray3D(vector3.copy_new(o), vector3.copy_new(d));
    }

    void normalize()
    {
        vector3.normalize_ref_slf(d);
        setDirection(d);
    }
    
    float* getPoint(float t)
    {
        return vector3.add_new(o, vector3.scale_new(d, t) );
    }
    
    void getPoint_ref(float t, float* dst)
    {
        vector3.add_ref(o, vector3.scale_new(d, t), dst);
    }

    // void draw(PApplet p)
    // {
    //     float* e = getPoint(1);
    //     p.line(o[0], o[1], o[2], e[0], e[1], e[2]);
    // }
    
    // void draw(PApplet p, float t)
    // {
    //     float* e = getPoint(t);
    //     p.line(o[0], o[1], o[2], e[0], e[1], e[2]);
    // }
    
    void setEndpoint(float* endpoint)
    {
        d = vector3.sub_new(endpoint, o);
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
  }


}