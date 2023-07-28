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

int GetWindowWidth()
{
    return screenWidth;
}

int GetWindowHeight()
{
    return screenHeight;
}

void RDrawPixel(int x, int y, Color color)
{
    if(x > 0 && x < screenWidth && y > 0 && y < screenHeight)
        colorBuffer[(screenWidth * y) + x] = color;
}

//void RDrawLine (int x0, int y0, int x1, int y1, Color color)
//{
//    // DDA Algorithm
//    int delta_x = (x1 - x0);
//    int delta_y = (y1 - y0);
//
//    int longest_side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);
//
//    // Find how much we should increment in both x and y each step
//    float x_inc = delta_x / (float)longest_side_length;
//    float y_inc = delta_y / (float)longest_side_length;
//
//    float current_x = x0;
//    float current_y = y0;
//
//    for(int i = 0; i <= longest_side_length; i++)
//    {
//        RDrawPixel(round(current_x), round(current_y), color);
//        current_x += x_inc;
//        current_y += y_inc;
//    }
//}

void RDrawLine(int x0, int y0, int x1, int y1, Color color)
{
    // Bresenham Algorithms
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    for (;;) /* loop */
    {
        RDrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
}

void RDrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color)
{
    RDrawLine(x0, y0, x1, y1, color);
    RDrawLine(x0, y0, x2, y2, color);
    RDrawLine(x1, y1, x2, y2, color);
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
    for (int j = y; j < y + height; j++)
    {
        for (int i = x; i < x + width; i++)
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