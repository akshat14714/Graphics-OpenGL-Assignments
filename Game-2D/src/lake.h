#include "main.h"

#ifndef LAKE_H
#define LAKE_H


class Lake {
public:
    Lake() {}
    Lake(float radius, float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    float radius;
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // LAKE_H
