#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 1;
    this->speedx = 0;
    this->speedy = 0;
    this->acclr = 0.006;
    this->initialy = 1;
    this->score = 0;
    this->health = 100;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data_1[] = {
        // Front
        -2.0f, 0.0f, 4.0f,
        2.0f, 0.0f, 4.0f,
        -3.0f, 2.0f, 4.0f,

        2.0f, 0.0f, 4.0f,
        3.0f, 2.0f, 4.0f,
        -3.0f, 2.0f, 4.0f,

        // Back
        -2.0f, 0.0f, -4.0f,
        2.0f, 0.0f, -4.0f,
        -3.0f, 2.0f, -4.0f,

        2.0f, 0.0f, -4.0f,
        3.0f, 2.0f, -4.0f,
        -3.0f, 2.0f, -4.0f,

        // Left
        -2.0f, 0.0f, 4.0f,
        -2.0f, 0.0f, -4.0f,
        -3.0f, 2.0f, -4.0f,

        -2.0f, 0.0f, 4.0f,
        -3.0f, 2.0f, 4.0f,
        -3.0f, 2.0f, -4.0f,

        // Right
        2.0f, 0.0f, 4.0f,
        2.0f, 0.0f, -4.0f,
        3.0f, 2.0f, -4.0f,

        2.0f, 0.0f, 4.0f,
        3.0f, 2.0f, 4.0f,
        3.0f, 2.0f, -4.0f,
    };

    static GLfloat vertex_buffer_data_2[] = {
        // Bottom
        -2.0f, 0.0f, 4.0f,
        2.0f, 0.0f, 4.0f,
        2.0f, 0.0f, -4.0f,

        -2.0f, 0.0f, 4.0f,
        -2.0f, 0.0f, -4.0f,
        2.0f, 0.0f, -4.0f,
    };

    static GLfloat vertex_buffer_data_3[] = {
        // Mast
        0.0f, 0.0f, 0.0f,
        0.2f, 0.0f, 0.0f,
        0.0f, 15.0f, 0.0f,
        0.0f, 15.0f, 0.0f,
        0.2f, 15.0f, 0.0f,
        0.2f, 0.0f, 0.0f,

        0.2f, 12.0f, 0.0f,
        6.0f, 10.0f, 0.0f,
        0.2f, 15.0f, 0.0f
    };

    // static GLfloat vertex_buffer_data_4[] = {
    //     // Cannon
    //     -0.5f, 1.5f, -4.0f,
    //     -0.5f, 0.5f, -4.0f,
    //     0.5f, 0.5f, -4.0f,
    //     -0.5f, 1.5f, -4.0f,
    //     0.5f, 1.5f, -4.0f,
    //     0.5f, 0.5f, -4.0f,
    //
    //     -0.5f, 1.5f, -8.0f,
    //     -0.5f, 0.5f, -8.0f,
    //     0.5f, 0.5f, -8.0f,
    //     -0.5f, 1.5f, -8.0f,
    //     0.5f, 1.5f, -8.0f,
    //     0.5f, 0.5f, -8.0f,
    //
    //     0.5f, 1.5f, -4.0f,
    //     0.5f, 0.5f, -4.0f,
    //     0.5f, 0.5f, -8.0f,
    //     0.5f, 1.5f, -4.0f,
    //     0.5f, 1.5f, -8.0f,
    //     0.5f, 0.5f, -8.0f,
    //
    //     -0.5f, 1.5f, -4.0f,
    //     -0.5f, 0.5f, -4.0f,
    //     -0.5f, 0.5f, -8.0f,
    //     -0.5f, 1.5f, -4.0f,
    //     -0.5f, 1.5f, -8.0f,
    //     -0.5f, 0.5f, -8.0f,
    //
    //     -0.5f, 1.5f, -4.0f,
    //     0.5f, 1.5f, -4.0f,
    //     0.5f, 1.5f, -8.0f,
    //     -0.5f, 1.5f, -4.0f,
    //     -0.5f, 1.5f, -8.0f,
    //     0.5f, 1.5f, -8.0f,
    //
    //     -0.5f, 0.5f, -4.0f,
    //     0.5f, 0.5f, -4.0f,
    //     0.5f, 0.5f, -8.0f,
    //     -0.5f, 0.5f, -4.0f,
    //     -0.5f, 0.5f, -8.0f,
    //     0.5f, 0.5f, -8.0f
    // };

    this->object1 = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data_1, COLOR_BROWN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2, COLOR_GR, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data_3, COLOR_PLAY, GL_FILL);
    // this->object4 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_4, COLOR_MAG, GL_FILL);
    // this->object = create3DObject(GL_TRIANGLES, 13*3, vertex_buffer_data, color, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(3.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    // draw3DObject(this->object4);
    // draw3DObject(this->object);
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
    this->position.y += speedy;
    this->position.x += speedx;
    if (this->position.y > this->initialy) {
      this->speedy -= acclr;
    }
    else {
      this->speedy = 0;
      this->position.y = this->initialy;
    }
}

bounding_box_t Boat::bounding_box() {
  float x = this->position.x;
  float y = this->position.y;
  float z = this->position.z;
  bounding_box_t bbox = {x, y, z, 16, 8, 3};
  return bbox;
}
