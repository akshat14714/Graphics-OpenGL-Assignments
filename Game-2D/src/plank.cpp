#include "plank.h"
#include "main.h"

Plank::Plank(float x, float y, float radius, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0.0;
    this->radius = radius;
    speed = 0.01;

    int k=0;

    double ang = (double)M_PI / 180;

    static GLfloat vertex_buffer_data[360*9+18];

    for(int i=0;i<360;i++)
    {
      vertex_buffer_data[i*9] = 0.0f;
      vertex_buffer_data[i*9+1] = 0.0f;
      vertex_buffer_data[i*9+2] = 0.0f;
      vertex_buffer_data[i*9+3] = radius * (float)cos(i * 1 * ang);
      vertex_buffer_data[i*9+4] = radius * (float)sin(i * 1 * ang);
      vertex_buffer_data[i*9+5] = 0.0f;
      vertex_buffer_data[i*9+6] = radius * (float)cos((i+1) * 1 * ang);
      vertex_buffer_data[i*9+7] = radius * (float)sin((i+1) * 1 * ang);
      vertex_buffer_data[i*9+8] = 0.0f;
      k = i*9+9;
    }

    vertex_buffer_data[k++]=(-radius*sqrt(2)-0.1/sqrt(2));
    vertex_buffer_data[k++]=0.1/sqrt(2);
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=-0.1/sqrt(2);
    vertex_buffer_data[k++]=(radius*sqrt(2)+0.1/sqrt(2));
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=0;
    vertex_buffer_data[k++]=radius*sqrt(2);
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=0;
    vertex_buffer_data[k++]=radius*sqrt(2);
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=-radius*sqrt(2);
    vertex_buffer_data[k++]=0;
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=(-radius*sqrt(2)-0.1/sqrt(2));
    vertex_buffer_data[k++]=0.1/sqrt(2);
    vertex_buffer_data[k++]=0.0f;

    this->object = create3DObject(GL_TRIANGLES, 360*3+6, vertex_buffer_data, color, GL_FILL);
}

void Plank::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Plank::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plank::tick() {
    this->position.x -= speed;
    if (this->position.x > 10) {
      float x = -25 + rand() % 20;
      float y = rand() % 5 - 1;
      this->set_position(x, y);
    }
    // this->position.y -= speedy;
}

bounding_box_t Plank::bounding_box() {
    float radius = this->radius;
    // float width = this->width;
    float x = this->position.x;
    float y = this->position.y;
    bounding_box_t bbox = { x, y, radius, 0.4, 0.4};
    return bbox;
}
