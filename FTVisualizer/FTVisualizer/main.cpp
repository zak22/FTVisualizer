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


void rectangle(float xLeft, float xRight, float yBottom, float yTop);

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	rectangle(-1,1,-0.5,0.5);

	glFlush();
    glutPostRedisplay();
}


void init()
{
	glClearColor(0,0,0,0);
	gluOrtho2D(-5,5,-5,5);
}


void rectangle(float xLeft,float xRight,float yBottom,float yTop)
{
    glColor3f(0,0,1);

	glBegin(GL_LINES);

	glVertex2f(xLeft,yTop);
	glVertex2f(xLeft,yBottom);

    glVertex2f(xRight,yTop);
	glVertex2f(xRight,yBottom);

    glVertex2f(xLeft,yTop);
	glVertex2f(xRight,yTop);

    glVertex2f(xLeft,yBottom);
	glVertex2f(xRight,yBottom);

    glEnd();
}


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


