#include "../../dependencies/glm/ext/matrix_transform.hpp"
#include "../../dependencies/glm/gtx/rotate_vector.hpp"
#include "cube.h"

Cube::Cube(glm::vec3 position) : _position{position} {}

void Cube::add_rotation(float angle, glm::vec3 axis)
{
    _current_rotation = glm::rotate(glm::mat4(1.0f), angle, axis) * _current_rotation;
}

glm::mat4 Cube::get_transform() const
{
    return _current_rotation * glm::translate(glm::mat4(1.0f), _position);
}
