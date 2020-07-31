#include "main.h"

#ifndef FLAG_H
#define FLAG_H


class Flag {
public:
    Flag() {}
    Flag(float x, float y, color_t color);
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
