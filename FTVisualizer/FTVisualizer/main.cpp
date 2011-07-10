#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
      
using namespace std;

//window
int windowWidth  = 640;   // Window's width
int windowHeight = 480;   // Window's height
int windowPosX   = 50;    // Window's top-left corner x
int windowPosY   = 50;    // Window's top-left corner y
float blue[]={0,0,153}, pink[]={204,0,153}, white[]={1,1,1};



void rectangle(float xLeft, float xRight, float yBottom, float yTop,float width, float *color);
void display();
void init();


void main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(windowPosX,windowPosY);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("FTVisualizer");
	init();
	glutDisplayFunc(display);
    glutMainLoop();
}



void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	rectangle(-3,-1,-0.5,0.5,0.1, pink);
	rectangle(1,3,-0.5,0.5,0.1, blue);
	
	glFlush();
    glutPostRedisplay();
}


void init()
{
	glClearColor(0,0,0,0);
	gluOrtho2D(-5,5,-5,5);
}


void rectangle(float xLeft,float xRight,float yBottom,float yTop,float width, float *color)
{
    glColor3f(color[0],color[1],color[2]);

	glBegin(GL_QUADS);

	glVertex2f(xLeft,yTop);
	glVertex2f(xLeft-width,yTop);
	glVertex2f(xLeft-width,yBottom);
	glVertex2f(xLeft,yBottom);


	glVertex2f(xRight,yTop);
	glVertex2f(xRight+width,yTop);
	glVertex2f(xRight+width,yBottom);
	glVertex2f(xRight,yBottom);

    
	glVertex2f(xLeft,yTop);
	glVertex2f(xLeft,yTop+width);
	glVertex2f(xRight,yTop+width);
	glVertex2f(xRight,yTop);


	glVertex2f(xLeft,yBottom);
    glVertex2f(xLeft,yBottom-width);
	glVertex2f(xRight,yBottom-width);
	glVertex2f(xRight,yBottom);

    glEnd();
}




