//Copyright (C) 2011 by Zakaria Almatar, Husain Al-Matar, and Osamh Hamali

#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <Windows.h>
#include <math.h>

using namespace std;

//window
int windowWidth  = 640;   // Window's width
int windowHeight = 480;   // Window's height
int windowPosX   = 50;    // Window's top-left corner x
int windowPosY   = 50;    // Window's top-left corner y

//colors
float blue[]={0,0,153}; 
float pink[]={204,0,153};
float white[]={1,1,1};

//corners
const int topL = 0;
const int topR = 1;
const int bottomR = 2;
const int bottomL = 3;

//rectangles


class rectangle{
	public:
        rectangle(float xLeft,float xRight,float yBottom,float yTop,float width, float *color, float sleep);                        //constructor
	    void display();                  //display rectangle
	private:
		bool animate;
		float xLeft;
		float xRight;
		float yBottom;
		float yTop;
		float width;
		float *color;
		float sleep;
		void animeRec();
};


rectangle::rectangle(float xLeft,float xRight,float yBottom,float yTop,float width, float *color, float sleep){
	this->animate = true;
	this->xLeft = xLeft;
	this->xRight = xRight;
	this->yBottom = yBottom;
	this->yTop = yTop;
	this->width = width;
	this->color = color;
	this->sleep = sleep;
}


void rectangle::display(){
    if(animate)
	{
		animeRec();
		return;
	}

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



void rectangle::animeRec()
{
	float val = 0.01;
	float perimeter = ((xRight - xLeft)) + ((yTop - yBottom));
	int slp = (int) floor(sleep/(perimeter/val));

	//Bottom Bar
	float tmpL = (((xRight - xLeft)/2) + xLeft) - val;
	float tmpR = (((xRight - xLeft)/2) + xLeft) + val;
	while(1)
	{
		glColor3f(color[0],color[1],color[2]);

		glBegin(GL_QUADS);
		glVertex2f(tmpL,yBottom);
		glVertex2f(tmpL,yBottom-width);
		glVertex2f(tmpR,yBottom-width);
		glVertex2f(tmpR,yBottom);
		glEnd();

		glFlush();
		glutPostRedisplay();
		tmpL -= val;
		tmpR += val;
		if(tmpL < xLeft)
			break;
		Sleep(slp);
	}


	//left and right bars
	float tmpT = yBottom + val;
	while(1)
	{
		glColor3f(color[0],color[1],color[2]);

		glBegin(GL_QUADS);
		//Left Bar
		glVertex2f(xLeft,tmpT);
		glVertex2f(xLeft-width,tmpT);
		glVertex2f(xLeft-width,yBottom);
		glVertex2f(xLeft,yBottom);
		//Right Bar
		glVertex2f(xRight,tmpT);
		glVertex2f(xRight+width,tmpT);
		glVertex2f(xRight+width,yBottom);
		glVertex2f(xRight,yBottom);
		glEnd();

		glFlush();
		glutPostRedisplay();
		tmpT += val;
		if(tmpT > yTop)
			break;
		Sleep(slp);
	}

	//Top Bar
	tmpL = xLeft + val;
	tmpR = xRight - val;
	while(1)
	{
		glColor3f(color[0],color[1],color[2]);

		glBegin(GL_QUADS);		
		//Top Bar (Left)
		glVertex2f(xLeft,yTop);
		glVertex2f(xLeft,yTop+width);
		glVertex2f(tmpL,yTop+width);
		glVertex2f(tmpL,yTop);
		//Top Bar (Right)
		glVertex2f(tmpR,yTop);
		glVertex2f(tmpR,yTop+width);
		glVertex2f(xRight,yTop+width);
		glVertex2f(xRight,yTop);		
		glEnd();

		glFlush();
		glutPostRedisplay();
		tmpL += val;
		tmpR -= val;
		if(tmpL >= tmpR)
			break;
		Sleep(slp);
	}

	animate = 0;
    //glEnd();
}


//int animate = 1;

//functions
//void rectangle(float xLeft, float xRight, float yBottom, float yTop,float width, float *color, float sleep);
//void animeRec(float xLeft,float xRight,float yBottom,float yTop,float width, float *color, float sleep);
void display();
void init();

rectangle r1 = rectangle(-3,-1,-0.5,0.5,0.1, pink, 1000);





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
	
	r1.display();
	
	glFlush();
    glutPostRedisplay();
}


void init()
{
	glClearColor(0,0,0,0);
	gluOrtho2D(-5,5,-5,5);
}



