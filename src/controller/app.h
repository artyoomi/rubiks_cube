#pragma once

#include <cstddef>

#include <atomic>
#include <mutex>

#include <GLFW/glfw3.h>
#include "../model/scene.h"
#include "../view/renderer.h"

class App
{
public:
    App(std::size_t window_width, std::size_t window_height);
    ~App();
    void run();
private:
    void _setup_glfw();
    void _handle_input();

    std::size_t _win_width, _win_height;
    GLFWwindow *_window;

    Scene    *_scene;
    Renderer *_renderer;

    std::atomic<bool> _is_solving;
};
