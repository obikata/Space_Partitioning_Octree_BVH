#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include "HELPER.hpp"
// #include "AABB.hpp"
// #include "OBJ_Mesh.hpp"

namespace OBJ_Loader
{

    class OBJ_File
    {
    public:

        // OBJ_Material materials;
        // OBJ_Mesh m; // meshes
        // OBJ_Face f; // faces
        float** v; // vertices
        float** vt; // texture coordinates (normalized)
        float** vn; // vertex-normals
        int row_v = 0, col_v = 0;
        int row_vt = 0, col_vt = 0;
        int row_vn = 0, col_vn = 0;
        // Math::AABB aabb; // Axis Aligned Bounding Box
        
        OBJ_File(const char *filename)
        {

            Utils::HELPER helper;
            std::vector<std::string> lines = helper.readASCIIfile(filename);
            
            // dynamic data buffers
            std::vector<float> tmp_v;
            std::vector<float> tmp_vt;
            std::vector<float> tmp_vn;
            std::vector<std::vector<float>> vec_tmp_v;
            std::vector<std::vector<float>> vec_tmp_vt;
            std::vector<std::vector<float>> vec_tmp_vn;
            // std::vector<OBJ_Face> tmp_f;
            // std::vector<OBJ_Mesh> tmp_m;

            // OBJ_Material mat_cur = OBJ_Material.MAT_DEFAULT;
            // OBJ_Mesh mesh_cur = new OBJ_Mesh(this, "___DEFAULT___");
            // tmp_m.push_back(mesh_cur);
            
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
                    std::string element;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "v")
                        {
                            if(element.size() > 0)
                            {
                                tmp_v.push_back(helper.string2float(element));   
                                // std::cout << "v = " << element << std::endl;             
                            }
                        }
                    }
                    vec_tmp_v.push_back(tmp_v);
                    tmp_v.clear();
                    // std::cout << "" << std::endl;
                
                }

                // texture coordinates
                else if (token == "vt")
                {
                    std::istringstream stoken(line);
                    std::string element;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "vt")
                        {
                            if(element.size() > 0)
                            {
                                tmp_vt.push_back(helper.string2float(element));                
                                // std::cout << "vt = " << element << std::endl;             
                            }
                        }
                    }
                    vec_tmp_vt.push_back(tmp_vt);
                    tmp_vt.clear();
                    // std::cout << "" << std::endl;

                }
                // vertex normals
                else if (token == "vn")
                {
                    std::istringstream stoken(line);
                    std::string element;
                    while (std::getline(stoken, element, ' '))
                    {
                        if (element != "vn")
                        {
                            if(element.size() > 0)
                            {
                                tmp_vn.push_back(helper.string2float(element));                
                                // std::cout << "vn = " << element << std::endl;             
                            }
                        }
                    }
                    vec_tmp_vn.push_back(tmp_vn);
                    tmp_vn.clear();
                    // std::cout << "" << std::endl;

                }
                // // faces
                // else if (token == "f")
                // {
                //     std::istringstream stoken(line);
                //     std::string element;
                //     while (std::getline(stoken, element, ' '))
                //     {
                //         if (element != "f")
                //         {
                //             if(element.size() > 0)
                //             {
                //                 std::istringstream sub_stoken(element);
                //                 std::string new_element;
                //                 std::vector<int> tmp(3);
                //                 int count = 0;
                //                 int reset = 0;
                //                 while (std::getline(sub_stoken, new_element, '/'))
                //                 {
                //                     tmp[count] = helper.string2integer(new_element);
                //                     count++;
                //                     std::cout << "f = " << new_element << std::endl;             
                //                 }
                //                 OBJ_Face face = new OBJ_Face(this);
                //                 face.IDX_V[0] = tmp[0] -1;
                //                 if( A.length > 1 && !A[1].isEmpty()) face.IDX_T[0] = Integer.parseInt(A[1]) - 1;
                //                 if( A.length > 2 && !A[2].isEmpty()) face.IDX_N[0] = Integer.parseInt(A[2]) - 1;
            
                //                 face.IDX_V[1] = Integer.parseInt(B[0]) - 1;
                //                 if( B.length > 1 && !B[1].isEmpty()) face.IDX_T[1] = Integer.parseInt(B[1]) - 1;
                //                 if( B.length > 2 && !B[2].isEmpty()) face.IDX_N[1] = Integer.parseInt(B[2]) - 1;
            
                //                 face.IDX_V[2] = Integer.parseInt(C[0]) - 1;
                //                 if( C.length > 1 && !C[1].isEmpty()) face.IDX_T[2] = Integer.parseInt(C[1]) - 1;
                //                 if( C.length > 2 && !C[2].isEmpty()) face.IDX_N[2] = Integer.parseInt(C[2]) - 1;
                                        
                //                 tmp_f.push_back(face)
                //                 mesh_cur.faces.push_back(face);
                //                 face.MESH = mesh_cur;
                //                 face.MATERIAL = mat_cur;
                //                 // tmp_f.push_back(tmp);
                //                 // tmp.clear();              
                //             }
                //         }
                //     }
                //     f.push_back(tmp_f);
                //     tmp_f.clear();
                //     std::cout << "" << std::endl;
                // }

            }

            // Contiguous Memory Allocation
            row_v = vec_tmp_v.size(), col_v = vec_tmp_v[0].size();
            row_vt = vec_tmp_vt.size(), col_vt = vec_tmp_vt[0].size();
            row_vn = vec_tmp_vn.size(), col_vn = vec_tmp_vn[0].size();
            v = (float**)malloc2d(sizeof(float), row_v, col_v);
            vt = (float**)malloc2d(sizeof(float), row_vt, col_vt);
            vn = (float**)malloc2d(sizeof(float), row_vn, col_vn);
            // v = (float**)malloc(vec_tmp_v.size() * sizeof(float*));
            // v[0] = (float*)malloc(vec_tmp_v.size() * 3 * sizeof(float));
            // for (int i=1; i<vec_tmp_v.size();i++) v[i] = v[i-1]+ 3;
            
            // vt = (float**)malloc(vec_tmp_vt.size() * sizeof(float*));
            // vt[0] = (float*)malloc(vec_tmp_vt.size() * 2 * sizeof(float));
            // for (int i=1; i<vec_tmp_vt.size();i++) vt[i] = vt[i-1]+ 2;
            
            // vn = (float**)malloc(vec_tmp_vn.size() * sizeof(float*));
            // vn[0] = (float*)malloc(vec_tmp_vn.size() * 3 * sizeof(float));
            // for (int i=1; i<vec_tmp_vn.size();i++) vn[i] = vn[i-1]+ 3;

            for (int i=0; i < vec_tmp_v.size(); i++)
            {
                for (int j=0; j < vec_tmp_v[0].size(); j++)
                {
                    v[i][j] = vec_tmp_v[i][j];
                }
            }

            for (int i=0; i < vec_tmp_vt.size(); i++)
            {
                for (int j=0; j < vec_tmp_vt[0].size(); j++)
                {
                    vt[i][j] = vec_tmp_vt[i][j];
                }
            }

            for (int i=0; i < vec_tmp_vn.size(); i++)
            {
                for (int j=0; j < vec_tmp_vn[0].size(); j++)
                {
                    vn[i][j] = vec_tmp_vn[i][j];
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