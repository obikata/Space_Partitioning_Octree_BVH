#ifndef __OBJ_FILE_HPP__
#define __OBJ_FILE_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include "HELPER.hpp"
#include "OBJ_Face.hpp"
// #include "OBJ_Mesh.hpp"
// #include "AABB.hpp"

namespace OBJ_Loader
{

    class OBJ_File
    {
    public:

        // OBJ_Material* materials;
        // OBJ_Mesh* m; // meshes
        // OBJ_Face* f; // faces
        float** v; // vertices
        float** vt; // texture coordinates (normalized)
        float** vn; // vertex-normals
        // Math::AABB aabb; // Axis Aligned Bounding Box
        
        int row_v = 0, col_v = 0;
        int row_vt = 0, col_vt = 0;
        int row_vn = 0, col_vn = 0;
        
        OBJ_File(const char *filename)
        {

            Utils::HELPER helper;
            std::vector<std::string> lines = helper.readASCIIfile(filename);
            
            // dynamic data buffers
            std::vector<std::vector<float>> buf_vertices;
            std::vector<std::vector<float>> buf_textures;
            std::vector<std::vector<float>> buf_normals;
            std::vector<OBJ_Face>           buf_faces;
            std::vector<OBJ_Mesh>           buf_meshes;

            OBJ_Material mat_cur = OBJ_Material.MAT_DEFAULT;
            OBJ_Mesh mesh_cur = new OBJ_Mesh(this, "___DEFAULT___");
            buf_meshes.push_back(mesh_cur);
            
            for (int i=0; i < lines.size(); i++)
            {

                // rhino export breaks too long lines, so this tries to rebuild the line 
                // as it should be
                std::string line = lines[i];
                while (helper.endWith(line, "\\"))
                {
                    line = line.substr(0, line.size()-2);
                    line += " " + lines[++i];
                    // std::cout << line << std::endl;
                }

                // split token
                int ws_pos = line.find(' ');
                std::string token(line, 0, ws_pos);

                // // load materials from file
                // if( token == "mtllib")
                // {
                //     std::istringstream stoken(line);
                //     std::string element;
                //     while (std::getlineEAST to the Satellite whenever you are ready.

                //             if(element.size() > 0)
                //             {
                //                 materials = OBJ_Material.loadFromFile(filename, element);
                //             }
                //         }
                //     }
                // }

                // // use material
                // if (token == "usemtl")
                // {
                //     std::istringstream stoken(line);
                //     std::string element;
                //     while (std::getline(stoken, element, ' '))
                //     {
                //         if (element != "usemtl")
                //         {
                //             if(element.size() > 0)
                //             {
                //                 OBJ_Material mat_tmp = OBJ_Material.getByteName(materials, element);
                //                 mat_cur = (mat_tmp != NULL) ? mat_tmp ; mat_cur;
                //             }EAST to the Satellite whenever you are ready.

                // // new mesh
                // if (token == "g")
                // {
                //     std::istringstream stoken(line);
                //     std::string element;
                //     while (std::getline(stoken, element, ' '))
                //     {
                //         if (element != "g")
                //         {
                //             if(element.size() > 0)
                //             {
                //                 mesh_cur = new.OBJ_Mesh(this, element);
                //                 tmp_m.push_back(mesh_cur);
                //             }
                //         }
                //     }
                // }

                // vertices
                if (token == "v")
                {
                    std::istringstream stoken(line);
                    std::string element = new std::string();
                    std::vector<float> vertex = new std::vector<float>(3);
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "v")
                        {
                            if(element.size() > 0)
                            {
                                vertex.push_back(helper.string2float(element));   
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
                    std::string element = new std::string();
                    std::vector<float> texture = new std::vector<float>(2);
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "vt")
                        {
                            if(element.size() > 0)
                            {
                                texture.push_back(helper.string2float(element));                
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
                    std::string element = new std::string();
                    std::vector<float> normal = new std::vector<float>(3);
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "vn")
                        {
                            if(element.size() > 0)
                            {
                                normal.push_back(helper.string2float(element));                
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
                    OBJ_Face face = new OBJ_Face(this);
                    for (int i=0, std::getline(stoken, element, ' '); i<3; i++)
                    {
                        if (element != "f")
                        {
                            if(element.size() > 0)
                            {
                                std::istringstream sub_stoken(element);
                                std::string sFace;
                                std::vector<int> vFace;
                                while (std::getline(sub_stoken, sFace, '/'))
                                {
                                    vFace.push_back(helper.string2integer(sFace));
                                    std::cout << "f = " << sFace << std::endl;
                                }
                                face.IDX_V[i] = vFace[0] -1;
                                if( vFace.size() > 1 && !vFace[1].empty()) face.IDX_T[i] = vFace[1] - 1;
                                if( vFace.size() > 2 && !vFace[2].empty()) face.IDX_N[i] = vFace[2] - 1;
                                vFace.clear();
                            }
                        }
                    }
                    buf_faces.push_back(face);
                    mesh_cur.faces.push_back(face);
                    face.MESH = mesh_cur;
                    face.MATERIAL = mat_cur;
                }
            }

            // Contiguous Memory Allocation
            row_v = buf_vertices.size(), col_v = buf_vertices[0].size();
            row_vt = buf_textures.size(), col_vt = buf_textures[0].size();
            row_vn = buf_normals.size(), col_vn = buf_normals[0].size();
            v = (float**)malloc2d(sizeof(float), row_v, col_v);
            vt = (float**)malloc2d(sizeof(float), row_vt, col_vt);
            vn = (float**)malloc2d(sizeof(float), row_vn, col_vn);
            // v = (float**)malloc(buf_vertices.size() * sizeof(float*));
            // v[0] = (float*)malloc(buf_vertices.size() * 3 * sizeof(float));
            // for (int i=1; i<buf_vertices.size();i++) v[i] = v[i-1]+ 3;
            
            // vt = (float**)malloc(buf_textures.size() * sizeof(float*));
            // vt[0] = (float*)malloc(buf_textures.size() * 2 * sizeof(float));
            // for (int i=1; i<buf_textures.size();i++) vt[i] = vt[i-1]+ 2;
            
            // vn = (float**)malloc(buf_normals.size() * sizeof(float*));
            // vn[0] = (float*)malloc(buf_normals.size() * 3 * sizeof(float));
            // for (int i=1; i<buf_normals.size();i++) vn[i] = vn[i-1]+ 3;

            for (int i=0; i < buf_vertices.size(); i++)
            {
                for (int j=0; j < buf_vertices[0].size(); j++)
                {
                    v[i][j] = buf_vertices[i][j];
                }
            }

            for (int i=0; i < buf_textures.size(); i++)
            {
                for (int j=0; j < buf_textures[0].size(); j++)
                {
                    vt[i][j] = buf_textures[i][j];
                }
            }

            for (int i=0; i < buf_normals.size(); i++)
            {
                for (int j=0; j < buf_normals[0].size(); j++)
                {
                    vn[i][j] = buf_normals[i][j];
                }
            }

        }

        void *malloc2d(size_t size, int row, int col)
        {

            // http://pukulab.blog.fc2.com/blog-entry-28.html

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
            
            return NULL;
        }

        void display()
        {
            for (int i = 0; i < row_v; i++)
            {
                std::cout << "v = " << v[i][0] << " " << v[i][1] << " " << v[i][2] << std::endl;
                // std::cout << &v[i][0] << std::endl;
                // std::cout << &v[i][1] << std::endl;
                // std::cout << &v[i][2] << std::endl;
            }
            for (int i = 0; i < row_vt; i++)
            {
                std::cout << "vt = " << vt[i][0] << " " << vt[i][1] << std::endl;
                // std::cout << &vt[i][0] << std::endl;
                // std::cout << &vt[i][1] << std::endl;
            }
            for (int i = 0; i < row_vn; i++)
            {
                std::cout << "vn = " << vn[i][0] << " " << vn[i][1] << " " << vn[i][2] << std::endl;
                // std::cout << &vn[i][0] << std::endl;
                // std::cout << &vn[i][1] << std::endl;
                // std::cout << &vn[i][2] << std::endl;
            }
        }
        
    };

}

#endif