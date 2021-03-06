#include "slope.h"
#include "main.h"

Slope::Slope(float x, float y, float length, float width, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 30.0;
    this->length = length;
    this->width = width;
    speed = 0.01;

    static GLfloat vertex_buffer_data[] = {
          -1 * length/2.0, 0, 0, // vertex 1
          length/2.0, -1 * width, 0, // vertex 2
          length/2.0, 0, 0, // vertex 3

          -1 * length/2.0, 0, 0, // vertex 3
          -1 * length/2.0, -1 * width, 0, // vertex 4
          length/2.0, -1 * width, 0, // vertex 1
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Slope::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Slope::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Slope::tick() {
    this->position.x -= speed;
    // this->position.y -= speedy;
}

bounding_box_t Slope::bounding_box() {
    float length = this->length;
    float width = this->width;
    float x = this->position.x;
    float y = this->position.y;
    bounding_box_t bbox = { x, y, length, width };
    return bbox;
}
