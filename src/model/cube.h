#pragma once
#include "../../dependencies/glm/glm.hpp"

class Cube
{
public:
    Cube(glm::vec3 position);
    void add_rotation(float angle, glm::vec3 axis);


    glm::mat4 get_transform() const;
private:
    glm::vec3 _position = {0.0f, 0.0f, 0.0f};
    glm::mat4 _current_rotation = glm::mat4(1.0f);
};
