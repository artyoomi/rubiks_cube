#include "camera.h"
#include "../../dependencies/glm/ext/matrix_transform.hpp"


void Camera::look_at(glm::vec3 target)
{
    _target = target;

    // recalculate axes
    _direction = glm::normalize(_position - _target);
    _right     = glm::normalize(glm::cross(_world_up, _direction));
    _up        = glm::cross(_direction, _right);
}

void Camera::move(glm::vec3 position)
{
    _position = position;

    // recalculate axes
    _direction = glm::normalize(_position - _target);
    _right     = glm::normalize(glm::cross(_world_up, _direction));
    _up        = glm::cross(_direction, _right);
}

glm::vec3 Camera::get_position() const
{
    return _position;
}

glm::vec3 Camera::get_target() const
{
    return _target;
}

glm::mat4 Camera::get_transform() const
{    
    return glm::lookAt(_position, _target, _up);
}
