#include "coin.h"
#include "main.h"

Coin::Coin(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    double ang = (double)M_PI / 180;

    static GLfloat vertex_buffer_data[360*9];

    for(int i=0;i<360;i++)
    {
      vertex_buffer_data[i*9] = 0.0f;
      vertex_buffer_data[i*9+1] = 0.0f;
      vertex_buffer_data[i*9+2] = 0.0f;
      vertex_buffer_data[i*9+3] = 4.0 * (float)cos(i * 1 * ang);
      vertex_buffer_data[i*9+4] = 4.0 * (float)sin(i * 1 * ang);
      vertex_buffer_data[i*9+5] = 0.0f;
      vertex_buffer_data[i*9+6] = 4.0 * (float)cos((i+1) * 1 * ang);
      vertex_buffer_data[i*9+7] = 4.0 * (float)sin((i+1) * 1 * ang);
      vertex_buffer_data[i*9+8] = 0.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coin::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Coin::tick() {
    this->rotation += this->speed;
}

bounding_box_t Coin::bounding_box() {
    float x = this->position.x;
    float y = this->position.y;
    float z = this->position.z;

    bounding_box_t bbox = {x, y, z, 0.0, 0.0, 0.0};

    return bbox;
}
