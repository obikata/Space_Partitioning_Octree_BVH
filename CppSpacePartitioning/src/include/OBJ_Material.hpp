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

namespace OBJ_Loader
{
    class OBJ_Material
    {

    private:
        static void addToList(std::vector<OBJ_Material> material_list, OBJ_Material mat)
        {
      //    mat.Ks[0] *= 0.1f;
      //    mat.Ks[1] *= 0.1f;
      //    mat.Ks[2] *= 0.1f;
      //    mat.Ns    *= 10.0f;
          mat.reflectivity  = mat.Ka[0];
      //    mat.printMaterial();
          
          mat.is_reflective = (mat.Ka[0] > 0.0);
          mat.is_emissive   = (mat.Ke[0] > 0.0) || (mat.Ke[1] > 0.0) || (mat.Ke[2] > 0.0);
          mat.is_glossy     = (mat.Ks[0] > 0.0) || (mat.Ks[1] > 0.0) || (mat.Ks[2] > 0.0);
          mat.Ke[0] *= 10;
          mat.Ke[1] *= 10;
          mat.Ke[2] *= 10;
          material_list.push_back(mat);
        }

        static OBJ_Material mat_null()
        {
            NULL;
        }

        static OBJ_Material mat_default()
        {
            MAT_DEFAULT = OBJ_Material("mat_default");
            MAT_DEFAULT.Ns     = 10.0f;
            MAT_DEFAULT.Ni     = 1.5f;
            MAT_DEFAULT.d      = 1.0f;
            MAT_DEFAULT.Tr     = 0.0f;
            MAT_DEFAULT.Tf     = new float[3] {1.0f, 1.0f, 1.0f};
            MAT_DEFAULT.illum  = 2;
            MAT_DEFAULT.Ka     = new float[3]{0.5880f, 0.5880f, 0.5880f};
            MAT_DEFAULT.Kd     = new float[3]{0.5880f, 0.5880f, 0.5880f};
            MAT_DEFAULT.Ks     = new float[3]{0.0000f, 0.0000f, 0.0000f};
            MAT_DEFAULT.Ke     = new float[3]{0.0000f, 0.0000f, 0.0000f};
        }

    public:
        static OBJ_Material MAT_DEFAULT;
        Math::Vec3 vector3;

        std::string name = ""; // material name
        float Ns = 0; // coeff specular [0,100] ... glossiness
        float Ni = 0; // index of refraction
        float d = 0; // transparency or dissolved [0,1] = 1-Tr
        float Tr = 0; // transparency [0, 1]
        float* Tf; // color transparency
        float illum = 0; // illumination model
        float* Ka; // color ambient 3x[0,1]
        float* Kd; // color diffuse 3x[0,1]
        float* Ks; // color specular 3x[0,10] ... specular*specular-level (3dsmax)
        float* Ke; // color self emitting
        float reflectivity = 0;      
        bool is_reflective = false;
        bool is_emissive = false;
        bool is_glossy = false;

        OBJ_Material(std::string name){
            this->name = name;
        }

        void printMaterial()
        {
            std::cout << "------------------- < OBJ MTL > -------------------" << std::endl;
            std::cout << "   name   = " << name << std::endl;
            std::cout << "   Ns     = " << Ns << std::endl;
            std::cout << "   Ni     = " << Ni << std::endl;
            std::cout << "   d      = " << d << std::endl;
            std::cout << "   Tr     = " << Tr << std::endl;
            std::cout << "   Tf     = " << vector3.toStr(Tf, 3) << std::endl;
            std::cout << "   illum  = " << illum << std::endl;
            std::cout << "   Ka     = " << vector3.toStr(Ka, 3) << std::endl;
            std::cout << "   Kd     = " << vector3.toStr(Kd, 3) << std::endl;
            std::cout << "   Ks     = " << vector3.toStr(Ks, 3) << std::endl;
            std::cout << "   Ke     = " << vector3.toStr(Ke, 3) << std::endl;
            std::cout << "   reflectivity = " << reflectivity << std::endl;
            std::cout << "------------------- </ OBJ MTL > -------------------" << std::endl;
        }

        static std::vector<OBJ_Material> loadFromFile(const char *filename)
        {

            Utils::HELPER helper;
            std::vector<std::string> lines = helper.readASCIIfile(filename);            
            
            std::vector<OBJ_Material> material_list;
            OBJ_Material mat_cur("");
            for(int i = 0; i < lines.size(); i++)
            {
                std::string line = lines[i];
                if (line.find("newmtl "))
                {
                    std::istringstream stoken(line);
                    std::string element;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "newmtl ")
                        {
                            if(element.size() > 0)
                            {
                                mat_cur = OBJ_Material(element);
                            }
                        }
                    }
                }

                if(line.find("Ns "))
                {
                    std::istringstream stoken(line);
                    std::string element;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "Ns ")
                        {
                            if(element.size() > 0)
                            {
                                mat_cur.Ns = helper.string2float(element);
                            }
                        }
                    }
                }
                if(line.find("Ni "))
                {
                    std::istringstream stoken(line);
                    std::string element;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "Ni ")
                        {
                            if(element.size() > 0)
                            {
                                mat_cur.Ni = helper.string2float(element);
                            }
                        }
                    }
                }
                if(line.find("d " ))
                {
                    std::istringstream stoken(line);
                    std::string element;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "d ")
                        {
                            if(element.size() > 0)
                            {
                                mat_cur.d = helper.string2float(element);
                            }
                        }
                    }
                }

                if(line.find("Tr "))
                {
                    std::istringstream stoken(line);
                    std::string element;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "Tr ")
                        {
                            if(element.size() > 0)
                            {
                                mat_cur.Tr = helper.string2float(element);
                            }
                        }
                    }
                }
                if(line.find("Tf "))
                {
                    std::istringstream stoken(line);
                    std::string element;
                    float tmp[3];
                    int cnt = 0;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "Tf ")
                        {
                            if(element.size() > 0)
                            {
                                tmp[cnt] = helper.string2float(element);
                                cnt++;
                            }
                        }
                    }
                    mat_cur.Tf = tmp;
                }
                if(line.find("Ka "))
                {
                    std::istringstream stoken(line);
                    std::string element;
                    float tmp[3];
                    int cnt = 0;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "Ka ")
                        {
                            if(element.size() > 0)
                            {
                                tmp[cnt] = helper.string2float(element);
                                cnt++;
                            }
                        }
                    }
                    mat_cur.Ka = tmp;
                }
                if(line.find("Kd "))
                {
                    std::istringstream stoken(line);
                    std::string element;
                    float tmp[3];
                    int cnt = 0;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "Kd ")
                        {
                            if(element.size() > 0)
                            {
                                tmp[cnt] = helper.string2float(element);
                                cnt++;
                            }
                        }
                    }
                    mat_cur.Kd = tmp;
                }
                if(line.find("Ks "))
                {
                    std::istringstream stoken(line);
                    std::string element;
                    float tmp[3];
                    int cnt = 0;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "Ks ")
                        {
                            if(element.size() > 0)
                            {
                                tmp[cnt] = helper.string2float(element);
                                cnt++;
                            }
                        }
                    }
                    mat_cur.Ks = tmp;
                }
                if(line.find("Ke "))
                {
                    std::istringstream stoken(line);
                    std::string element;
                    float tmp[3];
                    int cnt = 0;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "Ke ")
                        {
                            if(element.size() > 0)
                            {
                                tmp[cnt] = helper.string2float(element);
                                cnt++;
                            }
                        }
                    }
                    mat_cur.Ke = tmp;
                }
                if(line.find("illum "))
                {
                    std::istringstream stoken(line);
                    std::string element;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "Tr ")
                        {
                            if(element.size() > 0)
                            {
                                mat_cur.Tr = helper.string2float(element);
                            }
                        }
                    }
                }
        
                if( mat_cur.name != "")
                {
                    addToList(material_list, mat_cur);
                }
            }
            
            for( OBJ_Material m : material_list )
            {
                m.printMaterial();
            }
            return material_list;
        }
  
        static OBJ_Material getByName(std::vector<OBJ_Material> materials, std::string name)
        {
            if( materials.size() == 0)
            {
                return mat_null();
            }
            for(int i = 0; i < materials.size(); i++ )
            {
                OBJ_Material mat_tmp = materials[i];
                if( name == mat_tmp.name )
                {
                    return mat_tmp;
                }
            }
            return mat_null();
        }

    };
}

#endif