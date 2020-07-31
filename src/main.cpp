//#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"
#include <iostream>
#include <sstream>
#include "timer.h"
#include "ball.h"
#include "ball.h"
#include "ground.h"
#include "hill.h"
#include "sea.h"
#include "flag.h"
#include "volcano.h"
#include "line.h"
#include "sea.h"
#include "bomb.h"
#include "drop.h"
#include "vertical.h"
#include "speed.h"
#include "line1.h"
#include "line2.h"
#include "rec.h"
#include "rec1.h"
#include "rec2.h"
#include "rec3.h"
#include "cannon.h"
#include "parachute.h"
#include "thread.h"
#include "pararec.h"
#include "arrow.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
Ball ball1;
int fluster;
int j=0,k=0;
int score=0;
int book;
float arr1[10000];
float arr2[1000];
int count=0;
int flag=0;
Ground ground1[100];
Cannon cannon1[1000];
Parachute parachute1[1000];
Speed speed1;
Hill hill1[100];
Flag flag1[100];
Sea sea1;
Thread thread1[1000];
Pararec pararec1[1000];
Rec rec1[1000];
Rec1 rec2[1000];
Rec2 rec3[1000];
Rec3 rec4[1000];
Line line1[100];
Volcano volc1[10];
Bomb bomb1[10000];
Drop drop1[1000];
Arrow arrow1[1000];
Line1 line11;
Line2 line22;
Vertical vertical1[1000];
float screen_zoom = 3.5, screen_center_x = 0, screen_center_y = 0;
float eye_x=5,eye_y=5,eye_z=10;
float target_x=0,target_y=0,target_z=0;
float camera_rotation_angle = 0;
float z=5;
float z1=0;
float x=0;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye(eye_x,eye_y,eye_z);  //tower view
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (target_x,target_y,target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    // Scene render
    ball1.draw(VP);
    for(int i=0;i<32;i++)
      ground1[i].draw(VP);
    for(int i=32;i<34;i++)
    {
      ground1[i].r=0.3;
      ground1[i].draw(VP);
    }
    for(int i=0;i<20;i++)
      hill1[i].draw(VP);
    for(int i=20;i<30;i++)
      hill1[i].draw(VP);
    for(int i=0;i<10;i++)
      flag1[i].draw(VP);
    volc1[0].draw(VP);
    volc1[1].draw(VP);
    for(int i=0;i<=5;i++)
        line1[i].draw(VP);
    sea1.draw(VP);
    for(int i=0;i<3;i++)
        bomb1[i].draw(VP);
    for(int i=0;i<10;i++)
        cannon1[i].draw(VP);
    if(fluster==2)
    {
        drop1[0].draw(VP);
        drop1[0].position.y-=0.02;
        vertical1[0].draw(VP);
        vertical1[0].position.y-=0.02;
        vertical1[1].draw(VP);
        vertical1[1].position.y-=0.02;
    }
    if(flag==5)
    {
        thread1[0].draw(VP);
        pararec1[0].draw(VP);
        parachute1[0].draw(VP);
        thread1[0].position.y-=0.02;
        pararec1[0].position.y-=0.02;
        parachute1[0].position.y-=0.02;
    }
    speed1.draw(VP);
    if(flag==3)
    {
        line22.draw(VP);
        line11.position.z-=0.3;
         line11.position.x=line11.position.x-0.1*tan((2*3.14*(ball1.rot_y))/180);
         if(ball1.rot_z!=0)
            line11.position.x=(line11.position.x-(line11.position.x/30)*cos(2*3.14*ball1.rot_z/180));
         line11.position.y=((line11.position.y+line11.position.x/300*sin((2*3.14*ball1.rot_z)/180)));
         line22.position.z-=0.3;
         line22.position.x=line22.position.x-0.1*tan((2*3.14*(ball1.rot_y))/180);
         if(ball1.rot_z!=0)
            line22.position.x=(line22.position.x-(line22.position.x/30)*cos(2*3.14*ball1.rot_z/180));
         line22.position.y=((line22.position.y+line22.position.x/300*sin((2*3.14*ball1.rot_z)/180)));
         speed1.position.z-=0.3;
         speed1.position.x=speed1.position.x-0.1*tan((2*3.14*(ball1.rot_y))/180);
         if(ball1.rot_z!=0)
            speed1.position.x=((speed1.position.x-(speed1.position.x/30)*cos(2*3.14*ball1.rot_z/180)));
         speed1.position.y=((speed1.position.y+speed1.position.x/300*sin((2*3.14*ball1.rot_z)/180)));
         rec1[0].position.z-=0.3;
         rec1[0].position.x=rec1[0].position.x-0.1*tan((2*3.14*(ball1.rot_y))/180);
         if(ball1.rot_z!=0)
            rec1[0].position.x=(rec1[0].position.x-(rec1[0].position.x/30)*cos(2*3.14*ball1.rot_z/180));
         rec1[0].position.y=((rec1[0].position.y+rec1[0].position.x/300*sin((2*3.14*ball1.rot_z)/180)));
         rec1[0].draw(VP);
         rec2[0].position.z-=0.3;
         rec2[0].position.x=rec2[0].position.x-0.1*tan((2*3.14*(ball1.rot_y))/180);
         if(ball1.rot_z!=0)
            rec2[0].position.x=(rec2[0].position.x-(rec2[0].position.x/30)*cos(2*3.14*ball1.rot_z/180));
         rec2[0].position.y=((rec2[0].position.y+rec2[0].position.x/300*sin((2*3.14*ball1.rot_z)/180)));
         rec2[0].draw(VP);
         rec3[0].position.z-=0.3;
         rec3[0].position.x=rec3[0].position.x-0.1*tan((2*3.14*(ball1.rot_y))/180);
         if(ball1.rot_z!=0)
            rec3[0].position.x=(rec3[0].position.x-(rec3[0].position.x/30)*cos(2*3.14*ball1.rot_z/180));
         rec4[0].position.z-=0.3;
         rec4[0].position.x=rec4[0].position.x-0.1*tan((2*3.14*(ball1.rot_y))/180);
         if(ball1.rot_z!=0)
            rec4[0].position.x=(rec4[0].position.x-(rec4[0].position.x/30)*cos(2*3.14*ball1.rot_z/180));
         rec4[0].position.y-=0.0001;
    }
    if(flag==0)
        line11.draw(VP);
    if(flag==10)
        line22.draw(VP);
    rec1[0].draw(VP);
    rec2[0].draw(VP);
    rec3[0].draw(VP);
    rec4[0].draw(VP);
    if(thread1[1].position.z>=-1000)
    {
            thread1[1].position.z=thread1[1].position.z-0.01;
            pararec1[1].position.z=pararec1[1].position.z-0.01;
            parachute1[1].position.z=parachute1[1].position.z-0.01;
            thread1[1].draw(VP);
            pararec1[1].draw(VP);
            parachute1[1].draw(VP);
            thread1[2].position.z=thread1[2].position.z-0.01;
            pararec1[2].position.z=pararec1[2].position.z-0.01;
            parachute1[2].position.z=parachute1[2].position.z-0.01;
            thread1[2].draw(VP);
            pararec1[2].draw(VP);
            parachute1[2].draw(VP);
    }
    for(int i=j;i<10;i++)
    {
        if((ball1.position.z<=flag1[i].position.z+1.4 &&ball1.position.z>=flag1[i].position.z-1.4)&&(ball1.position.x<=flag1[i].position.x+1.4&&ball1.position.x>=flag1[i].position.x-1.4))
        {
            arrow1[j+1].draw(VP);
            rec4[0].position.y=rec4[0].position.y+0.01;
            rec4[0].draw(VP);
            j=j+1;
            break;
        }
        else
        {
            arrow1[j].draw(VP);
        }
    }
    for(int i=k;i<10;i++)
    {
        if((vertical1[0].position.y<=cannon1[i].position.y+0.7 &&vertical1[0].position.y>=cannon1[i].position.y-0.7)&&(vertical1[0].position.x<=cannon1[i].position.x+1.4&&vertical1[0].position.x>=cannon1[i].position.x-1.4)&&(vertical1[0].position.z<=cannon1[i].position.z+1.4 &&vertical1[0].position.z>=cannon1[i].position.z-1.4))
        {
            cannon1[i].position.y=-500;
            k=k+1;
            break;
        }
        else
        {
            cannon1[k].draw(VP);
        }
    }
    if((ball1.position.z<=volc1[0].position.z+1.4 && ball1.position.z>=volc1[0].position.z-1.4 && ball1.position.x<=volc1[0].position.x+1.4 && ball1.position.x>=volc1[0].position.x-1.4 && ball1.position.y>=volc1[0].position.y-1.4 && ball1.position.y<=volc1[0].position.y+1.4)||(ball1.position.z<=volc1[1].position.z+1.4 && ball1.position.z>=volc1[1].position.z-1.4 && ball1.position.x<=volc1[1].position.x+1.4 && ball1.position.x>=volc1[1].position.x-1.4 && ball1.position.y<=volc1[1].position.y+1.4 && ball1.position.y>=volc1[1].position.y-1.4)||ball1.position.y<=-5||rec4[0].position.y<=-5)
    {
        quit(window);
    }
    if(ball1.position.x>=bomb1[0].position.x-1.4 && ball1.position.x<=bomb1[0].position.x+1.4 && ball1.position.z<=-200 && ball1.position.z >=-230)
    {
        rec4[0].position.y=rec4[0].position.y+0.001;
        rec4[0].draw(VP);
        if(score==100)
            score=600;
        else if(score==200)
            score==700;
        else if(score==0)
            score=500;
    }
    if(book==99)
    {
        cannon1[1].draw(VP);
        cannon1[1].position.z-=0.09;
    }
    if(cannon1[1].position.x>=pararec1[1].position.x-0.5 && cannon1[1].position.x<=pararec1[1].position.x+0.5 &&cannon1[1].position.y<=pararec1[1].position.y+0.5 &&cannon1[1].position.y>=pararec1[1].position.y-0.5&&cannon1[1].position.z>=pararec1[1].position.z-0.05&&cannon1[1].position.z<=pararec1[1].position.z+0.05)
    {
        parachute1[1].position.z=-500;
        pararec1[1].position.z=-500;
        thread1[1].position.z=-500;
        parachute1[1].draw(VP);
        pararec1[1].draw(VP);
        thread1[1].draw(VP);
        rec4[0].position.y=rec4[0].position.y+0.01;
        rec4[0].draw(VP);
        score=score+100;
    }
    if(cannon1[1].position.x>=pararec1[2].position.x-0.5 && cannon1[1].position.x<=pararec1[2].position.x+0.5 &&cannon1[1].position.y<=pararec1[2].position.y+0.5 &&cannon1[1].position.y>=pararec1[2].position.y-0.5&&cannon1[1].position.z>=pararec1[2].position.z-0.05&&cannon1[1].position.z<=pararec1[2].position.z+0.05)
    {
        parachute1[2].position.z=-500;
        pararec1[2].position.z=-500;
        thread1[2].position.z=-500;
        parachute1[2].draw(VP);
        pararec1[2].draw(VP);
        thread1[2].draw(VP);
        rec4[0].position.y=rec4[0].position.y+0.01;
        rec4[0].draw(VP);
        score=score+100;
    }
}
void tick_input(GLFWwindow *window) {
    int tilt_left  = glfwGetKey(window, GLFW_KEY_A);
    int tilt_right = glfwGetKey(window, GLFW_KEY_D);
    int up    = glfwGetKey(window, GLFW_KEY_SPACE);
    int dow  = glfwGetKey(window, GLFW_KEY_DOWN);
    int front = glfwGetKey(window, GLFW_KEY_F);
    int rotate_left=glfwGetKey(window,GLFW_KEY_S);
    int rotate_right=glfwGetKey(window,GLFW_KEY_E);
    int plane_view=glfwGetKey(window,GLFW_KEY_P);
    int top_view=glfwGetKey(window,GLFW_KEY_T);
    int tower_view=glfwGetKey(window,GLFW_KEY_W);
    //int helicopter_view=glfwGetKey(window,GLFW_KEY_P);
    int bom=glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_1);
    int missile=glfwGetKey(window,GLFW_KEY_M);
    int parach=glfwGetKey(window,GLFW_KEY_V);
    if (tilt_left) {
        ball1.rotation_z+=1;
    }
   if (tilt_right) {
        ball1.rotation_z-=1;
    }
    if(rotate_left) {
        ball1.rotation_y+=1;
    }
    if(rotate_right){
        ball1.rotation_y-=1;
    }
    if (up) {
        flag=10;
        line11.position.y+=0.1;
        line22.position.y+=0.1;
        speed1.position.y+=0.1;
        rec1[0].position.y+=0.1;
        rec2[0].position.y+=0.1;
        rec3[0].position.y+=0.1+ball1.position.y/30000;
        ball1.position.y+=0.1;
        rec4[0].position.y+=0.1-ball1.position.y/300000;
        for(int i=0;i<10;i++)
            cannon1[i].rotation_x-=1;
    }
    if (dow) {
        flag=10;
        line11.position.y-=0.1;
        line22.position.y-=0.1;
        speed1.position.y-=0.1;
        rec1[0].position.y-=0.1;
        rec2[0].position.y-=0.1;
        rec3[0].position.y-=0.1+ball1.position.y/30000;
        ball1.position.y-=0.1;
        rec4[0].position.y-=0.1+ball1.position.y/300000;
        for(int i=0;i<10;i++)
            cannon1[i].rotation_x+=1;
        
    }
    if(front) {
         for(int i=0;i<10;i++)
            cannon1[i].rotation_y+=1;
         flag=3;
         ball1.position.z-=0.3;
         ball1.position.x=ball1.position.x-0.1*tan((2*3.14*(ball1.rot_y))/180);
         if(ball1.rot_z!=0)
            ball1.position.x=(ball1.position.x-(ball1.position.x/30)*cos(2*3.14*ball1.rot_z/180));
         ball1.position.y=((ball1.position.y+ball1.position.x/300*sin((2*3.14*ball1.rot_z)/180)));
    }
    if(!front && !up && !dow)
        flag=0;
    if(bom==GLFW_PRESS){
        fluster=2;
        drop1[0]=Drop(ball1.position.x,ball1.position.y-0.3,COLOR_DARKRED,0.5);
        vertical1[0]=Vertical(ball1.position.x,ball1.position.y-0.3,COLOR_DARKRED,0.5);
        vertical1[0].position.z=ball1.position.z;
        vertical1[1]=Vertical(ball1.position.x,ball1.position.y-0.3,COLOR_DARKRED,0.5);
        vertical1[1].position.z=ball1.position.z-1;
        drop1[0].position.z=ball1.position.z;
    }
     if(parach==GLFW_PRESS)
     {
        flag=5;
        thread1[0]=Thread(ball1.position.x,ball1.position.y-1.3,COLOR_BLACK);
        parachute1[0]=Parachute(ball1.position.x,ball1.position.y-1.3,COLOR_YELLOW,1);
        pararec1[0]=Pararec(ball1.position.x,ball1.position.y-3.3,COLOR_BLACK);
        thread1[0].position.z=ball1.position.z;
        pararec1[0].position.z=ball1.position.z;
        parachute1[0].position.z=ball1.position.z;
     }
     if(missile==GLFW_PRESS)
     {
        book=99;
        cannon1[1]=Cannon(ball1.position.x,ball1.position.y,COLOR_GREY,0.2);
        cannon1[1].position.z=ball1.position.z-2;
     }
    if(plane_view){
        eye_x=ball1.position.x;
        eye_y=ball1.position.y;
        eye_z=ball1.position.z-5;

        target_x=ball1.position.x;
        target_y=ball1.position.y;
        target_z=ball1.position.z-20;
    }
    else if(top_view){
        eye_x=5;
        eye_y=100;
        eye_z=5;

        target_x=ball1.position.x;
        target_y=ball1.position.y;
        target_z=ball1.position.z;
    }
    else if(tower_view){
        eye_x=5;
        eye_y=10;
        eye_z=10;
                          
        target_x=ball1.position.x;
        target_y=ball1.position.y;
        target_z=ball1.position.z;
    }
    else{
        eye_x=ball1.position.x;
        eye_y=ball1.position.y+5;
        eye_z=ball1.position.z+20;
       
        target_x=ball1.position.x;
        target_y=ball1.position.y;
        target_z=ball1.position.z;
    }
}
void tick_elements() {
    camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball1       = Ball(0, 0, COLOR_RED);
    ball1.position.z=0;
    ground1[0]  =Ground(-4,-3,COLOR_DARKGREEN,1.4);
    //sea1=Sea(0,0,COLOR_BLUE);
    hill1[0]=Hill(-4,-3,COLOR_BROWN);
    hill1[0].position.z-=20;
    ground1[0].position.z-=20;
    for(int i=1;i<10;i++)
    {
        ground1[i]     = Ground(-4,-3,COLOR_DARKGREEN,1.4);
        ground1[i].position.z=ground1[i-1].position.z-20;
        hill1[i]=Hill(-4,-3,COLOR_BROWN);
        hill1[i].position.z=hill1[i-1].position.z-20;
    }
    for(int i=10;i<20;i++)
    {
       ground1[i]     = Ground(-4,-3,COLOR_DARKGREEN,1.4);
       ground1[i].position.z=ground1[i-1].position.z-20;
       hill1[i]=Hill(-4,-3,COLOR_BROWN);
       hill1[i].position.z=hill1[i-1].position.z-20;
    }    
    for(int i=20;i<30;i++)
    {
        ground1[i]=Ground(-4,-3,COLOR_DARKGREEN,1.4);
        ground1[20].position.z=ground1[3].position.z-30;
        if(i>20)
        {
            ground1[i].position.z=ground1[i-1].position.z-60;
        }
        flag1[i-20]=Flag(-4,-3,COLOR_PINK);
        flag1[0].position.z=ground1[3].position.z-30;
        if(i>20)
            flag1[i-20].position.z=flag1[i-21].position.z-60;
        arrow1[i-20]=Arrow(flag1[i-20].position.x,1,COLOR_RED);
        arrow1[i-20].position.z=flag1[i-20].position.z;
    }
    for(int i=20;i<30;i++)
    {
        hill1[i]=Hill(-2.85,-3,COLOR_YELLOW);
        hill1[20].position.z=ground1[3].position.z-30;
        if(i>20)
            hill1[i].position.z=hill1[i-1].position.z-60;
        cannon1[i-20]=Cannon(-2.85,-2.5,COLOR_GREY,0.25);
        cannon1[0].position.z=ground1[3].position.z-30;
        if(i>20)
        {
            cannon1[i-20].position.z=cannon1[i-21].position.z-60;
        }

    }
    for(int i=30;i<32;i++)
    {
        ground1[i]=Ground(-9,-3,COLOR_DARKGREEN,1.4);
        ground1[30].position.z=-130;
        ground1[31].position.z=-190;
    }
    volc1[0]=Volcano(-9,-3,COLOR_GREY);
    volc1[1]=Volcano(-9,-3,COLOR_GREY);
    volc1[0].position.z=-130;
    volc1[1].position.z=-190;
    for(int i=32;i<34;i++)
    {
        //ground1[i].r=0.3;
        ground1[i]=Ground(-9,-2.5,COLOR_DARKRED,0.4);
        //ground1[i].r=0.3;
        ground1[32].position.z=-130;
        ground1[33].position.z=-190;
    }
    for(int i=0;i<3;i++)
    {
        line1[i]=Line(-9,-2.5,COLOR_DARKRED);
        line1[i].position.z=-130;
    }
    for(int i=3;i<=5;i++)
    {
        line1[i]=Line(-9,-2.5,COLOR_DARKRED);
        line1[i].position.z=-190;
    }
    sea1=Sea(0,-4,COLOR_BLUE);
    for(int i=0;i<3;i++)
    {
        bomb1[i]=Bomb(0,2,COLOR_DARKRED,1.4);
        bomb1[0].position.z=-200;
        if(i>=1)
            bomb1[i].position.z=bomb1[i-1].position.z-10;
    }
    speed1=Speed(2.3,-2,COLOR_ORANGE,0.75);
    line11=Line1(2.3,-2,COLOR_DARKRED);
    line22=Line2(2.3,-2,COLOR_DARKRED);
    rec1[0]=Rec(3.5,-1,COLOR_DARKRED);
    rec2[0]=Rec1(3.5,-4.0,COLOR_DARKRED);
    rec3[0]=Rec2(3.5,-1,COLOR_DARKGREEN);
    rec4[0]=Rec3(3.5,-3.3,COLOR_DARKGREEN);
    parachute1[1]=Parachute(1,4,COLOR_YELLOW,1);
    thread1[1]=Thread(1,4,COLOR_BLACK);
    pararec1[1]=Pararec(1,2,COLOR_BLACK);
    parachute1[1].position.z=2;
    thread1[1].position.z=2;
    pararec1[1].position.z=2;
    thread1[2]=Thread(3.5,4,COLOR_BLACK);
    pararec1[2]=Pararec(3.5,2,COLOR_BLACK);
    parachute1[2]=Parachute(3.5,4,COLOR_YELLOW,1);
    parachute1[2].position.z=-4;
    thread1[2].position.z=-4;
    pararec1[2].position.z=-4;
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;
    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            string final;
            stringstream convert;
            convert<<score;
            final=convert.str();
            const char *initial="Score:";
            const char *end=final.c_str();
            string total(string(initial)+string(end));
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);

            glfwSetWindowTitle(window,total.c_str());
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}
void reset_screen() {
    float top    = screen_center_y + 2 / screen_zoom;
    float bottom = screen_center_y - 2 / screen_zoom;
    float left   = screen_center_x - 2 / screen_zoom;
    float right  = screen_center_x + 2 / screen_zoom;
    Matrices.projection = glm::perspective(right, left, top,bottom);
}
//void drop_bomb(){
  //  fluster=2;
//}