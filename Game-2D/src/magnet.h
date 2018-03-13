#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, int k, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    float radius;
    float initialy;
    int k;
    void set_position(float x, float y);
    void tick();
    double speed;
    double speedy;
    double acclr;
    int play;
    int inwater;
    int jmp;
    int zinda;
    int vis;
    int start;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // MAGNET_H
