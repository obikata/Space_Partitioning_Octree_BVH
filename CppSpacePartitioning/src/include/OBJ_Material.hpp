#ifndef __OBJ_MATERIAL_HPP__
#define __OBJ_MATERIAL_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include "HELPER.hpp"
#include "Vec3.hpp"
#include "OBJ_File.hpp"

namespace OBJ_Loader
{
    class OBJ_Material : public OBJ_File
    {

    public:
        Math::Vec3 vector3;
        std::string _name; // material name
        float _Ns = 0.0f; // coeff specular [0,100] ... glossiness
        float _Ni = 0.0f; // index of refraction
        float _d = 0.0f; // transparency or dissolved [0,1] = 1-Tr
        float _Tr = 0.0f; // transparency [0, 1]
        float _Tf[3] = {0.0f, 0.0f, 0.0f}; // color transparency
        // float* _Tf; // color transparency
        float _illum; // illumination model
        float _Ka[3] = {0.0f, 0.0f, 0.0f}; // color ambient 3x[0,1]
        float _Kd[3] = {0.0f, 0.0f, 0.0f}; // color diffuse 3x[0,1]
        float _Ks[3] = {0.0f, 0.0f, 0.0f}; // color specular 3x[0,10] ... specular*specular-level (3dsmax)
        float _Ke[3] = {0.0f, 0.0f, 0.0f}; // color self emitting
        float _reflectivity = 0.0f;
        bool _is_reflective = false;
        bool _is_emissive = false;
        bool _is_glossy = false;

        // OBJ_Material() {};
        OBJ_Material(std::string name) : _name(name) {};
        
        void printMaterial();

        // callable functions without generating an object
        static std::vector<OBJ_Material> loadFromFile(std::string path, std::string filename);
  
        static OBJ_Material getByName(std::vector<OBJ_Material> materials, std::string name);

        static bool checkByName(std::vector<OBJ_Material> materials, std::string name);

        static OBJ_Material mat_default();

    private:
        static void addToList(OBJ_Material mat)
        {
        //    mat.Ks[0] *= 0.1f;
        //    mat.Ks[1] *= 0.1f;
        //    mat.Ks[2] *= 0.1f;
        //    mat.Ns    *= 10.0f;
            mat._reflectivity  = mat._Ka[0];
            // mat.printMaterial();
            
            mat._is_reflective = (mat._Ka[0] > 0.0f);
            mat._is_emissive   = (mat._Ke[0] > 0.0f) || (mat._Ke[1] > 0.0f) || (mat._Ke[2] > 0.0f);
            mat._is_glossy     = (mat._Ks[0] > 0.0f) || (mat._Ks[1] > 0.0f) || (mat._Ks[2] > 0.0f);
            mat._Ke[0] *= 10.0f;
            mat._Ke[1] *= 10.0f;
            mat._Ke[2] *= 10.0f;
        }

    };
}

#endif