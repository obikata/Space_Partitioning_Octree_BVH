
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include "HELPER.hpp"
#include "Vec3.hpp"
#include "OBJ_Material.hpp"

namespace OBJ_Loader
{

    void OBJ_Material::printMaterial()
    {
        std::cout << "------------------- < OBJ MTL > -------------------" << std::endl;
        std::cout << "   name   = " << _name << std::endl;
        std::cout << "   Ns     = " << _Ns << std::endl;
        std::cout << "   Ni     = " << _Ni << std::endl;
        std::cout << "   d      = " << _d << std::endl;
        std::cout << "   Tr     = " << _Tr << std::endl;
        std::cout << "   Tf     = " << vector3.toStr(_Tf, 3) << std::endl;
        std::cout << "   illum  = " << _illum << std::endl;
        std::cout << "   Ka     = " << vector3.toStr(_Ka, 3) << std::endl;
        std::cout << "   Kd     = " << vector3.toStr(_Kd, 3) << std::endl;
        std::cout << "   Ks     = " << vector3.toStr(_Ks, 3) << std::endl;
        std::cout << "   Ke     = " << vector3.toStr(_Ke, 3) << std::endl;
        std::cout << "   reflectivity = " << _reflectivity << std::endl;
        std::cout << "------------------- </ OBJ MTL > -------------------" << std::endl;
    }

    std::vector<OBJ_Material> OBJ_Material::loadFromFile(const char *filename)
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
                            mat_cur._Ns = helper.string2float(element);
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
                            mat_cur._Ni = helper.string2float(element);
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
                            mat_cur._d = helper.string2float(element);
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
                            mat_cur._Tr = helper.string2float(element);
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
                mat_cur._Tf = tmp;
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
                mat_cur._Ka = tmp;
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
                mat_cur._Kd = tmp;
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
                mat_cur._Ks = tmp;
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
                mat_cur._Ke = tmp;
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
                            mat_cur._Tr = helper.string2float(element);
                        }
                    }
                }
            }
    
            if( mat_cur._name != "")
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

    OBJ_Material OBJ_Material::getByName(std::vector<OBJ_Material> materials, std::string name)
    {
        if( materials.size() == 0)
        {
            return nullptr;
        }
        for(int i = 0; i < materials.size(); i++ )
        {
            OBJ_Material mat_tmp = materials[i];
            if( name == mat_tmp._name )
            {
                return mat_tmp;
            }
        }
        return nullptr;
    }
    
    OBJ_Material OBJ_Material::mat_default()
    {
        MAT_DEFAULT = OBJ_Material("mat_default");
        MAT_DEFAULT._Ns     = 10.0f;
        MAT_DEFAULT._Ni     = 1.5f;
        MAT_DEFAULT._d      = 1.0f;
        MAT_DEFAULT._Tr     = 0.0f;
        MAT_DEFAULT._Tf     = new float[3] {1.0f, 1.0f, 1.0f};
        MAT_DEFAULT._illum  = 2;
        MAT_DEFAULT._Ka     = new float[3] {0.5880f, 0.5880f, 0.5880f};
        MAT_DEFAULT._Kd     = new float[3] {0.5880f, 0.5880f, 0.5880f};
        MAT_DEFAULT._Ks     = new float[3] {0.0000f, 0.0000f, 0.0000f};
        MAT_DEFAULT._Ke     = new float[3] {0.0000f, 0.0000f, 0.0000f};
    }

}