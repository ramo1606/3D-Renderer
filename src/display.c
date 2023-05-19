#include "display.h"

#include <stdlib.h>

static Color* colorBuffer = NULL;
static RenderTexture2D colorBufferTexture;

static int screenWidth = 0;
static int screenHeight = 0;

void InitiRaylibWindow(void) 
{
    InitWindow(screenWidth, screenHeight, "Rasterizer");
    int currentMonitor = GetCurrentMonitor();
    screenWidth = GetMonitorWidth(currentMonitor);
    screenHeight = GetMonitorHeight(currentMonitor);
    SetWindowSize(screenWidth, screenHeight);
    SetWindowState(FLAG_WINDOW_MAXIMIZED);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Allocate the required memory in bytes to hold the color buffer and new Render Texture where we are going to draw the buffer
    colorBuffer = (Color*)RL_CALLOC(screenWidth * screenHeight, sizeof(Color));
    colorBufferTexture = LoadRenderTexture(screenWidth, screenHeight);
}

void DestroyRaylibWindow(void) 
{
    RL_FREE(colorBuffer);
    CloseWindow();
}

void RDrawPixel(int x, int y, Color color)
{
    if(x > 0 && x < screenWidth && y > 0 && y < screenHeight)
        colorBuffer[(screenWidth * y) + x] = color;
}

void RDrawGrid(Color color)
{
    for (int y = 25; y < screenHeight; y += 50)
    {
        for (int x = 25; x < screenWidth; x += 50)
        {
            RDrawPixel(x, y, color);
        }
    }
}

void RDrawRectangle(int x, int y, int width, int height, Color color)
{
    //Draw a rectangle
    for (int i = y; i < y + height; i++)
    {
        for (int j = x; j < x + width; j++)
        {
            RDrawPixel(i, j, color);
        }
    }
}

void ClearColorBuffer(Color color)
{
    // Set all pixels in screen with color
    for (int i = 0; i < screenWidth * screenHeight; i++)
    {
        colorBuffer[i] = color;
    }
}

void RenderColorBuffer(void)
{
    // Update RenderTexture with our buffer and Draw the RenderTexture to screen
    UpdateTexture(colorBufferTexture.texture, (void*)colorBuffer);
    DrawTexture(colorBufferTexture.texture, 0, 0, WHITE);
}