#pragma once
#include "../../dependencies/glm/glm.hpp"
#include "../../dependencies/glm/ext/scalar_constants.hpp"
#include <vector>
#include <deque>
#include "camera.h"
#include "cube.h"
#include "../algorithm/cube_bg_model.h"

#include <mutex>
#include <atomic>

#define ROTATION_SPEED 5 * 360.0f // deg / sec
#define CAMERA_DIST    15.0f

enum class ealgo_type {HUMAN, THISTLETHWAITE};

class Scene
{
public:
    Scene();
    ~Scene();

    void update(float dt);
    
    glm::mat4 get_camera_transform() const;
    std::vector<glm::mat4> get_cubes_transform() const;

    void rotate_cube(rotation_side side, rotation_type rot);
    void rotate_camera(float angle_x, float angle_y);
    void shuffle_cube();
    void solve_cube(ealgo_type algo_type, std::atomic<bool>& is_solving);

private:
    Camera *_camera;
    std::vector<Cube> _cubes;
    Cube_bg_model *_bg_cube;

    std::mutex mtx;

    std::deque<std::pair<rotation_side, rotation_type>> _rot_queue;
    float _cur_rot_amount = 0.0f;

    // camera position in spherical coordinates (radians)
    float _camera_phi = glm::pi<float>() / 4.0f;
    float _camera_theta = glm::pi<float>() / 4.0f;

    // initial members of the sides
    // every side is scanned up-down, left-right
    // up is scanned back-front, left-right
    // down is scanned back-front, right-left
    // the cube parts are numerated by layers, up-down, left-right
    std::vector<int> _side_L = { 0,  3,  6,  9, 12, 14, 17, 20, 23};
    std::vector<int> _side_R = { 8,  5,  2, 16, 13, 11, 25, 22, 19};
    std::vector<int> _side_F = { 6,  7,  8, 14, 15, 16, 23, 24, 25};
    std::vector<int> _side_B = { 2,  1,  0, 11, 10,  9, 19, 18, 17};
    std::vector<int> _side_U = { 0,  1,  2,  3,  4,  5,  6,  7,  8};
    std::vector<int> _side_D = {19, 18, 17, 22, 21, 20, 25, 24, 23};
};
