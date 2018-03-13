#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    float initialy;
    float speedx;
    float speedy;
    float speedz;
    float acclr;
    // float initialy;
    void set_position(float x, float y, float z);
    void tick();
    // int color;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // CANNON_H
