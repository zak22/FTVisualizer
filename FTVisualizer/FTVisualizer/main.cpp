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

void glutDrawText(void *font, char *text, float xPos, float yPos);

//rectangles


class rectangle{
	public:
        rectangle(float xLeft,float xRight,float yTop,float yBottom,float width, float *color, float sleep);                        //constructor
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
		char *name;
		void animeRec();
};


rectangle::rectangle(float xLeft,float xRight,float yTop,float yBottom,float width, float *color, float sleep){
	this->animate = true;
	this->xLeft = xLeft;
	this->xRight = xRight;
	this->yBottom = yBottom;
	this->yTop = yTop;
	this->width = width;
	this->color = color;
	this->sleep = sleep;
	this->name = name;
}


void rectangle::display(){
    if(animate)
	{
		animeRec();
		return;
	}

	glColor3f(color[0],color[1],color[2]);

	glBegin(GL_QUADS);

	glVertex2i(xLeft,yTop);
	glVertex2i(xLeft-width,yTop);
	glVertex2i(xLeft-width,yBottom);
	glVertex2i(xLeft,yBottom);


	glVertex2i(xRight,yTop);
	glVertex2i(xRight+width,yTop);
	glVertex2i(xRight+width,yBottom);
	glVertex2i(xRight,yBottom);

    
	glVertex2i(xLeft,yTop);
	glVertex2i(xLeft,yTop-width);
	glVertex2i(xRight,yTop-width);
	glVertex2i(xRight,yTop);


	glVertex2i(xLeft,yBottom);
    glVertex2i(xLeft,yBottom+width);
	glVertex2i(xRight,yBottom+width);
	glVertex2i(xRight,yBottom);

    glEnd();

	glutDrawText(GLUT_BITMAP_HELVETICA_18, "text", 80, 80);
}

void glutDrawText(void *font, char *text, float xPos, float yPos)
{
	glRasterPos2i(xPos, yPos);
	while(*text){
		glutBitmapCharacter(font, *text);
		text++;
	}
}


void rectangle::animeRec()
{
	float val = 1;
	float perimeter = ((xRight - xLeft)) + ((yBottom - yTop));
	int slp = (int) floor(sleep/(perimeter/val));

	//Bottom Bar
	float tmpL = (((xRight - xLeft)/2) + xLeft) - val;
	float tmpR = (((xRight - xLeft)/2) + xLeft) + val;
	while(tmpL >= xLeft)
	{
		glColor3f(color[0],color[1],color[2]);

		glBegin(GL_QUADS);
		glVertex2i(tmpL,yBottom);
		glVertex2i(tmpL,yBottom+width);
		glVertex2i(tmpR,yBottom+width);
		glVertex2i(tmpR,yBottom);
		glEnd();

		glFlush();
		glutPostRedisplay();
		tmpL -= val;
		tmpR += val;
		Sleep(slp);
	}


	//left and right bars
	float tmpT = yBottom - val;
	while(tmpT >= yTop)
	{
		glColor3f(color[0],color[1],color[2]);

		glBegin(GL_QUADS);
		//Left Bar
		glVertex2i(xLeft,tmpT);
		glVertex2i(xLeft-width,tmpT);
		glVertex2i(xLeft-width,yBottom);
		glVertex2i(xLeft,yBottom);
		//Right Bar
		glVertex2i(xRight,tmpT);
		glVertex2i(xRight+width,tmpT);
		glVertex2i(xRight+width,yBottom);
		glVertex2i(xRight,yBottom);
		glEnd();

		glFlush();
		glutPostRedisplay();
		tmpT -= val;
		Sleep(slp);
	}

	//Top Bar
	tmpL = xLeft + val;
	tmpR = xRight - val;
	while(tmpL <= tmpR)
	{
		glColor3f(color[0],color[1],color[2]);

		glBegin(GL_QUADS);		
		
		//Top Bar (Left)
		glVertex2i(xLeft,yTop);
		glVertex2i(xLeft,yTop-width);
		glVertex2i(tmpL,yTop-width);
		glVertex2i(tmpL,yTop);
		
		//Top Bar (Right)
		glVertex2i(tmpR,yTop);
		glVertex2i(tmpR,yTop-width);
		glVertex2i(xRight,yTop-width);
		glVertex2i(xRight,yTop);		
		glEnd();

		glFlush();
		glutPostRedisplay();
		tmpL += val;
		tmpR -= val;
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

rectangle r1 = rectangle(50,200,50,100,5, pink, 1000);


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

	//glColor3f(pink[0],pink[1],pink[2]);
	//glBegin(GL_QUADS);		
	//glVertex2i(50,50);
	//glVertex2i(100,50);
	//glVertex2i(100,100);
	//glVertex2i(50,100);
	//glEnd();

	//glColor3f(pink[0],pink[1],pink[2]);
	//glRasterPos2i(100, 100);
	//glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'a');

	
	glFlush();
    glutPostRedisplay();
}


void init()
{
	glClearColor(0,0,0,0);
	gluOrtho2D(0,windowWidth,windowHeight,0);
}



