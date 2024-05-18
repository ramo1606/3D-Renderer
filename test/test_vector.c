#include "minunit.h"
#include "rasterizer/vector.h"
#include <math.h>

#define EPSILON 0.0001f  // Tolerance for floating-point comparisons

MU_TEST(test_Vec3RotateX) 
{
    // Test case 1: 90-degree rotation around X
    Vec3 v1 = { 0.0f, 1.0f, 0.0f };
    Vec3 expected1 = { 0.0f, 0.0f, 1.0f };
    Vec3 result1 = Vec3RotateX(v1, M_PI_2);
    mu_assert_float_eq(expected1.x, result1.x, EPSILON);
    mu_assert_float_eq(expected1.y, result1.y, EPSILON);
    mu_assert_float_eq(expected1.z, result1.z, EPSILON);

    // Test case 2: 180-degree rotation around X
    Vec3 v2 = { 0.0f, 0.0f, 1.0f };
    Vec3 expected2 = { 0.0f, 0.0f, -1.0f };
    Vec3 result2 = Vec3RotateX(v2, M_PI);
    mu_assert_float_eq(expected2.x, result2.x, EPSILON);
    mu_assert_float_eq(expected2.y, result2.y, EPSILON);
    mu_assert_float_eq(expected2.z, result2.z, EPSILON);

    // Add more test cases as needed...
}

// Tests for Vec3RotateY
MU_TEST(test_Vec3RotateY) 
{
    // Test case 1: 90-degree rotation around Y
    Vec3 v1 = { 0.0f, 0.0f, 1.0f };
    Vec3 expected1 = { -1.0f, 0.0f, 0.0f };
    Vec3 result1 = Vec3RotateY(v1, M_PI_2);
    mu_assert_float_eq(expected1.x, result1.x, EPSILON);
    mu_assert_float_eq(expected1.y, result1.y, EPSILON);
    mu_assert_float_eq(expected1.z, result1.z, EPSILON);

    // ... add more tests for Vec3RotateY
}

// Tests for Vec3RotateZ
MU_TEST(test_Vec3RotateZ) 
{
    // Test case 1: 90-degree rotation around Z
    Vec3 v1 = { 1.0f, 0.0f, 0.0f };
    Vec3 expected1 = { 0.0f, 1.0f, 0.0f };
    Vec3 result1 = Vec3RotateZ(v1, M_PI_2);
    mu_assert_float_eq(expected1.x, result1.x, EPSILON);
    mu_assert_float_eq(expected1.y, result1.y, EPSILON);
    mu_assert_float_eq(expected1.z, result1.z, EPSILON);

    // ... add more tests for Vec3RotateZ
}

MU_TEST_SUITE(test_suite) 
{
    MU_RUN_TEST(test_Vec3RotateX);  
    MU_RUN_TEST(test_Vec3RotateY);
    MU_RUN_TEST(test_Vec3RotateZ);
}

int main() 
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE; 
}