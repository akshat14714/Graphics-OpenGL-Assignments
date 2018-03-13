#include "main.h"

#ifndef PLANK_H
#define PLANK_H

class Plank {
public:
    Plank() {}
    Plank(float x, float y, float radius, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    float radius;
    double speed;
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // PLANK_H
