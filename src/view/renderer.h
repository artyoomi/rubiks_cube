#pragma once
#include "../../dependencies/GLFW/glfw3.h"
#include "../model/scene.h"
#include "cube_mesh.h"

class Renderer
{
public:
    Renderer(GLFWwindow *window);
    ~Renderer();

    void render(const Scene &scene);
private:
    void _prepare_opengl();
    void _load_assets();

    struct shader_in {
        unsigned int model_transform;
        unsigned int camera_transform;
        unsigned int projection_transform;
    };
    
    GLFWwindow *_window;
    
    CubeMesh    *_cube_mesh;
    unsigned int _cube_texture;

    unsigned int _shader;
    shader_in _shader_data;
};
