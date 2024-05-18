#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

// Maximum number of vertices and faces for a mesh (can be adjusted if needed)
#define MAX_MESH_VERTICES 8
#define MAX_MESH_FACES (6 * 2) // Assuming 6 faces for a cube

// Mesh structure
//typedef struct Mesh
//{
//    Vec3 vertices[MAX_MESH_VERTICES]; // Array of vertices
//    Face faces[MAX_MESH_FACES];        // Array of faces
//    int num_vertices;                   // Actual number of vertices in the mesh
//    int num_faces;                     // Actual number of faces in the mesh
//} Mesh;

// Mesh Data (defined in mesh.c)
extern const Vec3 mesh_vertices[MAX_MESH_VERTICES];
extern const Face mesh_faces[MAX_MESH_FACES];

#endif // MESH_H
