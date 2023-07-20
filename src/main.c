//#include "raylib.h//"

//#define RAYGUI_IMPLEMENTATION
//#include "raygui.h"
//#define RMEM_IMPLEMENTATION
//#include "rmem.h"

#include "display.h"
#include "vector.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define N_POINTS (9*9*9)
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];

vec3_t camera_position = { .x = 0, .y = 0, .z = -5 };
vec3_t cube_rotation = { .x = 0, .y = 0, .z = 0 };

float fov_factor = 512;

bool isRunning = true;

void Setup(void)
{
    int point_count = 0;

    // start loading my array of vectors
    // form -1 to 1
    for(float x = -1.f; x <= 1.f; x += 0.25f)
    {
        for (float y = -1.f; y <= 1.f; y += 0.25f)
        {
            for (float z = -1.f; z <= 1.f; z += 0.25f)
            {
                vec3_t new_point = { .x = x, .y = y, .z = z };
                cube_points[point_count++] = new_point;
            }
        }
    }
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

    for(int i = 0; i < N_POINTS; ++i)
    {
        vec3_t point = cube_points[i];

        vec3_t transformed_point = vec3_rotate_x(point, cube_rotation.x);
        transformed_point = vec3_rotate_y(transformed_point, cube_rotation.y);
        transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);

        // Translate the points away from the camera
        transformed_point.z -= camera_position.z;

        // Save the projected 2D vector in the array of projected points
        projected_points[i] = project(transformed_point);
    }
}

void Render(void)
{
    BeginDrawing();
        ClearColorBuffer(BLACK);
        RDrawGrid(WHITE);
        for (int i = 0; i < N_POINTS; ++i)
        {
            RDrawRectangle(
                projected_points[i].x + (GetWindowWidth() / 2), 
                projected_points[i].y + (GetWindowHeight() / 2), 
                4, 
                4, 
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