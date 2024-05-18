#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"  // Include the Vec2 and Vec3 structures

// Face Structure
typedef struct Face
{
    int a;   // Index of the first vertex
    int b;   // Index of the second vertex
    int c;   // Index of the third vertex
} Face;

// Triangle Structure
typedef struct Triangle
{
    Vec2 points[3];  // Three vertices of the triangle
    // (You can add more attributes like normals, texture coordinates, colors later)
} Triangle;

#endif // TRIANGLE_H