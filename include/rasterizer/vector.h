#ifndef VECTOR_H
#define VECTOR_H

// 2D Vector
typedef struct Vec2 {
    float x;   // X component
    float y;   // Y component
} Vec2;

// 3D Vector
typedef struct Vec3 {
    float x;   // X component
    float y;   // Y component
    float z;   // Z component
} Vec3;

/**
 * @brief Rotates a Vec3 around the X axis.
 * @param v The Vec3 to rotate.
 * @param angle The angle of rotation in radians.
 * @return The rotated Vec3.
 */
Vec3 Vec3RotateX(Vec3 v, float angle);

/**
 * @brief Rotates a Vec3 around the Y axis.
 * @param v The Vec3 to rotate.
 * @param angle The angle of rotation in radians.
 * @return The rotated Vec3.
 */
Vec3 Vec3RotateY(Vec3 v, float angle);

/**
 * @brief Rotates a Vec3 around the Z axis.
 * @param v The Vec3 to rotate.
 * @param angle The angle of rotation in radians.
 * @return The rotated Vec3.
 */
Vec3 Vec3RotateZ(Vec3 v, float angle);

#endif // VECTOR_H