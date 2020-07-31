//#define GLM_ENABLE_EXPERIMENTAL
#include "parachute.h"
#include "main.h"

Parachute::Parachute(float x, float y, color_t color,float r) {
    this->position = glm::vec3(x, y, 0);
    //this->rotation = 0;
    this->rotation_y = 0;
    this->rotation_x = 0;
    this->rotation_z = 0;
    //this->r=1.4;
    speed = 1;
    //static const GLfloat vertex_buffer_data[] = {
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
        int n=20;
        float th=(2*3.14)/(float)n;
        //float r = 1.4;
        GLfloat vertex_buffer_data[9*n+1];
        int j=0,i;
        int cur=0;
        for(i=0;i<9*n/2;i+=9)
        {
                vertex_buffer_data[i]=0.0f;
                vertex_buffer_data[i+1]=0.0f;
                vertex_buffer_data[i+2]=0.0f;
                vertex_buffer_data[i+3]=r*cos(th*cur);
                vertex_buffer_data[i+4]=r*sin(th*cur);
                vertex_buffer_data[i+5]=0.0f;
                vertex_buffer_data[i+6]=r*cos(th*(cur+1));
                vertex_buffer_data[i+7]=r*sin(th*(cur+1));
                vertex_buffer_data[i+8]=0.0f;
                cur++;
        }
    this->object = create3DObject(GL_TRIANGLES, n*3/2, vertex_buffer_data, color, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    //rotate    *= glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate    *= glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Parachute::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Parachute::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

