#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <limits>
#include <stdio.h>
#include <string.h>
#include "AABB.hpp"
#include "HELPER.hpp"
#include "OBJ_File.hpp"
#include "OBJ_Face.hpp"
#include "OBJ_Mesh.hpp"
#include "OBJ_Material.hpp"

namespace OBJ_Loader
{

    void OBJ_File::read_file(std::string path, std::string filename)
    {

        std::vector<std::string> lines = Utils::HELPER::readASCIIfile((path + filename).c_str());

        // dynamic data buffers
        std::vector<std::vector<float>> buf_vertices;
        std::vector<std::vector<float>> buf_textures;
        std::vector<std::vector<float>> buf_normals;
        std::vector<OBJ_Face>           buf_faces;
        std::vector<OBJ_Mesh>           buf_meshes;
        std::vector<OBJ_Face>           mg_buf_faces;

        std::vector<OBJ_Material>       materials; // list of materials loaded from *.mtl file
        std::vector<OBJ_Material>       buf_materials; // list of materials used in *.obj file

        OBJ_Mesh mesh_cur = OBJ_Mesh( "___DEFAULT___");
        int mesh_group_idx = 0;
        buf_meshes.push_back(mesh_cur);

        OBJ_Material mat_cur = OBJ_Material::mat_default();
        int mat_idx = 0;
        buf_materials.push_back(mat_cur);
        
        for (int i=0; i < lines.size(); i++)
        {

            // rhino export breaks too long lines, so this tries to rebuild the line 
            // as it should be
            std::string line = lines[i];
            while (Utils::HELPER::endWith(line, "\\"))
            {
                line = line.substr(0, line.size()-2);
                line += " " + lines[++i];
                // std::cout << line << std::endl;
            }

            // split token
            int ws_pos = line.find(' ');
            std::string token(line, 0, ws_pos);

            // load materials from file
            if( token == "mtllib")
            {
                std::istringstream stoken(line);
                std::string element;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "mtllib")
                    {
                        if(element.size() > 0)
                        {
                            materials = OBJ_Material::loadFromFile(path, element);
                        }
                    }
                }
            }

            // use material
            if (token == "usemtl")
            {
                std::istringstream stoken(line);
                std::string element;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "usemtl")
                    {
                        if(element.size() > 0)
                        {
                            OBJ_Material mat_tmp = OBJ_Material::getByName(materials, element);
                            if (mat_tmp._name != "mat_default")
                            {
                                mat_idx += 1;
                                mat_cur = mat_tmp;
                                buf_materials.push_back(mat_cur);
                            }
                        }
                    }
                }
            }

            // new mesh
            if (token == "g")
            {
                std::istringstream stoken(line);
                std::string element;
                std::vector<float> vertex;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "g")
                    {
                        if(element.size() > 0)
                        {

                            // Store previous mesh group faces and clear
                            buf_meshes[mesh_group_idx]._buf_faces = mg_buf_faces;
                            mg_buf_faces.clear();

                            // Store current mesh group index and name
                            mesh_group_idx += 1;
                            mesh_cur = OBJ_Mesh(element);
                            buf_meshes.push_back(mesh_cur);

                        }
                    }
                }
            }
            
            // vertices
            if (token == "v")
            {
                std::istringstream stoken(line);
                std::string element;
                std::vector<float> vertex;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "v")
                    {
                        if(element.size() > 0)
                        {
                            vertex.push_back(Utils::HELPER::string2float(element));   
                        }
                    }
                }
                buf_vertices.push_back(vertex);
                vertex.clear();
            }
            // texture coordinates
            else if (token == "vt")
            {
                std::istringstream stoken(line);
                std::string element;
                std::vector<float> texture;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "vt")
                    {
                        if(element.size() > 0)
                        {
                            texture.push_back(Utils::HELPER::string2float(element));                
                        }
                    }
                }
                buf_textures.push_back(texture);
                texture.clear();
            }
            // vertex normals
            else if (token == "vn")
            {
                std::istringstream stoken(line);
                std::string element;
                std::vector<float> normal;
                while (std::getline(stoken, element, ' '))
                {
                    if (element != "vn")
                    {
                        if(element.size() > 0)
                        {
                            normal.push_back(Utils::HELPER::string2float(element));                
                        }
                    }
                }
                buf_normals.push_back(normal);
                normal.clear();
            }
            // faces
            else if (token == "f")
            {
                std::istringstream stoken(line);
                std::string element;
                OBJ_Face face;
                int cnt = 0;

                while (std::getline(stoken, element, ' '))
                {
                    if (element != "f")
                    {
                        if(element.size() > 0)
                        {
                            std::istringstream sub_stoken(element);
                            std::string sFace;
                            std::vector<std::string> vFace;
                            while (std::getline(sub_stoken, sFace, '/'))
                            {
                                vFace.push_back(sFace);
                            }
                            face.IDX_V[cnt] = Utils::HELPER::string2integer(vFace[0]) -1;
                            if( vFace[1]!="") face.IDX_T[cnt] = Utils::HELPER::string2integer(vFace[1]) - 1;
                            if( vFace[2]!="") face.IDX_N[cnt] = Utils::HELPER::string2integer(vFace[2]) - 1;
                            vFace.clear();
                            cnt++;                            
                        }
                    }
                }
                face.MeshGroupIdx = mesh_group_idx;
                face.MaterialIdx = mat_idx;
                buf_faces.push_back(face);
                mg_buf_faces.push_back(face);
            }
        }
        
        buf_meshes[mesh_group_idx]._buf_faces = mg_buf_faces;

        // Contiguous Memory Allocation
        if (buf_vertices.size() > 0) row_v = buf_vertices.size(), col_v = buf_vertices[0].size();
        if (buf_textures.size() > 0) row_vt = buf_textures.size(), col_vt = buf_textures[0].size();
        if (buf_normals.size() > 0) row_vn = buf_normals.size(), col_vn = buf_normals[0].size();
        if (buf_faces.size() > 0) row_f = buf_faces.size();
        if (buf_meshes.size() > 0) row_m = buf_meshes.size();
        if (buf_materials.size() > 0) row_mat = buf_materials.size();
        if (row_v  > 0)  _v = (float**)malloc2d(sizeof(float), row_v, col_v);
        if (row_vt > 0) _vt = (float**)malloc2d(sizeof(float), row_vt, col_vt);
        if (row_vn > 0) _vn = (float**)malloc2d(sizeof(float), row_vn, col_vn);
        if (row_f  > 0)  _f = (OBJ_Face*)malloc(row_f * sizeof(OBJ_Face));
        if (row_m  > 0)  _m = (OBJ_Mesh*)malloc(row_m * sizeof(OBJ_Mesh));
        if (row_mat > 0) _mat =  (OBJ_Material*)malloc(row_mat * sizeof(OBJ_Material));

        for (int i=0; i < row_v; i++)
        {
            for (int j=0; j < col_v; j++)
            {
                _v[i][j] = buf_vertices[i][j];
            }
        }

        for (int i=0; i < row_vt; i++)
        {
            for (int j=0; j < col_vt; j++)
            {
                _vt[i][j] = buf_textures[i][j];
            }
        }

        for (int i=0; i < row_vn; i++)
        {
            for (int j=0; j < col_vn; j++)
            {
                _vn[i][j] = buf_normals[i][j];
            }
        }

        for (int i=0; i < row_f; i++)
        {
            _f[i] = buf_faces[i];
        }

        for (int i=0; i < row_m; i++)
        {
            _m[i] = buf_meshes[i];
        }

        for (int i=0; i < row_mat; i++)
        {
            _mat[i] = buf_materials[i];
        }
        
    }

    void* OBJ_File::malloc2d(size_t size, int row, int col)
    {

        // http://pukulab.blog.fc2.com/blog-entry-28.html
        // https://qiita.com/tanabeman/items/bb39e9d1ddb67ddf4233

        char **a, *b;
        int  t = size * col;
    
        // インデックスと要素を一気に確保
        a = (char**)malloc((sizeof(*a) + t) * row);
        
        if (a) {
            // [インデックス, インデックス, ..., 要素, 要素, 要素, ...]
            // と整列させるため要素の開始位置をずらす
            b = (char*)(a + row);
    
            // 各行の先頭アドレスを与える
            for (int i = 0; i < row; i++) {
                a[i] = b;
                b += t; // 要素のサイズ×列の長さの分だけずらす
            }
    
            return a;
        }
        
        return nullptr;
    }

    void OBJ_File::display()
    {
        
        if (_v == nullptr)
        {
            std::cout << "No vertex data is found." << std::endl;
        }
        else
        {
            for (int i = 0; i < row_v; i++)
            {
                std::cout << "v = " << _v[i][0] << " " << _v[i][1] << " " << _v[i][2] << std::endl;
                // std::cout << &_v[i][0] << std::endl;
                // std::cout << &_v[i][1] << std::endl;
                // std::cout << &_v[i][2] << std::endl;
            }
        }

        if (_vt == nullptr)
        {
            std::cout << "No texture data is found." << std::endl;
        }
        else
        {
            for (int i = 0; i < row_vt; i++)
            {
                std::cout << "vt = " << _vt[i][0] << " " << _vt[i][1] << std::endl;
                // std::cout << &_vt[i][0] << std::endl;
                // std::cout << &_vt[i][1] << std::endl;
            }
        }

        if (_vn == nullptr)
        {
            std::cout << "No normal data is found." << std::endl;
        }
        else
        {            
            for (int i = 0; i < row_vn; i++)
            {
                std::cout << "vn = " << _vn[i][0] << " " << _vn[i][1] << " " << _vn[i][2] << std::endl;
                // std::cout << &_vn[i][0] << std::endl;
                // std::cout << &_vn[i][1] << std::endl;
                // std::cout << &_vn[i][2] << std::endl;
            }
        }

        if (_f == nullptr)
        {
            std::cout << "No face data is found." << std::endl;
        }
        else
        {            
            for (int i = 0; i < row_f; i++)
            {
                std::cout << "f = " << std::flush;
                for (int j = 0; j<3; j++)
                {
                    std::cout << _f[i].IDX_V[j] << "/" << _f[i].IDX_T[j] << "/" << _f[i].IDX_N[j] << " " << std::flush;
                }
                std::cout << "(MeshGroupIdx = " << _f[i].MeshGroupIdx << ")" << std::endl;
            }
        }

        if (_m == nullptr)
        {
            std::cout << std::endl;
            std::cout << "No mesh data is found." << std::endl;
        }
        else
        {   
            for (int i = 0; i < row_m; i++)
            {
                std::cout << std::endl;
                std::cout << "MeshGroup[" << i << "] = " << _m[i]._name << std::endl;
                
                if (_m[i]._buf_faces.size() == 0)
                {
                    std::cout << "No face data is found." << std::endl;
                }
                else
                {            
                    for (int j = 0; j < _m[i]._buf_faces.size(); j++)
                    {
                        std::cout << "f = " << std::flush;
                        for (int k = 0; k<3; k++)
                        {
                            std::cout << _m[i]._buf_faces[j].IDX_V[k] << "/" << _m[i]._buf_faces[j].IDX_T[k] << "/" << _m[i]._buf_faces[j].IDX_N[k] << " " << std::flush;
                        }
                        std::cout << "(MeshGroupIdx = " << _m[i]._buf_faces[j].MeshGroupIdx << ", MaterialIdx = " << _m[i]._buf_faces[j].MaterialIdx  << ")" << std::endl;
                    }
                }
            }
        }
    }

    void OBJ_File::computeAABB()
    {
        _aabb = Math::AABB::init();
        for(int i=0; i<row_m; i++)
        {
            OBJ_Mesh mesh = _m[i];
            mesh.computeAABB();
            _aabb.grow(mesh._aabb);
        }
    }

}