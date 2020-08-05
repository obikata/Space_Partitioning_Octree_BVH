#include "include/AABB.hpp"
#include <iostream>
#include <chrono>
#include <sstream>

int main(int argc, char **argv)
{

    ///////////// Functionality Test 1 /////////////
    std::cout << "Instantiate, then initialize aabb object without argument" << std::endl;
    Math::AABB aabb;
    
    // Check AABB initial values
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MIN = " << aabb._min[i] << std::endl;
    }
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MAX = " << aabb._max[i] << std::endl;
    }

    std::cout << "\nInitialized" << std::endl;

    aabb.init();
    // Math::AABB aabb = Math::AABB::GetInitializedAABB();
    
    // Check AABB initial values
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MIN = " << aabb._min[i] << std::endl;
    }
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MAX = " << aabb._max[i] << std::endl;
    }

    std::cout << "\n" << std::endl;

    ///////////// Functionality Test 2 /////////////
    std::cout << "Instantiate aabb object with min/max arguments" << std::endl;
    float* min;
    float* max;
    min = new float[3];
    max = new float[3];
    // min = (float*)malloc(3 * sizeof(float));
    // max = (float*)malloc(3 * sizeof(float));

    min[0] = -0.1f;
    min[1] = -0.1f;
    min[2] = -0.1f;
    max[0] = 0.1f;
    max[1] = 0.1f;
    max[2] = 0.1f;
    Math::AABB aabb2(min, max);

    // Check AABB initial values
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MIN = " << aabb2._min[i] << std::endl;
    }
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MAX = " << aabb2._max[i] << std::endl;
    }

    std::cout << "\n" << std::endl;

    ///////////// Functionality Test 3 /////////////
    std::cout << "Instantiate aabb object with three vertices" << std::endl;
    float* A;
    float* B;
    float* C;
    A = new float[3];
    B = new float[3];
    C = new float[3];
    // min = (float*)malloc(3 * sizeof(float));
    // max = (float*)malloc(3 * sizeof(float));
    A[0] = -10.0f;
    A[1] = 5.5f;
    A[2] = -400.9f;
    B[0] = 500.0f;
    B[1] = -301.0f;
    B[2] = -50.0f;
    C[0] = -200.0f;
    C[1] = 100.1f;
    C[2] = 100.1f;

    Math::AABB aabb3(A, B, C);

    // Check AABB initial values
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MIN = " << aabb3._min[i] << std::endl;
    }
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MAX = " << aabb3._max[i] << std::endl;
    }

    std::cout << "\n" << std::endl;

    ///////////// Functionality Test 4 /////////////
    std::cout << "Deep Copy AABB" << std::endl;

    Math::AABB aabb4;
    aabb4 = aabb3.deep_copy();
    
    if (&aabb3 != &aabb4) std::cout << "Different addresses are assigned!" << std::endl;
    // Check AABB initial values
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MIN = " << aabb4._min[i] << std::endl;
    }
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MAX = " << aabb4._max[i] << std::endl;
    }

    std::cout << "\n" << std::endl;

    ///////////// Functionality Test 5 /////////////
    std::cout << "Shallow Copy AABB" << std::endl;

    Math::AABB* aabb5;
    aabb5 = aabb4.shallow_copy();
    // aabb5 = &aabb4;
    
    if (&aabb4 == aabb5) std::cout << "Same address is assigned!" << std::endl;
    // Check AABB initial values
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MIN = " << aabb5->_min[i] << std::endl;
    }
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MAX = " << aabb5->_max[i] << std::endl;
    }

    std::cout << "\n" << std::endl;

    ///////////// Functionality Test 6 /////////////
    std::cout << "Get Volume" << std::endl;
    float vol = aabb4.getVolume();
    std::cout << vol << std::endl;

    ///////////// Functionality Test 7 /////////////
    std::cout << "Get Surface Area" << std::endl;
    float surface_area = aabb4.getSurfaceArea();
    std::cout << surface_area << std::endl;

    ///////////// Functionality Test 8 /////////////
    std::cout << "Get Size" << std::endl;
    float* size;
    size = aabb4.getSize();
    for (int i = 0; i < 3; i++) std::cout << size[i] << std::endl;

    ///////////// Functionality Test 9 /////////////
    std::cout << "Get Half Size" << std::endl;
    float* half_size;
    half_size = aabb4.getHalfSize();
    for (int i = 0; i < 3; i++) std::cout << half_size[i] << std::endl;

    ///////////// Functionality Test 10 /////////////
    std::cout << "Get Center" << std::endl;
    float* center;
    center = aabb4.getCenter();
    for (int i = 0; i < 3; i++) std::cout << center[i] << std::endl;

    ///////////// Functionality Test 11 /////////////
    std::cout << "Get Corners" << std::endl;
    float** corners;
    corners = aabb4.getCorners();

    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << corners[i][j] << std::endl;
        }
    }

    ///////////// Functionality Test 12 /////////////
    std::cout << "Get isInside" << std::endl;
    float v0[3] {0.0f, 0.0f, 0.0f};
    float v1[3] {0.0f, 0.0f, 0.0f};
    float v2[3] {0.0f, 0.0f, 0.0f};
    std::cout << aabb4.isInside(v0, v1, v2) << std::endl;
    float v3[3] {0.0f, 0.0f, 0.0f};
    float v4[3] {0.0f, 1000.0f, 0.0f};
    float v5[3] {0.0f, 0.0f, 0.0f};
    std::cout << aabb4.isInside(v3, v4, v5) << std::endl;

    ///////////// Functionality Test 13 /////////////
    std::cout << "Grow AABB" << std::endl;
    Math::AABB aabb6;
    aabb6 = aabb.deep_copy();
    // Check AABB initial values
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MIN = " << aabb6._min[i] << std::endl;
    }
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MAX = " << aabb6._max[i] << std::endl;
    }
    aabb6.grow(aabb2);
    // Check AABB initial values
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MIN = " << aabb6._min[i] << std::endl;
    }
    for (int i = 0; i < 3; i++)
    {
        std::cout << "AABB_MAX = " << aabb6._max[i] << std::endl;
    }

    ///////////// Functionality Test 14 /////////////
    std::cout << "Has Same Value" << std::endl;
    std::cout << aabb6.hasSameValues(aabb2) << std::endl;
    std::cout << aabb6.hasSameValues(Math::AABB::GetInitializedAABB()) << std::endl;

    return 0;

}
