# Rasterizer

A simple 3D software renderer written in C89, using raylib as a backend.

## Features

- **Core Data Structures:** Vectors, meshes, triangles
- **Rendering Pipeline:** Basic ray tracing/rasterization (implementation in progress)
- **Mathematical Utilities:** Vector/matrix operations
- **Build System:** CMake
- **Testing Framework:** minunit

## Getting Started

1. **Clone:** `git clone https://github.com/ramo1606/3D-Renderer.git`
2. **Build:** 
   - `cd Rasterizer`
   - `mkdir build && cd build`
   - `cmake ..`
   - `cmake --build .`
3. **Run:** `./Rasterizer` (from the `build` directory)

## Project Structure

- **assets/:** Store your textures, 3D models, or other assets.
- **build/:** The output directory for the build process.
- **docs/:**  (Optional) Contains any documentation you create.
- **include/rasterizer/:** Public header files that define the interface of your renderer.
- **src/:** Source code of the renderer, organized into modules:
    - **core/:** Fundamental data structures and algorithms.
    - **math/:** Mathematical helper functions.
    - **rendering/:** Rendering logic and interaction with raylib.
- **test/:** Unit tests, mirroring the structure of the `src` directory.
- **CMakeLists.txt:** CMake configuration for building the project and running tests.


## Running Tests

To run the unit tests, use `ctest` from the `build` directory.