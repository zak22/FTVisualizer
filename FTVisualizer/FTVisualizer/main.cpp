//Copyright (C) 2011 by Zakaria Almatar, Husain Al-Matar, and Osamh Hamali
//License can be found at https://github.com/zak22/FTVisualizer/wiki/License

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
#include <vector>
#include <fstream>


using namespace std;

//window
int windowWidth  = 1000;   // Window's width
int windowHeight = 700;   // Window's height
int windowPosX   = 50;    // Window's top-left corner x
int windowPosY   = 50;    // Window's top-left corner y

//colors
float blue[]={0,0,153}; 
float pink[]={204,0,153};
float red[]={200,0,0};
float white[]={1,1,1};
float gray[]={105,105,105};

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

//Shapes drawing variables
const float WIDTH = 7;
const float ANIME_INCREMENT = 1;
float personWidth = 120;
float personHeight = 50;
float linkWidth = 50;

//Shapes dimensions variables
float rootFarLeft = -1;
float rootFarRight = -1;
float screenFarLeft = -1;
float screenFarRight = -1;

//Childern
float childrenSpacing = 30;


//Current Date
int currDate = 2011;
int lastDate = 2011;

//text size
int TEXT_SIZE = 18;


//represent an event
struct events
{
	int date;
	int eventType;
	char ** details;
};
struct eventsDraw
{
	int date;
	int type;
	int index;
};
struct position
{
	float left;
	float right;
	float top;
	float bottom;
};



void glutDrawText(void *font, char *text, float xPos, float yPos);
void viewManage();
void display();
void init();
int numOfOccurrences(char *a, char c);
int posToInsert(int date);
void eventsJoin();

//rectangles

//globals
class marriage;
class person;
vector <person*> people;
vector <person*> tChildren;
vector <marriage*> marriages;
int doneEvents=0;
events *eventsList = NULL;
eventsDraw *eventsFullList = NULL;
int lineCount=0;





class person{
	public:
        person(int date, float xLeft,float xRight,float yTop,float yBottom, float *color, float sleep, char *name);                        //constructor
	    void display();                  //display rectangle
		float **getPos();                  //display rectangle
		void drawNameAndAge();
		void setNameAndAgePos();
		char *name;
		int date;
		int deathDate;
		bool dead;
		bool root;
		bool justPartner;
		bool child;
		bool married;
		int childNum;
		marriage *marriageLink;
		float xLeft;
		float xRight;
		float yBottom;
		float yTop;
		person *parent;
	private:
		bool animate;
		float *color;
		float sleep;
		char *age;
		void *font;
		float textX;
		float textY;
		float ageX;
		float ageY;
		void draw();
		void setAge();
};
person::person(int date, float xLeft,float xRight,float yTop,float yBottom, float *color, float sleep, char *name){
	this->animate = true;
	this->dead = false;
	this->root = false;
	this->justPartner = false;
	this->child = false;
	this->married = false;
	marriageLink = NULL;
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
	this->age = new char[5];
	setAge();
	setNameAndAgePos();
}
void person::display(){
	
	
	if(dead && deathDate/10000 <= currDate)
	{
		glColor3f(.3,.3,.3);
		glBegin(GL_QUADS);
		glVertex2i(xLeft,yTop);
		glVertex2i(xRight,yTop);
		glVertex2i(xRight,yBottom);
		glVertex2i(xLeft,yBottom);
		glEnd();

		//glColor3f(white[0],white[1],white[2]);
		//glutDrawText(font, name, textX, textY);
		//glutDrawText(font, age, ageX, ageY);
	}
	else
	{
		setAge();
	}	
	
	//draw name and age
	glColor3f(white[0],white[1],white[2]);
	glutDrawText(font, name, textX, textY);
	glutDrawText(font, age, ageX, ageY);

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
void person::setAge()
{
	int birthYear = date/10000;
	itoa(currDate - birthYear,age,10);
}
void person::setNameAndAgePos()
{
	int nameWidth = glutBitmapLength(font, (unsigned char*)name);
	textX = (((xRight-xLeft)/2) + xLeft) - (nameWidth/2);
	textY = ((yBottom-yTop)/2) + yTop - 3;
	int ageWidth = glutBitmapLength(font, (unsigned char*)age);
	ageX = (((xRight-xLeft)/2) + xLeft) - (ageWidth/2);
	ageY = textY + TEXT_SIZE + 3;
}


class marriage{
	public:
        marriage(int date, person *groom, person *bride, float sleep);                        //constructor
	    void display();                  //display rectangle
		void displayChildren();
		void addChild(events e);
		void makeChildrenSpace(int chNum);
		int date;
		bool divorce;
		bool children;
		vector <person*> childrenList;
		int divorceDate;
		person *side1;
		person *side2;
	private:
		position chLine1;
		position chLine2;
		bool animate;
		float xLeft;
		float xRight;
		float y;
		float *color;
		float sleep;
		void draw();
};
marriage::marriage(int date, person *groom, person *bride, float sleep){
	this->animate = true;
	this->children = false;
	this->divorce = false;
	this->side1 = groom;
	this->side2 = bride;
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
	
	groom->marriageLink = this;
	bride->marriageLink = this;
	groom->married = true;
	bride->married = true;
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

	if(side1->justPartner)
		side1->display();

	if(side2->justPartner)
		side2->display();

	if(children)
		displayChildren();

	if(divorce && divorceDate/10000 <= currDate)
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
}
void marriage::addChild(events e)
{
	person *tmpP;
	position tmpPos;
	int childrenCount;
	float l2Len;
	float *c;
	
	if(e.details[1][0] == 'm')
		c = blue;
	else
		c = pink;

	if(!children)
	{
		//first line
		chLine1.left = (((xRight-xLeft)/2)-(WIDTH/2)) + xLeft;
		chLine1.right = chLine1.left + WIDTH;
		chLine1.top = y;
		chLine1.bottom = chLine1.top + (personHeight*1.5);
		
		//person pos
		tmpPos.left = (((xRight-xLeft)/2) + xLeft) - personWidth/2;
		tmpPos.right = tmpPos.left + personWidth;
		tmpPos.top = y + (personHeight*1.5);
		tmpPos.bottom = tmpPos.top + personHeight;

		tmpP = new person(e.date, tmpPos.left, tmpPos.right, tmpPos.top, tmpPos.bottom, c, 1000, e.details[0]);
		tmpP->child = true;
		tmpP->childNum = 0;
		tmpP->parent = this->side1;
		childrenList.push_back(tmpP);
		tChildren.push_back(tmpP);
		children = true;
	}
	else
	{
		chLine1.bottom = y + personHeight;
		childrenCount = this->childrenList.size();
		
		l2Len = (personWidth*childrenCount) + (childrenSpacing*childrenCount);
		chLine2.left = (chLine1.left + (WIDTH/2)) - (l2Len/2)  ;
		chLine2.right = chLine2.left + l2Len;
		chLine2.top = chLine1.bottom;
		chLine2.bottom = chLine2.top + WIDTH;

		tmpP = new person(e.date, 0, 0, childrenList[0]->yTop, childrenList[0]->yBottom, c, 1000, e.details[0]);
		tmpP->child = true;
		tmpP->childNum = childrenCount;
		tmpP->parent = this->side1;
		childrenList.push_back(tmpP);
		tChildren.push_back(tmpP);
		++childrenCount;

		childrenList[childrenCount-1]->xLeft = chLine2.left - (personWidth/2);
		childrenList[childrenCount-1]->xRight = childrenList[childrenCount-1]->xLeft + personWidth;
		childrenList[childrenCount-1]->setNameAndAgePos();

		if(childrenList[childrenCount-1]->xLeft < screenFarLeft)
			screenFarLeft = childrenList[childrenCount-1]->xLeft;

		for(int i=childrenCount-2;i>=0;--i)
		{
			childrenList[i]->xLeft = childrenList[i+1]->xRight + childrenSpacing;
			childrenList[i]->xRight = childrenList[i]->xLeft + personWidth;
			childrenList[i]->setNameAndAgePos();

			if(childrenList[i]->xRight > screenFarRight)
				screenFarRight = childrenList[i]->xRight;
		}
	}
}
void marriage::displayChildren()
{
	int childrenCount = childrenList.size();
	
	glColor3f(white[0],white[1],white[2]);
	glBegin(GL_QUADS);
	glVertex2i(chLine1.left, chLine1.top);
	glVertex2i(chLine1.right, chLine1.top);
	glVertex2i(chLine1.right, chLine1.bottom);
	glVertex2i(chLine1.left, chLine1.bottom);
	glEnd();

	if(childrenCount>1)
	{
		glBegin(GL_QUADS);
		glVertex2i(chLine2.left, chLine2.top);
		glVertex2i(chLine2.right, chLine2.top);
		glVertex2i(chLine2.right, chLine2.bottom);
		glVertex2i(chLine2.left, chLine2.bottom);
		glEnd();
	}
	
	for(int i=0;i<childrenCount;++i)
	{
		glColor3f(white[0],white[1],white[2]);
		glBegin(GL_QUADS);
		glVertex2i((childrenList[i]->xRight-(personWidth/2))-(WIDTH/2), childrenList[i]->yTop-((personHeight/2)));
		glVertex2i((childrenList[i]->xRight-(personWidth/2))+(WIDTH/2), childrenList[i]->yTop-((personHeight/2)));
		glVertex2i((childrenList[i]->xRight-(personWidth/2))+(WIDTH/2), childrenList[i]->yTop-WIDTH);
		glVertex2i((childrenList[i]->xRight-(personWidth/2))-(WIDTH/2), childrenList[i]->yTop-WIDTH);
		glEnd();
		childrenList[i]->display();
	}
}


void marriage::makeChildrenSpace(int chNum)
{
	int childrenCount = childrenList.size();
	float l2Len = (chLine2.right - chLine2.left) + linkWidth + personWidth;

	chLine2.left = (chLine1.left + (WIDTH/2)) - (l2Len/2);
	chLine2.right = chLine2.left + l2Len;

	childrenList[childrenCount-1]->xLeft = chLine2.left - (personWidth/2);
	childrenList[childrenCount-1]->xRight = childrenList[childrenCount-1]->xLeft + personWidth;
	childrenList[childrenCount-1]->setNameAndAgePos();

	if(childrenList[childrenCount-1]->xLeft < screenFarLeft)
		screenFarLeft = childrenList[childrenCount-1]->xLeft;

	for(int i=childrenCount-2;i>chNum;--i)
	{
		childrenList[i]->xLeft = childrenList[i+1]->xRight + childrenSpacing;
		childrenList[i]->xRight = childrenList[i]->xLeft + personWidth;
		childrenList[i]->setNameAndAgePos();

		if(childrenList[i]->xRight > screenFarRight)
			screenFarRight = childrenList[i]->xRight;
	}	

	childrenList[chNum]->xLeft = childrenList[chNum+1]->xRight + childrenSpacing + linkWidth + personWidth;
	childrenList[chNum]->xRight = childrenList[chNum]->xLeft + personWidth;
	childrenList[chNum]->setNameAndAgePos();

	if(childrenList[chNum]->xRight > screenFarRight)
		screenFarRight = childrenList[chNum]->xRight;

	for(int i=chNum-1;i>=0;--i)
	{
		childrenList[i]->xLeft = childrenList[i+1]->xRight + childrenSpacing;
		childrenList[i]->xRight = childrenList[i]->xLeft + personWidth;
		childrenList[i]->setNameAndAgePos();

		if(childrenList[i]->xRight > screenFarRight)
			screenFarRight = childrenList[i]->xRight;
	}	
}

void newPerson(events e);
void setDeath(events e);
void newMarriage(events e);
void setDivorce(events e);



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

void viewManage()
{
	//vector <person*> people;
	//vector <marriage*> marriages;
	//events *eventsList;
	int  peopleCount=0;
	int marriagesCount=0;
	int peopleCounter = 0;
	int marriagesCounter = 0;
	
	int eventsCount; 
	char year[5];
	char *line;
	string lineStr;
	int itemsCount=0;
	char *tmp;

	if(!eventsList)
	{
		ifstream read;							 // to read from data file
		read.open ("events");      // opening data file
		if (!read.is_open())              
			return;

		while (getline(read,lineStr))
			++lineCount;
	
		eventsList = new events[lineCount];
	
		read.clear();
		read.seekg(0);
	

		for(int i=0;i<lineCount;++i)
		{
			getline(read,lineStr);
			line = (char*)lineStr.c_str();
			itemsCount = numOfOccurrences(line,',')-1;
			eventsList[i].details = new char*[itemsCount];
		
			eventsList[i].date = atoi(strtok(line,","));
			eventsList[i].eventType = atoi(strtok(NULL,","));
		
			for(int k=0;k<itemsCount;++k)
			{
				tmp = strtok(NULL,",");
				eventsList[i].details[k] = new char[strlen(tmp)+1];
				strcpy(eventsList[i].details[k],tmp);
			}
		}
		read.clear();
		read.close();
	
		//for(int i=0;i<lineCount;++i)
		//{
		//	if(eventsList[i].eventType == 1)
		//		newPerson(eventsList[i]);
		//	else if(eventsList[i].eventType == 2)
		//		setDeath(eventsList[i]);
		//	else if(eventsList[i].eventType == 3)
		//		newMarriage(eventsList[i]);
		//	else if(eventsList[i].eventType == 4)
		//		setDivorce(eventsList[i]);
		//}
		//eventsJoin();
		currDate = (eventsList[0].date/10000)-3;
	}
	else
	{
		for(int i=doneEvents;i<lineCount;++i)
		{
			glColor3f(white[0],white[1],white[2]);
			glutDrawText(GLUT_BITMAP_HELVETICA_18, itoa(currDate,year,10), (windowWidth/2)-10, 20);

			if(eventsList[i].date/10000 <= currDate)
			{
				if(eventsList[i].eventType == 1)
				{
					newPerson(eventsList[i]);
					++doneEvents;
				}
				else if(eventsList[i].eventType == 2)
				{
					setDeath(eventsList[i]);
					++doneEvents;
				}
				else if(eventsList[i].eventType == 3)
				{
					newMarriage(eventsList[i]);
					++doneEvents;
				}
				else if(eventsList[i].eventType == 4)
				{
					setDivorce(eventsList[i]);		
					++doneEvents;
				}
			}
			else
				break;
		}
		peopleCount = people.size();
		marriagesCount = marriages.size();
		peopleCounter = 0;
		marriagesCounter = 0;

		for(int i=0; i<doneEvents;++i)
		{
			glColor3f(white[0],white[1],white[2]);
			glutDrawText(GLUT_BITMAP_HELVETICA_18, itoa(currDate,year,10), (windowWidth/2)-10, 20);
			if(peopleCounter < peopleCount)
			{
				if(marriagesCounter!=0 && people[peopleCounter]->date < marriages[marriagesCounter]->date)
				{
					if(!people[peopleCounter]->justPartner)
					{
						people[peopleCounter]->display();
					}
				}
				else
				{
					if(!people[peopleCounter]->justPartner)
					{
						people[peopleCounter]->display();
					}
				}
				++peopleCounter;
			}
			else if(marriagesCounter < marriagesCount)
			{
				marriages[marriagesCounter]->display();
				++marriagesCounter;
			}
		}
		if(lastDate > currDate)
			++currDate;
		Sleep(600);	
	}		
		
		//eventsCount = people.size() + marriages.size();
		//for(int i=0;i<eventsCount;++i)
		//{
		//	glColor3f(white[0],white[1],white[2]);
		//	glutDrawText(GLUT_BITMAP_HELVETICA_18, itoa(currDate,year,10), (windowWidth/2)-10, 20);

		//	if(eventsFullList[i].date/10000 <= currDate)
		//	{
		//		if(eventsFullList[i].type == 0)
		//		{
		//			if(!people[eventsFullList[i].index]->justPartner)
		//			{
		//				people[eventsFullList[i].index]->display();
		//			}
		//		}
		//		else
		//		{
		//			marriages[eventsFullList[i].index]->display();
		//		}
		//	}
		//	else
		//		break;
		//}
}
void newPerson(events e)
{
	int L, R, T, B;
	int peopleCount;
	float *c; 

	if(e.details[2][0]=='0' && e.details[3][0]=='0')
	{
		if(rootFarLeft < 0)
		{
			L = (windowWidth/2)-(personWidth/2);
			R = L+personWidth;
			T = 50;
			B = T+personHeight;
			
			if(e.details[1][0] == 'm')
				c = blue;
			else
				c = pink;

			rootFarLeft = L;
			rootFarRight = R;
			screenFarLeft = L;
			rootFarRight = R;
		}
		else
		{
			if(rootFarLeft > windowWidth-rootFarRight)
			{
				R = rootFarLeft - linkWidth;
				L = R - personWidth;
				T = 50;
				B = T+personHeight;

				if(e.details[1][0] == 'm')
					c = blue;
				else
					c = pink;

				rootFarLeft = L;
				if(L < screenFarLeft)
					screenFarLeft = L;
			}
			else
			{
				L = rootFarRight + linkWidth;
				R = L + personWidth;
				T = 50;
				B = T+personHeight;

				if(e.details[1][0] == 'm')
					c = blue;
				else
					c = pink;

				rootFarRight = R;
				if(R > screenFarRight)
					screenFarRight = R;
			}
		}
		
		people.push_back(new person(e.date,L,R,T,B, c, 1000, e.details[0]));
		people[people.size()-1]->root = true;
	}
	else
	{
		peopleCount = people.size();
		for(int i=0;i<peopleCount;++i)
		{
			if(!strcmp(people[i]->name,e.details[2]))
			{
				people[i]->marriageLink->addChild(e);
				break;
			}
			else if(!strcmp(people[i]->name,e.details[3]))
			{
				people[i]->marriageLink->addChild(e);
				break;
			}
		}

		//find parents then call marriage add child
	}
}
void setDeath(events e)
{
	int peopleCount = people.size();
	for(int i=0;i<peopleCount;++i)
	{
		if(!strcmp(people[i]->name, e.details[0]))
		{
			people[i]->dead = true;
			people[i]->deathDate = e.date;
			return;
		}
	}
}
void newMarriage(events e)
{
	int L, R, T, B;
	float *c;	
	int peopleCount = people.size();
	int tChildrenCount = tChildren.size();
	int groom=-1;
	int bride=-1;
	person *g=NULL, *b=NULL;
	float **pos;
	int insertPos;
	int childCount;

	if(peopleCount)
	{
		for(int i=0;i<peopleCount;++i)
		{
			if(!strcmp(people[i]->name, e.details[0]))
			{
				g = people[i];
			}
			else if(!strcmp(people[i]->name, e.details[1]))
			{
				b = people[i];
			}
		}
	}

	if(tChildrenCount)
	{
		for(int i=0;i<tChildrenCount;++i)
		{
			if(!strcmp(tChildren[i]->name, e.details[0]))
			{
				g = tChildren[i];
			}
			else if(!strcmp(tChildren[i]->name, e.details[1]))
			{
				b = tChildren[i];
			}
		}
	}

	if(!g)
	{
		pos = b->getPos();
		if(b->child)
		{
			if(b->childNum == 0)
			{
				L = pos[RIGHT][X_COORD]+(linkWidth)+(WIDTH*2);
				R = L+personWidth;
				T = pos[TOP][Y_COORD]+WIDTH;
				B = T+personHeight;				
			}
			else if(b->childNum == b->parent->marriageLink->childrenList.size()-1)
			{
				L = pos[LEFT][X_COORD]-(linkWidth+personWidth)+WIDTH;
				R = L+personWidth;
				T = pos[TOP][Y_COORD]+WIDTH;
				B = T+personHeight;
			}
			else
			{
				b->parent->marriageLink->makeChildrenSpace(b->childNum);
				pos = b->getPos();
				L = pos[LEFT][X_COORD]-(linkWidth+personWidth)+WIDTH;
				R = L+personWidth;
				T = pos[TOP][Y_COORD]+WIDTH;
				B = T+personHeight;
			}
		}
		else
		{
			L = pos[LEFT][X_COORD]-(linkWidth+personWidth)+WIDTH;
			R = L+personWidth;
			T = pos[TOP][Y_COORD]+WIDTH;
			B = T+personHeight;
		}

		//insertPos = posToInsert(e.date);

		if(b->root)
		{
			if(L > rootFarLeft)
				;//make space (people[bride])
			else
			{
				rootFarLeft = L;
			}
		}

		g = new person(atoi(e.details[2]), L, R, T, B, blue, 1000, e.details[0]);	
		g->justPartner = true;
		people.push_back(g);

	}
	else if(!b)
	{
		pos = g->getPos();

		if(g->child)
		{
			if(g->childNum == 0)
			{
				L = pos[RIGHT][X_COORD]+(linkWidth)+(WIDTH*2);
				R = L+personWidth;
				T = pos[TOP][Y_COORD]+WIDTH;
				B = T+personHeight;								
			}
			else if(g->childNum == g->parent->marriageLink->childrenList.size()-1)
			{
				L = pos[LEFT][X_COORD]-(linkWidth+personWidth)+WIDTH;
				R = L+personWidth;
				T = pos[TOP][Y_COORD]+WIDTH;
				B = T+personHeight;
			}
			else
			{
				g->parent->marriageLink->makeChildrenSpace(g->childNum);
				pos = g->getPos();
				L = pos[LEFT][X_COORD]-(linkWidth+personWidth)+WIDTH;
				R = L+personWidth;
				T = pos[TOP][Y_COORD]+WIDTH;
				B = T+personHeight;
			}
		}
		else
		{
			L = pos[LEFT][X_COORD]-(linkWidth+personWidth)+WIDTH;
			R = L+personWidth;
			T = pos[TOP][Y_COORD]+WIDTH;
			B = T+personHeight;
		}
		
		insertPos = posToInsert(e.date);

		if(g->root)
		{
			if(L > rootFarLeft)
				;//make space (people[bride])
			else
			{
				rootFarLeft = L;
			}
		}
		
		b = new person(atoi(e.details[2]), L, R, T, B, pink, 1000, e.details[1]);
		b->justPartner = true;
		people.push_back(b);
	}
	marriages.push_back(new marriage(e.date, g, b, 1000));
}
void setDivorce(events e)
{
	int marriagesCount = marriages.size();
	for(int i=0;i<marriagesCount;++i)
	{
		if((!strcmp(marriages[i]->side1->name, e.details[0]) && !strcmp(marriages[i]->side2->name, e.details[1])) || (!strcmp(marriages[i]->side1->name, e.details[1]) && !strcmp(marriages[i]->side2->name, e.details[0])))
		{
			marriages[i]->divorce = true;
			marriages[i]->divorceDate = e.date;
			return;
		}
	}
}
int posToInsert(int date)
{
	int peopleCount=people.size();
	int p = -1;

	if(date < people[0]->date)
	{
		p=0;
	}
	else
	{
		for(int i=1;i<peopleCount;++i)
		{
			if(date >= people[i-1]->date && date < people[i]->date)
			{
				p=i;
			}
		}
	}
	return p;
}
void eventsJoin()
{
	int peopleCount = people.size();
	int marriagesCount = marriages.size();
	int eventsCount = peopleCount + marriagesCount;
	int peopleCounter = 0;
	int marriagesCounter = 0;
	
	eventsFullList = new eventsDraw[eventsCount];
	for(int i=0; i<eventsCount;++i)
	{
		if(peopleCounter < peopleCount && people[peopleCounter]->date < marriages[marriagesCounter]->date)
		{
			eventsFullList[i].date = people[peopleCounter]->date;
			eventsFullList[i].type = 0;
			eventsFullList[i].index = peopleCounter;
			++peopleCounter;
		}
		else if(marriagesCounter < marriagesCount)
		{
			eventsFullList[i].date = marriages[marriagesCounter]->date;
			eventsFullList[i].type = 1;
			eventsFullList[i].index = marriagesCounter;
			++marriagesCounter;
		}
	}
}


int numOfOccurrences(char *a, char c)
{
	int arrLen = strlen(a);
	int count=0;
	for(int i=0;i<arrLen;++i)
		if(a[i]==c)
			++count;
	return count;
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	//r1->display();
	//r2->display();
	//m->display();
	viewManage();

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