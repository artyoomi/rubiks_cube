#pragma once
#include "../../dependencies/glm/glm.hpp"

class Camera {
public:
    void look_at(glm::vec3 target);  // set new camera target
    void move(glm::vec3 position);   // set new camera position

    glm::vec3 get_position() const;
    glm::vec3 get_target()   const;

    glm::mat4 get_transform() const; // get the transformation matrix
    
private:
    glm::vec3 _world_up  = {0.0f, 0.0f, 1.0f}; // this specifies the camera roll angle
    glm::vec3 _position  = {10.0f, 10.0f, 10.0f}; // the camera position itself
    glm::vec3 _target    = {0.0f, 0.0f, 0.0f}; // the camera pointing at

    // the next 3 vectors form the coordinate system with the camera at it's origin
    glm::vec3 _direction = glm::normalize(_position - _target); // vector from the camera to the target
    glm::vec3 _right     = glm::normalize(glm::cross(_world_up, _direction));
    glm::vec3 _up        = glm::cross(_direction, _right);
};
