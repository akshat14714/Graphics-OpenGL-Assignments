#include "monster.h"
#include "main.h"
#include "cuboid.h"

Monster::Monster(float x, float y, float z, float length, float height, float width, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->length = length;
    this->height = height;
    this->width = width;
    this->speed = 0;
    this->isDead = 0;
    this->shots = 0;
    this->boss = 0;
    // speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data_1[] = {
      -length/2, -height/2, -width/2,
      -length/2, -height/2, width/2,
      length/2, -height/2, -width/2,
      -length/2, -height/2, width/2,
      length/2, -height/2, width/2,
      length/2, -height/2, -width/2,

      -length/2, height/2, -width/2,
      -length/2, height/2, width/2,
      length/2, height/2, -width/2,
      -length/2, height/2, width/2,
      length/2, height/2, width/2,
      length/2, height/2, -width/2,

      length/2, -height/2, width/2,
      length/2, height/2, width/2,
      length/2, -height/2, -width/2,
      length/2, -height/2, -width/2,
      length/2, height/2, -width/2,
      length/2, height/2, width/2,

      -length/2, -height/2, width/2,
      -length/2, height/2, width/2,
      -length/2, -height/2, -width/2,
      -length/2, -height/2, -width/2,
      -length/2, height/2, -width/2,
      -length/2, height/2, width/2,

      -length/2, -height/2, width/2,
      -length/2, height/2, width/2,
      length/2, height/2, width/2,
      length/2, height/2, width/2,
      length/2, -height/2, width/2,
      -length/2, -height/2, width/2,

      -length/2, -height/2, -width/2,
      -length/2, height/2, -width/2,
      length/2, height/2, -width/2,
      length/2, height/2, -width/2,
      length/2, -height/2, -width/2,
      -length/2, -height/2, -width/2,
    };

    static GLfloat vertex_buffer_data_2[] = {
      -length/4, -height, width/4,
      -length/4, -height/2, width/4,
      length/4, -height, width/4,
      -length/4, -height/2, width/4,
      length/4, -height/2, width/4,
      length/4, -height, width/4,

      -length/4, -height, -width/4,
      -length/4, -height/2, -width/4,
      length/4, -height, -width/4,
      -length/4, -height/2, -width/4,
      length/4, -height/2, -width/4,
      length/4, -height, -width/4,

      length/4, -height, width/4,
      length/4, -height/2, width/4,
      length/4, -height/2, -width/4,
      length/4, -height/2, -width/4,
      length/4, -height, -width/4,
      length/4, -height/2, -width/4,

      -length/4, -height, width/4,
      -length/4, -height/2, width/4,
      -length/4, -height/2, -width/4,
      -length/4, -height/2, -width/4,
      -length/4, -height, -width/4,
      -length/4, -height/2, -width/4,

      -length/4, -height/2, width/4,
      -length/4, -height/2, -width/4,
      length/4, -height/2, -width/4,
      length/4, -height/2, width/4,
      length/4, -height/2, -width/4,
      -length/4, -height/2, width/4,

      -length/4, -height, width/4,
      -length/4, -height, -width/4,
      length/4, -height, -width/4,
      length/4, -height, width/4,
      length/4, -height, -width/4,
      -length/4, -height, width/4,
    };

    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_2, color, GL_FILL);
}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Monster::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Monster::tick() {
    if (this->boss == 0) {
        this->speed = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 0.2;
        int k = -1 + rand() % 3;
        if (k == 1) {
          this->position.x += this->speed;
          this->position.z -= this->speed;
        }
        else {
          this->position.x -= this->speed;
          this->position.z += this->speed;
        }
    }
}

bounding_box_t Monster::bounding_box() {
  float x = this->position.x;
  float y = this->position.y;
  float z = this->position.z;
  float length = this->length;
  float width = this->width;
  float height = this->height;

  bounding_box_t bbox = {x, y, z, length, width, height};

  return bbox;
}
