#pragma once

#include "raylib.h"

/* Window Creation and Destroy */
void InitiRaylibWindow(void);
void DestroyRaylibWindow(void);

/* Drawing Functions */
void RDrawPixel(int x, int y, Color color);
void RDrawGrid(Color color);
void RDrawRectangle(int x, int y, int width, int height, Color color);

/* Rendering Functions*/
void ClearColorBuffer(Color color);
void RenderColorBuffer(void);