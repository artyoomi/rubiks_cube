#include <random>
#include "scene.h"
#include "../algorithm/solver.h"
#include "../../dependencies/glm/gtx/rotate_vector.hpp"

Scene::Scene()
{
    _camera = new Camera();
    this->rotate_camera(0, 0); // just to update camera position

    _bg_cube = new Cube_bg_model();

    for(int layer = 2; layer >= 0; layer--) {
        for(int x = 0; x < 3; x++) {
            for(int y = 0; y < 3; y++) {
                if(y == 1 && x == 1 && layer == 1)
                    continue;
                // axes swapped to have more "human-like" placement in the vector
                _cubes.emplace_back(glm::vec3({x-1.0f, y-1.0f, layer-1.0f}));
            }
        }
    }
}

Scene::~Scene()
{
    delete _camera;
    delete _bg_cube;
}

void Scene::rotate_cube(rotation_side side, rotation_type rot)
{
    _rot_queue.emplace_back(side, rot);
    _bg_cube->rotate(side, rot);
}

void Scene::solve_cube()
{
    auto moves = solver::solve(*_bg_cube);
    for(const auto &i : moves) {
        _bg_cube->rotate(i.first, i.second);
        this->rotate_cube(i.first, i.second);
    }
}

void Scene::rotate_camera(float angle_x, float angle_y)
{
    _camera_phi += glm::radians(angle_x);
    _camera_theta += glm::radians(angle_y);
    
    if(_camera_theta > glm::pi<float>())
        _camera_theta = glm::pi<float>();
    if(_camera_theta < 0.0f)
        _camera_theta = 0.01f;

    if(_camera_phi > (glm::pi<float>() * 2.0))
        _camera_phi -= glm::pi<float>() * 2.0;
    if(_camera_phi < (glm::pi<float>() * -2.0))
        _camera_phi += glm::pi<float>() * 2.0;

    glm::vec3 camera_pos = {CAMERA_DIST * glm::cos(_camera_phi) * glm::sin(_camera_theta),
                            CAMERA_DIST * glm::sin(_camera_phi) * glm::sin(_camera_theta),
                            CAMERA_DIST * glm::cos(_camera_theta)};

    _camera->move(camera_pos);
}

void Scene::shuffle_cube()
{
    std::random_device rd_dev;
    std::mt19937 rnd_gen(rd_dev());
    std::uniform_int_distribution<> moves_count_rnd(20, 50);
    std::uniform_int_distribution<> move_side_rnd(0, 5);
    std::uniform_int_distribution<> move_type_rnd(0, 2);

    // generate N random moves
    int n = moves_count_rnd(rnd_gen);
    for(; n > 0; n--) {
        rotation_side rot_side = static_cast<rotation_side>(move_side_rnd(rnd_gen));
        rotation_type rot_type = static_cast<rotation_type>(move_type_rnd(rnd_gen));
        this->rotate_cube(rot_side, rot_type);
    }
}

void Scene::update(float dt)
{
    if(_rot_queue.empty())
        return;
    
    float rot_amount = dt * ROTATION_SPEED;
    _cur_rot_amount += rot_amount;
    
    // select the group
    std::vector<int> *group_ptr;
    glm::vec3 rotation_axis;
    switch(_rot_queue.front().first) {
        case rotation_side::SIDE_F:
            group_ptr = &_side_F;
            rotation_axis = {-1.0f, 0.0f, 0.0f};
            break;
        case rotation_side::SIDE_B:
            group_ptr = &_side_B;
            rotation_axis = {1.0f, 0.0f, 0.0f};
            break;
        case rotation_side::SIDE_R:
            group_ptr = &_side_R;
            rotation_axis = {0.0f, -1.0f, 0.0f};
            break;
        case rotation_side::SIDE_L:
            group_ptr = &_side_L;
            rotation_axis = {0.0f, 1.0f, 0.0f};
            break;
        case rotation_side::SIDE_U:
            group_ptr = &_side_U;
            rotation_axis = {0.0f, 0.0f, -1.0f};
            break;
        case rotation_side::SIDE_D:
            group_ptr = &_side_D;
            rotation_axis = {0.0f, 0.0f, 1.0f};
            break;
    }

    float mul = (_rot_queue.front().second == rotation_type::ROTATION_R) ? 1.0f : -1.0f;
    // apply rotation
    for(const auto &i : *group_ptr) {
        _cubes[i].add_rotation(glm::radians(mul * rot_amount), rotation_axis);
    }
    
    if(_cur_rot_amount >= 90.0f) {
        // Quantize the rotation to 90 deg
        for(const auto &i : *group_ptr) {
            _cubes[i].add_rotation(glm::radians(mul * (_cur_rot_amount - 90.0f)), -rotation_axis);
        }
        
        // Scary things here - editing side groups

        // First reorder rotated group:
        if(_rot_queue.front().second == rotation_type::ROTATION_R) {
            // 0 1 2    6 3 0
            // 3 4 5 -> 7 4 1
            // 6 7 8    8 5 2
            int tmp0 = (*group_ptr)[0];
            int tmp1 = (*group_ptr)[1];
            int tmp2 = (*group_ptr)[2];
            (*group_ptr)[0] = (*group_ptr)[6];
            (*group_ptr)[1] = (*group_ptr)[3];
            (*group_ptr)[3] = (*group_ptr)[7];
            (*group_ptr)[6] = (*group_ptr)[8];
            (*group_ptr)[7] = (*group_ptr)[5];
            (*group_ptr)[2] = tmp0;
            (*group_ptr)[5] = tmp1;
            (*group_ptr)[8] = tmp2;
        }
        else {
            // 0 1 2    2 5 8
            // 3 4 5 -> 1 4 7
            // 6 7 8    0 3 6
            int tmp0 = (*group_ptr)[0];
            int tmp1 = (*group_ptr)[1];
            int tmp2 = (*group_ptr)[2];
            (*group_ptr)[1] = (*group_ptr)[5];
            (*group_ptr)[2] = (*group_ptr)[8];
            (*group_ptr)[5] = (*group_ptr)[7];
            (*group_ptr)[7] = (*group_ptr)[3];
            (*group_ptr)[8] = (*group_ptr)[6];
            (*group_ptr)[6] = tmp0;
            (*group_ptr)[3] = tmp1;
            (*group_ptr)[0] = tmp2;
        }
        
        // Then update neighbor sides:
        switch(_rot_queue.front().first) {
            case rotation_side::SIDE_F:
                _side_L[2] = _side_F[0];
                _side_L[5] = _side_F[3];
                _side_L[8] = _side_F[6];
                
                _side_U[6] = _side_F[0];
                _side_U[7] = _side_F[1];
                _side_U[8] = _side_F[2];

                _side_R[0] = _side_F[2];
                _side_R[3] = _side_F[5];
                _side_R[6] = _side_F[8];

                _side_D[8] = _side_F[6];
                _side_D[7] = _side_F[7];
                _side_D[6] = _side_F[8];
                break;
            case rotation_side::SIDE_B:
                _side_L[0] = _side_B[2];
                _side_L[3] = _side_B[5];
                _side_L[6] = _side_B[8];
                
                _side_U[0] = _side_B[2];
                _side_U[1] = _side_B[1];
                _side_U[2] = _side_B[0];

                _side_R[2] = _side_B[0];
                _side_R[5] = _side_B[3];
                _side_R[8] = _side_B[6];

                _side_D[2] = _side_B[8];
                _side_D[1] = _side_B[7];
                _side_D[0] = _side_B[6];
                break;
            case rotation_side::SIDE_L:
                _side_B[2] = _side_L[0];
                _side_B[5] = _side_L[3];
                _side_B[8] = _side_L[6];
                
                _side_F[0] = _side_L[2];
                _side_F[3] = _side_L[5];
                _side_F[6] = _side_L[8];

                _side_U[0] = _side_L[0];
                _side_U[3] = _side_L[1];
                _side_U[6] = _side_L[2];

                _side_D[2] = _side_L[6];
                _side_D[5] = _side_L[7];
                _side_D[8] = _side_L[8];
                break;
            case rotation_side::SIDE_R:
                _side_B[0] = _side_R[2];
                _side_B[3] = _side_R[5];
                _side_B[6] = _side_R[8];
                
                _side_F[2] = _side_R[0];
                _side_F[5] = _side_R[3];
                _side_F[8] = _side_R[6];

                _side_U[2] = _side_R[2];
                _side_U[5] = _side_R[1];
                _side_U[8] = _side_R[0];

                _side_D[0] = _side_R[8];
                _side_D[3] = _side_R[7];
                _side_D[6] = _side_R[6];
                break;
            case rotation_side::SIDE_U:
                _side_B[0] = _side_U[2];
                _side_B[1] = _side_U[1];
                _side_B[2] = _side_U[0];
                
                _side_F[0] = _side_U[6];
                _side_F[1] = _side_U[7];
                _side_F[2] = _side_U[8];

                _side_L[0] = _side_U[0];
                _side_L[1] = _side_U[3];
                _side_L[2] = _side_U[6];

                _side_R[0] = _side_U[8];
                _side_R[1] = _side_U[5];
                _side_R[2] = _side_U[2];
                break;
            case rotation_side::SIDE_D:
                _side_B[6] = _side_D[0];
                _side_B[7] = _side_D[1];
                _side_B[8] = _side_D[2];
                
                _side_F[6] = _side_D[8];
                _side_F[7] = _side_D[7];
                _side_F[8] = _side_D[6];

                _side_L[6] = _side_D[2];
                _side_L[7] = _side_D[5];
                _side_L[8] = _side_D[8];

                _side_R[6] = _side_D[6];
                _side_R[7] = _side_D[3];
                _side_R[8] = _side_D[0];
                break;
        }
        
        _cur_rot_amount = 0.0f;
        _rot_queue.pop_front();
    }
}

glm::mat4 Scene::get_camera_transform() const
{
    return _camera->get_transform();
}

std::vector<glm::mat4> Scene::get_cubes_transform() const
{
    std::vector<glm::mat4> result;
    for(const auto &i : _cubes) {
        result.push_back(i.get_transform());
    }

    return result;
}
