//#define GLM_ENABLE_EXPERIMENTAL
#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    //this->rotation = 0;
    this->rotation_y = 0;
    this->rotation_x = 0;
    this->rotation_z = 0;
    this->rot_x=0;
    this->rot_y=0;
    this->rot_z=0;
    glm::mat4 rotate;
    speed = 1;
    static const GLfloat vertex_buffer_data[] = {
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
        /*-1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
         1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f*/
         -0.25f,0.25f,-1.5f,
          0.25f,0.25f,-1.5f,
         -0.25f,-0.25f,-1.5f,
          0.25f,0.25f,-1.5f,
         -0.25f,-0.25f,-1.5f,
          0.25f,-0.25f,-1.5f,

         -0.4f,0.25f,1.5f,
          0.4f,0.25f,1.5f,
         -0.4f,-0.25f,1.5f,
          0.4f,0.25f,1.5f,
         -0.4f,-0.25f,1.5f,
          0.4f,-0.25f,1.5f,

         -0.25f,0.25f,-1.5f,
          0.25f,0.25f,-1.5f,
         -0.4f,0.25f,1.5f,
         -0.4f,0.25f,1.5f,
          0.4f,0.25f,1.5f,
          0.25f,0.25f,-1.5f,

          -0.25f,0.25f,-1.5f,
          -0.25f,-0.25f,-1.5f,
          -0.4f,0.25f,1.5f,
          -0.4f,0.25f,1.5f,
          -0.4f,-0.25f,1.5f,
          -0.25f,-0.25f,-1.5f,

          -0.25f,-0.25f,-1.5f,
           0.25f,-0.25f,-1.5f,
          -0.4f,-0.25f,1.5f,
          -0.4f,-0.25f,1.5f,
           0.4f,-0.25f,1.5f,
           0.25f,-0.25f,-1.5f,

           0.25f,0.25f,-1.5f,
           0.25f,-0.25f,-1.5f,
           0.4f,0.25f,1.5f,
           0.4f,0.25f,1.5f,
           0.4f,-0.25f,1.5f,
           0.25f,-0.25f,-1.5f,

           -0.25f,-0.25f,-1.2f,
           -0.95f,-0.25f,-1.2f,
           -0.25f,0.25f,-1.2f,
          
            0.25f,0.25f,-1.2f,
            0.25f,-0.25f,-1.2f,
            0.95f,-0.25f,-1.2f,

            -0.3f,0.25f,1.2f,
            -0.3f,-0.25f,1.2f,
            -0.8f,-0.25f,1.2f,

            0.3f,0.25f,1.2f,
            0.3f,-0.25f,1.2f,
            0.8f,-0.25f,1.2f,

    };
    this->object = create3DObject(GL_TRIANGLES, 16*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_z    = glm::rotate((float) (this->rotation_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate_x    = glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));

      
    rotate    *= rotate_z*rotate_x*rotate_y;
    this->rot_x+=this->rotation_x;
    this->rot_y+=this->rotation_y;
    this->rot_z+=this->rotation_z;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

    this->rotation_y = 0;
    this->rotation_x = 0;
    this->rotation_z = 0;
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

