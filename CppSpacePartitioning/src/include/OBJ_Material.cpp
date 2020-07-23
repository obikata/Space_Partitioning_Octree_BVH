
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

    std::vector<OBJ_Material> OBJ_Material::loadFromFile(std::string path, std::string filename)
    {

        Utils::HELPER helper;
        std::vector<std::string> lines = helper.readASCIIfile((path + filename).c_str());            
        
        std::vector<OBJ_Material> material_list;
        OBJ_Material mat_cur = OBJ_Material::mat_default();
        for(int i = 0; i < lines.size(); i++)
        {

            std::string line = lines[i];

            // split token
            int ws_pos = line.find(' ');
            std::string token(line, 0, ws_pos);

            if (token == "newmtl")
            {

                if ( mat_cur._name != "mat_default" )
                {
                    addToList(mat_cur);
                    material_list.push_back(mat_cur);
                    // std::cout << mat_cur._name << std::endl;
                    // std::cout << material_list.size() << std::endl;
                }

                std::istringstream stoken(line);
                std::string element;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "newmtl")
                    {
                        if(element.size() > 0)
                        {
                            mat_cur = OBJ_Material(element);
                        }
                    }
                }
            }

            else if(token == "Ns")
            {
                std::istringstream stoken(line);
                std::string element;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "Ns")
                    {
                        if(element.size() > 0)
                        {
                            mat_cur._Ns = helper.string2float(element);
                        }
                    }
                }
            }
            else if(token == "Ni")
            {
                std::istringstream stoken(line);
                std::string element;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "Ni")
                    {
                        if(element.size() > 0)
                        {
                            mat_cur._Ni = helper.string2float(element);
                        }
                    }
                }
            }
            else if(token == "d")
            {
                std::istringstream stoken(line);
                std::string element;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "d")
                    {
                        if(element.size() > 0)
                        {
                            mat_cur._d = helper.string2float(element);
                        }
                    }
                }
            }

            else if(token == "Tr")
            {
                std::istringstream stoken(line);
                std::string element;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "Tr")
                    {
                        if(element.size() > 0)
                        {
                            mat_cur._Tr = helper.string2float(element);
                        }
                    }
                }
            }
            else if(token == "Tf")
            {
                std::istringstream stoken(line);
                std::string element;
                float tmp[3];
                int cnt = 0;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "Tf")
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
            else if(token == "Ka")
            {
                std::istringstream stoken(line);
                std::string element;
                float tmp[3];
                int cnt = 0;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "Ka")
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
            else if(token == "Kd")
            {
                std::istringstream stoken(line);
                std::string element;
                float tmp[3];
                int cnt = 0;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "Kd")
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
            else if(token == "Ks")
            {
                std::istringstream stoken(line);
                std::string element;
                float tmp[3];
                int cnt = 0;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "Ks")
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
            else if(token == "Ke")
            {
                std::istringstream stoken(line);
                std::string element;
                float tmp[3];
                int cnt = 0;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "Ke")
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
            else if(token == "illum")
            {
                std::istringstream stoken(line);
                std::string element;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "illum")
                    {
                        if(element.size() > 0)
                        {
                            mat_cur._Tr = helper.string2float(element);
                        }
                    }
                }
            }
    
        }

        if ( mat_cur._name != "mat_default" )
        {
            addToList(mat_cur);
            material_list.push_back(mat_cur);
            // std::cout << mat_cur._name << std::endl;
            // std::cout << material_list.size() << std::endl;
        }
        
        for( OBJ_Material m : material_list )
        {
            m.printMaterial();
        }
        return material_list;

    }

    OBJ_Material OBJ_Material::getByName(std::vector<OBJ_Material> materials, std::string name)
    {
        if( materials.size() == 0) // No materials
        {
            return OBJ_Material::mat_default();
        }
        for(int i = 0; i < materials.size(); i++ )
        {
            OBJ_Material mat_tmp = materials[i];
            if( name == mat_tmp._name )
            {
                return mat_tmp;
            }
        }
        return OBJ_Material::mat_default(); // No matching
    }
    
    OBJ_Material OBJ_Material::mat_default()
    {
        OBJ_Material MAT_DEFAULT = OBJ_Material("mat_default");
        MAT_DEFAULT._Ns     = 10.0f;
        MAT_DEFAULT._Ni     = 1.5f;
        MAT_DEFAULT._d      = 1.0f;
        MAT_DEFAULT._Tr     = 0.0f;
        MAT_DEFAULT._Tf[0]  = 1.0f;
        MAT_DEFAULT._Tf[1]  = 1.0f;
        MAT_DEFAULT._Tf[2]  = 1.0f;
        MAT_DEFAULT._illum  = 2;
        MAT_DEFAULT._Ka[0]  = 0.5880f;
        MAT_DEFAULT._Ka[1]  = 0.5880f;
        MAT_DEFAULT._Ka[2]  = 0.5880f;
        MAT_DEFAULT._Kd[0]  = 0.5880f;
        MAT_DEFAULT._Kd[1]  = 0.5880f;
        MAT_DEFAULT._Kd[2]  = 0.5880f;
        MAT_DEFAULT._Ks[0]  = 0.0000f;
        MAT_DEFAULT._Ks[1]  = 0.0000f;
        MAT_DEFAULT._Ks[2]  = 0.0000f;
        MAT_DEFAULT._Ke[0]  = 0.0000f;
        MAT_DEFAULT._Ke[1]  = 0.0000f;
        MAT_DEFAULT._Ke[2]  = 0.0000f;
        return MAT_DEFAULT;
    }

}