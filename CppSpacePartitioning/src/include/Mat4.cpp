#include <iostream>
#include <sstream>
#include <cmath>
#include <math.h>
#include <iostream>
#include "Vec3.hpp"

namespace Math
{

    Vec3 vector3;

    class Mat4
    {

        static float* nullmatrix()
        {
            return new float[16] {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };
        }

        static void copy_ref(float* mat, float* dst)
        {
            dst[0] = mat[0]; dst[4] = mat[4]; dst[ 8] = mat[ 8]; dst[12] = mat[12];
            dst[1] = mat[1]; dst[5] = mat[5]; dst[ 9] = mat[ 9]; dst[13] = mat[13];
            dst[2] = mat[2]; dst[6] = mat[6]; dst[10] = mat[10]; dst[14] = mat[14];
            dst[3] = mat[3]; dst[7] = mat[7]; dst[11] = mat[11]; dst[15] = mat[15];
        }

        static float* copy_ref(float* mat)
        {
            return new float[16] {mat[0], mat[1], mat[2], mat[3], mat[4], mat[5], mat[6], mat[7], mat[8], mat[9], mat[10], mat[11], mat[12], mat[13], mat[14], mat[15]};
        }

        static void identity_ref(float* dst)
        {
            dst[0] = 1; dst[4] = 0; dst[ 8] = 0; dst[12] = 0;
            dst[1] = 0; dst[5] = 1; dst[ 9] = 0; dst[13] = 0;
            dst[2] = 0; dst[6] = 0; dst[10] = 1; dst[14] = 0;
            dst[3] = 0; dst[7] = 0; dst[11] = 0; dst[15] = 1;
        }

        static float* identity_new()
        {
            return new float[16]{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
        }

        static void transpose_ref(float* mat, float* dst)
        {
            dst[ 0] = mat[ 0];  dst[ 4] = mat[ 1];  dst[ 8] = mat[ 2];  dst[12] = mat[ 3];
            dst[ 1] = mat[ 4];  dst[ 5] = mat[ 5];  dst[ 9] = mat[ 6];  dst[13] = mat[ 7];
            dst[ 2] = mat[ 8];  dst[ 6] = mat[ 9];  dst[10] = mat[10];  dst[14] = mat[11];
            dst[ 3] = mat[12];  dst[ 7] = mat[13];  dst[11] = mat[14];  dst[15] = mat[15];
        }

        static float* transpose_new (float* mat)
        {
            return new float[16]{mat[0], mat[4], mat[8], mat[12],    mat[1], mat[5], mat[9], mat[13],    mat[2], mat[6], mat[10], mat[14],  mat[3], mat[7], mat[11], mat[15]    };
        }

        static void transpose_ref_slf(float* dst)
        {
            float a01 = dst[1],
                  a02 = dst[2],
                  a03 = dst[3],
                  a12 = dst[6],
                  a13 = dst[7],
                  a23 = dst[11];

            dst[ 1] = dst[ 4];
            dst[ 2] = dst[ 8];
            dst[ 3] = dst[12];
            dst[ 4] = a01;
            dst[ 6] = dst[ 9];
            dst[ 7] = dst[13];
            dst[ 8] = a02;
            dst[ 9] = a12;
            dst[11] = dst[14];
            dst[12] = a03;
            dst[13] = a13;
            dst[14] = a23;
        }

        static void toMat3_ref (float* mat, float* dst_m3)
        {
            dst_m3[0] = mat[ 0];  dst_m3[3] = mat[ 4];  dst_m3[6] = mat[ 8];
            dst_m3[1] = mat[ 1];  dst_m3[4] = mat[ 5];  dst_m3[7] = mat[ 9];
            dst_m3[2] = mat[ 2];  dst_m3[5] = mat[ 6];  dst_m3[8] = mat[10];
        }

        static float* toMat3_new(float* mat)
        {
            return new float[9]{mat[0], mat[1], mat[2],     mat[4], mat[5], mat[6],    mat[8], mat[9], mat[10] };
        }

        static float* getColumnVec4_new(float* mat, int idx)
        {
            idx *= 4;
            return new float[4]{ mat[idx+0], mat[idx+1], mat[idx+2], mat[idx+3]};
        }

        static void getColumnVec4_ref(float* mat, int idx, float* v4)
        {
            idx *= 4;
            v4[0] =  mat[idx+0];
            v4[1] =  mat[idx+1];
            v4[2] =  mat[idx+2];
            v4[3] =  mat[idx+3];
        }
        
        static float* getColumnVec3_new(float* mat, int idx)
        {
            idx *= 4;
            return new float[3]{ mat[idx+0], mat[idx+1], mat[idx+2]};
        }
  
        static void getColumnVec3_ref(float* mat, int idx, float* v3)
        {
            idx *= 4;
            v3[0] =  mat[idx+0];
            v3[1] =  mat[idx+1];
            v3[2] =  mat[idx+2];
        }
        
        static float* getRowVec4_new(float* mat, int idx)
        {
            return new float[4]{ mat[idx+0], mat[idx+4], mat[idx+8], mat[idx+12]};
        }
              
        static void getRowVec4_ref(float* mat, int idx, float* v4)
        {
            v4[0] =  mat[idx+ 0];
            v4[1] =  mat[idx+ 4];
            v4[2] =  mat[idx+ 8];
            v4[3] =  mat[idx+12];
        }

        static float* getRowVec3_new(float* mat, int idx)
        {
            return new float[3]{ mat[idx+0], mat[idx+4], mat[idx+8]};
        }
        
        static void getRowVec3_ref(float* mat, int idx, float* v3)
        {
            v3[0] =  mat[idx+ 0];
            v3[1] =  mat[idx+ 4];
            v3[2] =  mat[idx+ 8];
        }

        static void getAxisX_ref(float* mat, float* v3_x)
        {
            v3_x[0] = mat[0];
            v3_x[1] = mat[1];
            v3_x[2] = mat[2];
        }

        static float* getAxisX_new(float* mat)
        {
            return new float[3]{mat[0], mat[1], mat[2] };
        }

        static void getAxisY_ref(float* mat, float* v3_y)
        {
            v3_y[0] = mat[4];
            v3_y[1] = mat[5];
            v3_y[2] = mat[6];
        }
        
        static float* getAxisY_new(float* mat)
        {
            return new float[3]{ mat[4], mat[5], mat[6] };
        }

        static void getAxisZ_ref (float* mat, float* v3_z)
        {
            v3_z[0] = mat[ 8];
            v3_z[1] = mat[ 9];
            v3_z[2] = mat[10];
        }

        static float* getAxisZ_new(float* mat) 
        {
            return new float[3]{ mat[8], mat[9], mat[10] };
        }

        static void getAxisXYZ_ref(float* mat, float* v3_x, float* v3_y, float* v3_z)
        {
            v3_x[0] = mat[0];  v3_y[0] = mat[4];  v3_z[0] = mat[ 8];
            v3_x[1] = mat[1];  v3_y[1] = mat[5];  v3_z[1] = mat[ 9];
            v3_x[2] = mat[2];  v3_y[2] = mat[6];  v3_z[2] = mat[10];
        }

        static void setAxisX(float* mat, float* v3_x)
        {
            mat[0] = v3_x[0];
            mat[1] = v3_x[1];
            mat[2] = v3_x[2];
        }

        static void setAxisY(float* mat, float* v3_y)
        {
            mat[4] = v3_y[0];
            mat[5] = v3_y[1];
            mat[6] = v3_y[2];
        }

        static void setAxisZ(float* mat, float* v3_z)
        {
            mat[ 8] = v3_z[0];
            mat[ 9] = v3_z[1];
            mat[10] = v3_z[2];
        }

        static void setAxisXYZ_ref(float* mat, float* v3_x, float* v3_y, float* v3_z)
        {
            mat[0] = v3_x[0];  mat[4] = v3_y[0];  mat[ 8] = v3_z[0];
            mat[1] = v3_x[1];  mat[5] = v3_y[1];  mat[ 9] = v3_z[1];
            mat[2] = v3_x[2];  mat[6] = v3_y[2];  mat[10] = v3_z[2];
        }

        static void setTranslation(float* mat, float* v3_t)
        {
            mat[12] = v3_t[0];
            mat[13] = v3_t[1];
            mat[14] = v3_t[2];
        }

        static float determinant(float* mat)
        {
            float
                a00 = mat[ 0], a10 = mat[ 4], a20 = mat[ 8], a30 = mat[12],
                a01 = mat[ 1], a11 = mat[ 5], a21 = mat[ 9], a31 = mat[13],
                a02 = mat[ 2], a12 = mat[ 6], a22 = mat[10], a32 = mat[14],
                a03 = mat[ 3], a13 = mat[ 7], a23 = mat[11], a33 = mat[15];

            return float
            {
                a30 * a21 * a12 * a03 - a20 * a31 * a12 * a03 - a30 * a11 * a22 * a03 + a10 * a31 * a22 * a03 +
                a20 * a11 * a32 * a03 - a10 * a21 * a32 * a03 - a30 * a21 * a02 * a13 + a20 * a31 * a02 * a13 +
                a30 * a01 * a22 * a13 - a00 * a31 * a22 * a13 - a20 * a01 * a32 * a13 + a00 * a21 * a32 * a13 +
                a30 * a11 * a02 * a23 - a10 * a31 * a02 * a23 - a30 * a01 * a12 * a23 + a00 * a31 * a12 * a23 +
                a10 * a01 * a32 * a23 - a00 * a11 * a32 * a23 - a20 * a11 * a02 * a33 + a10 * a21 * a02 * a33 +
                a20 * a01 * a12 * a33 - a00 * a21 * a12 * a33 - a10 * a01 * a22 * a33 + a00 * a11 * a22 * a33
            };
        }


        static bool inverse_ref(float* mat, float* dst)
        {
            float
                a00 = mat[ 0], a10 = mat[ 4], a20 = mat[ 8], a30 = mat[12],
                a01 = mat[ 1], a11 = mat[ 5], a21 = mat[ 9], a31 = mat[13],
                a02 = mat[ 2], a12 = mat[ 6], a22 = mat[10], a32 = mat[14],
                a03 = mat[ 3], a13 = mat[ 7], a23 = mat[11], a33 = mat[15];

            float
                b00 = a00 * a11 - a01 * a10,
                b01 = a00 * a12 - a02 * a10,
                b02 = a00 * a13 - a03 * a10,
                b03 = a01 * a12 - a02 * a11,
                b04 = a01 * a13 - a03 * a11,
                b05 = a02 * a13 - a03 * a12,
                b06 = a20 * a31 - a21 * a30,
                b07 = a20 * a32 - a22 * a30,
                b08 = a20 * a33 - a23 * a30,
                b09 = a21 * a32 - a22 * a31,
                b10 = a21 * a33 - a23 * a31,
                b11 = a22 * a33 - a23 * a32;

            float det = (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);

            if (det == 0) //TODO
                return false;
            float det_inv = 1.0f / det;

            dst[ 0] = det_inv * ( a11 * b11 - a12 * b10 + a13 * b09);
            dst[ 1] = det_inv * (-a01 * b11 + a02 * b10 - a03 * b09);
            dst[ 2] = det_inv * ( a31 * b05 - a32 * b04 + a33 * b03);
            dst[ 3] = det_inv * (-a21 * b05 + a22 * b04 - a23 * b03);
            dst[ 4] = det_inv * (-a10 * b11 + a12 * b08 - a13 * b07);
            dst[ 5] = det_inv * ( a00 * b11 - a02 * b08 + a03 * b07);
            dst[ 6] = det_inv * (-a30 * b05 + a32 * b02 - a33 * b01);
            dst[ 7] = det_inv * ( a20 * b05 - a22 * b02 + a23 * b01);
            dst[ 8] = det_inv * ( a10 * b10 - a11 * b08 + a13 * b06);
            dst[ 9] = det_inv * (-a00 * b10 + a01 * b08 - a03 * b06);
            dst[10] = det_inv * ( a30 * b04 - a31 * b02 + a33 * b00);
            dst[11] = det_inv * (-a20 * b04 + a21 * b02 - a23 * b00);
            dst[12] = det_inv * (-a10 * b09 + a11 * b07 - a12 * b06);
            dst[13] = det_inv * ( a00 * b09 - a01 * b07 + a02 * b06);
            dst[14] = det_inv * (-a30 * b03 + a31 * b01 - a32 * b00);
            dst[15] = det_inv * ( a20 * b03 - a21 * b01 + a22 * b00);
            return true;
        }


        static float* inverse_new(float* mat)
        {
            float* dst = new float[16];
            inverse_ref(mat, dst);
            return dst;
        }
  
        static void inverse_ref_self(float* mat)
        {
            inverse_ref(mat, mat);
        }

        static bool toMat3inverse_ref(float* mat, float* dst_m3)
        {
            float
                a00 = mat[0], a10 = mat[4], a20 = mat[ 8],
                a01 = mat[1], a11 = mat[5], a21 = mat[ 9],
                a02 = mat[2], a12 = mat[6], a22 = mat[10];
            float
                b01 =  a22 * a11 - a12 * a21,
                b11 = -a22 * a10 + a12 * a20,
                b21 =  a21 * a10 - a11 * a20;

            float det = a00 * b01 + a01 * b11 + a02 * b21;

            if (det == 0)//TODO
              return false;
            float det_inv = 1.0f / det;

            dst_m3[0] = det_inv *  ( b01);
            dst_m3[1] = det_inv *  (-a22 * a01 + a02 * a21);
            dst_m3[2] = det_inv *  ( a12 * a01 - a02 * a11);

            dst_m3[3] = det_inv *  ( b11);
            dst_m3[4] = det_inv *  ( a22 * a00 - a02 * a20);
            dst_m3[5] = det_inv *  (-a12 * a00 + a02 * a10);

            dst_m3[6] = det_inv *  ( b21) ;
            dst_m3[7] = det_inv *  (-a21 * a00 + a01 * a20);
            dst_m3[8] = det_inv *  ( a11 * a00 - a01 * a10);
            return true;
        }

        static float* toMat3inverse_new (float* mat)
        {
            float* dst_m3 = new float[9];
            toMat3inverse_ref(mat, dst_m3);
            return dst_m3;
        }

        static bool toMat3inverseTranspose_ref(float* mat, float* dst_m3)
        {
            float
                a00 = mat[0], a10 = mat[4], a20 = mat[8],
                a01 = mat[1], a11 = mat[5], a21 = mat[9],
                a02 = mat[2], a12 = mat[6], a22 = mat[10];
            float
                b01 =  a22 * a11 - a12 * a21,
                b11 = -a22 * a10 + a12 * a20,
                b21 =  a21 * a10 - a11 * a20;

            float det = a00 * b01 + a01 * b11 + a02 * b21;

            if (det == 0)//TODO
                return false;
            float det_inv = 1.0f / det;

            dst_m3[0] = det_inv *  ( b01);
            dst_m3[3] = det_inv *  (-a22 * a01 + a02 * a21);
            dst_m3[6] = det_inv *  ( a12 * a01 - a02 * a11);

            dst_m3[1] = det_inv *  ( b11);
            dst_m3[4] = det_inv *  ( a22 * a00 - a02 * a20);
            dst_m3[7] = det_inv *  (-a12 * a00 + a02 * a10);

            dst_m3[2] = det_inv *  ( b21) ;
            dst_m3[5] = det_inv *  (-a21 * a00 + a01 * a20);
            dst_m3[8] = det_inv *  ( a11 * a00 - a01 * a10);
            return false;
        }


        static float* toMat3inverseTranspose_new(float* mat)
        {
            float* dst_m3 = new float[9];
            toMat3inverseTranspose_ref(mat, dst_m3);
            return dst_m3;
        }

        static void mult_ref(float* mat_A, float* mat_B, float* dst_mat)
        {
            float
                a00 = mat_A[ 0], a10 = mat_A[ 4], a20 = mat_A[ 8], a30 = mat_A[12],
                a01 = mat_A[ 1], a11 = mat_A[ 5], a21 = mat_A[ 9], a31 = mat_A[13],
                a02 = mat_A[ 2], a12 = mat_A[ 6], a22 = mat_A[10], a32 = mat_A[14],
                a03 = mat_A[ 3], a13 = mat_A[ 7], a23 = mat_A[11], a33 = mat_A[15];
            float
                b00 = mat_B[ 0], b10 = mat_B[ 4], b20 = mat_B[ 8], b30 = mat_B[12],
                b01 = mat_B[ 1], b11 = mat_B[ 5], b21 = mat_B[ 9], b31 = mat_B[13],
                b02 = mat_B[ 2], b12 = mat_B[ 6], b22 = mat_B[10], b32 = mat_B[14],
                b03 = mat_B[ 3], b13 = mat_B[ 7], b23 = mat_B[11], b33 = mat_B[15];

            dst_mat[ 0] = b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30;
            dst_mat[ 1] = b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31;
            dst_mat[ 2] = b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32;
            dst_mat[ 3] = b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33;
            dst_mat[ 4] = b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30;
            dst_mat[ 5] = b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31;
            dst_mat[ 6] = b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32;
            dst_mat[ 7] = b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33;
            dst_mat[ 8] = b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30;
            dst_mat[ 9] = b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31;
            dst_mat[10] = b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32;
            dst_mat[11] = b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33;
            dst_mat[12] = b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30;
            dst_mat[13] = b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31;
            dst_mat[14] = b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32;
            dst_mat[15] = b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33;
        }

        static float* mult_new(float* mat_A, float* mat_B)
        {
            float* dst = new float[16];
            float
                a00 = mat_A[ 0], a10 = mat_A[ 4], a20 = mat_A[ 8], a30 = mat_A[12],
                a01 = mat_A[ 1], a11 = mat_A[ 5], a21 = mat_A[ 9], a31 = mat_A[13],
                a02 = mat_A[ 2], a12 = mat_A[ 6], a22 = mat_A[10], a32 = mat_A[14],
                a03 = mat_A[ 3], a13 = mat_A[ 7], a23 = mat_A[11], a33 = mat_A[15];
            float
                b00 = mat_B[ 0], b10 = mat_B[ 4], b20 = mat_B[ 8], b30 = mat_B[12],
                b01 = mat_B[ 1], b11 = mat_B[ 5], b21 = mat_B[ 9], b31 = mat_B[13],
                b02 = mat_B[ 2], b12 = mat_B[ 6], b22 = mat_B[10], b32 = mat_B[14],
                b03 = mat_B[ 3], b13 = mat_B[ 7], b23 = mat_B[11], b33 = mat_B[15];

            dst[ 0] = b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30;
            dst[ 1] = b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31;
            dst[ 2] = b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32;
            dst[ 3] = b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33;
            dst[ 4] = b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30;
            dst[ 5] = b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31;
            dst[ 6] = b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32;
            dst[ 7] = b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33;
            dst[ 8] = b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30;
            dst[ 9] = b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31;
            dst[10] = b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32;
            dst[11] = b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33;
            dst[12] = b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30;
            dst[13] = b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31;
            dst[14] = b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32;
            dst[15] = b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33;
            return dst;
        }

        static void multVec3_ref (float* mat,  float* v3, float* dst_v3)
        {
            float x = v3[0], y = v3[1], z = v3[2];

            dst_v3[0] = mat[0]*x + mat[4]*y + mat[ 8]*z + mat[12];
            dst_v3[1] = mat[1]*x + mat[5]*y + mat[ 9]*z + mat[13];
            dst_v3[2] = mat[2]*x + mat[6]*y + mat[10]*z + mat[14];
        }

        static float* multVec3_new(float* mat, float* v3)
        {
            float* dst_v3 = new  float[3];
            float x = v3[0], y = v3[1], z = v3[2];

            dst_v3[0] = mat[0]*x + mat[4]*y + mat[ 8]*z + mat[12];
            dst_v3[1] = mat[1]*x + mat[5]*y + mat[ 9]*z + mat[13];
            dst_v3[2] = mat[2]*x + mat[6]*y + mat[10]*z + mat[14];
            return dst_v3;
        }

        static void multVec4_ref(float* mat, float* v4, float* dst_v4)
        {
            float x = v4[0], y = v4[1], z = v4[2], w = v4[3];

            dst_v4[0] = mat[0]*x + mat[4]*y + mat[ 8]*z + mat[12]*w;
            dst_v4[1] = mat[1]*x + mat[5]*y + mat[ 9]*z + mat[13]*w;
            dst_v4[2] = mat[2]*x + mat[6]*y + mat[10]*z + mat[14]*w;
            dst_v4[3] = mat[3]*x + mat[7]*y + mat[11]*z + mat[15]*w;
        }

        static void multVec4_ref_slf(float* mat, float* v4)
        {
            float x = v4[0], y = v4[1], z = v4[2], w = v4[3];

            v4[0] = mat[0]*x + mat[4]*y + mat[ 8]*z + mat[12]*w;
            v4[1] = mat[1]*x + mat[5]*y + mat[ 9]*z + mat[13]*w;
            v4[2] = mat[2]*x + mat[6]*y + mat[10]*z + mat[14]*w;
            v4[3] = mat[3]*x + mat[7]*y + mat[11]*z + mat[15]*w;
        }

        static float* multVec4_new(float* mat, float* v4)
        {
            float* dst = new float[4];
            float x = v4[0], y = v4[1], z = v4[2], w = v4[3];

            dst[0] = mat[0]*x + mat[4]*y + mat[ 8]*z + mat[12]*w;
            dst[1] = mat[1]*x + mat[5]*y + mat[ 9]*z + mat[13]*w;
            dst[2] = mat[2]*x + mat[6]*y + mat[10]*z + mat[14]*w;
            dst[3] = mat[3]*x + mat[7]*y + mat[11]*z + mat[15]*w;
            return dst;
        }

        static void translate_ref(float* mat, float* v3, float* dst_mat)
        {
            float x = v3[0], y = v3[1], z = v3[2];
            float
                a00 = mat[0], a01 = mat[1], a02 = mat[ 2], a03 = mat[ 3],
                a10 = mat[4], a11 = mat[5], a12 = mat[ 6], a13 = mat[ 7],
                a20 = mat[8], a21 = mat[9], a22 = mat[10], a23 = mat[11];

            dst_mat[0] = a00;  dst_mat[4] = a10;  dst_mat[ 8] = a20;  dst_mat[12] = a00 * x + a10 * y + a20 * z + mat[12];
            dst_mat[1] = a01;  dst_mat[5] = a11;  dst_mat[ 9] = a21;  dst_mat[13] = a01 * x + a11 * y + a21 * z + mat[13];
            dst_mat[2] = a02;  dst_mat[6] = a12;  dst_mat[10] = a22;  dst_mat[14] = a02 * x + a12 * y + a22 * z + mat[14];
            dst_mat[3] = a03;  dst_mat[7] = a13;  dst_mat[11] = a23;  dst_mat[15] = a03 * x + a13 * y + a23 * z + mat[15];
        }

        static void translate_ref_slf(float* mat, float* v3)
        {
            float x = v3[0], y = v3[1], z = v3[2];

            mat[12] = mat[0] * x + mat[4] * y + mat[ 8] * z +mat[12];
            mat[13] = mat[1] * x + mat[5] * y + mat[ 9] * z +mat[13];
            mat[14] = mat[2] * x + mat[6] * y + mat[10] * z +mat[14];
            mat[15] = mat[3] * x + mat[7] * y + mat[11] * z +mat[15];
        }

        static float* translate_new(float* mat, float* v3)
        {
            float* dst_mat = new float[16];
            float x = v3[0], y = v3[1], z = v3[2];
            float
                a00 = mat[0], a01 = mat[1], a02 = mat[ 2], a03 = mat[ 3],
                a10 = mat[4], a11 = mat[5], a12 = mat[ 6], a13 = mat[ 7],
                a20 = mat[8], a21 = mat[9], a22 = mat[10], a23 = mat[11];

            dst_mat[0] = a00;  dst_mat[4] = a10;  dst_mat[ 8] = a20;  dst_mat[12] = a00 * x + a10 * y + a20 * z + mat[12];
            dst_mat[1] = a01;  dst_mat[5] = a11;  dst_mat[ 9] = a21;  dst_mat[13] = a01 * x + a11 * y + a21 * z + mat[13];
            dst_mat[2] = a02;  dst_mat[6] = a12;  dst_mat[10] = a22;  dst_mat[14] = a02 * x + a12 * y + a22 * z + mat[14];
            dst_mat[3] = a03;  dst_mat[7] = a13;  dst_mat[11] = a23;  dst_mat[15] = a03 * x + a13 * y + a23 * z + mat[15];
            return dst_mat;
        }

        static void scale_ref(float* mat, float* v3, float* dst_mat)
        {
            float x = v3[0], y = v3[1], z = v3[2];

            dst_mat[ 0] = mat[ 0] * x;  dst_mat[ 4] = mat[ 4] * y;  dst_mat[ 8] = mat[ 8] * z;  dst_mat[12] = mat[12];
            dst_mat[ 1] = mat[ 1] * x;  dst_mat[ 5] = mat[ 5] * y;  dst_mat[ 9] = mat[ 9] * z;  dst_mat[13] = mat[13];
            dst_mat[ 2] = mat[ 2] * x;  dst_mat[ 6] = mat[ 6] * y;  dst_mat[10] = mat[10] * z;  dst_mat[14] = mat[14];
            dst_mat[ 3] = mat[ 3] * x;  dst_mat[ 7] = mat[ 7] * y;  dst_mat[11] = mat[11] * z;  dst_mat[15] = mat[15];
        }

        static void scale_ref_slf(float* mat, float* v3)
        {
            float x = v3[0], y = v3[1], z = v3[2];

            mat[ 0] *= x;  mat[ 4] *= y;  mat[ 8] *= z;
            mat[ 1] *= x;  mat[ 5] *= y;  mat[ 9] *= z;
            mat[ 2] *= x;  mat[ 6] *= y;  mat[10] *= z;
            mat[ 3] *= x;  mat[ 7] *= y;  mat[11] *= z;
        }

        static float* scale_new(float* mat, float* v3)
        {
            float* dst_mat = new float[16];
            float x = v3[0], y = v3[1], z = v3[2];

            dst_mat[ 0] = mat[ 0] * x;  dst_mat[ 4] = mat[ 4] * y;  dst_mat[ 8] = mat[ 8] * z;  dst_mat[12] = mat[12];
            dst_mat[ 1] = mat[ 1] * x;  dst_mat[ 5] = mat[ 5] * y;  dst_mat[ 9] = mat[ 9] * z;  dst_mat[13] = mat[13];
            dst_mat[ 2] = mat[ 2] * x;  dst_mat[ 6] = mat[ 6] * y;  dst_mat[10] = mat[10] * z;  dst_mat[14] = mat[14];
            dst_mat[ 3] = mat[ 3] * x;  dst_mat[ 7] = mat[ 7] * y;  dst_mat[11] = mat[11] * z;  dst_mat[15] = mat[15];
            return dst_mat;
        }

        /**
         *
         * @param mat
         * @param angle rotation-angle (radians)
         * @param axis  rotation axis (normalized)
         * @param dst
         */

        static void rotate_ref(float* mat, float angle_f, float* axis_v3, float* dst_mat)
        {
            float x = axis_v3[0], y = axis_v3[1], z = axis_v3[2];

            float
                s = (float) std::sin(angle_f),
                c = (float) std::cos(angle_f),
                t = 1 - c;

            float
                a00 = mat[0], a10 = mat[4], a20 = mat[ 8],
                a01 = mat[1], a11 = mat[5], a21 = mat[ 9],
                a02 = mat[2], a12 = mat[6], a22 = mat[10],
                a03 = mat[3], a13 = mat[7], a23 = mat[11];

            // rotation matrix components
            float
                b00 = x*x*t + c,      b10 = x*y*t - z*s,   b20 = x*z*t + y*s,
                b01 = y*x*t + z*s,    b11 = y*y*t + c,     b21 = y*z*t - x*s,
                b02 = z*x*t - y*s,    b12 = z*y*t + x*s,   b22 = z*z*t + c;

            dst_mat[ 0] = a00 * b00 + a10 * b01 + a20 * b02;
            dst_mat[ 1] = a01 * b00 + a11 * b01 + a21 * b02;
            dst_mat[ 2] = a02 * b00 + a12 * b01 + a22 * b02;
            dst_mat[ 3] = a03 * b00 + a13 * b01 + a23 * b02;

            dst_mat[ 4] = a00 * b10 + a10 * b11 + a20 * b12;
            dst_mat[ 5] = a01 * b10 + a11 * b11 + a21 * b12;
            dst_mat[ 6] = a02 * b10 + a12 * b11 + a22 * b12;
            dst_mat[ 7] = a03 * b10 + a13 * b11 + a23 * b12;

            dst_mat[ 8] = a00 * b20 + a10 * b21 + a20 * b22;
            dst_mat[ 9] = a01 * b20 + a11 * b21 + a21 * b22;
            dst_mat[10] = a02 * b20 + a12 * b21 + a22 * b22;
            dst_mat[11] = a03 * b20 + a13 * b21 + a23 * b22;

            dst_mat[12] = mat[12];
            dst_mat[13] = mat[13];
            dst_mat[14] = mat[14];
            dst_mat[15] = mat[15];
        }

        static void rotate_ref_slf(float* mat, float angle_f, float* axis_v3)
        {
            float x = axis_v3[0], y = axis_v3[1], z = axis_v3[2];

            float
                s = (float) std::sin(angle_f),
                c = (float) std::cos(angle_f),
                t = 1 - c;

            float
                a00 = mat[0], a10 = mat[4], a20 = mat[ 8],
                a01 = mat[1], a11 = mat[5], a21 = mat[ 9],
                a02 = mat[2], a12 = mat[6], a22 = mat[10],
                a03 = mat[3], a13 = mat[7], a23 = mat[11];

            // rotation matrix components
            float
                b00 = x*x*t + c,      b10 = x*y*t - z*s,   b20 = x*z*t + y*s,
                b01 = y*x*t + z*s,    b11 = y*y*t + c,     b21 = y*z*t - x*s,
                b02 = z*x*t - y*s,    b12 = z*y*t + x*s,   b22 = z*z*t + c;

            mat[ 0] = a00 * b00 + a10 * b01 + a20 * b02;
            mat[ 1] = a01 * b00 + a11 * b01 + a21 * b02;
            mat[ 2] = a02 * b00 + a12 * b01 + a22 * b02;
            mat[ 3] = a03 * b00 + a13 * b01 + a23 * b02;

            mat[ 4] = a00 * b10 + a10 * b11 + a20 * b12;
            mat[ 5] = a01 * b10 + a11 * b11 + a21 * b12;
            mat[ 6] = a02 * b10 + a12 * b11 + a22 * b12;
            mat[ 7] = a03 * b10 + a13 * b11 + a23 * b12;

            mat[ 8] = a00 * b20 + a10 * b21 + a20 * b22;
            mat[ 9] = a01 * b20 + a11 * b21 + a21 * b22;
            mat[10] = a02 * b20 + a12 * b21 + a22 * b22;
            mat[11] = a03 * b20 + a13 * b21 + a23 * b22;
        }

        static float* rotate_new(float* mat, float angle_f, float* axis_v3)
        {
            float* dst_mat = new float[16];
            float x = axis_v3[0], y = axis_v3[1], z = axis_v3[2];

            float
                s = (float) std::sin(angle_f),
                c = (float) std::cos(angle_f),
                t = 1 - c;

            float
                a00 = mat[0], a10 = mat[4], a20 = mat[ 8],
                a01 = mat[1], a11 = mat[5], a21 = mat[ 9],
                a02 = mat[2], a12 = mat[6], a22 = mat[10],
                a03 = mat[3], a13 = mat[7], a23 = mat[11];

            // rotation matrix components
            float
                b00 = x*x*t + c,      b10 = x*y*t - z*s,   b20 = x*z*t + y*s,
                b01 = y*x*t + z*s,    b11 = y*y*t + c,     b21 = y*z*t - x*s,
                b02 = z*x*t - y*s,    b12 = z*y*t + x*s,   b22 = z*z*t + c;

            dst_mat[ 0] = a00 * b00 + a10 * b01 + a20 * b02;
            dst_mat[ 1] = a01 * b00 + a11 * b01 + a21 * b02;
            dst_mat[ 2] = a02 * b00 + a12 * b01 + a22 * b02;
            dst_mat[ 3] = a03 * b00 + a13 * b01 + a23 * b02;

            dst_mat[ 4] = a00 * b10 + a10 * b11 + a20 * b12;
            dst_mat[ 5] = a01 * b10 + a11 * b11 + a21 * b12;
            dst_mat[ 6] = a02 * b10 + a12 * b11 + a22 * b12;
            dst_mat[ 7] = a03 * b10 + a13 * b11 + a23 * b12;

            dst_mat[ 8] = a00 * b20 + a10 * b21 + a20 * b22;
            dst_mat[ 9] = a01 * b20 + a11 * b21 + a21 * b22;
            dst_mat[10] = a02 * b20 + a12 * b21 + a22 * b22;
            dst_mat[11] = a03 * b20 + a13 * b21 + a23 * b22;

            dst_mat[12] = mat[12];
            dst_mat[13] = mat[13];
            dst_mat[14] = mat[14];
            dst_mat[15] = mat[15];
            return dst_mat;
        }
        
        static void rotateX_ref(float* mat, float angle_f, float* dst_mat)
        {
            float
                s = (float) std::sin(angle_f),
                c = (float) std::cos(angle_f);
            float
                a10 = mat[ 4],  a20 = mat[ 8],
                a11 = mat[ 5],  a21 = mat[ 9],
                a12 = mat[ 6],  a22 = mat[10],
                a13 = mat[ 7],  a23 = mat[11];

            dst_mat[0] = mat[0];  dst_mat[ 4] = a10 * c + a20 * s;   dst_mat[ 8] = a10 * -s + a20 * c;  dst_mat[12] = mat[12];
            dst_mat[1] = mat[1];  dst_mat[ 5] = a11 * c + a21 * s;   dst_mat[ 9] = a11 * -s + a21 * c;  dst_mat[13] = mat[13];
            dst_mat[2] = mat[2];  dst_mat[ 6] = a12 * c + a22 * s;   dst_mat[10] = a12 * -s + a22 * c;  dst_mat[14] = mat[14];
            dst_mat[3] = mat[3];  dst_mat[ 7] = a13 * c + a23 * s;   dst_mat[11] = a13 * -s + a23 * c;  dst_mat[15] = mat[15];
        }

        static void rotateX_ref_slf(float* mat, float angle_f)
        {
            float
                s = (float) std::sin(angle_f),
                c = (float) std::cos(angle_f);
            float
                a10 = mat[ 4],  a20 = mat[ 8],
                a11 = mat[ 5],  a21 = mat[ 9],
                a12 = mat[ 6],  a22 = mat[10],
                a13 = mat[ 7],  a23 = mat[11];

            mat[ 4] = a10 * c + a20 * s;  mat[ 8] = a10 * -s + a20 * c;
            mat[ 5] = a11 * c + a21 * s;  mat[ 9] = a11 * -s + a21 * c;
            mat[ 6] = a12 * c + a22 * s;  mat[10] = a12 * -s + a22 * c;
            mat[ 7] = a13 * c + a23 * s;  mat[11] = a13 * -s + a23 * c;
        }

        static float* rotateX_new(float* mat, float angle_f)
        {
            float* dst_mat = new float[16];
            float
                s = (float) std::sin(angle_f),
                c = (float) std::cos(angle_f);
            float
                a10 = mat[ 4],  a20 = mat[ 8],
                a11 = mat[ 5],  a21 = mat[ 9],
                a12 = mat[ 6],  a22 = mat[10],
                a13 = mat[ 7],  a23 = mat[11];

            dst_mat[0] = mat[0];  dst_mat[ 4] = a10 * c + a20 * s;   dst_mat[ 8] = a10 * -s + a20 * c;  dst_mat[12] = mat[12];
            dst_mat[1] = mat[1];  dst_mat[ 5] = a11 * c + a21 * s;   dst_mat[ 9] = a11 * -s + a21 * c;  dst_mat[13] = mat[13];
            dst_mat[2] = mat[2];  dst_mat[ 6] = a12 * c + a22 * s;   dst_mat[10] = a12 * -s + a22 * c;  dst_mat[14] = mat[14];
            dst_mat[3] = mat[3];  dst_mat[ 7] = a13 * c + a23 * s;   dst_mat[11] = a13 * -s + a23 * c;  dst_mat[15] = mat[15];
            return dst_mat;
        }

        static void rotateY_ref (float* mat, float angle_f, float* dst_mat)
        {
            float
                s = (float) std::sin(angle_f),
                c = (float) std::cos(angle_f);
            float
                a00 = mat[0],  a20 = mat[ 8],
                a01 = mat[1],  a21 = mat[ 9],
                a02 = mat[2],  a22 = mat[10],
                a03 = mat[3],  a23 = mat[11];

            dst_mat[ 0] = a00 * c + a20 * -s;  dst_mat[ 4] = mat[ 4];   dst_mat[ 8] = a00 * s + a20 * c;    dst_mat[12] =mat[12];
            dst_mat[ 1] = a01 * c + a21 * -s;  dst_mat[ 5] = mat[ 5];   dst_mat[ 9] = a01 * s + a21 * c;    dst_mat[13] =mat[13];
            dst_mat[ 2] = a02 * c + a22 * -s;  dst_mat[ 6] = mat[ 6];   dst_mat[10] = a02 * s + a22 * c;    dst_mat[14] =mat[14];
            dst_mat[ 3] = a03 * c + a23 * -s;  dst_mat[ 7] = mat[ 7];   dst_mat[11] = a03 * s + a23 * c;    dst_mat[15] =mat[15];
        }

        static void rotateY_ref_slf(float* mat, float angle_f)
        {
            float
                s = (float) std::sin(angle_f),
                c = (float) std::cos(angle_f);
            float
                a00 = mat[0],  a20 = mat[ 8],
                a01 = mat[1],  a21 = mat[ 9],
                a02 = mat[2],  a22 = mat[10],
                a03 = mat[3],  a23 = mat[11];

            mat[ 0] = a00 * c + a20 * -s;  mat[ 8] = a00 * s + a20 * c;
            mat[ 1] = a01 * c + a21 * -s;  mat[ 9] = a01 * s + a21 * c;
            mat[ 2] = a02 * c + a22 * -s;  mat[10] = a02 * s + a22 * c;
            mat[ 3] = a03 * c + a23 * -s;  mat[11] = a03 * s + a23 * c;
        }

        static float* rotateY_new(float* mat, float angle_f)
        {
            float* dst_mat = new float[16];
            float
                s = (float) std::sin(angle_f),
                c = (float) std::cos(angle_f);
            float
                a00 = mat[0],  a20 = mat[ 8],
                a01 = mat[1],  a21 = mat[ 9],
                a02 = mat[2],  a22 = mat[10],
                a03 = mat[3],  a23 = mat[11];

            dst_mat[ 0] = a00 * c + a20 * -s;  dst_mat[ 4] = mat[ 4];   dst_mat[ 8] = a00 * s + a20 * c;  dst_mat[12] = mat[12];
            dst_mat[ 1] = a01 * c + a21 * -s;  dst_mat[ 5] = mat[ 5];   dst_mat[ 9] = a01 * s + a21 * c;  dst_mat[13] = mat[13];
            dst_mat[ 2] = a02 * c + a22 * -s;  dst_mat[ 6] = mat[ 6];   dst_mat[10] = a02 * s + a22 * c;  dst_mat[14] = mat[14];
            dst_mat[ 3] = a03 * c + a23 * -s;  dst_mat[ 7] = mat[ 7];   dst_mat[11] = a03 * s + a23 * c;  dst_mat[15] = mat[15];
            return dst_mat;
        }

        static void rotateZ_ref (float* mat, float angle_f, float* dst_mat)
        {
            float
                s = (float) std::sin(angle_f),
                c = (float) std::cos(angle_f);
            float
                a00 = mat[0],  a10 = mat[4],
                a01 = mat[1],  a11 = mat[5],
                a02 = mat[2],  a12 = mat[6],
                a03 = mat[3],  a13 = mat[7];

            dst_mat[0] = a00 * c + a10 * s;  dst_mat[4] = a00 * -s + a10 * c;   dst_mat[ 8] = mat[ 8];   dst_mat[12] = mat[12];
            dst_mat[1] = a01 * c + a11 * s;  dst_mat[5] = a01 * -s + a11 * c;   dst_mat[ 9] = mat[ 9];   dst_mat[13] = mat[13];
            dst_mat[2] = a02 * c + a12 * s;  dst_mat[6] = a02 * -s + a12 * c;   dst_mat[10] = mat[10];   dst_mat[14] = mat[14];
            dst_mat[3] = a03 * c + a13 * s;  dst_mat[7] = a03 * -s + a13 * c;   dst_mat[11] = mat[11];   dst_mat[15] = mat[15];
        }

        static void rotateZ_ref_slf(float* mat, float angle_f)
        {
            float
                s = (float) std::sin(angle_f),
                c = (float) std::cos(angle_f);
            float
                a00 = mat[0],  a10 = mat[4],
                a01 = mat[1],  a11 = mat[5],
                a02 = mat[2],  a12 = mat[6],
                a03 = mat[3],  a13 = mat[7];

            mat[0] = a00 * c + a10 * s;  mat[4] = a00 * -s + a10 * c;
            mat[1] = a01 * c + a11 * s;  mat[5] = a01 * -s + a11 * c;
            mat[2] = a02 * c + a12 * s;  mat[6] = a02 * -s + a12 * c;
            mat[3] = a03 * c + a13 * s;  mat[7] = a03 * -s + a13 * c;
        }

        static float* rotateZ_new(float* mat, float angle_f)
        {
            float* dst_mat = new float[16];
            float
                s = (float) std::sin(angle_f),
                c = (float) std::cos(angle_f);
            float
                a00 = mat[0],  a10 = mat[4],
                a01 = mat[1],  a11 = mat[5],
                a02 = mat[2],  a12 = mat[6],
                a03 = mat[3],  a13 = mat[7];

            dst_mat[0] = a00 * c + a10 * s;  dst_mat[4] = a00 * -s + a10 * c;   dst_mat[ 8] = mat[ 8];   dst_mat[12] = mat[12];
            dst_mat[1] = a01 * c + a11 * s;  dst_mat[5] = a01 * -s + a11 * c;   dst_mat[ 9] = mat[ 9];   dst_mat[13] = mat[13];
            dst_mat[2] = a02 * c + a12 * s;  dst_mat[6] = a02 * -s + a12 * c;   dst_mat[10] = mat[10];   dst_mat[14] = mat[14];
            dst_mat[3] = a03 * c + a13 * s;  dst_mat[7] = a03 * -s + a13 * c;   dst_mat[11] = mat[11];   dst_mat[15] = mat[15];
            return dst_mat;
        }

        /**
        *
        * @param r      (float) right
        * @param l      (float) left
        * @param b      (float) top
        * @param t      (float) bottom
        * @param n      (float) near
        * @param f      (float) far
        * @param dst_mat (mat4) output matrix
        */
        static void frustum_ref(float l, float r, float b, float t, float n, float f, float* dst_mat)
        {
            float
                rl = (r - l),
                tb = (t - b),
                nf = (n - f);

            dst_mat[0] = (2*n) / rl;  dst_mat[4] = 0;            dst_mat[ 8] = (r+l) / rl;    dst_mat[12] = 0;
            dst_mat[1] = 0;           dst_mat[5] = (2*n) / tb;   dst_mat[ 9] = (t+b) / tb;    dst_mat[13] = 0;
            dst_mat[2] = 0;           dst_mat[6] = 0;            dst_mat[10] = (n+f) / nf;    dst_mat[14] = (2*n*f) / nf;
            dst_mat[3] = 0;           dst_mat[7] = 0;            dst_mat[11] = -1;            dst_mat[15] = 0;
        }

        static float* frustum_new(float l, float r, float b, float t, float n, float f)
        {
            float* dst_mat = new float[16];
            float
                rl = (r - l),
                tb = (t - b),
                nf = (n - f);

            dst_mat[0] = (2*n) / rl;  dst_mat[4] = 0;            dst_mat[ 8] = (r+l) / rl;    dst_mat[12] = 0;
            dst_mat[1] = 0;           dst_mat[5] = (2*n) / tb;   dst_mat[ 9] = (t+b) / tb;    dst_mat[13] = 0;
            dst_mat[2] = 0;           dst_mat[6] = 0;            dst_mat[10] = (n+f) / nf;    dst_mat[14] = (2*n*f) / nf;
            dst_mat[3] = 0;           dst_mat[7] = 0;            dst_mat[11] = -1;            dst_mat[15] = 0;
            return dst_mat;
        }

        /**
        *
        * @param fovy   (float) field of view, y (degrees)
        * @param aspect (float) ratio (width/height)
        * @param n      (float) near
        * @param f      (float) far
        * @param dst_mat (mat4) output matrix
        */
        static void perspective_ref(float fovy, float aspect, float n, float f, float* dst_mat)
        {
            float cot = (float) (std::tan((180 - fovy)*M_PI/360.0f));
            float nf = (n - f);

            dst_mat[0] = cot/aspect;  dst_mat[4] = 0;     dst_mat[ 8] = 0;             dst_mat[12] = 0;
            dst_mat[1] = 0;           dst_mat[5] = cot;   dst_mat[ 9] = 0;             dst_mat[13] = 0;
            dst_mat[2] = 0;           dst_mat[6] = 0;     dst_mat[10] = (n+f) / nf;    dst_mat[14] = (2*n*f) / nf;
            dst_mat[3] = 0;           dst_mat[7] = 0;     dst_mat[11] = -1;            dst_mat[15] = 0;
        }

        static float* perspective_new(float fovy, float aspect, float n, float f)
        {
            float* dst_mat = new float[16];
            float cot = (float) (std::tan((180 - fovy)*M_PI/360.0f));
            float nf = (n - f);
            dst_mat[0] = cot/aspect;  dst_mat[4] = 0;     dst_mat[ 8] = 0;             dst_mat[12] = 0;
            dst_mat[1] = 0;           dst_mat[5] = cot;   dst_mat[ 9] = 0;             dst_mat[13] = 0;
            dst_mat[2] = 0;           dst_mat[6] = 0;     dst_mat[10] = (n+f) / nf;    dst_mat[14] = (2*n*f) / nf;
            dst_mat[3] = 0;           dst_mat[7] = 0;     dst_mat[11] = -1;            dst_mat[15] = 0;
            return dst_mat;
        }

        /**
        *
        * @param r      (float) right
        * @param l      (float) left
        * @param b      (float) top
        * @param t      (float) bottom
        * @param n      (float) near
        * @param f      (float) far
        * @param dst_mat (mat4) output matrix
        */
        static void ortho_ref(float l, float r, float b, float t, float n, float f, float* dst_mat)
        {
            float
                rl = (r - l),
                tb = (t - b),
                nf = (n - f);
              dst_mat[ 0] = 2 / rl;   dst_mat[ 4] = 0;        dst_mat[ 8] = 0;          dst_mat[12] = (-l - r) / rl;
            dst_mat[ 1] = 0;        dst_mat[ 5] = 2 / tb;   dst_mat[ 9] = 0;          dst_mat[13] = (-t - b) / tb;
            dst_mat[ 2] = 0;        dst_mat[ 6] = 0;        dst_mat[10] = 2 / nf;     dst_mat[14] = ( f + n) / nf;
            dst_mat[ 3] = 0;        dst_mat[ 7] = 0;        dst_mat[11] = 0;          dst_mat[15] = 1;
        }

        static float* ortho_new(float l, float r, float b, float t, float n, float f)
        {
            float* dst_mat = new float[16];
            float
                rl = (r - l),
                tb = (t - b),
                nf = (n - f);
            dst_mat[ 0] = 2 / rl;   dst_mat[ 4] = 0;        dst_mat[ 8] = 0;          dst_mat[12] = (-l - r) / rl;
            dst_mat[ 1] = 0;        dst_mat[ 5] = 2 / tb;   dst_mat[ 9] = 0;          dst_mat[13] = (-t - b) / tb;
            dst_mat[ 2] = 0;        dst_mat[ 6] = 0;        dst_mat[10] = 2 / nf;     dst_mat[14] = ( f + n) / nf;
            dst_mat[ 3] = 0;        dst_mat[ 7] = 0;        dst_mat[11] = 0;          dst_mat[15] = 1;
            return dst_mat;
        }

        static void lookAt_ref (float* eye, float* center, float* up, float* dst_mat)
        {
            if( vector3.equals(eye, center) )
            {
                identity_ref(dst_mat);
                return;
            }

            float* z = vector3.sub_new(eye, center); vector3.normalize_ref_slf(z);
            float* x = vector3.cross_new(up, z );    vector3.normalize_ref_slf(x);
            float* y = vector3.cross_new(z, x );     vector3.normalize_ref_slf(y);

            float w[3] { -(vector3.dot(x, eye)), -(vector3.dot(y, eye)), -(vector3.dot(z, eye)) };

            dst_mat[ 0] = x[0];   dst_mat[ 4] = x[1];   dst_mat[ 8] = x[2];   dst_mat[12] = w[0];
            dst_mat[ 1] = y[0];   dst_mat[ 5] = y[1];   dst_mat[ 9] = y[2];   dst_mat[13] = w[1];
            dst_mat[ 2] = z[0];   dst_mat[ 6] = z[1];   dst_mat[10] = z[2];   dst_mat[14] = w[2];
            dst_mat[ 3] = 0;      dst_mat[ 7] = 0;      dst_mat[11] = 0;      dst_mat[15] = 1;
        }

        static float* lookAt_new(float* eye, float* center, float* up)
        {
            float* dst_mat = new float[16];
            if(  vector3.equals(eye, center) )
            {
                identity_ref(dst_mat);
                return dst_mat;
            }

            float* z = vector3.sub_new(eye, center); vector3.normalize_ref_slf(z);
            float* x = vector3.cross_new(up, z );    vector3.normalize_ref_slf(x);
            float* y = vector3.cross_new(z, x );     vector3.normalize_ref_slf(y);

            float w[3] { -(vector3.dot(x, eye)), -(vector3.dot(y, eye)), -(vector3.dot(z, eye)) };

            dst_mat[ 0] = x[0];   dst_mat[ 4] = x[1];   dst_mat[ 8] = x[2];   dst_mat[12] = w[0];
            dst_mat[ 1] = y[0];   dst_mat[ 5] = y[1];   dst_mat[ 9] = y[2];   dst_mat[13] = w[1];
            dst_mat[ 2] = z[0];   dst_mat[ 6] = z[1];   dst_mat[10] = z[2];   dst_mat[14] = w[2];
            dst_mat[ 3] = 0;      dst_mat[ 7] = 0;      dst_mat[11] = 0;      dst_mat[15] = 1;
            return dst_mat;
        }

        static std::string toStr(float* mat, int prec) 
        {
            std::ostringstream m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15;
            m0.precision(prec);
            m0 << std::fixed << mat[0];
            m1.precision(prec);
            m1 << std::fixed << mat[1];
            m2.precision(prec);
            m2 << std::fixed << mat[2];
            m3.precision(prec);
            m3 << std::fixed << mat[3];
            m4.precision(prec);
            m4 << std::fixed << mat[4];
            m5.precision(prec);
            m5 << std::fixed << mat[5];
            m6.precision(prec);
            m6 << std::fixed << mat[6];
            m7.precision(prec);
            m7 << std::fixed << mat[7];
            m8.precision(prec);
            m8 << std::fixed << mat[8];
            m9.precision(prec);
            m9 << std::fixed << mat[9];
            m10.precision(prec);
            m10 << std::fixed << mat[10];
            m11.precision(prec);
            m11 << std::fixed << mat[11];
            m12.precision(prec);
            m12 << std::fixed << mat[12];
            m13.precision(prec);
            m13 << std::fixed << mat[13];
            m14.precision(prec);
            m14 << std::fixed << mat[14];
            m15.precision(prec);
            m15 << std::fixed << mat[15];
            std::string line;
            line  = "[" + m0.str() + ", " + m4.str() + ", " +  m8.str() + m12.str() + "]" + "\n";
            line += "[" + m1.str() + ", " + m5.str() + ", " +  m9.str() + m13.str() + "]" + "\n";
            line += "[" + m2.str() + ", " + m6.str() + ", " + m10.str() + m14.str() + "]" + "\n";
            line += "[" + m3.str() + ", " + m7.str() + ", " + m11.str() + m15.str() + "]" + "\n";
            return line;
        }

        static void print(float* mat, int prec)
        {
          std::cout << toStr(mat, prec) << std::endl;
        }

    };
}