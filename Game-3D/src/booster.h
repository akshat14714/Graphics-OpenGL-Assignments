#include "main.h"

#ifndef BOOSTER_H
#define BOOSTER_H


class Booster {
public:
    Booster() {}
    Booster(float x, float y, float z, float length, float width, float height, color_t color);
    glm::vec3 position;
    float rotation;
    float length;
    float width;
    float height;
    int consumed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BOOSTER_H
