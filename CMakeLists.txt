cmake_minimum_required(VERSION 3.23)

project(MazeCLI)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20) # User C++20
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
add_executable(MazeCLI
    main.cpp
    src/welcome.cpp
    src/builder.cpp
)

# Add include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)
