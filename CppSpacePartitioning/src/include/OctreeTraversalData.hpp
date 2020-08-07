#include "Vec3.hpp"
#include "OctreeNode.hpp"

namespace OCT
{
    class OctreeTraversalData
    {

    private:

        Math::Vec3 vector3;

    public:

        OctreeTraversalData* prev;
        OctreeNode* node;
        float* t0;
        float* t1;
        
        OctreeTraversalData(OctreeNode* node, float* t0, float* t1)
        {
            this->node = node;
            this->t0 = t0;
            this->t1 = t1;
        }
        
        OctreeTraversalData(OctreeNode* node, float t0x,float t0y, float t0z, float t1x,float t1y,float t1z)
        {
            this->node = node;
            this->t0 = new float[3]{t0x, t0y, t0z};
            this->t1 = new float[3]{t1x, t1y, t1z};
        }
        
        float* tm()
        {
            return vector3.scale_new( vector3.add_new(t0, t1), 0.5f);
        }

        
        float tNear()
        {
            return vector3.maxComponent(t0);
        }

        float tFar ()
        {
            return vector3.minComponent(t1);
        }

    };

}