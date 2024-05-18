#include "rasterizer/display.h"
#include "rasterizer/vector.h"
#include "rasterizer/mesh.h"

#include <stdbool.h>

// Private (static) variables
static Vec3 cameraPosition = { 0.0f, 0.0f, -5.0f };  // Camera's position in 3D space
static Vec3 cubeRotation = { 0.0f, 0.0f, 0.0f };     // Cube's rotation angles
static float fovFactor = 600.0f;                 // Field-of-view factor

// Array to store triangles to be rendered after transformations
static Triangle trianglesToRender[MAX_MESH_FACES];

static bool isRunning = true;                     // Flag to control the main loop

// Function to project 3D points to 2D screen coordinates
// Takes a 3D point as input and returns the corresponding 2D point after projection.
static Vec2 Project(Vec3 point)
{
    Vec2 projectedPoint =
    {
        .x = (fovFactor * point.x) / point.z,
        .y = (fovFactor * point.y) / point.z
    };
    return projectedPoint;
}


// Setup function (called once at the start)
// Can be used for any additional initialization you might need.
void Setup(void)
{
    // (You can add more initialization code here if needed)
}

// Input handling function (called every frame)
// Processes user input and updates the 'isRunning' flag if the escape key is pressed.
void ProcessInput(void)
{
    if (IsKeyDown(KEY_ESCAPE))
    {
        isRunning = false;
    }
}

// Update function (called every frame)
// Updates the state of the game world, including rotations, transformations, etc.
void Update(void)
{
    // Update cube rotation angles
    cubeRotation.x += 0.01f;
    cubeRotation.y += 0.01f;
    cubeRotation.z += 0.01f;

    // Process each face of the mesh
    for (int i = 0; i < MAX_MESH_FACES; i++)
    {
        Face meshFace = mesh_faces[i];

        // Get vertices for the current face (adjusting indices from 1-based to 0-based)
        Vec3 faceVertices[3] =
        {
            mesh_vertices[meshFace.a - 1],
            mesh_vertices[meshFace.b - 1],
            mesh_vertices[meshFace.c - 1]
        };

        // Transform and project each vertex of the face
        for (int j = 0; j < 3; j++)
        {
            Vec3 transformedVertex = faceVertices[j];

            // Rotate the vertex around each axis
            transformedVertex = Vec3RotateX(transformedVertex, cubeRotation.x);
            transformedVertex = Vec3RotateY(transformedVertex, cubeRotation.y);
            transformedVertex = Vec3RotateZ(transformedVertex, cubeRotation.z);

            // Translate the vertex away from the camera
            transformedVertex.z += cameraPosition.z;

            // Project the 3D vertex to 2D screen coordinates
            Vec2 projectedVertex = Project(transformedVertex);

            // Scale and translate the projected point to the center of the screen
            projectedVertex.x += (float)GetWindowWidth() / 2;
            projectedVertex.y += (float)GetWindowHeight() / 2;

            // Store the projected vertex in the trianglesToRender array
            trianglesToRender[i].points[j] = projectedVertex;
        }
    }
}

// Render function (called every frame)
// Renders the scene using the custom drawing functions from `display.c`
void Render(void)
{
    BeginDrawing();

    // Clear the color buffer to black before starting the drawing
    ClearColorBuffer(BLACK);

    // Draw the grid
    RDrawGrid(WHITE);

    // Iterate through all triangles to be rendered
    for (int i = 0; i < MAX_MESH_FACES; ++i)
    {
        // Draw each triangle using the vertex data from trianglesToRender
        RDrawTriangle(trianglesToRender[i].points[0].x, trianglesToRender[i].points[0].y,
                      trianglesToRender[i].points[1].x, trianglesToRender[i].points[1].y,
                      trianglesToRender[i].points[2].x, trianglesToRender[i].points[2].y,
                      RED);
    }

    // After drawing, copy the content of color buffer to the screen 
    RenderColorBuffer();

    EndDrawing();
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    InitRaylibWindow();
    Setup();

    // Main game loop
    while (isRunning && !WindowShouldClose()) // Keep running until the user closes the window or presses Escape.
    {
        ProcessInput(); // Handle user input
        Update();      // Update game state
        Render();      // Render the scene
    }

    // Clean up
    CloseRaylibWindow(); // Close the window and release resources.
    return 0;
}
