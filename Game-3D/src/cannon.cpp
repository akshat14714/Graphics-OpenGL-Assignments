#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speedx = 0.0;
    this->speedy = 0.0;
    this->speedz = 0.0;
    this->acclr = 0.006;
    this->initialy = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[] = {
      -0.5f, 0.0f, 0.5f,
      -0.5f, 6.0f, 0.5f,
      0.5f, 0.0f, 0.5f,
      0.5f, 6.0f, 0.5f,
      -0.5f, 6.0f, 0.5f,
      0.5f, 0.0f, 0.5f,

      -0.5f, 0.0f, -0.5f,
      -0.5f, 6.0f, -0.5f,
      0.5f, 0.0f, -0.5f,
      0.5f, 6.0f, -0.5f,
      -0.5f, 6.0f, -0.5f,
      0.5f, 0.0f, -0.5f,

      0.5f, 0.0f, 0.5f,
      0.5f, 0.0f, -0.5f,
      0.5f, 6.0f, -0.5f,
      0.5f, 0.0f, 0.5f,
      0.5f, 6.0f, 0.5f,
      0.5f, 6.0f, -0.5f,

      -0.5f, 0.0f, 0.5f,
      -0.5f, 0.0f, -0.5f,
      -0.5f, 6.0f, -0.5f,
      -0.5f, 0.0f, 0.5f,
      -0.5f, 6.0f, 0.5f,
      -0.5f, 6.0f, -0.5f,

      -0.5f, 6.0f, 0.5f,
      0.5f, 6.0f, 0.5f,
      0.5f, 6.0f, -0.5f,
      -0.5f, 6.0f, 0.5f,
      -0.5f, 6.0f, -0.5f,
      0.5f, 6.0f, -0.5f,

      -0.5f, 0.0f, 0.5f,
      0.5f, 0.0f, 0.5f,
      0.5f, 0.0f, -0.5f,
      -0.5f, 0.0f, 0.5f,
      -0.5f, 0.0f, -0.5f,
      0.5f, 0.0f, -0.5f,
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {
  this->position.y += speedy;
  this->position.x += this->speedx;
  if (this->position.y > this->initialy) {
    this->speedy -= acclr;
  }
  else {
    this->speedy = 0;
    this->position.y = this->initialy;
  }
}
