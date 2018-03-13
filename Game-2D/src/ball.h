#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float radius, float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    float radius;
    float initialy;
    void set_position(float x, float y);
    void tick();
    double speed;
    double speedy;
    double acclr;
    int play;
    int inwater;
    int jmp;
    int life;
    int score;
    int colour;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
