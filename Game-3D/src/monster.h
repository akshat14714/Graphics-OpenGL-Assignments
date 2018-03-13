#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H


class Monster {
public:
    Monster() {}
    Monster(float x, float y, float z, float length, float width, float height, color_t color);
    glm::vec3 position;
    float rotation;
    float length;
    float height;
    float width;
    int isDead;
    int shots;
    int boss;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object1;
    VAO *object2;
};

#endif // MONSTER_H
