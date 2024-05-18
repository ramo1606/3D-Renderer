#include "rasterizer/display.h"
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

// Private (static) variables
static Color* colorBuffer = NULL;
static RenderTexture2D colorBufferTexture;
static int screenWidth = 0;
static int screenHeight = 0;

void InitRaylibWindow(void)
{
    if (screenWidth != 0 || screenHeight != 0)
    {
        TraceLog(LOG_WARNING, "InitRaylibWindow: Window already initialized.");
        return;
    }

    // Initialize raylib window, full screen and maximized
    InitWindow(screenWidth, screenHeight, "Rasterizer");
    int currentMonitor = GetCurrentMonitor();
    screenWidth = GetMonitorWidth(currentMonitor);
    screenHeight = GetMonitorHeight(GetCurrentMonitor());
    SetWindowSize(screenWidth, screenHeight);
    SetWindowState(FLAG_WINDOW_MAXIMIZED); // Start maximized
    
    SetTargetFPS(60);

    // Allocate memory for the color buffer and create a RenderTexture
    colorBuffer = (Color*)RL_CALLOC(screenWidth * screenHeight, sizeof(Color));
    if (!colorBuffer)
    {
        TraceLog(LOG_ERROR, "InitRaylibWindow: Failed to allocate color buffer.");
        return;
    }

    colorBufferTexture = LoadRenderTexture(screenWidth, screenHeight);
    if (colorBufferTexture.id == 0)
    {
        TraceLog(LOG_ERROR, "InitRaylibWindow: Failed to create render texture.");
        RL_FREE(colorBuffer); // Free the color buffer if texture loading fails
        return;
    }
}

void CloseRaylibWindow(void)
{
    if (colorBuffer == NULL)
    {
        TraceLog(LOG_WARNING, "CloseRaylibWindow: Color buffer not initialized.");
        return;
    }
    if (colorBufferTexture.id == 0)
    {
        TraceLog(LOG_WARNING, "CloseRaylibWindow: Render texture not initialized.");
        return;
    }

    RL_FREE(colorBuffer);
    UnloadRenderTexture(colorBufferTexture);
    CloseWindow();
}

int GetWindowWidth(void)
{
    return screenWidth;
}

int GetWindowHeight(void)
{
    return screenHeight;
}

void RDrawPixel(int x, int y, Color color)
{
    if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight)
    {
        TraceLog(LOG_WARNING, "RDrawPixel: Coordinates out of bounds.");
        return;
    }
    colorBuffer[(screenWidth * y) + x] = color; // Calculate 1D index from 2D coords
}


void RDrawLine(int x0, int y0, int x1, int y1, Color color)
{
    if (x0 < 0 || x0 >= screenWidth || y0 < 0 || y0 >= screenHeight ||
        x1 < 0 || x1 >= screenWidth || y1 < 0 || y1 >= screenHeight)
    {
        TraceLog(LOG_WARNING, "RDrawLine: Coordinates out of bounds.");
        return;
    }

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
    // Check all three vertices for valid coordinates
    if (x0 < 0 || x0 >= screenWidth || y0 < 0 || y0 >= screenHeight ||
        x1 < 0 || x1 >= screenWidth || y1 < 0 || y1 >= screenHeight ||
        x2 < 0 || x2 >= screenWidth || y2 < 0 || y2 >= screenHeight)
    {
        TraceLog(LOG_WARNING, "RDrawTriangle: Coordinates out of bounds.");
        return;
    }

    RDrawLine(x0, y0, x1, y1, color);
    RDrawLine(x1, y1, x2, y2, color);
    RDrawLine(x2, y2, x0, y0, color);
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
    // Check for valid input
    if (width <= 0 || height <= 0)
    {
        TraceLog(LOG_WARNING, "RDrawRectangle: Invalid dimensions. Width and height must be positive.");
        return;
    }

    // Calculate the actual coordinates to draw, clipping to the screen bounds
    int x0 = (x < 0) ? 0 : x;
    int y0 = (y < 0) ? 0 : y;
    int x1 = (x + width > screenWidth) ? screenWidth - 1 : x + width - 1;
    int y1 = (y + height > screenHeight) ? screenHeight - 1 : y + height - 1;

    // Draw the four lines of the rectangle
    RDrawLine(x0, y0, x1, y0, color);    // Top
    RDrawLine(x1, y0, x1, y1, color);    // Right
    RDrawLine(x1, y1, x0, y1, color);    // Bottom
    RDrawLine(x0, y1, x0, y0, color);    // Left
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
    // Update RenderTexture with our buffer and draw it to the screen
    UpdateTexture(colorBufferTexture.texture, colorBuffer);
    DrawTexture(colorBufferTexture.texture, 0, 0, WHITE);
}

