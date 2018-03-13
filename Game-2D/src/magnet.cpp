#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, int k, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    this->zinda = 0;
    this->start = 600;
    this->vis = 300;

    static GLfloat vertex_buffer_data[] = {
      -1*k, 3.5, 0,
      -1.5*k, 3.5, 0,
      -1*k, 3.75, 0,

      -1*k, 3.75, 0,
      -1.5*k, 3.75, 0,
      -1.5*k, 3.5, 0,

      -1.5*k, 3.75, 0,
      -1.5*k, 3.5, 0,
      -1.75*k, 4, 0,

      -2*k, 4, 0,
      -1.75*k, 4, 0,
      -1.5*k, 3.5, 0,

      -2*k, 4, 0,
      -1.75*k, 4, 0,
      -1.75*k, 4.5, 0,

      -2*k, 4, 0,
      -2*k, 4.5, 0,
      -1.75*k, 4.5, 0,

      -1.75*k, 4.5, 0,
      -2*k, 4.5, 0,
      -1.5*k, 4.75, 0,

      -2*k, 4.5, 0,
      -1.5*k, 5, 0,
      -1.5*k, 4.75, 0,

      -1*k, 5, 0,
      -1.5*k, 5, 0,
      -1.5*k, 4.75, 0,

      -1*k, 5, 0,
      -1.5*k, 4.75, 0,
      -1*k, 4.75, 0,
    };

    // for(int i=0;i<360;i++)
    // {
    //   vertex_buffer_data[i*9] = 0.0f;
    //   vertex_buffer_data[i*9+1] = 0.0f;
    //   vertex_buffer_data[i*9+2] = 0.0f;
    //   vertex_buffer_data[i*9+3] = radius * (float)cos(i * 1 * ang);
    //   vertex_buffer_data[i*9+4] = radius * (float)sin(i * 1 * ang);
    //   vertex_buffer_data[i*9+5] = 0.0f;
    //   vertex_buffer_data[i*9+6] = radius * (float)cos((i+1) * 1 * ang);
    //   vertex_buffer_data[i*9+7] = radius * (float)sin((i+1) * 1 * ang);
    //   vertex_buffer_data[i*9+8] = 0.0f;
    // }

    this->object = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

// void Magnet::tick() {
//     this->position.x -= speed;
//     if (this->position.x > 10) {
//       float x = -25 + rand() % 20;
//       float y = rand() % 5 - 1;
//       this->set_position(x, y);
//     }
//     if(this->play == 1) {
//       this->position.y += speedy;
//       if (this->position.x<(3.3) && this->position.x>(0.7) && this->position.y<=-1.7) {
//           this->position.y = -1 * sqrt(1.3*1.3 - (2 - this->position.x)*(2 - this->position.x)) - 1.7;
//           this->inwater = 1;
//           if (this->position.x==3.3-this->radius && this->position.x==0.7+this->radius) {
//             this->position.y += this->radius;
//           }
//           if (this->jmp==1) {
//             this->speedy -= 1.5 * acclr;
//           }
//       }
//       else {
//         this->inwater = 0;
//       }
//       if (this->inwater==0) {
//         if(this->position.y > this->initialy) {
//           this->speedy -= acclr;
//         }
//         else {
//           this->position.y = this->initialy;
//           this->speedy = 0;
//           this->jmp = 0;
//         }
//       }
//     }
// }

// bounding_box_t Magnet::bounding_box() {
//     float r = this->radius;
//     float x = this->position.x, y = this->position.y;
//     bounding_box_t bbox = { r, x, y, 0.4, 0.4 };
//     return bbox;
// }
