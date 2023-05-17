#include "raylib.h"

//#define RAYGUI_IMPLEMENTATION
//#include "raygui.h"
#define RMEM_IMPLEMENTATION
#include "rmem.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool isRunning = false;

static uint32_t* colorBuffer = NULL;
static RenderTexture2D colorBufferTexture;

static const int screenWidth = 800;
static const int screenHeight = 600;

void MyDrawGrid(void)
{
    // TODO:
}

void RenderColorBuffer(void)
{
    UpdateTexture(colorBufferTexture.texture, (void*)colorBuffer);
    DrawTexture(colorBufferTexture.texture, 0, 0, WHITE);
}

void ClearColorBuffer(uint32_t color)
{
    for (int i = 0; i < screenWidth * screenHeight; i++) 
    {
        colorBuffer[i] = color;
    }
}

void Setup(void)
{
    // Allocate the required memory in bytes to hold the color buffer
    colorBuffer = (uint32_t*)RL_CALLOC(screenWidth * screenHeight, sizeof(uint32_t));

    // Creating a SDL texture that is used to display the color buffer
    colorBufferTexture = LoadRenderTexture(screenWidth, screenHeight);
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
        ClearBackground(RED);
        MyDrawGrid();
        ClearColorBuffer(0xFF0000FF); //ABGR
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
    InitWindow(screenWidth, screenHeight, "Rasterizer");

    // Mouse and Window variables
    Vector2 mousePosition = { 0 };
    Vector2 windowPosition = { 500, 200 };
    Vector2 panOffset = mousePosition;
    bool dragWindow = false;
    bool exitWindow = false;

    Setup();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!exitWindow && !WindowShouldClose())    // Detect window close button or ESC key
    {
        //Window Update
        //----------------------------------------------------------------------------------
        mousePosition = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePosition, (Rectangle) { 0, 0, screenWidth, 20 }))
            {
                dragWindow = true;
                panOffset = mousePosition;
            }
        }

        if (dragWindow)
        {
            windowPosition.x += (mousePosition.x - panOffset.x);
            windowPosition.y += (mousePosition.y - panOffset.y);

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) dragWindow = false;

            SetWindowPosition(windowPosition.x, windowPosition.y);
        }

        // Update
        //----------------------------------------------------------------------------------
        ProcessInput();
        Update();
        Render();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_FREE(colorBuffer);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}