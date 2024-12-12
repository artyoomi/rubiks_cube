#include "../../dependencies/glad/glad.h"
#include "cube_mesh.h"
#include <vector>

CubeMesh::CubeMesh(glm::vec3 size) {
    _make_mesh(size.x / 2.0, size.y / 2.0, size.z / 2.0);
}

CubeMesh::~CubeMesh() {
    glDeleteBuffers(1, &_VBO);
    glDeleteVertexArrays(1, &_VAO);
}

void CubeMesh::_make_mesh(float l, float w, float h)
{
    std::vector<float> vertices = {
      // x,  y,  z,   r,    g,    b, tex_x, tex_y
         l,  w, -h, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
         l, -w, -h, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -l, -w, -h, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -l, -w, -h, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -l,  w, -h, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         l,  w, -h, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,

        -l, -w,  h, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         l, -w,  h, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         l,  w,  h, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         l,  w,  h, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -l,  w,  h, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -l, -w,  h, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        -l,  w,  h, 1.0f, 0.4f, 0.0f, 1.0f, 1.0f,
        -l,  w, -h, 1.0f, 0.4f, 0.0f, 1.0f, 0.0f,
        -l, -w, -h, 1.0f, 0.4f, 0.0f, 0.0f, 0.0f,
        -l, -w, -h, 1.0f, 0.4f, 0.0f, 0.0f, 0.0f,
        -l, -w,  h, 1.0f, 0.4f, 0.0f, 0.0f, 1.0f,
        -l,  w,  h, 1.0f, 0.4f, 0.0f, 1.0f, 1.0f,

         l, -w, -h, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         l,  w, -h, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         l,  w,  h, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         l,  w,  h, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         l, -w,  h, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         l, -w, -h, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

        -l, -w, -h, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
         l, -w, -h, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         l, -w,  h, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  
         l, -w,  h, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -l, -w,  h, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -l, -w, -h, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

         l,  w,  h, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
         l,  w, -h, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -l,  w, -h, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 
        -l,  w, -h, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -l,  w,  h, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
         l,  w,  h, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    };

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void*)0);
    glEnableVertexAttribArray(0);

    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, (void*)12);
    glEnableVertexAttribArray(1);

    // texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, (void*)24);
    glEnableVertexAttribArray(2);
}

void CubeMesh::draw()
{
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
