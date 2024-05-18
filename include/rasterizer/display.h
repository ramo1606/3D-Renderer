#ifndef DISPLAY_H
#define DISPLAY_H

#include "raylib.h"

// Window Management
/**
 * @brief Initializes the raylib window to full screen and maximized.
 */
void InitRaylibWindow(void);

/**
 * @brief Closes the raylib window and unloads resources.
 */
void CloseRaylibWindow(void);

/**
 * @brief Gets the width of the window.
 * @return The width of the window in pixels.
 */
int GetWindowWidth(void);

/**
 * @brief Gets the height of the window.
 * @return The height of the window in pixels.
 */
int GetWindowHeight(void);

// Low-Level Drawing Functions (Rasterizer-specific)

/**
 * @brief Draws a pixel at the specified coordinates.
 *
 * If the coordinates are out of bounds, a warning is logged and the function returns.
 *
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel (raylib Color struct).
 */
void RDrawPixel(int x, int y, Color color);

/**
 * @brief Draws a line between two points.
 *
 * If the coordinates are out of bounds, a warning is logged and the function returns.
 *
 * @param x0 The x-coordinate of the starting point.
 * @param y0 The y-coordinate of the starting point.
 * @param x1 The x-coordinate of the ending point.
 * @param y1 The y-coordinate of the ending point.
 * @param color The color of the line (raylib Color struct).
 */
void RDrawLine(int x0, int y0, int x1, int y1, Color color);

/**
 * @brief Draws a filled triangle.
 *
 * If any of the vertices' coordinates are out of bounds, a warning is logged and the function returns.
 *
 * @param x0 The x-coordinate of the first vertex.
 * @param y0 The y-coordinate of the first vertex.
 * @param x1 The x-coordinate of the second vertex.
 * @param y1 The y-coordinate of the second vertex.
 * @param x2 The x-coordinate of the third vertex.
 * @param y2 The y-coordinate of the third vertex.
 * @param color The color of the triangle (raylib Color struct).
 */
void RDrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color);

/**
 * @brief Draws a grid of points.
 * @param color The color ofthe grid points (raylib Color struct).
 */
void RDrawGrid(Color color);

/**
 * @brief Draws a filled rectangle.
 *
 * If the coordinates are out of bounds, a warning is logged and the function returns.
 *
 * @param x The x-coordinate of the top-left corner.
 * @param y The y-coordinate of the top-left corner.
 * @param width The width of the rectangle.
 * @param the rectangle (raylib Color struct).
 */
void RDrawRectangle(int x, int y, int width, int height, Color color);


// Rendering Utilities
/**
 * @brief Clears the color buffer with the specified color.
 * @param color The color to clear the buffer with (raylib Color struct).
 */
void ClearColorBuffer(Color color);

/**
 * @brief Renders the contents of the color buffer to the screen.
 */
void RenderColorBuffer(void);

#endif // DISPLAY_H
