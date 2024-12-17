cmake_minimum_required(VERSION 3.12.0)
project(rubik VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# for Debug
set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building in Debug mode")
else()
    message(STATUS "Building in Release mode")
endif()

# to autofetch glfw
include(FetchContent)

# Check if GLFW is already installed
find_package(glfw3 QUIET)

if ((NOT glfw3_FOUND) AND MINGW)
    message(WARNING "GLFW not found. Fetching and building GLFW locally. Its better to install GLFW system-wide first.")
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
    )
    FetchContent_MakeAvailable(glfw)
else()
    message(STATUS "GLFW found.")
endif()

find_package(OpenGL REQUIRED)

include_directories(src src/algorithm)

add_executable(Rubiks_cube
    src/main.cpp 
    src/glad.c
    src/model/camera.cpp
    src/model/cube.cpp
    src/model/scene.cpp
    src/view/cube_mesh.cpp
    src/view/renderer.cpp
    src/view/resource_load.cpp
    src/controller/app.cpp
    src/stb_image.cpp
    src/algorithm/cube_bg_model.cpp
    src/algorithm/human_algorithm/human_algo.cpp
)

target_link_libraries(Rubiks_cube
    glfw
    OpenGL::GL 
)

