#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include <conio.h>
#include<iostream>
#include <stdio.h>
#include <string.h>
#include<vector>
#include<cmath>
#include"cube.h"
#define ROTATE 9
#define F0 0
#define F1 1
#define F2 2
#define L0 3
#define L1 4
#define L2 5
#define C0 6
#define C1 7
#define C2 8
#define FORMAT 10
using namespace std;
float a = 0.4f;
int mode = ROTATE;
float sx = 0.0, sy = 0.0, sz = 0.0;
float ex = 0.0, ey = 0.0, ez = 0.0;
float vx = 0.0, vy = 0.0, vz = 0.0;
int startx = 0, starty = 0, endx = 0, endy = 0;
int width = 500, height =500;
float curx = 0, cury = 0;
float ssqr = 0.0, esqr = 0.0;
float x_angle = 0.0;
float y_angle = 0.0;
float z_angle = 0.0;
float tempangle = 0;
float dx = 0.0, dy = 0.0;
float incx;
float incy;
float incz;
int f = 0;
int l = 0;
int c = 0;
float tempx = 0;
float tempy = 0;
float tempz = 0;
int rx=0;
int ry=0;
int rz=0;
int temprx = 0;
int tempry = 0;
int temprz = 0;
int tempmode = ROTATE;
bool canmove = true;
float lightx = 1;
float lighty = 1;
float lightz = 1;
vector<Cube> clist;
GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light1_position[] = { lightx, lighty, lightz, 1.0 };
GLfloat light_position[] = { -2,-2, -2, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat spot_direction[] = { -1.0, -1.0, -1.0 };
float cr = 1.0;
float cg = 1.0;
float cb = 1.0;
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightfv(GL_LIGHT1, GL_SPECULAR, mat_specular);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, mat_diffuse);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	for (int i = 0; i < 27; i++)
	{
		Cube c(i,i,0,0,0,0,0,0,0,0,0);
		if (i / 9 == 0)//back
		{
			c.ba = 5;
		}
		if (i / 9 == 2)//front
		{
			c.f = 6;
		}
		//up
		if (i % 9 >= 6)
		{
			c.u = 1;
		}
		//down
		if (i % 9 <= 2)
		{
			c.b = 2;
		}
		//left
		if (i % 3 == 0)
		{
			c.l = 3;
		}
		//right
		if (i % 3 == 2)
		{
			c.r = 4;
		}
		clist.push_back(c);
	}
}

void keydown(unsigned char key, int x, int y)
{
	switch (key)
	{
	//rotate whole
	case 'r':
		tempmode = mode;
		mode = ROTATE;
		
		break;
	//Front and back
	case 'q':
		tempmode = mode;
		mode = F0;
		f = 0;
		if (tempmode != mode&&tempmode!=ROTATE&&tempmode!=FORMAT)
			canmove = false;
		break;
	case 'w':
		tempmode = mode;
		mode = F1;
		f = 1;
		if (tempmode != mode&&tempmode!=ROTATE&&tempmode!=FORMAT)
			canmove = false;
		break;
	case 'e':
		tempmode = mode;
		mode = F2;
		f = 2;
		if (tempmode != mode&&tempmode!=ROTATE&&tempmode!=FORMAT)
			canmove = false;
		break;
	//Left and right
	case 'a':
		tempmode = mode;
		mode = L0;
		l = 0;
		if (tempmode != mode&&tempmode!=ROTATE&&tempmode!=FORMAT)
			canmove = false;
		
		break;
	case 's':
		tempmode = mode;
		mode = L1;
		l = 1;
		if (tempmode != mode&&tempmode!=ROTATE&&tempmode!=FORMAT)
			canmove = false;
		
		break;
	case 'd':
		tempmode = mode;
		mode = L2;
		l = 2;
		if (tempmode != mode&&tempmode!=ROTATE&&tempmode!=FORMAT)
			canmove = false;
		
		break;
	//Clockwise/counterclockwise
	case 'z':
		tempmode = mode;
		mode = C0;
		c = 0;
		if (tempmode != mode&&tempmode!=ROTATE&&tempmode!=FORMAT)
			canmove = false;
		break;
	case 'x':
		tempmode = mode;
		mode = C1;
		c = 1;
		if (tempmode != mode&&tempmode!=ROTATE&&tempmode!=FORMAT)
			canmove = false;
		break;
	case 'c':
		tempmode = mode;
		mode = C2;
		c = 2;
		if (tempmode != mode&&tempmode!=ROTATE&&tempmode!=FORMAT)
			canmove = false;
		break;
	case 'f':
		tempmode = mode;
		mode = 10;
		break;
	case 'u':
		light_position[0] = light_position[0] + 1;
		break;
	case 'i':
		light_position[0] = light_position[0] - 1;
		break;
	case 'j':
		light_position[1] = light_position[1] + 1;
		break;
	case 'k':
		light_position[1] = light_position[1] - 1;
		break;
	case 'n':
		light_position[2] = light_position[2] + 1;
		break;
	case 'm':
		light_position[2] = light_position[2] - 1;
		break;
	default:
		break;
	}
}
void drawCube(int i,int num,float xa,float ya,float za)
{
	glRotatef(xa, 0, 1, 0);
	glRotatef(ya, 1, 0, 0);
	glRotatef(za, 0, 0, 1);
	float x = (i % 3 - 1)*a;
	float y = ((i / 3) % 3 - 1)*a;
	float z = (i / 9 - 1)*a;
		glEnable(GL_DEPTH_TEST);
		glBegin(GL_QUADS);

		{
			switch (clist[i].f)
			{
			case 6:
			case 5:
				glColor3f(1*cr, 0*cg, 0*cb);
				break;
			case 3:
			case 4:
				glColor3f(0 * cr, 1 * cg, 0 * cb);
				break;
			case 1:
			case 2:
				glColor3f(0 * cr, 0 * cg, 1 * cb);
				break;
			case 0:
				glColor3f(0, 0, 0);
				break;

			}
		}
		glVertex3f(x + a / 2, y + a / 2, z + a / 2);//bottom left
		glVertex3f(x - a / 2, y + a / 2, z + a / 2);//bottom right
		glVertex3f(x - a / 2, y - a / 2, z + a / 2);//upper right
		glVertex3f(x + a / 2, y - a / 2, z + a / 2);//upper left 

		
		switch (clist[i].ba)
		{
		case 6:
		case 5:
			glColor3f(1 * cr, 0 * cg, 0 * cb);
			break;
		case 3:
		case 4:
			glColor3f(0 * cr, 1 * cg, 0 * cb);
			break;
		case 1:
		case 2:
			glColor3f(0 * cr, 0 * cg, 1 * cb);
			break;
		case 0:
			glColor3f(0, 0, 0);
			break;

		}
		
		//back
		glVertex3f(x + a / 2, y + a / 2, z - a / 2);
		glVertex3f(x - a / 2, y + a / 2, z - a / 2);
		glVertex3f(x - a / 2, y - a / 2, z - a / 2);
		glVertex3f(x + a / 2, y - a / 2, z - a / 2);
		
		switch (clist[i].l)
		{
		case 6:
		case 5:
			glColor3f(1 * cr, 0 * cg, 0 * cb);
			break;
		case 3:
		case 4:
			glColor3f(0 * cr, 1 * cg, 0 * cb);
			break;
		case 1:
		case 2:
			glColor3f(0 * cr, 0 * cg, 1 * cb);
			break;
		case 0:
			glColor3f(0, 0, 0);
			break;

		}
		
		//left
		glVertex3f(x - a / 2, y + a / 2, z + a / 2);//bottom left 
		glVertex3f(x - a / 2, y + a / 2, z - a / 2);//bottom right
		glVertex3f(x - a / 2, y - a / 2, z - a / 2);//upper right
		glVertex3f(x - a / 2, y - a / 2, z + a / 2);//upper left

		
		switch (clist[i].r)
		{
		case 6:
		case 5:
			glColor3f(1 * cr, 0 * cg, 0 * cb);
			break;
		case 3:
		case 4:
			glColor3f(0 * cr, 1 * cg, 0 * cb);
			break;
		case 1:
		case 2:
			glColor3f(0 * cr, 0 * cg, 1 * cb);
			break;
		case 0:
			glColor3f(0, 0, 0);
			break;

		}
		
		//right
		glVertex3f(x + a / 2, y + a / 2, z + a / 2);//bottom left 
		glVertex3f(x + a / 2, y - a / 2, z + a / 2);//bottom right
		glVertex3f(x + a / 2, y - a / 2, z - a / 2);//upper right
		glVertex3f(x + a / 2, y + a / 2, z - a / 2);//upper left

		
		switch (clist[i].b)
		{
		case 6:
		case 5:
			glColor3f(1 * cr, 0 * cg, 0 * cb);
			break;
		case 3:
		case 4:
			glColor3f(0 * cr, 1 * cg, 0 * cb);
			break;
		case 1:
		case 2:
			glColor3f(0 * cr, 0 * cg, 1 * cb);
			break;
		case 0:
			glColor3f(0, 0, 0);
			break;

		}
		
		//bottom
		glVertex3f(x + a / 2, y - a / 2, z + a / 2);//bottom left 
		glVertex3f(x + a / 2, y - a / 2, z - a / 2);//bottom right
		glVertex3f(x - a / 2, y - a / 2, z - a / 2);//upper right
		glVertex3f(x - a / 2, y - a / 2, z + a / 2);//upper left

		switch (clist[i].u)
		{
		case 6:
		case 5:
			glColor3f(1 * cr, 0 * cg, 0 * cb);
			break;
		case 3:
		case 4:
			glColor3f(0 * cr, 1 * cg, 0 * cb);
			break;
		case 1:
		case 2:
			glColor3f(0 * cr, 0 * cg, 1 * cb);
			break;
		case 0:
			glColor3f(0, 0, 0);
			break;

		}
		
		//up
		glVertex3f(x + a / 2, y + a / 2, z + a / 2);//bottom left 
		glVertex3f(x + a / 2, y + a / 2, z - a / 2);//bottom right
		glVertex3f(x - a / 2, y + a / 2, z - a / 2);//upper right
		glVertex3f(x - a / 2, y + a / 2, z + a / 2);//upper left
		glEnd();
}
	
void display()
{

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// setup the perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
	

	switch (mode)
	{
	case ROTATE:
		for (int i = 0; i < 27; i++)
		{
			glPushMatrix();
			glRotatef(y_angle, 1, 0, 0);
			glRotatef(x_angle, 0, 1, 0);
			glPushMatrix();
			drawCube(i,clist[i].id, clist[i].xa, clist[i].ya, clist[i].za);
			glPopMatrix();
			glPopMatrix();
		}
		break;
	case F0:
	case F1:
	case F2:
	case L0:
	case L1:
	case L2:
	case C0:
	case C1:
	case C2:
		for (int i = 0; i < 27; i++)
		{
			{
				glPushMatrix();
				glColor3f(1, 0, 0);
				glRotatef(y_angle, 1, 0, 0);
				glRotatef(x_angle, 0, 1, 0);
				glPushMatrix();
				drawCube(i,clist[i].id, clist[i].xa, clist[i].ya, clist[i].za);
				glPopMatrix();
				glPopMatrix();
			}
		}
		break;
	case FORMAT:
			
			switch (tempmode)
			{
			case F0:
				temprx = rx;
				tempry = ry;
				temprz = rz;
				rx = round(clist[0].xa / 90);
				ry = round(clist[0].ya / 90);
				rz = round(clist[0].za / 90);
				if (ry < 0)
				{
					for (int j = 0; j < -ry; j++)
					{
						int idt = clist[0].id;
						clist[0].id = clist[6].id;
						clist[6].id = clist[24].id;
						clist[24].id = clist[18].id;
						clist[18].id = idt;
						idt = clist[3].id;
						clist[3].id = clist[15].id;
						clist[15].id = clist[21].id;
						clist[21].id = clist[9].id;
						clist[9].id = idt;

						int lt = clist[0].l;
						clist[0].l = clist[6].l;
						clist[6].l = clist[24].l;
						clist[24].l = clist[18].l;
						clist[18].l = lt;
						lt = clist[3].l;
						clist[3].l = clist[15].l;
						clist[15].l = clist[21].l;
						clist[21].l = clist[9].l;
						clist[9].l = lt;

						int rt = clist[0].r;
						clist[0].r = clist[6].r;
						clist[6].r = clist[24].r;
						clist[24].r = clist[18].r;
						clist[18].r = rt;
						rt = clist[3].r;
						clist[3].r = clist[15].r;
						clist[15].r = clist[21].r;
						clist[21].r = clist[9].r;
						clist[9].r = rt;

						int idc0 = clist[24].u;
						int idc1 = clist[15].u;
						int idc2 = clist[6].u;

						clist[24].u = clist[6].ba;
						clist[15].u = clist[3].ba;
						clist[6].u = clist[0].ba;

						clist[6].ba = clist[0].b;
						clist[3].ba = clist[9].b;
						clist[0].ba = clist[18].b;

						clist[0].b = clist[18].f;
						clist[9].b = clist[21].f;
						clist[18].b = clist[24].f;

						clist[18].f = idc0;
						clist[21].f = idc1;
						clist[24].f = idc2;
					}
				}
				if (ry > 0)
				{
					for (int j = 0; j < ry; j++)
					{
						int idt = clist[6].id;
						clist[6].id = clist[0].id;
						clist[0].id = clist[18].id;
						clist[18].id = clist[24].id;
						clist[24].id = idt;
						idt = clist[3].id;
						clist[3].id = clist[9].id;
						clist[9].id = clist[21].id;
						clist[21].id = clist[15].id;
						clist[15].id = idt;

						int lt = clist[6].l;
						clist[6].l = clist[0].l;
						clist[0].l = clist[18].l;
						clist[18].l = clist[24].l;
						clist[24].l = lt;
						lt = clist[3].l;
						clist[3].l = clist[9].l;
						clist[9].l = clist[21].l;
						clist[21].l = clist[15].l;
						clist[15].l = lt;


						int rt = clist[6].r;
						clist[6].r = clist[0].r;
						clist[0].r = clist[18].r;
						clist[18].r = clist[24].r;
						clist[24].r = rt;
						rt = clist[3].r;
						clist[3].r = clist[9].r;
						clist[9].r = clist[21].r;
						clist[21].r = clist[15].r;
						clist[15].r = rt;

						int idc0 = clist[0].b;
						int idc1 = clist[9].b;
						int idc2 = clist[18].b;
						clist[0].b = clist[6].ba;
						clist[9].b = clist[3].ba;
						clist[18].b = clist[0].ba;

						clist[6].ba = clist[24].u;
						clist[3].ba = clist[15].u;
						clist[0].ba = clist[6].u;

						clist[24].u = clist[18].f;
						clist[15].u = clist[21].f;
						clist[6].u = clist[24].f;

						clist[18].f = idc0;
						clist[21].f = idc1;
						clist[24].f = idc2;
					}
				}
				
				for (int i = 0; i < 27; i++)
				{
					if (i % 3 == 0)
					{
						clist[i].ya = 90 * ry;
						clist[i].xa = 90 * rx;
						clist[i].za = 90 * rz;
					}
					glPushMatrix();
					glColor3f(1, 0, 0);
					glRotatef(y_angle, 1, 0, 0);
					glRotatef(x_angle, 0, 1, 0);
					glPushMatrix();

					drawCube(i, clist[i].id, clist[i].xa, clist[i].ya, clist[i].za);
					glPopMatrix();
					glPopMatrix();
					if (i % 3 == 0)
					{
						clist[i].ya = 0;
					}
				}
				canmove = true;
				break;
				
			case F1:
				temprx = rx;
				tempry = ry;
				temprz = rz;
				rx = round(clist[1].xa / 90);
				ry = round(clist[1].ya / 90);
				rz = round(clist[1].za / 90);
				if (ry < 0)
				{
					for (int j = 0; j < -ry; j++)
					{
						int idt = clist[0+1].id;
						clist[0+1].id = clist[6+1].id;
						clist[6+1].id = clist[24+1].id;
						clist[24+1].id = clist[18+1].id;
						clist[18+1].id = idt;
						idt = clist[3+1].id;
						clist[3+1].id = clist[15+1].id;
						clist[15+1].id = clist[21+1].id;
						clist[21+1].id = clist[9+1].id;
						clist[9+1].id = idt;

						int lt = clist[0 + 1].l;
						clist[0 + 1].l = clist[6 + 1].l;
						clist[6 + 1].l = clist[24 + 1].l;
						clist[24 + 1].l = clist[18 + 1].l;
						clist[18 + 1].l = lt;
						lt = clist[3 + 1].l;
						clist[3 + 1].l = clist[15 + 1].l;
						clist[15 + 1].l = clist[21 + 1].l;
						clist[21 + 1].l = clist[9 + 1].l;
						clist[9 + 1].l = lt;

						int rt = clist[0 + 1].r;
						clist[0 + 1].r = clist[6 + 1].r;
						clist[6 + 1].r = clist[24 + 1].r;
						clist[24 + 1].r = clist[18 + 1].r;
						clist[18 + 1].r = rt;
						rt = clist[3 + 1].r;
						clist[3 + 1].r = clist[15 + 1].r;
						clist[15 + 1].r = clist[21 + 1].r;
						clist[21 + 1].r = clist[9 + 1].r;
						clist[9 + 1].r = rt;

						int idc0 = clist[24+1].u;
						int idc1 = clist[15+1].u;
						int idc2 = clist[6+1].u;

						clist[24+1].u = clist[6+1].ba;
						clist[15+1].u = clist[3+1].ba;
						clist[6+1].u = clist[0+1].ba;

						clist[6+1].ba = clist[0+1].b;
						clist[3+1].ba = clist[9+1].b;
						clist[0+1].ba = clist[18+1].b;

						clist[0+1].b = clist[18+1].f;
						clist[9+1].b = clist[21+1].f;
						clist[18+1].b = clist[24+1].f;

						clist[18+1].f = idc0;
						clist[21+1].f = idc1;
						clist[24+1].f = idc2;
					}
				}
				if (ry > 0)
				{
					for (int j = 0; j < ry; j++)
					{
						int idt = clist[6+1].id;
						clist[6+1].id = clist[0+1].id;
						clist[0+1].id = clist[18+1].id;
						clist[18+1].id = clist[24+1].id;
						clist[24+1].id = idt;
						idt = clist[3+1].id;
						clist[3+1].id = clist[9+1].id;
						clist[9+1].id = clist[21+1].id;
						clist[21+1].id = clist[15+1].id;
						clist[15+1].id = idt;

						int rt = clist[6 + 1].r;
						clist[6 + 1].r = clist[0 + 1].r;
						clist[0 + 1].r = clist[18 + 1].r;
						clist[18 + 1].r = clist[24 + 1].r;
						clist[24 + 1].r = rt;
						rt = clist[3 + 1].r;
						clist[3 + 1].r = clist[9 + 1].r;
						clist[9 + 1].r = clist[21 + 1].r;
						clist[21 + 1].r = clist[15 + 1].r;
						clist[15 + 1].r = rt;

						int lt = clist[6 + 1].l;
						clist[6 + 1].l = clist[0 + 1].l;
						clist[0 + 1].l = clist[18 + 1].l;
						clist[18 + 1].l = clist[24 + 1].l;
						clist[24 + 1].l = lt;
						lt = clist[3 + 1].l;
						clist[3 + 1].l = clist[9 + 1].l;
						clist[9 + 1].l = clist[21 + 1].l;
						clist[21 + 1].l = clist[15 + 1].l;
						clist[15 + 1].l = lt;

						int idc0 = clist[0+1].b;
						int idc1 = clist[9+1].b;
						int idc2 = clist[18+1].b;
						clist[0+1].b = clist[6+1].ba;
						clist[9+1].b = clist[3+1].ba;
						clist[18+1].b = clist[0+1].ba;

						clist[6+1].ba = clist[24+1].u;
						clist[3+1].ba = clist[15+1].u;
						clist[0+1].ba = clist[6+1].u;

						clist[24+1].u = clist[18+1].f;
						clist[15+1].u = clist[21+1].f;
						clist[6+1].u = clist[24+1].f;

						clist[18+1].f = idc0;
						clist[21+1].f = idc1;
						clist[24+1].f = idc2;
					}
				}
				for (int i = 0; i < 27; i++)
				{
					if (i % 3 == 1)
					{
						clist[i].ya = 90 * ry;
						clist[i].xa = 90 * rx;
						clist[i].za = 90 * rz;
					}
					canmove = true;
					glPushMatrix();
					glRotatef(y_angle, 1, 0, 0);
					glRotatef(x_angle, 0, 1, 0);
					glPushMatrix();
					drawCube(i, clist[i].id, clist[i].xa, clist[i].ya, clist[i].za);
					glPopMatrix();
					glPopMatrix();
					if (i % 3 == 1)
					{
						clist[i].ya = 0;
					}

				}
				break;
			case F2:
				temprx = rx;
				tempry = ry;
				temprz = rz;
				rx = round(clist[2].xa / 90);
				ry = round(clist[2].ya / 90);
				rz = round(clist[2].za / 90);
				if (ry < 0)
				{
					for (int j = 0; j < -ry; j++)
					{
						int idt = clist[0+2].id;
						clist[0+2].id = clist[6+2].id;
						clist[6+2].id = clist[24+2].id;
						clist[24+2].id = clist[18+2].id;
						clist[18+2].id = idt;
						idt = clist[3+2].id;
						clist[3+2].id = clist[15+2].id;
						clist[15+2].id = clist[21+2].id;
						clist[21+2].id = clist[9+2].id;
						clist[9+2].id = idt;

						int lt = clist[0 + 2].l;
						clist[0 + 2].l = clist[6 + 2].l;
						clist[6 + 2].l = clist[24 + 2].l;
						clist[24 + 2].l = clist[18 + 2].l;
						clist[18 + 2].l = lt;
						lt = clist[3 + 2].l;
						clist[3 + 2].l = clist[15 + 2].l;
						clist[15 + 2].l = clist[21 + 2].l;
						clist[21 + 2].l = clist[9 + 2].l;
						clist[9 + 2].l = lt;

						int rt = clist[0 + 2].r;
						clist[0 + 2].r = clist[6 + 2].r;
						clist[6 + 2].r = clist[24 + 2].r;
						clist[24 + 2].r = clist[18 + 2].r;
						clist[18 + 2].r = rt;
						rt = clist[3 + 2].r;
						clist[3 + 2].r = clist[15 + 2].r;
						clist[15 + 2].r = clist[21 + 2].r;
						clist[21 + 2].r = clist[9 + 2].r;
						clist[9 + 2].r = rt;

						int idc0 = clist[24+2].u;
						int idc1 = clist[15+2].u;
						int idc2 = clist[6+2].u;

						clist[24+2].u = clist[6+2].ba;
						clist[15+2].u = clist[3+2].ba;
						clist[6+2].u = clist[0+2].ba;

						clist[6+2].ba = clist[0+2].b;
						clist[3+2].ba = clist[9+2].b;
						clist[0+2].ba = clist[18+2].b;

						clist[0+2].b = clist[18+2].f;
						clist[9+2].b = clist[21+2].f;
						clist[18+2].b = clist[24+2].f;

						clist[18+2].f = idc0;
						clist[21+2].f = idc1;
						clist[24+2].f = idc2;
					}
				}
				if (ry > 0)
				{
					for (int j = 0; j < ry; j++)
					{
						int idt = clist[6+2].id;
						clist[6+2].id = clist[0+2].id;
						clist[0+2].id = clist[18+2].id;
						clist[18+2].id = clist[24+2].id;
						clist[24+2].id = idt;
						idt = clist[3+2].id;
						clist[3+2].id = clist[9+2].id;
						clist[9+2].id = clist[21+2].id;
						clist[21+2].id = clist[15+2].id;
						clist[15+2].id = idt;

						int rt = clist[6 + 2].r;
						clist[6 + 2].r = clist[0 + 2].r;
						clist[0 + 2].r = clist[18 + 2].r;
						clist[18 + 2].r = clist[24 + 2].r;
						clist[24 + 2].r = rt;
						rt = clist[3 + 2].r;
						clist[3 + 2].r = clist[9 + 2].r;
						clist[9 + 2].r = clist[21 + 2].r;
						clist[21 + 2].r = clist[15 + 2].r;
						clist[15 + 2].r = rt;

						int lt = clist[6 + 2].l;
						clist[6 + 2].l = clist[0 + 2].l;
						clist[0 + 2].l = clist[18 + 2].l;
						clist[18 + 2].l = clist[24 + 2].l;
						clist[24 + 2].l = lt;
						lt = clist[3 + 2].l;
						clist[3 + 2].l = clist[9 + 2].l;
						clist[9 + 2].l = clist[21 + 2].l;
						clist[21 + 2].l = clist[15 + 2].l;
						clist[15 + 2].l = lt;

						int idc0 = clist[0+2].b;
						int idc1 = clist[9+2].b;
						int idc2 = clist[18+2].b;
						clist[0+2].b = clist[6+2].ba;
						clist[9+2].b = clist[3+2].ba;
						clist[18+2].b = clist[0+2].ba;

						clist[6+2].ba = clist[24+2].u;
						clist[3+2].ba = clist[15+2].u;
						clist[0+2].ba = clist[6+2].u;

						clist[24+2].u = clist[18+2].f;
						clist[15+2].u = clist[21+2].f;
						clist[6+2].u = clist[24+2].f;

						clist[18+2].f = idc0;
						clist[21+2].f = idc1;
						clist[24+2].f = idc2;
					}
				}
				for (int i = 0; i < 27; i++)
				{
					if (i % 3 == 2)
					{
						clist[i].ya = 90 * ry;
						clist[i].xa = 90 * rx;
						clist[i].za = 90 * rz;
					}
					canmove = true;
					glPushMatrix();
					glRotatef(y_angle, 1, 0, 0);
					glRotatef(x_angle, 0, 1, 0);
					glPushMatrix();
					drawCube(i, clist[i].id, clist[i].xa, clist[i].ya, clist[i].za);
					glPopMatrix();
					glPopMatrix();
					if (i % 3 == 2)
					{
						clist[i].ya = 0;
					}
				}
				break;
			case L0:
				temprx = rx;
				tempry = ry;
				temprz = rz;
				rx = round(clist[0].xa / 90);
				ry = round(clist[0].ya / 90);
				rz = round(clist[0].za / 90);
				if (rz < 0)
				{
					for (int j = 0; j < -rz; j++)
					{
						int idt = clist[6].id;
						clist[6].id = clist[0].id;
						clist[0].id = clist[2].id;						
						clist[2].id = clist[8].id;
						clist[8].id = idt;
						idt = clist[3].id;
						clist[3].id = clist[1].id;
						clist[1].id = clist[5].id;
						clist[5].id = clist[7].id;
						clist[7].id = idt;

						int ft = clist[6].f;
						clist[6].f = clist[0].f;
						clist[0].f = clist[2].f;
						clist[2].f = clist[8].f;
						clist[8].f = ft;
						ft = clist[3].f;
						clist[3].f = clist[1].f;
						clist[1].f = clist[5].f;
						clist[5].f = clist[7].f;
						clist[7].f = ft;

						int bat = clist[6].ba;
						clist[6].ba = clist[0].ba;
						clist[0].ba = clist[2].ba;
						clist[2].ba = clist[8].ba;
						clist[8].ba = bat;
						bat = clist[3].ba;
						clist[3].ba = clist[1].ba;
						clist[1].ba = clist[5].ba;
						clist[5].ba = clist[7].ba;
						clist[7].ba = bat;

						int idc0 = clist[6].u;
						int idc1 = clist[7].u;
						int idc2 = clist[8].u;

						clist[6].u = clist[0].l;
						clist[7].u = clist[3].l;
						clist[8].u = clist[6].l;

						clist[0].l = clist[2].b;
						clist[3].l = clist[1].b;
						clist[6].l = clist[0].b;

						clist[0].b = clist[2].r;
						clist[1].b = clist[5].r;
						clist[2].b = clist[8].r;

						clist[8].r = idc0;
						clist[5].r = idc1;
						clist[2].r = idc2;
					}
				}
				if (rz > 0)
				{
					for (int j = 0; j < rz; j++)
					{
						int idt = clist[0].id;
						clist[0].id = clist[6].id;
						clist[6].id = clist[8].id;
						clist[8].id = clist[2].id;
						clist[2].id = idt;
						idt = clist[3].id;
						clist[3].id = clist[7].id;
						clist[7].id = clist[5].id;
						clist[5].id = clist[1].id;
						clist[1].id = idt;

						int bat = clist[0].ba;
						clist[0].ba = clist[6].ba;
						clist[6].ba = clist[8].ba;
						clist[8].ba = clist[2].ba;
						clist[2].ba = bat;
						bat = clist[3].ba;
						clist[3].ba = clist[7].ba;
						clist[7].ba = clist[5].ba;
						clist[5].ba = clist[1].ba;
						clist[1].ba = bat;

						int ft = clist[0].f;
						clist[0].f = clist[6].f;
						clist[6].f = clist[8].f;
						clist[8].f = clist[2].f;
						clist[2].f = ft;
						ft = clist[3].f;
						clist[3].f = clist[7].f;
						clist[7].f = clist[5].f;
						clist[5].f = clist[1].f;
						clist[1].f = ft;
	
						int idc0 = clist[6].u;
						int idc1 = clist[7].u;
						int idc2 = clist[8].u;

						clist[6].u = clist[8].r;
						clist[7].u = clist[5].r;
						clist[8].u = clist[2].r;

						clist[8].r = clist[2].b;
						clist[5].r = clist[1].b;
						clist[2].r = clist[0].b;

						clist[0].b = clist[6].l;
						clist[1].b = clist[3].l;
						clist[2].b = clist[0].l;

						clist[0].l = idc0;
						clist[3].l = idc1;
						clist[6].l = idc2;
					}
				}

				for (int i = 0; i < 27; i++)
				{
					if (i <9)
					{
						clist[i].ya = 90 * ry;
						clist[i].xa = 90 * rx;
						clist[i].za = 90 * rz;
					}
					glPushMatrix();
					glColor3f(1, 0, 0);
					glRotatef(y_angle, 1, 0, 0);
					glRotatef(x_angle, 0, 1, 0);
					glPushMatrix();

					drawCube(i, clist[i].id, clist[i].xa, clist[i].ya, clist[i].za);
					glPopMatrix();
					glPopMatrix();
					if (i <9)
					{
						clist[i].za = 0;
					}
				}
				canmove = true;
				break;
			case L1:
				temprx = rx;
				tempry = ry;
				temprz = rz;
				rx = round(clist[9].xa / 90);
				ry = round(clist[9].ya / 90);
				rz = round(clist[9].za / 90);
				if (rz < 0)
				{
					for (int j = 0; j < -rz; j++)
					{
						int idt = clist[6+9].id;
						clist[6+9].id = clist[0+9].id;
						clist[0+9].id = clist[2+9].id;
						clist[2+9].id = clist[8+9].id;
						clist[8+9].id = idt;
						idt = clist[3+9].id;
						clist[3+9].id = clist[1+9].id;
						clist[1+9].id = clist[5+9].id;
						clist[5+9].id = clist[7+9].id;
						clist[7+9].id = idt;

						int ft = clist[6 + 9].f;
						clist[6 + 9].f = clist[0 + 9].f;
						clist[0 + 9].f = clist[2 + 9].f;
						clist[2 + 9].f = clist[8 + 9].f;
						clist[8 + 9].f = ft;
						ft = clist[3 + 9].f;
						clist[3 + 9].f = clist[1 + 9].f;
						clist[1 + 9].f = clist[5 + 9].f;
						clist[5 + 9].f = clist[7 + 9].f;
						clist[7 + 9].f = ft;

						int bat = clist[6 + 9].ba;
						clist[6 + 9].ba = clist[0 + 9].ba;
						clist[0 + 9].ba = clist[2 + 9].ba;
						clist[2 + 9].ba = clist[8 + 9].ba;
						clist[8 + 9].ba = bat;
						bat = clist[3 + 9].ba;
						clist[3 + 9].ba = clist[1 + 9].ba;
						clist[1 + 9].ba = clist[5 + 9].ba;
						clist[5 + 9].ba = clist[7 + 9].ba;
						clist[7 + 9].ba = bat;

						int idc0 = clist[6+9].u;
						int idc1 = clist[7+9].u;
						int idc2 = clist[8+9].u;

						clist[6+9].u = clist[0+9].l;
						clist[7+9].u = clist[3+9].l;
						clist[8+9].u = clist[6+9].l;

						clist[0+9].l = clist[2+9].b;
						clist[3+9].l = clist[1+9].b;
						clist[6+9].l = clist[0+9].b;

						clist[0+9].b = clist[2+9].r;
						clist[1+9].b = clist[5+9].r;
						clist[2+9].b = clist[8+9].r;

						clist[8+9].r = idc0;
						clist[5+9].r = idc1;
						clist[2+9].r = idc2;
					}
				}
				if (rz > 0)
				{
					for (int j = 0; j < rz; j++)
					{
						int idt = clist[0+9].id;
						clist[0+9].id = clist[6+9].id;
						clist[6+9].id = clist[8+9].id;
						clist[8+9].id = clist[2+9].id;
						clist[2+9].id = idt;
						idt = clist[3+9].id;
						clist[3+9].id = clist[7+9].id;
						clist[7+9].id = clist[5+9].id;
						clist[5+9].id = clist[1+9].id;
						clist[1+9].id = idt;

						int ft = clist[0 + 9].f;
						clist[0 + 9].f = clist[6 + 9].f;
						clist[6 + 9].f = clist[8 + 9].f;
						clist[8 + 9].f = clist[2 + 9].f;
						clist[2 + 9].f = ft;
						ft = clist[3 + 9].f;
						clist[3 + 9].f = clist[7 + 9].f;
						clist[7 + 9].f = clist[5 + 9].f;
						clist[5 + 9].f = clist[1 + 9].f;
						clist[1 + 9].f = ft;

						int bat = clist[0 + 9].ba;
						clist[0 + 9].ba = clist[6 + 9].ba;
						clist[6 + 9].ba = clist[8 + 9].ba;
						clist[8 + 9].ba = clist[2 + 9].ba;
						clist[2 + 9].ba = bat;
						bat = clist[3 + 9].ba;
						clist[3 + 9].ba = clist[7 + 9].ba;
						clist[7 + 9].ba = clist[5 + 9].ba;
						clist[5 + 9].ba = clist[1 + 9].ba;
						clist[1 + 9].ba = bat;

						int idc0 = clist[6+9].u;
						int idc1 = clist[7+9].u;
						int idc2 = clist[8+9].u;

						clist[6+9].u = clist[8+9].r;
						clist[7+9].u = clist[5+9].r;
						clist[8+9].u = clist[2+9].r;

						clist[8+9].r = clist[2+9].b;
						clist[5+9].r = clist[1+9].b;
						clist[2+9].r = clist[0+9].b;

						clist[0+9].b = clist[6+9].l;
						clist[1+9].b = clist[3+9].l;
						clist[2+9].b = clist[0+9].l;

						clist[0+9].l = idc0;
						clist[3+9].l = idc1;
						clist[6+9].l = idc2;
					}
				}

				for (int i = 0; i < 27; i++)
				{
					if (i >=9&&i<18)
					{
						clist[i].ya = 90 * ry;
						clist[i].xa = 90 * rx;
						clist[i].za = 90 * rz;
					}
					glPushMatrix();
					glRotatef(y_angle, 1, 0, 0);
					glRotatef(x_angle, 0, 1, 0);
					glPushMatrix();

					drawCube(i, clist[i].id, clist[i].xa, clist[i].ya, clist[i].za);
					glPopMatrix();
					glPopMatrix();
					if (i >= 9 && i<18)
					{
						clist[i].za = 0;
					}
				}
				canmove = true;
				break;
			case L2:
				temprx = rx;
				tempry = ry;
				temprz = rz;
				rx = round(clist[18].xa / 90);
				ry = round(clist[18].ya / 90);
				rz = round(clist[18].za / 90);
				if (rz < 0)
				{
					for (int j = 0; j < -rz; j++)
					{
						int idt = clist[6+18].id;
						clist[6+18].id = clist[0+18].id;
						clist[0+18].id = clist[2+18].id;
						clist[2+18].id = clist[8+18].id;
						clist[8+18].id = idt;
						idt = clist[3+18].id;
						clist[3+18].id = clist[1+18].id;
						clist[1+18].id = clist[5+18].id;
						clist[5+18].id = clist[7+18].id;
						clist[7+18].id = idt;

						int bat = clist[6 + 18].ba;
						clist[6 + 18].ba = clist[0 + 18].ba;
						clist[0 + 18].ba = clist[2 + 18].ba;
						clist[2 + 18].ba = clist[8 + 18].ba;
						clist[8 + 18].ba = bat;
						bat = clist[3 + 18].ba;
						clist[3 + 18].ba = clist[1 + 18].ba;
						clist[1 + 18].ba = clist[5 + 18].ba;
						clist[5 + 18].ba = clist[7 + 18].ba;
						clist[7 + 18].ba = bat;

						int ft = clist[6 + 18].f;
						clist[6 + 18].f = clist[0 + 18].f;
						clist[0 + 18].f = clist[2 + 18].f;
						clist[2 + 18].f = clist[8 + 18].f;
						clist[8 + 18].f = ft;
						ft = clist[3 + 18].f;
						clist[3 + 18].f = clist[1 + 18].f;
						clist[1 + 18].f = clist[5 + 18].f;
						clist[5 + 18].f = clist[7 + 18].f;
						clist[7 + 18].f = ft;

						int idc0 = clist[6+18].u;
						int idc1 = clist[7+18].u;
						int idc2 = clist[8+18].u;

						clist[6+18].u = clist[0+18].l;
						clist[7+18].u = clist[3+18].l;
						clist[8+18].u = clist[6+18].l;

						clist[0+18].l = clist[2+18].b;
						clist[3+18].l = clist[1+18].b;
						clist[6+18].l = clist[0+18].b;

						clist[0+18].b = clist[2+18].r;
						clist[1+18].b = clist[5+18].r;
						clist[2+18].b = clist[8+18].r;

						clist[8+18].r = idc0;
						clist[5+18].r = idc1;
						clist[2+18].r = idc2;
					}
				}
				if (rz > 0)
				{
					for (int j = 0; j < rz; j++)
					{
						int idt = clist[0+18].id;
						clist[0+18].id = clist[6+18].id;
						clist[6+18].id = clist[8+18].id;
						clist[8+18].id = clist[2+18].id;
						clist[2+18].id = idt;
						idt = clist[3+18].id;
						clist[3+18].id = clist[7+18].id;
						clist[7+18].id = clist[5+18].id;
						clist[5+18].id = clist[1+18].id;
						clist[1+18].id = idt;

						int ft = clist[0 + 18].f;
						clist[0 + 18].f = clist[6 + 18].f;
						clist[6 + 18].f = clist[8 + 18].f;
						clist[8 + 18].f = clist[2 + 18].f;
						clist[2 + 18].f = ft;
						ft = clist[3 + 18].f;
						clist[3 + 18].f = clist[7 + 18].f;
						clist[7 + 18].f = clist[5 + 18].f;
						clist[5 + 18].f = clist[1 + 18].f;
						clist[1 + 18].f = ft;

						int bat = clist[0 + 18].ba;
						clist[0 + 18].ba = clist[6 + 18].ba;
						clist[6 + 18].ba = clist[8 + 18].ba;
						clist[8 + 18].ba = clist[2 + 18].ba;
						clist[2 + 18].ba = bat;
						bat = clist[3 + 18].ba;
						clist[3 + 18].ba = clist[7 + 18].ba;
						clist[7 + 18].ba = clist[5 + 18].ba;
						clist[5 + 18].ba = clist[1 + 18].ba;
						clist[1 + 18].ba = bat;

						int idc0 = clist[6+18].u;
						int idc1 = clist[7+18].u;
						int idc2 = clist[8+18].u;

						clist[6+18].u = clist[8+18].r;
						clist[7+18].u = clist[5+18].r;
						clist[8+18].u = clist[2+18].r;

						clist[8+18].r = clist[2+18].b;
						clist[5+18].r = clist[1+18].b;
						clist[2+18].r = clist[0+18].b;

						clist[0+18].b = clist[6+18].l;
						clist[1+18].b = clist[3+18].l;
						clist[2+18].b = clist[0+18].l;

						clist[0+18].l = idc0;
						clist[3+18].l = idc1;
						clist[6+18].l = idc2;
					}
				}
				for (int i = 0; i < 27; i++)
				{
					if (i >=18)
					{
						clist[i].ya = 90 * ry;
						clist[i].xa = 90 * rx;
						clist[i].za = 90 * rz;
					}
					glPushMatrix();
					glRotatef(y_angle, 1, 0, 0);
					glRotatef(x_angle, 0, 1, 0);
					glPushMatrix();

					drawCube(i, clist[i].id, clist[i].xa, clist[i].ya, clist[i].za);
					glPopMatrix();
					glPopMatrix();
					if (i >= 18)
					{
						clist[i].za = 0;
					}
				}
				canmove = true;
				break;

			case C0:
				temprx = rx;
				tempry = ry;
				temprz = rz;
				rx = round(clist[0].xa / 90);
				ry = round(clist[0].ya / 90);
				rz = round(clist[0].za / 90);
				if (rx > 0)
				{
					for (int j = 0; j < -rx; j++)
					{
						int idt = clist[0].id;
						clist[0].id = clist[2].id;
						clist[2].id = clist[20].id;
						clist[20].id = clist[18].id;
						clist[18].id = idt;
						idt = clist[1].id;
						clist[1].id = clist[11].id;
						clist[11].id = clist[19].id;
						clist[19].id = clist[9].id;
						clist[9].id = idt;

						int bt = clist[0].b;
						clist[0].b = clist[2].b;
						clist[2].b = clist[20].b;
						clist[20].b = clist[18].b;
						clist[18].b = bt;
						bt = clist[1].b;
						clist[1].b = clist[11].b;
						clist[11].b = clist[19].b;
						clist[19].b = clist[9].b;
						clist[9].b = bt;

						int ut = clist[0].u;
						clist[0].u = clist[2].u;
						clist[2].u = clist[20].u;
						clist[20].u = clist[18].u;
						clist[18].u = ut;
						ut = clist[1].u;
						clist[1].u = clist[11].u;
						clist[11].u = clist[19].u;
						clist[19].u = clist[9].u;
						clist[9].u = ut;

						int idc0 = clist[0].ba;
						int idc1 = clist[1].ba;
						int idc2 = clist[2].ba;

						clist[0].ba = clist[2].r;
						clist[1].ba = clist[11].r;
						clist[2].ba = clist[20].r;

						clist[2].r = clist[20].f;
						clist[11].r = clist[19].f;
						clist[20].r = clist[18].f;

						clist[18].f = clist[0].l;
						clist[19].f = clist[9].l;
						clist[20].f = clist[18].l;

						clist[0].l = idc0;
						clist[9].l = idc1;
						clist[18].l = idc2;


					}
				}
				if (rx < 0)
				{
					for (int j = 0; j < rx; j++)
					{
						int idt = clist[0].id;
						clist[0].id = clist[18].id;
						clist[18].id = clist[20].id;
						clist[20].id = clist[2].id;
						clist[2].id = idt;
						idt = clist[9].id;
						clist[9].id = clist[19].id;
						clist[19].id = clist[11].id;
						clist[11].id = clist[1].id;	
						clist[1].id = idt;

						int bt = clist[0].b;
						clist[0].b = clist[18].b;
						clist[18].b = clist[20].b;
						clist[20].b = clist[2].b;
						clist[2].b = bt;
						bt = clist[9].b;
						clist[9].b = clist[19].b;
						clist[19].b = clist[11].b;
						clist[11].b = clist[1].b;
						clist[1].b = bt;

						int ut = clist[0].u;
						clist[0].u = clist[18].u;
						clist[18].u = clist[20].u;
						clist[20].u = clist[2].u;
						clist[2].u = ut;
						ut = clist[9].u;
						clist[9].u = clist[19].u;
						clist[19].u = clist[11].u;
						clist[11].u = clist[1].u;
						clist[1].u = ut;

						int idc0 = clist[0].ba;
						int idc1 = clist[1].ba;
						int idc2 = clist[2].ba;

						clist[0].ba = clist[18].l;
						clist[1].ba = clist[9].l;
						clist[2].ba = clist[0].l;

						clist[0].l = clist[18].f;
						clist[9].l = clist[19].f;
						clist[18].l = clist[20].f;

						clist[18].f = clist[20].r;
						clist[19].f = clist[11].r;
						clist[20].f = clist[2].r;

						clist[2].r = idc0;
						clist[11].r = idc1;
						clist[20].r = idc2;
					}
				}

				for (int i = 0; i < 27; i++)
				{
					if (i % 9 == 0 || i % 9 == 1 || i % 9 == 2)
					{
						clist[i].ya = 90 * ry;
						clist[i].xa = 90 * rx;
						clist[i].za = 90 * rz;
					}
					glPushMatrix();
					glColor3f(1, 0, 0);
					glRotatef(y_angle, 1, 0, 0);
					glRotatef(x_angle, 0, 1, 0);
					glPushMatrix();

					drawCube(i, clist[i].id, clist[i].xa, clist[i].ya, clist[i].za);
					glPopMatrix();
					glPopMatrix();
					if (i % 9 == 0 || i % 9 == 1 || i % 9 == 2)
					{
						clist[i].ya = 0;
					}
				}
				canmove = true;
				break;
			case C1:
				temprx = rx;
				tempry = ry;
				temprz = rz;
				rx = round(clist[3].xa / 90);
				ry = round(clist[3].ya / 90);
				rz = round(clist[3].za / 90);
				if (rx > 0)
				{
					for (int j = 0; j < -rx; j++)
					{


						int idt = clist[0+3].id;
						clist[0+3].id = clist[2+3].id;
						clist[2+3].id = clist[20+3].id;
						clist[20+3].id = clist[18+3].id;
						clist[18+3].id = idt;
						idt = clist[1+3].id;
						clist[1+3].id = clist[11+3].id;
						clist[11+3].id = clist[19+3].id;
						clist[19+3].id = clist[9+3].id;
						clist[9+3].id = idt;

						int bt = clist[0 + 3].b;
						clist[0 + 3].b = clist[2 + 3].b;
						clist[2 + 3].b = clist[20 + 3].b;
						clist[20 + 3].b = clist[18 + 3].b;
						clist[18 + 3].b = bt;
						bt = clist[1 + 3].b;
						clist[1 + 3].b = clist[11 + 3].b;
						clist[11 + 3].b = clist[19 + 3].b;
						clist[19 + 3].b = clist[9 + 3].b;
						clist[9 + 3].b = bt;

						int ut = clist[0 + 3].u;
						clist[0 + 3].u = clist[2 + 3].u;
						clist[2 + 3].u = clist[20 + 3].u;
						clist[20 + 3].u = clist[18 + 3].u;
						clist[18 + 3].u = ut;
						ut = clist[1 + 3].u;
						clist[1 + 3].u = clist[11 + 3].u;
						clist[11 + 3].u = clist[19 + 3].u;
						clist[19 + 3].u = clist[9 + 3].u;
						clist[9 + 3].u = ut;

						int idc0 = clist[0+3].ba;
						int idc1 = clist[1+3].ba;
						int idc2 = clist[2+3].ba;

						clist[0+3].ba = clist[2+3].r;
						clist[1+3].ba = clist[11+3].r;
						clist[2+3].ba = clist[20+3].r;

						clist[2+3].r = clist[20+3].f;
						clist[11+3].r = clist[19+3].f;
						clist[20+3].r = clist[18+3].f;

						clist[18+3].f = clist[0+3].l;
						clist[19+3].f = clist[9+3].l;
						clist[20+3].f = clist[18+3].l;

						clist[0+3].l = idc0;
						clist[9+3].l = idc1;
						clist[18+3].l = idc2;
					}
				}
				if (rx < 0)
				{
					for (int j = 0; j < rx; j++)
					{

						int idt = clist[0+3].id;
						clist[0+3].id = clist[18+3].id;
						clist[18+3].id = clist[20+3].id;
						clist[20+3].id = clist[2+3].id;
						clist[2+3].id = idt;
						idt = clist[9+3].id;
						clist[9+3].id = clist[19+3].id;
						clist[19+3].id = clist[11+3].id;
						clist[11+3].id = clist[1+3].id;
						clist[1+3].id = idt;

						int bt = clist[0 + 3].b;
						clist[0 + 3].b = clist[18 + 3].b;
						clist[18 + 3].b = clist[20 + 3].b;
						clist[20 + 3].b = clist[2 + 3].b;
						clist[2 + 3].b = bt;
						bt = clist[9 + 3].b;
						clist[9 + 3].b = clist[19 + 3].b;
						clist[19 + 3].b = clist[11 + 3].b;
						clist[11 + 3].b = clist[1 + 3].b;
						clist[1 + 3].b = bt;

						int ut = clist[0 + 3].u;
						clist[0 + 3].u = clist[18 + 3].u;
						clist[18 + 3].u = clist[20 + 3].u;
						clist[20 + 3].u = clist[2 + 3].u;
						clist[2 + 3].u = ut;
						ut = clist[9 + 3].u;
						clist[9 + 3].u = clist[19 + 3].u;
						clist[19 + 3].u = clist[11 + 3].u;
						clist[11 + 3].u = clist[1 + 3].u;
						clist[1 + 3].u = ut;

						int idc0 = clist[0+3].ba;
						int idc1 = clist[1+3].ba;
						int idc2 = clist[2+3].ba;

						clist[0+3].ba = clist[18+3].l;
						clist[1+3].ba = clist[9+3].l;
						clist[2+3].ba = clist[0+3].l;

						clist[0+3].l = clist[18+3].f;
						clist[9+3].l = clist[19+3].f;
						clist[18+3].l = clist[20+3].f;

						clist[18+3].f = clist[20+3].r;
						clist[19+3].f = clist[11+3].r;
						clist[20+3].f = clist[2+3].r;

						clist[2+3].r = idc0;
						clist[11+3].r = idc1;
						clist[20+3].r = idc2;
					}
				}

				for (int i = 0; i < 27; i++)
				{
					if (i % 9 == 3 || i % 9 == 4 || i % 9 == 5)
					{
						clist[i].ya = 90 * ry;
						clist[i].xa = 90 * rx;
						clist[i].za = 90 * rz;
					}
					glPushMatrix();
					glColor3f(1, 0, 0);
					glRotatef(y_angle, 1, 0, 0);
					glRotatef(x_angle, 0, 1, 0);
					glPushMatrix();

					drawCube(i, clist[i].id, clist[i].xa, clist[i].ya, clist[i].za);
					glPopMatrix();
					glPopMatrix();
					if (i % 9 == 3 || i % 9 == 4 || i % 9 == 5)
					{
						clist[i].ya = 0;
					}
				}
				canmove = true;
				break;
			case C2:
				temprx = rx;
				tempry = ry;
				temprz = rz;
				rx = round(clist[6].xa / 90);
				ry = round(clist[6].ya / 90);
				rz = round(clist[6].za / 90);
				if (rx > 0)
				{
					for (int j = 0; j < -rx; j++)
					{
						int idt = clist[0+6].id;
						clist[0+6].id = clist[2+6].id;
						clist[2+6].id = clist[20+6].id;
						clist[20+6].id = clist[18+6].id;
						clist[18+6].id = idt;
						idt = clist[1+6].id;
						clist[1+6].id = clist[11+6].id;
						clist[11+6].id = clist[19+6].id;
						clist[19+6].id = clist[9+6].id;
						clist[9+6].id = idt;

						int ut = clist[0 + 6].u;
						clist[0 + 6].u = clist[2 + 6].u;
						clist[2 + 6].u = clist[20 + 6].u;
						clist[20 + 6].u = clist[18 + 6].u;
						clist[18 + 6].u = ut;
						ut = clist[1 + 6].u;
						clist[1 + 6].u = clist[11 + 6].u;
						clist[11 + 6].u = clist[19 + 6].u;
						clist[19 + 6].u = clist[9 + 6].u;
						clist[9 + 6].u = ut;

						int bt = clist[0 + 6].b;
						clist[0 + 6].b = clist[2 + 6].b;
						clist[2 + 6].b = clist[20 + 6].b;
						clist[20 + 6].b = clist[18 + 6].b;
						clist[18 + 6].b = bt;
						bt = clist[1 + 6].b;
						clist[1 + 6].b = clist[11 + 6].b;
						clist[11 + 6].b = clist[19 + 6].b;
						clist[19 + 6].b = clist[9 + 6].b;
						clist[9 + 6].b = bt;

						int idc0 = clist[0+6].ba;
						int idc1 = clist[1+6].ba;
						int idc2 = clist[2+6].ba;

						clist[0+6].ba = clist[2+6].r;
						clist[1+6].ba = clist[11+6].r;
						clist[2+6].ba = clist[20+6].r;

						clist[2+6].r = clist[20+6].f;
						clist[11+6].r = clist[19+6].f;
						clist[20+6].r = clist[18+6].f;

						clist[18+6].f = clist[0+6].l;
						clist[19+6].f = clist[9+6].l;
						clist[20+6].f = clist[18+6].l;

						clist[0+6].l = idc0;
						clist[9+6].l = idc1;
						clist[18+6].l = idc2;
					}
				}
				if (rx < 0)
				{
					for (int j = 0; j < rx; j++)
					{
						int idt = clist[0+6].id;
						clist[0+6].id = clist[18+6].id;
						clist[18+6].id = clist[20+6].id;
						clist[20+6].id = clist[2+6].id;
						clist[2+6].id = idt;
						idt = clist[9+6].id;
						clist[9+6].id = clist[19+6].id;
						clist[19+6].id = clist[11+6].id;
						clist[11+6].id = clist[1+6].id;
						clist[1+6].id = idt;

						int bt = clist[0 + 6].b;
						clist[0 + 6].b = clist[18 + 6].b;
						clist[18 + 6].b = clist[20 + 6].b;
						clist[20 + 6].b = clist[2 + 6].b;
						clist[2 + 6].b = bt;
						bt = clist[9 + 6].b;
						clist[9 + 6].b = clist[19 + 6].b;
						clist[19 + 6].b = clist[11 + 6].b;
						clist[11 + 6].b = clist[1 + 6].b;
						clist[1 + 6].b = bt;

						int ut = clist[0 + 6].u;
						clist[0 + 6].u = clist[18 + 6].u;
						clist[18 + 6].u = clist[20 + 6].u;
						clist[20 + 6].u = clist[2 + 6].u;
						clist[2 + 6].u = ut;
						ut = clist[9 + 6].u;
						clist[9 + 6].u = clist[19 + 6].u;
						clist[19 + 6].u = clist[11 + 6].u;
						clist[11 + 6].u = clist[1 + 6].u;
						clist[1 + 6].u = ut;

						int idc0 = clist[0+6].ba;
						int idc1 = clist[1+6].ba;
						int idc2 = clist[2+6].ba;

						clist[0+6].ba = clist[18+6].l;
						clist[1+6].ba = clist[9+6].l;
						clist[2+6].ba = clist[0+6].l;

						clist[0+6].l = clist[18+6].f;
						clist[9+6].l = clist[19+6].f;
						clist[18+6].l = clist[20+6].f;

						clist[18+6].f = clist[20+6].r;
						clist[19+6].f = clist[11+6].r;
						clist[20+6].f = clist[2+6].r;

						clist[2+6].r = idc0;
						clist[11+6].r = idc1;
						clist[20+6].r = idc2;
					}
				}

				for (int i = 0; i < 27; i++)
				{
					if (i % 9 == 6 || i % 9 ==7 || i % 9 == 8)
					{
						clist[i].ya = 90 * ry;
						clist[i].xa = 90 * rx;
						clist[i].za = 90 * rz;
					}
					glPushMatrix();
					glColor3f(1, 0, 0);
					glRotatef(y_angle, 1, 0, 0);
					glRotatef(x_angle, 0, 1, 0);
					glPushMatrix();

					drawCube(i, clist[i].id, clist[i].xa, clist[i].ya, clist[i].za);
					glPopMatrix();
					glPopMatrix();
					if (i % 9 == 6 || i % 9 == 7 || i % 9 == 8)
					{
						clist[i].ya = 0;
					}
				}
				canmove = true;
				break;
			default:
				break;
			}

		break;
	}
	glutSwapBuffers();
}
void reshape(int w,int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// force the redraw function
	glutPostRedisplay();
}
void onMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN&&(mode != FORMAT))
	{
		startx = x;
		starty = y;
	
	}

}
void onMotion(int mx, int my)
{
	if (mode == ROTATE)
	{
		x_angle += (mx - startx) / 5.0;
		if (x_angle > 180)
		{
			x_angle -= 360;
		}
		else if (x_angle < -180)
		{
			x_angle += 360;
		}
		y_angle += (my - starty) / 5.0;
		if (y_angle > 180)
		{
			y_angle -= 360;
		}
		else if (y_angle < -180)
		{
			y_angle += 360;
		}

	}
	
	if (mode == F0|| mode == F1||mode==F2)
	{
		if (canmove)
		{
			incy = (my - starty) / 3.0;
			tempy = y_angle + incy;
			if (tempy > 180)
			{
				incy -= 360;
			}
			else if (tempy < -180)
			{
				incy += 360;
			}
			for (int i = f; i < 27; i += 3)
			{
				clist[i].ya += incy;
			}

		}
	}
	if (mode == L0 || mode == L1 || mode == L2)
	{
		if (canmove)
		{
			incz = (my - starty) / 3.0;
			tempz = z_angle + incz;
			if (tempz > 180)
			{
				incz -= 360;
			}
			else if (tempz < -180)
			{
				incz += 360;
			}
			for (int i = l * 9; i < l * 9 + 9; i++)
			{
				clist[i].za += incz;
			}

		}
	}
	if (mode == C0 || mode == C1 || mode == C2)
	{
		if (canmove)
		{
			incx = (mx - startx) / 3.0;
			tempx = x_angle + incx;
			if (tempx > 180)
			{
				incx -= 360;
			}
			else if (tempx < -180)
			{
				incx += 360;
			}		
			for (int i = 0; i < 3; i++)
			{
				for (int j = c*3+i*9; j < c*3+3 + i * 9; j++)
				{
					clist[j].xa += incx;
				}

			}

		}
	}
	startx = mx;
	starty = my;

}
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MagicCube");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutKeyboardFunc(keydown);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return (EXIT_SUCCESS);
}