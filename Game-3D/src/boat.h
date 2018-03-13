#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    int health;
    int score;
    void draw(glm::mat4 VP);
    float speedy;
    float speed;
    float speedx;
    float acclr;
    float initialy;
    void set_position(float x, float y, float z);
    void tick();
    // double speed;
    bounding_box_t bounding_box();
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    // VAO *object;
};

#endif // BOAT_H
