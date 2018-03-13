#include "water.h"
#include "main.h"

Water::Water(float x, float y, color_t color) {
    this->position = glm::vec3(x, y+0.5, 0);
    this->rotation = 0;
    this->speedy = 0.0;

    GLfloat vertex_buffer_data[] = {
      1000.0f, 0.0f, -1000.0f,
      -1000.0f, 0.0f, -1000.0f,
      -1000.0f, 0.0f, 1000.0f,

      -1000.0f, 0.0f, 1000.0f,
      1000.0f, 0.0f, 1000.0f,
      1000.0f, 0.0f, -1000.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Water::set_position(float x, float z) {
    this->position = glm::vec3(x, this->position.y, z);
}

void Water::tick() {
  this->position.y += speedy;
  if (this->position.y <= 0.0) {
    this->speedy += 0.001;
  }
  else if (this->position.y > 0.0) {
    this->speedy -= 0.001;
  }
}
