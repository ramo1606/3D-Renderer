//#include "raylib.h//"

//#define RAYGUI_IMPLEMENTATION
//#include "raygui.h"
//#define RMEM_IMPLEMENTATION
//#include "rmem.h"

#include "display.h"
#include "vector.h"
#include "mesh.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

triangle_t triangles_to_render[N_MESH_FACES];

vec3_t camera_position = { .x = 0, .y = 0, .z = -5 };
vec3_t cube_rotation = { .x = 0, .y = 0, .z = 0 };

float fov_factor = 512;

bool isRunning = true;

void Setup(void)
{
   
}

void ProcessInput(void)
{
    if (IsKeyDown(KEY_ESCAPE)) isRunning = false;
}

vec2_t project(vec3_t point)
{
    vec2_t projected_point = { .x = (fov_factor * point.x) / point.z, .y = (fov_factor * point.y) / point.z };
    return projected_point;
}

void Update(void)
{
    cube_rotation.y += 0.01f;
    cube_rotation.z += 0.01f;
    cube_rotation.x += 0.01f;

    for (int i = 0; i < N_MESH_FACES; i++)
    {
        face_t mesh_face = mesh_faces[i];
        vec3_t face_vertices[3];
        face_vertices[0] = mesh_vertices[mesh_face.a - 1];
        face_vertices[1] = mesh_vertices[mesh_face.b - 1];
        face_vertices[2] = mesh_vertices[mesh_face.c - 1];

        triangle_t projected_triangle = { 0 };

        for (int j = 0; j < 3; j++)
        {
            vec3_t transformed_vertex = face_vertices[j];
            transformed_vertex = vec3_rotate_x(transformed_vertex, cube_rotation.x);
            transformed_vertex = vec3_rotate_y(transformed_vertex, cube_rotation.y);
            transformed_vertex = vec3_rotate_z(transformed_vertex, cube_rotation.z);

            // Translate the vertex away from the camera
            transformed_vertex.z -= camera_position.z;

            vec2_t projected_vertex = project(transformed_vertex);

            // Scale and translate the projected points to the middle of the screen
            projected_vertex.x += GetWindowWidth() / 2;
            projected_vertex.y += GetWindowHeight() / 2;

            projected_triangle.points[j] = projected_vertex;
        }

        triangles_to_render[i] = projected_triangle;
    }
}

void Render(void)
{
    BeginDrawing();
        ClearColorBuffer(BLACK);
        RDrawGrid(WHITE);
        for (int i = 0; i < N_MESH_FACES; ++i)
        {
            RDrawTriangle(triangles_to_render[i].points[0].x, triangles_to_render[i].points[0].y,
                triangles_to_render[i].points[1].x, triangles_to_render[i].points[1].y,
                triangles_to_render[i].points[2].x, triangles_to_render[i].points[2].y,
                RED);
        }
        RenderColorBuffer();
    EndDrawing();
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitiRaylibWindow();
    Setup();

    // Main game loop
    while (isRunning && !WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        ProcessInput();
        Update();
        Render();
    }
    
    // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    DestroyRaylibWindow();
    return 0;
}