# 1. Minimum CMake Version & Project Setup
cmake_minimum_required(VERSION 3.0)         # Ensure you have at least CMake 3.0
project(Rasterizer C)                        # Name the project and set the language to C


# 2. C Language Standard Enforcement
set(CMAKE_C_STANDARD 99)                    # Set the C standard to C99 (which is backward compatible with C89)
set(CMAKE_C_STANDARD_REQUIRED ON)           # Enforce the standard during compilation


# 3. External Dependencies (Raylib)
include(FetchContent)                        # Enable the FetchContent module to download and include external projects

# Declare the raylib library to be fetched from its Git repository
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)

# Download, build, and link raylib. This command will handle downloading the source code, configuring the build, and building raylib as part of your project.
FetchContent_MakeAvailable(raylib)


# 4. Project Files Collection

# Recursively find all C source files within the "src" directory and its subdirectories
file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/**/*.c")

# Recursively find all C header files within the "include/rasterizer" directory and its subdirectories
file(GLOB_RECURSE PROJECT_HEADERS "${CMAKE_CURRENT_LIST_DIR}/include/rasterizer/*.h")

# Set the include directory for public headers (those to be included by users of the library)
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/include")


# 5. Main Executable Target

# Create an executable target named "Rasterizer" using the collected source and header files
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

# Add include directories for the main target
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE}       # Include public headers (include/rasterizer/)
    "${CMAKE_CURRENT_LIST_DIR}/src/core" # Include headers from src/core/
    "${CMAKE_CURRENT_LIST_DIR}/src/math"  # Include headers from src/math/
    "${CMAKE_CURRENT_LIST_DIR}/src/rendering" # Include headers from src/rendering/
)

# Link the raylib library to the executable target
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)  


# 6. Asset Path Definition

# Set a preprocessor definition (ASSETS_PATH) to "./assets/", assuming the assets folder is next to the executable
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/")


# 7. Unit Testing with minunit

# Enable CMake's built-in testing functionality
enable_testing()

# Gather test sources and headers (recursively search for files)
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_LIST_DIR}/test/**/*.c")
file(GLOB_RECURSE TEST_HEADERS "${CMAKE_CURRENT_LIST_DIR}/test/*.h")
set(TEST_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/test")

# Create test executables for each test source file
foreach(test_source IN LISTS TEST_SOURCES)
    string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/test/" "" test_name ${test_source})

    # Create a test executable
    add_executable(${test_name} ${test_source} ${TEST_HEADERS})

    # Include the project and test headers
    target_include_directories(${test_name} PRIVATE 
        ${PROJECT_INCLUDE}       # Include public headers (include/rasterizer/)
        ${TEST_INCLUDE}        # Include test-specific headers (test/)
        "${CMAKE_CURRENT_LIST_DIR}/src/core" # Include headers from src/core/
        "${CMAKE_CURRENT_LIST_DIR}/src/math"  # Include headers from src/math/
        "${CMAKE_CURRENT_LIST_DIR}/src/rendering" # Include headers from src/rendering/
    )
    target_link_libraries(${test_name} PRIVATE raylib)  

    # Add the test executable to CTest
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

