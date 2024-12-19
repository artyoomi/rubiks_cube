#include "../../dependencies/glad/glad.h"

#include "app.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

App::App(std::size_t window_width, std::size_t window_height) :
    _win_width{window_width}, _win_height{window_height}
{
    _setup_glfw();
    _scene = new Scene();
    _renderer = new Renderer(_window);
}

App::~App()
{
    delete _scene;
    delete _renderer;
    glfwTerminate();
}

void App::_setup_glfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    _window = glfwCreateWindow(_win_width, _win_height, "Rubik's cube solver", NULL, NULL);
    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Couldn't load opengl" << std::endl;
        glfwTerminate();
    }
}

void App::_handle_input()
{
    static bool prev_states[9] = {};
    
    rotation_type rot_type = rotation_type::ROTATION_R;;
    if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
        glfwGetKey(_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
        rot_type = rotation_type::ROTATION_L;
    }
    
    if (glfwGetKey(_window, GLFW_KEY_F) == GLFW_PRESS && !prev_states[0]) {
        _scene->rotate_cube(rotation_side::SIDE_F, rot_type);
    }
    if (glfwGetKey(_window, GLFW_KEY_B) == GLFW_PRESS && !prev_states[1]) {
        _scene->rotate_cube(rotation_side::SIDE_B, rot_type);
    }
    if (glfwGetKey(_window, GLFW_KEY_R) == GLFW_PRESS && !prev_states[2]) {
        _scene->rotate_cube(rotation_side::SIDE_R, rot_type);
    }
    if (glfwGetKey(_window, GLFW_KEY_L) == GLFW_PRESS && !prev_states[3]) {
        _scene->rotate_cube(rotation_side::SIDE_L, rot_type);
    }
    if (glfwGetKey(_window, GLFW_KEY_U) == GLFW_PRESS && !prev_states[4]) {
        _scene->rotate_cube(rotation_side::SIDE_U, rot_type);
    }
    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS && !prev_states[5]) {
        _scene->rotate_cube(rotation_side::SIDE_D, rot_type);
    }
    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS && !prev_states[6]) {
        _scene->shuffle_cube();
    }
    if (glfwGetKey(_window, GLFW_KEY_EQUAL) == GLFW_PRESS && !prev_states[7]) {
        std::thread solver_thread(&Scene::solve_cube, _scene, ealgo_type::HUMAN);
        solver_thread.detach();
    }
    if (glfwGetKey(_window, GLFW_KEY_MINUS) == GLFW_PRESS && !prev_states[8]) {
        std::thread solver_thread(&Scene::solve_cube, _scene, ealgo_type::THISTLETHWAITE);
        solver_thread.detach();
    }
    
    prev_states[0] = (glfwGetKey(_window, GLFW_KEY_F) == GLFW_PRESS);
    prev_states[1] = (glfwGetKey(_window, GLFW_KEY_B) == GLFW_PRESS);
    prev_states[2] = (glfwGetKey(_window, GLFW_KEY_R) == GLFW_PRESS);
    prev_states[3] = (glfwGetKey(_window, GLFW_KEY_L) == GLFW_PRESS);
    prev_states[4] = (glfwGetKey(_window, GLFW_KEY_U) == GLFW_PRESS);
    prev_states[5] = (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS);
    prev_states[6] = (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS);
    prev_states[7] = (glfwGetKey(_window, GLFW_KEY_EQUAL) == GLFW_PRESS);
    prev_states[8] = (glfwGetKey(_window, GLFW_KEY_MINUS) == GLFW_PRESS);

    if (glfwGetWindowAttrib(_window, GLFW_HOVERED)) {
        static double prev_mouse_x = 0, prev_mouse_y = 0;
        double mouse_x, mouse_y;
        glfwGetCursorPos(_window, &mouse_x, &mouse_y);

        if(glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT)) {
            _scene->rotate_camera(prev_mouse_x - mouse_x, prev_mouse_y - mouse_y);
        }
        prev_mouse_x = mouse_x;
        prev_mouse_y = mouse_y;
    }
}

void App::run()
{
    std::chrono::steady_clock::time_point timestamp = std::chrono::steady_clock::now();
    while(!glfwWindowShouldClose(_window)) {
        glfwPollEvents();
        _handle_input();
        
        std::chrono::steady_clock::time_point timestamp_new = std::chrono::steady_clock::now();
        float seconds_on_frame = std::chrono::duration_cast<std::chrono::microseconds>(timestamp_new - timestamp).count() / 1000000.0f;
        _scene->update(seconds_on_frame);
        _renderer->render(*_scene);
        timestamp = timestamp_new;
    }
}
