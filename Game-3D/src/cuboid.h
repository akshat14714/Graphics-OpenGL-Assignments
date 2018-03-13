#include "main.h"

#ifndef CUBOID_H
#define CUBOID_H


class Cuboid {
public:
    Cuboid() {}
    Cuboid(float x, float y, float z, float length, float width, float height, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    float speedy;
    float speedz;
    float speedx;
    float length;
    float width;
    float height;
    int fire;
    void set_position(float x, float y, float z);
    void tick();
    float initialy;
    double acclr;
    int bomb;
    // double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // CUBOID_H
