#include "main.h"

#ifndef PARAREC_H
#define PARAREC_H


class Pararec {
public:
    Pararec() {}
    Pararec(float x, float y, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    float r;
    //float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
