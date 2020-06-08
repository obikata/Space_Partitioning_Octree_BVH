#include "Vec3.hpp"
#include "Mat4.hpp"

namespace Math
{
    const float Camera::ndc_NBL[4] = {-1, -1, -1, 1};
    const float Camera::ndc_NBR[4] = {+1, -1, -1, 1};
    const float Camera::ndc_NTR[4] = {+1, +1, -1, 1};
    const float Camera::ndc_NTL[4] = {-1, +1, -1, 1};
    const float Camera::ndc_FBL[4] = {-1, -1, +1, 1};
    const float Camera::ndc_FBR[4] = {+1, -1, +1, 1};
    const float Camera::ndc_FTR[4] = {+1, +1, +1, 1};
    const float Camera::ndc_FTL[4] = {-1, +1, +1, 1};
    Vec3 vector3;
    Mat4 matrix4;

    class Camera
    {
    private:
        CameraState cam_state = null;        
        int   viewport_size[2];
        float viewport_size_inv[2];

    public:
        static const float ndc_NBL[4];
        static const float ndc_NBR[4];
        static const float ndc_NTR[4];
        static const float ndc_NTL[4];
        static const float ndc_FBL[4];
        static const float ndc_FBR[4];
        static const float ndc_FTR[4];
        static const float ndc_FTL[4];
        
        float* world_NBL = new float[4];
        float* world_NBR = new float[4];
        float* world_NTR = new float[4];
        float* world_NTL = new float[4];
        float* world_FBL = new float[4];
        float* world_FBR = new float[4];
        float* world_FTR = new float[4];
        float* world_FTL = new float[4];
        
      
        float* MAT_projection     = new float[16];
        float* MAT_modelview      = new float[16];
      
        float* MAT_projection_inv = new float[16];
        float* MAT_modelview_inv  = new float[16];
      
        float* MAT_modelview_projection     = new float[16];
        float* MAT_modelview_projection_inv = new float[16];
        
        
        // TODO: make them accessible per getter methods
        float* eye   ; 
        float* center;
        float* up    ;
        float fovy;
        float aspect; 
        float n; 
        float f;
                
        const PApplet papplet; //TODO
        
        Camera(PApplet papplet)
        {
            this->papplet = papplet;
            this->viewport_size[0] = papplet.width;
            this->viewport_size[1] = papplet.height;
            this->viewport_size_inv[0] = 1.0f/viewport_size[0];
            this->viewport_size_inv[1] = 1.0f/viewport_size[1];

            getP5Matrix_MODELVIEW(); //TODO
            getP5Matrix_PROJECTION(); //TODO
            update(); //TODO
        }

        void update()
        {
            matrix4.mult_ref(MAT_projection, MAT_modelview, MAT_modelview_projection);
            matrix4.inverse_ref(MAT_projection, MAT_projection_inv);
            matrix4.inverse_ref(MAT_modelview,  MAT_modelview_inv);
            matrix4.inverse_ref(MAT_modelview_projection,  MAT_modelview_projection_inv);
            
            updateFarPlane_worldspace();
            updateNearPlane_worldspace();
        }

        void getP5Matrix_PROJECTION()
        {
            PMatrix3D mat_p5_tmp = new PMatrix3D(); 
            papplet.g.matrixMode(PApplet.PROJECTION);
            papplet.getMatrix( mat_p5_tmp );

            MAT_projection = mat_p5_tmp.get(MAT_projection);
            matrix4.transpose_ref_slf(MAT_projection);
            
            papplet.g.matrixMode(PApplet.MODELVIEW);
        }
        
        void getP5Matrix_MODELVIEW()
        {
            PMatrix3D mat_p5_tmp = new PMatrix3D(); 
            papplet.g.matrixMode(PApplet.MODELVIEW);
            papplet.getMatrix( mat_p5_tmp );
          
            MAT_modelview = mat_p5_tmp.get(MAT_modelview);
            matrix4.transpose_ref_slf(MAT_modelview);
            
            papplet.g.matrixMode(PApplet.MODELVIEW);
        }
  
        void updateNearPlane_worldspace()
        {
            matrix4.multVec4_ref(MAT_modelview_projection_inv, ndc_NBL, world_NBL);
            matrix4.multVec4_ref(MAT_modelview_projection_inv, ndc_NBR, world_NBR);
            matrix4.multVec4_ref(MAT_modelview_projection_inv, ndc_NTR, world_NTR);
            matrix4.multVec4_ref(MAT_modelview_projection_inv, ndc_NTL, world_NTL);    

            Vec4.multiply_ref_slf(world_NBL, 1.0f/world_NBL[3]);
            Vec4.multiply_ref_slf(world_NBR, 1.0f/world_NBR[3]);
            Vec4.multiply_ref_slf(world_NTR, 1.0f/world_NTR[3]);
            Vec4.multiply_ref_slf(world_NTL, 1.0f/world_NTL[3]);
        }

        void updateFarPlane_worldspace()
        {
            matrix4.multVec4_ref(MAT_modelview_projection_inv, ndc_FBL, world_FBL);
            matrix4.multVec4_ref(MAT_modelview_projection_inv, ndc_FBR, world_FBR);
            matrix4.multVec4_ref(MAT_modelview_projection_inv, ndc_FTR, world_FTR);
            matrix4.multVec4_ref(MAT_modelview_projection_inv, ndc_FTL, world_FTL);    

            Vec4.multiply_ref_slf(world_FBL, 1.0f/world_FBL[3]);
            Vec4.multiply_ref_slf(world_FBR, 1.0f/world_FBR[3]);
            Vec4.multiply_ref_slf(world_FTR, 1.0f/world_FTR[3]);
            Vec4.multiply_ref_slf(world_FTL, 1.0f/world_FTL[3]);
        }
  
        Ray3D getSceenRay(float x, float y)
        {
            float xnorm = x*viewport_size_inv[0];
            float ynorm = y*viewport_size_inv[1];
            float* mix_FB_LR = vector3.lerp_new(world_FBR, world_FBL, xnorm);
            float* mix_FT_LR = vector3.lerp_new(world_FTR, world_FTL, xnorm);
            float* mix_NB_LR = vector3.lerp_new(world_NBR, world_NBL, xnorm);
            float* mix_NT_LR = vector3.lerp_new(world_NTR, world_NTL, xnorm);
            
            float* mix_F_BT  = vector3.lerp_new(mix_FT_LR, mix_FB_LR, ynorm);
            float* mix_N_BT  = vector3.lerp_new(mix_NT_LR, mix_NB_LR, ynorm);
            
            return new Ray3D(mix_N_BT, vector3.sub_new(mix_F_BT, mix_N_BT));  
        }
  
  
        Ray3D getSceenRay(float x, float y, float* m4_MVP_inv)
        {
            float* f2_screen_ndc = screenToNDC(x,y);
            float* f4_ndc_n = float4(f2_screen_ndc, -1, 1); // near 
            float* f4_ndc_f = float4(f2_screen_ndc, +1, 1); // far
            float* f4_world_n = matrix4.multVec4_new(m4_MVP_inv, f4_ndc_n);  
            float* f4_world_f = matrix4.multVec4_new(m4_MVP_inv, f4_ndc_f);  
            Vec4.multiply_ref_slf(f4_world_n, 1.0f/f4_world_n[3]);
            Vec4.multiply_ref_slf(f4_world_f, 1.0f/f4_world_f[3]);
            float* f3_eye = f4_world_n;
            float* f3_dir = vector3.sub_new(f4_world_f, f3_eye);
            return new Ray3D(f3_eye, f3_dir);  
        }
    
        float* float4(float* xy, float z, float w)
        {
            return new float*{xy[0], xy[1], z, w};
        }
  
        float* screenToNDC(float x, float y)
        {
            float x_ndc = 2f*x*viewport_size_inv[0] - 1f;
            float y_ndc = 2f*y*viewport_size_inv[1] - 1f;
            return new float*{x_ndc, y_ndc};
        }
    
        int* projectVertex(float* f3_vtx)
        {
            float* v4 = {f3_vtx[0], f3_vtx[1], f3_vtx[2], 1.0f};
            matrix4.multVec4_ref_slf(MAT_modelview_projection, v4);       // project to ndc
            vector3.scale_ref_slf(v4, -1f/v4[3]);                         // perspective divvide: range: [-1, +1]
            int px = std::round((v4[0]*0.5f + 0.5f)*viewport_size[0]);   // map to screen_x
            int py = std::round((v4[1]*0.5f + 0.5f)*viewport_size[1]);   // map to screen_y

            if( px >= 0 && px < viewport_size[0] && py >= 0 && py < viewport_size[1] )
            {
               return new int*{px, py};
            }
            return null;
        }

    };
}