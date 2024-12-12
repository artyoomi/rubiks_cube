cmake_minimum_required(VERSION 3.12.0)
project(hello_window VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

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
    src/algorithm/solver.cpp
    src/algorithm/cube_bg_model.cpp
)

target_link_libraries(Rubiks_cube
    glfw
    OpenGL::GL 
)

