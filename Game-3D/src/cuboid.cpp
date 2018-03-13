#include "cuboid.h"
#include "main.h"

Cuboid::Cuboid(float x, float y, float z, float length, float width, float height, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->bomb = 0;
    this->speedx = 0;
    this->speedz = 0;
    this->speedy = 0;
    this->acclr = 0;
    this->fire = 0;
    this->length = length;
    this->width = width;
    this->height = height;
    // speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
      -length/2, -width/2, -height/2,
      -length/2, -width/2, height/2,
      length/2, -width/2, -height/2,
      -length/2, -width/2, height/2,
      length/2, -width/2, height/2,
      length/2, -width/2, -height/2,

      -length/2, width/2, -height/2,
      -length/2, width/2, height/2,
      length/2, width/2, -height/2,
      -length/2, width/2, height/2,
      length/2, width/2, height/2,
      length/2, width/2, -height/2,

      length/2, -width/2, height/2,
      length/2, width/2, height/2,
      length/2, -width/2, -height/2,
      length/2, -width/2, -height/2,
      length/2, width/2, -height/2,
      length/2, width/2, height/2,

      -length/2, -width/2, height/2,
      -length/2, width/2, height/2,
      -length/2, -width/2, -height/2,
      -length/2, -width/2, -height/2,
      -length/2, width/2, -height/2,
      -length/2, width/2, height/2,

      -length/2, -width/2, height/2,
      -length/2, width/2, height/2,
      length/2, width/2, height/2,
      length/2, width/2, height/2,
      length/2, -width/2, height/2,
      -length/2, -width/2, height/2,

      -length/2, -width/2, -height/2,
      -length/2, width/2, -height/2,
      length/2, width/2, -height/2,
      length/2, width/2, -height/2,
      length/2, -width/2, -height/2,
      -length/2, -width/2, -height/2,
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Cuboid::draw(glm::mat4 VP) {
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

void Cuboid::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cuboid::tick() {
    if (this->bomb == 1) {
      // this->speedx = sin(this->rotation * M_PI / 180.0f);
      // this->speedz = cos(this->rotation * M_PI / 180.0f);
      if (this->fire == 1) {
        this->acclr = 0.008;
        this->position.y += speedy;
        if (this->position.y > 1) {
          this->speedy -= acclr;
        }
        this->position.z -= this->speedz;
        this->position.x -= this->speedx;
      }
      else {
        this->acclr = 0.006;
        this->position.y += speedy;
        if (this->position.y > 1) {
          this->speedy -= acclr;
        }
      }
    }
}

bounding_box_t Cuboid::bounding_box() {
    float x = this->position.x;
    float y = this->position.y;
    float z = this->position.z;
    float length = this->length;
    float width = this->width;
    float height = this->height;

    bounding_box_t bbox = {x, y, z, length, width, height};

    return bbox;
}
