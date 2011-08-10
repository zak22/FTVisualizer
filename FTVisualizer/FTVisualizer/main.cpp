/*Copyright (C) 2011 by Zakaria Almatar, Husain Al-Matar, and Osamh Hamali
 *
 *Look at the LICENSE by going to this link: 
 *https://github.com/zak22/FTVisualizer/blob/master/LICENSE
 *
 */
 
 
#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <Windows.h>
#include <math.h>
#include <string>

using namespace std;

//window
int windowWidth  = 640;   // Window's width
int windowHeight = 480;   // Window's height
int windowPosX   = 50;    // Window's top-left corner x
int windowPosY   = 50;    // Window's top-left corner y

//colors
float blue[]={0,0,153}; 
float pink[]={204,0,153};
float red[]={200,0,0};
float white[]={1,1,1};

//corners
const int topL = 0;
const int topR = 1;
const int bottomR = 2;
const int bottomL = 3;

//sides
const int LEFT = 0;
const int TOP = 1;
const int RIGHT = 2;
const int BOTTOM = 3;
const int X_COORD = 0;
const int Y_COORD = 1;


const float WIDTH = 3;
const float ANIME_INCREMENT = 1;


void glutDrawText(void *font, char *text, float xPos, float yPos);

//rectangles





class person{
	public:
        person(int date, float xLeft,float xRight,float yTop,float yBottom, float *color, float sleep, char *name);                        //constructor
	    void display();                  //display rectangle
		float **getPos();                  //display rectangle
		int getDate();
	private:
		bool animate;
		int date;
		float xLeft;
		float xRight;
		float yBottom;
		float yTop;
		float *color;
		float sleep;
		char *name;
		float nameWidth;
		void *font;
		float textX;
		float textY;
		void draw();
};
person::person(int date, float xLeft,float xRight,float yTop,float yBottom, float *color, float sleep, char *name){
	this->animate = true;
	this->date = date;
	this->xLeft = xLeft;
	this->xRight = xRight;
	this->yBottom = yBottom;
	this->yTop = yTop;
	this->color = color;
	this->sleep = sleep;
	this->name = new char[strlen(name)];
	strcpy(this->name,name);
	font = GLUT_BITMAP_HELVETICA_18;
	nameWidth = glutBitmapLength(font, (unsigned char*)name);
	textX = (((xRight-xLeft)/2) + xLeft) - (nameWidth/2);
	textY = ((yBottom-yTop)/2) + yTop;
}
void person::display(){
	glColor3f(white[0],white[1],white[2]);
	glutDrawText(font, name, textX, textY);    

	if(animate)
	{
		draw();
		return;
	}

	glColor3f(color[0],color[1],color[2]);

	glBegin(GL_QUADS);

	glVertex2i(xLeft,yTop);
	glVertex2i(xLeft-WIDTH,yTop);
	glVertex2i(xLeft-WIDTH,yBottom);
	glVertex2i(xLeft,yBottom);


	glVertex2i(xRight,yTop);
	glVertex2i(xRight+WIDTH,yTop);
	glVertex2i(xRight+WIDTH,yBottom);
	glVertex2i(xRight,yBottom);

    
	glVertex2i(xLeft,yTop);
	glVertex2i(xLeft,yTop-WIDTH);
	glVertex2i(xRight,yTop-WIDTH);
	glVertex2i(xRight,yTop);


	glVertex2i(xLeft,yBottom);
    glVertex2i(xLeft,yBottom+WIDTH);
	glVertex2i(xRight,yBottom+WIDTH);
	glVertex2i(xRight,yBottom);

    glEnd();
}
void person::draw()
{
	float val = ANIME_INCREMENT;
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
		glVertex2i(tmpL,yBottom+WIDTH);
		glVertex2i(tmpR,yBottom+WIDTH);
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
		glVertex2i(xLeft-WIDTH,tmpT);
		glVertex2i(xLeft-WIDTH,yBottom);
		glVertex2i(xLeft,yBottom);
		//Right Bar
		glVertex2i(xRight,tmpT);
		glVertex2i(xRight+WIDTH,tmpT);
		glVertex2i(xRight+WIDTH,yBottom);
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
		glVertex2i(xLeft,yTop-WIDTH);
		glVertex2i(tmpL,yTop-WIDTH);
		glVertex2i(tmpL,yTop);
		
		//Top Bar (Right)
		glVertex2i(tmpR,yTop);
		glVertex2i(tmpR,yTop-WIDTH);
		glVertex2i(xRight,yTop-WIDTH);
		glVertex2i(xRight,yTop);		
		glEnd();

		glFlush();
		glutPostRedisplay();
		tmpL += val;
		tmpR -= val;
		Sleep(slp);
	}

	animate = false;
    //glEnd();
}
float **person::getPos()
{
	float **pos = new float*[4];
	for(int i=0;i<4;++i)
		pos[i] = new float[2];

	pos[LEFT][X_COORD] = xLeft-WIDTH;
	pos[LEFT][Y_COORD] = ((yBottom-yTop)/2) + yTop + (WIDTH/2);

	pos[RIGHT][X_COORD] = xRight+WIDTH;
	pos[RIGHT][Y_COORD] = ((yBottom-yTop)/2) + yTop + (WIDTH/2);

	pos[TOP][X_COORD] = ((xRight-xLeft)/2) + xLeft + (WIDTH/2);
	pos[TOP][Y_COORD] = yTop - WIDTH;

    pos[BOTTOM][X_COORD] = ((xRight-xLeft)/2) + xLeft + (WIDTH/2);
	pos[BOTTOM][Y_COORD] = yBottom+WIDTH;

	return pos;
}
int person::getDate()
{
	return date;
}

class marriage{
	public:
        marriage(int date, person *groom, person *bride, float sleep);                        //constructor
	    void display();                  //display rectangle
		void setDivorce();               //display rectangle
		int getDate();
	private:
		bool animate;
		bool children;
		bool divorce;
		int date;
		float xLeft;
		float xRight;
		float y;
		float *color;
		float sleep;
		void draw();
};
void marriage::setDivorce()
{
	divorce = !divorce;
}
marriage::marriage(int date, person *groom, person *bride, float sleep){
	this->animate = true;
	this->children = false;
	this->divorce = false;
	this->date = date;
	float **groomPos = groom->getPos();
	float **bridePos = bride->getPos();
	if(groomPos[LEFT][X_COORD] > bridePos[RIGHT][X_COORD])
	{
		this->xLeft = bridePos[RIGHT][X_COORD];
		this->xRight = groomPos[LEFT][X_COORD];
	}
	else
	{
		this->xLeft = groomPos[RIGHT][X_COORD];
		this->xRight = bridePos[LEFT][X_COORD];
	}
	this->y = groomPos[RIGHT][Y_COORD];
	this->color = white;
	this->sleep = sleep;
}
void marriage::display()
{
	if(animate)
	{
		draw();
		return;
	}

	glColor3f(color[0],color[1],color[2]);
	glBegin(GL_QUADS);
	glVertex2i(xLeft,y);
	glVertex2i(xLeft,y-WIDTH);
	glVertex2i(xRight,y-WIDTH);
	glVertex2i(xRight,y);
	glEnd();

	if(divorce)
	{
		float length = WIDTH*3;
		float xMid = ((xRight-xLeft)/2) + xLeft;
		float yMid = y-(WIDTH/2);
		float xStart = (xMid+(length/2)) - (WIDTH/2);
		float yStart = yMid-(length/2);
		float yEnd = yMid+(length/2);
		float increment = 0.25;

		glColor3f(red[0],red[1],red[2]);
		for(float i=yStart;i<=yEnd;i+=increment)
		{
			glBegin(GL_QUADS);
			glVertex2i(xStart,yStart);
			glVertex2i(xStart+WIDTH,yStart);
			glVertex2i(xStart+WIDTH,yStart+increment);
			glVertex2i(xStart,yStart+increment);
			glEnd();
			xStart-=increment;
			yStart+=increment;
		}
	}
}
void marriage::draw()
{
	float val = ANIME_INCREMENT;
	float length = xRight - xLeft;
	int slp = (int) floor(sleep/(length/val));
	glColor3f(white[0],white[1],white[2]);
		
	float tmpL = (((xRight - xLeft)/2) + xLeft) - val;
	float tmpR = (((xRight - xLeft)/2) + xLeft) + val;
	while(tmpL >= xLeft)
	{
		glColor3f(color[0],color[1],color[2]);

		glBegin(GL_QUADS);
		glVertex2i(tmpL,y);
		glVertex2i(tmpL,y-WIDTH);
		glVertex2i(tmpR,y-WIDTH);
		glVertex2i(tmpR,y);
		glEnd();

		glFlush();
		glutPostRedisplay();
		tmpL -= val;
		tmpR += val;
		Sleep(slp);
	}
	animate = false;
	return;
}
int marriage::getDate()
{
	return date;
}



void viewManage();
void display();
void init();

person *r1 = new person(19880101,300,450,50,100, blue, 1000, "Groom");
person *r2 = new person(19900101,50,200,50,100, pink, 1000, "Bride");
marriage *m = new marriage(20110101,r1,r2, 1000);

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
	
	r1->display();
	r2->display();
	m->display();


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
void glutDrawText(void *font, char *text, float xPos, float yPos)
{
	glRasterPos2i(xPos, yPos);
	while(*text){
		glutBitmapCharacter(font, *text);
		text++;
	}
}

