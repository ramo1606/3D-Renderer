#include "rasterizer/vector.h"
#include <math.h>
#include "raylib.h"  

#define ASSERT(condition, message) assert(condition && message) 

/**
 * @brief Rotates a Vec3 around the X axis.
 * @param v The Vec3 to rotate.
 * @param angle The angle of rotation in radians.
 * @return The rotated Vec3.
 */
Vec3 Vec3RotateX(Vec3 v, float angle)
{
    if (isnan(angle))
    {
        TraceLog(LOG_ERROR, "Vec3RotateX: Invalid angle (NaN).");
        return v; // Return the original vector 
    }

    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);

    Vec3 rotatedVector =
    {
        .x = v.x,
        .y = v.y * cosAngle - v.z * sinAngle,
        .z = v.y * sinAngle + v.z * cosAngle
    };
    return rotatedVector;
}


/**
 * @brief Rotates a Vec3 around the Y axis.
 * @param v The Vec3 to rotate.
 * @param angle The angle of rotation in radians.
 * @return The rotated Vec3.
 */
Vec3 Vec3RotateY(Vec3 v, float angle)
{
    if (isnan(angle))
    {
        TraceLog(LOG_ERROR, "Vec3RotateY: Invalid angle (NaN).");
        return v;
    }

    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);

    Vec3 rotatedVector =
    {
        .x = v.x * cosAngle + v.z * sinAngle,
        .y = v.y,
        .z = -v.x * sinAngle + v.z * cosAngle
    };
    return rotatedVector;
}


/**
 * @brief Rotates a Vec3 around the Z axis.
 * @param v The Vec3 to rotate.
 * @param angle The angle of rotation in radians.
 * @return The rotated Vec3.
 */
Vec3 Vec3RotateZ(Vec3 v, float angle)
{
    if (isnan(angle))
    {
        TraceLog(LOG_ERROR, "Vec3RotateZ: Invalid angle (NaN).");
        return v;
    }

    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);

    Vec3 rotatedVector =
    {
        .x = v.x * cosAngle - v.y * sinAngle,
        .y = v.x * sinAngle + v.y * cosAngle,
        .z = v.z
    };
    return rotatedVector;
}

