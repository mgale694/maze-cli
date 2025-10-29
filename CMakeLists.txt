cmake_minimum_required(VERSION 3.23)

project(MazeCLI)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20) # User C++20
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find required packages for GLFW version
find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)

# CLI version (text-based)
add_executable(MazeCLI
    main.cpp
    src/welcome.cpp
    src/builder.cpp
    src/runner.cpp
)

# GLFW version (graphical)
add_executable(MazeGLFW
    main_glfw.cpp
    src/welcome.cpp
    src/builder.cpp
    src/graphical_maze.cpp
)

# Link libraries for GLFW version
target_link_libraries(MazeGLFW
    ${OPENGL_LIBRARIES}
    glfw
    GLEW::GLEW
)
