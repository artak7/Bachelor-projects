#include "windows.h"
// ogl
#include <helper_gl.h>
#include <GL\glew.h>
#include <gl\freeglut.h>
// cuda
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
#include <helper_cuda.h>
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <algorithm>

static void HandleError( cudaError_t err,
                         const char *file,
                         int line ) {
    if (err != cudaSuccess) {
        printf( "%s in %s at line %d\n", cudaGetErrorString( err ),
                file, line );
        exit( EXIT_FAILURE );
    }
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

#define sunRaduis 0.4
#define earthRaduis 0.06
#define moonRaduis 0.016

GLfloat rotationSpeed = 0.1;
GLfloat daysInYear = 365;   
GLfloat year = 0.0; //degrees
GLfloat day = 0.0;
GLfloat moonAroundEarth = 0.0;
GLfloat moonItsSelf = 0.0;
GLfloat earthOrbitRadius = 1.0;
GLfloat moonOrbitRadius = 0.1;
GLfloat moonAroundEarthRate = 2 * rotationSpeed;
GLfloat moonRotationItselfRate = 5.0 * rotationSpeed;
GLfloat dayRate = 5.0 * rotationSpeed;
GLfloat yearRate = daysInYear / 360.0 * dayRate * rotationSpeed;
void drawSolarSystem(void);
void Initialization(void);
void displayFunc(void);
void reshapeFunc(int x, int y);
void idleFunc(void);


int width = 700,
    height = 700;
/*

void initCuda(int deviceId) {
    int deviceCount = 0;
    HANDLE_ERROR(cudaGetDeviceCount(&deviceCount));
 
    if (deviceCount <= 0) {
        printf("No CUDA devices found\n");
        exit(-1);
    }
 
    HANDLE_ERROR(cudaGLSetGLDevice(deviceId));
 
    cudaDeviceProp properties;
    HANDLE_ERROR(cudaGetDeviceProperties(&properties, deviceId));
 
    threads.x = 32;
    threads.y = properties.maxThreadsPerBlock / threads.x - 2; // to avoid cudaErrorLaunchOutOfResources error
 
    blocks.x = (width + threads.x - 1) / threads.x;
    blocks.y = (height + threads.y - 1) / threads.y;
 
    printf(
            "Debug: blocks(%d, %d), threads(%d, %d)\nCalculated Resolution: %d x %d\n",
            blocks.x, blocks.y, threads.x, threads.y, blocks.x * threads.x,
            blocks.y * threads.y);
}
__global__ void renderFrame(uchar4* screen) {
    int width = 700, height = 700;
    const float k = 20.0f;
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
 
    float2 force, t_force;
    force.x = force.y = 0.0f;
 
    if (x >= width || y >= height)
        return;
 
    for (char i = 0; i < dev_chargeCount; i++) {
        calculate(dev_charges[i], x, y, t_force);
 
        force.x += t_force.x;
        force.y += t_force.y;
    }
 
    force.x *= k;
    force.y *= k;
 
    setColor(force, screen[x + y * width]);
}

GLuint vbo, deviceId;
struct cudaGraphicsResource *cuda_vbo_resource;

void createVBO(GLuint *vbo, struct cudaGraphicsResource **vbo_res, unsigned int vbo_res_flags) {
    unsigned int size = width * height * sizeof(uchar4);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, *vbo);
    glBufferData(GL_PIXEL_UNPACK_BUFFER_ARB, size, NULL, GL_DYNAMIC_DRAW);

    HANDLE_ERROR( cudaGraphicsGLRegisterBuffer(vbo_res, *vbo, vbo_res_flags) );
}

void deleteVBO(GLuint *vbo, struct cudaGraphicsResource *vbo_res) {
    HANDLE_ERROR( cudaGraphicsUnregisterResource(cuda_vbo_resource) );

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, *vbo);
    glDeleteBuffers(1, vbo);

    *vbo = 0;
}
*/

int main(int argc, char* argv[])
{

    // Initialization for glut 
    glutInit(&argc, argv);
    // set the buffer mode ( double and colors (RGB)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // set the window frame size 
    glutInitWindowSize(width, height);
    glutCreateWindow("Solar system");
    Initialization();
    /*
    HANDLE_ERROR( cudaGLSetGLDevice(deviceId) );//
    createVBO(&vbo, &cuda_vbo_resource, cudaGraphicsMapFlagsWriteDiscard);//
    deleteVBO(&vbo, cuda_vbo_resource);//
    */
    // reshape call back function reference setting.
    glutReshapeFunc(reshapeFunc);
    // display call back function reference setting
    glutDisplayFunc(displayFunc);
    //  idle callback function reference setting ( used in animation )
    glutIdleFunc(idleFunc);
    
    // enters the GLUT event processing loop
    glutMainLoop();
    return 0;
}

/*void draw(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glutSwapBuffers();
}*/

void drawSolarSystem(void)
{

    glPushMatrix();
    /*
    glPushMatrix()
        pushes the current matrix stack down by one, duplicating the current matrix. That is,
            after a glPushMatrix call, the matrix on top of the stack is identical to the one below it.
        
    */
    
    
        gluLookAt(    0.0,0.0,-4.0,
                    0.0,0.0,1.0,
                    0.0,-3.0,0.0);
        //gluLookAt
        //creates a viewing matrix derived from an eye point, a reference point indicating the
        //center of the scene, and an UP vector

        // Color of the sun. 
        glColor3f(1.0,0.8,0.3);
        // Drawing the sun. 
        glutSolidSphere(sunRaduis,50,50);
        glPushMatrix();
        
            glRotatef(year,0.0,1.0,0.0); //rotation for earth
            glTranslatef(earthOrbitRadius,0.0,0.0); // translation for earth.
            glRotatef(-year,0.0,1.0,0.0);
            glPushMatrix();
                glRotatef(day,0.25,1.0,0.0);
                glColor3f(0.4,0.6,0.3);
                //Drawing the earth
                glutSolidSphere(earthRaduis,10,10);   
                 
            glPopMatrix();
            // rotation for moon.
            glRotatef(moonAroundEarth,0.0,1.0,0.0);
            // translation for moon.
            glTranslatef(moonOrbitRadius,0.0,0.0);
         
            // around earth rotation.
            glRotatef(-moonAroundEarth,0.0,1.0,0.0);
            // moon rotation about it self.
            glRotatef(moonItsSelf,0.0,1.0,0.0);

            glColor3f(0.3,0.3,0.5);
            // draw the moon
            glutSolidSphere(moonRaduis,8,8);
        glPopMatrix();
                
    glPopMatrix();
}

void Initialization(void)
{
    // background color
    glClearColor(0.0,0.0,0.0,0.0);
    glClearDepth(10.0);


    // GL_MODELVIEW :Applies subsequent matrix operations to the modelview matrix stack.
    /*
The modelview matrix is for transformation of geometry from model to view space 
(therefore the camera/view transform most correctly goes in the modelview matrix).
    */
    glMatrixMode(GL_MODELVIEW);
    // replace the current matrix with the identity matrix
    glLoadIdentity();
}

void displayFunc(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawSolarSystem();
    // flush to screen.
    glFlush();
    // swap buffers , yes we need this ( double buffering used!)
    glutSwapBuffers();
}

void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;
 
    glLoadIdentity();
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
    displayFunc();
}

void idleFunc(void)
{
    // idle event call back in animation , here we increase the values and redisply .
    day += dayRate;
    year += yearRate;
    moonItsSelf += moonRotationItselfRate;
    moonAroundEarth += moonAroundEarthRate;
    displayFunc();
}
/*
void idle(void) {
    uchar4* dev_screen;
    size_t size;

    HANDLE_ERROR( cudaGraphicsMapResources(1, &cuda_vbo_resource, 0) );
    HANDLE_ERROR( cudaGraphicsResourceGetMappedPointer((void**) &dev_screen, &size, cuda_vbo_resource) );

    // Render Image
    renderFrame<<<blocks, threads>>>(dev_screen);
    HANDLE_ERROR( cudaDeviceSynchronize() );

    HANDLE_ERROR( cudaGraphicsUnmapResources(1, &cuda_vbo_resource, 0) );

    glutPostRedisplay();
}*/