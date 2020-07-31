#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, color_t color);
    glm::vec3 position;
    glm::mat4 rotate;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    float rot_x;
    float rot_y;
    float rot_z;
    //float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
