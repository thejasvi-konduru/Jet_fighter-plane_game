#include "main.h"

#ifndef HILL_H
#define HILL_H


class Hill {
public:
    Hill() {}
    Hill(float x, float y, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    //float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
