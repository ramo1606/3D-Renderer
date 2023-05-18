//#include "raylib.h//"

//#define RAYGUI_IMPLEMENTATION
//#include "raygui.h"
//#define RMEM_IMPLEMENTATION
//#include "rmem.h"

#include "display.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool isRunning = true;

void Setup(void)
{
}

void ProcessInput(void)
{
    if (IsKeyDown(KEY_ESCAPE)) isRunning = false;
}

void Update(void)
{
    //TODO
}

void Render(void)
{
    BeginDrawing();
        ClearColorBuffer(BLACK);
        RDrawGrid(WHITE);
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