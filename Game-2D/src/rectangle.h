#include "main.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H


class Rectangle {
public:
    Rectangle() {}
    Rectangle(float x, float y, float length, float width, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    float length;
    float width;
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
