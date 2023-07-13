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

float fov_factor = 256;

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
    vec2_t projected_point = { .x = fov_factor * point.x, .y = fov_factor * point.y };
    return projected_point;
}

void Update(void)
{
    for(int i = 0; i < N_POINTS; ++i)
    {
        projected_points[i] = project(cube_points[i]);
    }
}

void Render(void)
{
    BeginDrawing();
        ClearColorBuffer(BLACK);
        RDrawGrid(WHITE);
        for (int i = 0; i < N_POINTS; ++i)
        {
            RDrawRectangle(projected_points[i].x + (GetWindowWidth() / 2), projected_points[i].y + (GetWindowHeight() / 2), 4, 4, RED);
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