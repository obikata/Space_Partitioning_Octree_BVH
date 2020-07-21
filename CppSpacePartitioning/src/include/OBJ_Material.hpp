#ifndef __OBJ_MATERIAL_HPP__
#define __OBJ_MATERIAL_HPP__

// #include <iostream>
// #include <fstream>
// #include <string>
// #include <vector>
// #include <sstream>
// #include <string>
// #include <iostream>
#include "HELPER.hpp"
#include "Vec3.hpp"

namespace OBJ_Loader
{
    class OBJ_Material
    {

    public:
        static OBJ_Material MAT_DEFAULT;
        Math::Vec3 vector3;

        std::string _name; // material name
        float _Ns; // coeff specular [0,100] ... glossiness
        float _Ni; // index of refraction
        float _d; // transparency or dissolved [0,1] = 1-Tr
        float _Tr; // transparency [0, 1]
        float* _Tf; // color transparency
        float _illum; // illumination model
        float* _Ka; // color ambient 3x[0,1]
        float* _Kd; // color diffuse 3x[0,1]
        float* _Ks; // color specular 3x[0,10] ... specular*specular-level (3dsmax)
        float* _Ke; // color self emitting
        float _reflectivity;      
        bool _is_reflective;
        bool _is_emissive;
        bool _is_glossy;

        OBJ_Material(std::string name) : _name(name), _Ns(0), _Ni(0), _d(0), _Tr(0), _Tf(nullptr), _illum(0), _Ka(nullptr), _Kd(nullptr), _Ks(nullptr), _Ke(nullptr), _reflectivity(0), _is_reflective(false), _is_emissive(false), _is_glossy(false) {};
        
        void printMaterial();

        std::vector<OBJ_Material> loadFromFile(const char *filename);
  
        OBJ_Material getByName(std::vector<OBJ_Material> materials, std::string name);

        OBJ_Material mat_default();

    private:
        void addToList(std::vector<OBJ_Material> material_list, OBJ_Material mat)
        {
        //    mat.Ks[0] *= 0.1f;
        //    mat.Ks[1] *= 0.1f;
        //    mat.Ks[2] *= 0.1f;
        //    mat.Ns    *= 10.0f;
            mat._reflectivity  = mat._Ka[0];
        //    mat.printMaterial();
            
            mat._is_reflective = (mat._Ka[0] > 0.0);
            mat._is_emissive   = (mat._Ke[0] > 0.0) || (mat._Ke[1] > 0.0) || (mat._Ke[2] > 0.0);
            mat._is_glossy     = (mat._Ks[0] > 0.0) || (mat._Ks[1] > 0.0) || (mat._Ks[2] > 0.0);
            mat._Ke[0] *= 10;
            mat._Ke[1] *= 10;
            mat._Ke[2] *= 10;
            material_list.push_back(mat);
        }

    };
}

#endif