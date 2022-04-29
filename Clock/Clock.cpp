#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include<time.h>
#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define PI 3.14

GLfloat SCREEN_W = SCREEN_WIDTH, SCREEN_H = SCREEN_HEIGHT;
GLfloat R = 250;
GLfloat sec = 0;
GLfloat min = 0;
GLfloat hour = 0;

void init();//初始化设置
void myreshape(int, int);//窗口变化
void draw_cir();//画表盘
void draw_hour();//画时针
void draw_minute();//画分针
void draw_second();//画秒针
void draw_button();//画纽扣
void myIdle();//获取时间

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glClearColor(1.0, 1.0, 1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
}

void myreshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, w, 0, h);
	SCREEN_W = w;
	SCREEN_H = h;
}

void mydisplaly()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw_cir();
	draw_hour();
	draw_minute();
	draw_second();
	draw_button();
	glutSwapBuffers();
}

void draw_cir()
{
	//底盘
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(SCREEN_W / 2, SCREEN_H / 2);
	for (GLfloat i = 0; i <= 361; i += 1)
	{
		glVertex2f(SCREEN_W / 2 + (R + 20) * cos(i / 360 * 2 * PI), 
			SCREEN_H / 2 + (R + 20) * sin(i / 360 * 2 * PI));
	}
	glEnd();
	//灰色盘
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.2, 0.2, 0.2);		
	glVertex2f(SCREEN_W/2, SCREEN_H/2);
	glColor3f(0.85,0.85,0.85);
	for (GLfloat i = 0; i <= 361; i+=1)
	{	
		glVertex2f(SCREEN_W / 2 + R * cos(i / 360 * 2 * PI), 
			SCREEN_H / 2 + R * sin(i / 360 * 2 * PI));
	}
	glEnd();
	//大刻度
	GLfloat theta = 0;
	glColor3f(0.0, 0.0, 0.0);
	for (int i = 0; i < 4; i++, theta = theta + 90)
	{
		GLfloat x = SCREEN_W / 2 + R * cos((theta / 360) * 2 * PI);
		GLfloat y = SCREEN_H / 2 + R * sin((theta / 360) * 2 * PI);
		glRectf(x - 20, y - 20, x + 20, y + 20);
	}

	//小刻度
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(5);
	glBegin(GL_LINES);
	theta = 30;
	glBegin(GL_LINES);
	for (int i = 0; i < 4; i++,theta +=60)
	{
		GLfloat x = SCREEN_W / 2 + R * cos((theta / 360) * 2 * PI);
		GLfloat y = SCREEN_H / 2 + R * sin((theta / 360) * 2 * PI);
		glVertex2f(x, y);
		x = SCREEN_W / 2 + (R - 30) * cos(theta / 360 * 2 * PI);
		y = SCREEN_H / 2 + (R - 30) * sin(theta / 360 * 2 * PI);
		glVertex2f(x, y);

		theta += 30;

		x = SCREEN_W / 2 + R * cos((theta / 360) * 2 * PI);
		y = SCREEN_H / 2 + R * sin((theta / 360) * 2 * PI);
		glVertex2f(x, y);
		x = SCREEN_W / 2 + (R - 30) * cos(theta / 360 * 2 * PI);
		y = SCREEN_H / 2 + (R - 30) * sin(theta / 360 * 2 * PI);
		glVertex2f(x, y);
	}
	glEnd();
	//横竖线
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(SCREEN_W / 2 - R, SCREEN_H / 2);
	glVertex2f(SCREEN_W / 2 + R, SCREEN_H / 2);
	glVertex2f(SCREEN_W / 2, SCREEN_H / 2 + R);
	glVertex2f(SCREEN_W / 2, SCREEN_H / 2 - R);
	glEnd();

}

void draw_hour()
{
	GLfloat theta = -2 * PI * hour / 12;
	GLfloat L1 = 100;
	GLfloat L2 = 20;
	GLfloat L3 = 30;
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(SCREEN_W / 2 + L1 * cos(theta + PI / 2),
		SCREEN_H / 2 + L1 * sin(theta + PI / 2));
	glVertex2f(SCREEN_W / 2 + L2 * cos(theta),
		SCREEN_H / 2 + L2 * sin(theta));
	glVertex2f(SCREEN_W / 2 + L3 * cos(theta +  3 * PI / 2),
		SCREEN_H / 2 + L3 * sin(theta + 3 * PI / 2));
	glVertex2f(SCREEN_W / 2 + L2 * cos(theta + PI),
		SCREEN_H / 2 + L2 * sin(theta + PI));
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(SCREEN_W / 2 + L1 * cos(theta + PI / 2),
		SCREEN_H / 2 + L1 * sin(theta + PI / 2));
	glVertex2f(SCREEN_W / 2 + L2 * cos(theta),
		SCREEN_H / 2 + L2 * sin(theta));
	glVertex2f(SCREEN_W / 2 + L3 * cos(theta + 3 * PI / 2),
		SCREEN_H / 2 + L3 * sin(theta + 3 * PI / 2));
	glVertex2f(SCREEN_W / 2 + L2 * cos(theta + PI),
		SCREEN_H / 2 + L2 * sin(theta + PI));
	glEnd();

}

void draw_minute()
{
	GLfloat theta = -2 * PI * min / 60;
	GLfloat theta1 = atan((double)(3/2));
	GLfloat L1 = 150;
	GLfloat L2 = sqrt(15*15+10*10);
	GLfloat L3 = 30;
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(SCREEN_W / 2 + L1 * cos(theta +PI / 2),
		SCREEN_H / 2 + L1 * sin(theta +PI / 2));
	glVertex2f(SCREEN_W / 2 + L2 * cos(theta + theta1 + 3*PI / 2),
		SCREEN_H / 2 + L2 * sin(theta + theta1 + 3 * PI / 2));
	glVertex2f(SCREEN_W / 2 + L3 * cos(theta + 3 * PI / 2),
		SCREEN_H / 2 + L3 * sin(theta + 3 * PI / 2));
	glVertex2f(SCREEN_W / 2 + L2 * cos(theta - theta1 + 3 * PI / 2),
		SCREEN_H / 2 + L2 * sin(theta - theta1 + 3 * PI / 2));
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(SCREEN_W / 2 + L1 * cos(theta +PI / 2),
		SCREEN_H / 2 + L1 * sin(theta +PI / 2));
	glVertex2f(SCREEN_W / 2 + L2 * cos(theta + theta1 + 3*PI / 2),
		SCREEN_H / 2 + L2 * sin(theta + theta1 + 3 * PI / 2));
	glVertex2f(SCREEN_W / 2 + L3 * cos(theta + 3 * PI / 2),
		SCREEN_H / 2 + L3 * sin(theta + 3 * PI / 2));
	glVertex2f(SCREEN_W / 2 + L2 * cos(theta - theta1 + 3 * PI / 2),
		SCREEN_H / 2 + L2 * sin(theta - theta1 + 3 * PI / 2));
	glEnd();

}

void draw_second()
{
	GLfloat theta = -2*PI * sec/60;
	GLfloat theta1 = atan((double)(3 / 210));
	GLfloat theta2 = atan((double)(0.1));
	GLfloat L1 = sqrt(3 * 3 + 210 * 210);
	GLfloat L2 = sqrt(3 * 3 + 30 * 30);
	glColor3f(0.8, 0.8, 0.8); 
	glBegin(GL_POLYGON);
	glVertex2f(SCREEN_W / 2 + L1 * cos(theta + theta1 + PI/2),
		SCREEN_H / 2 + L1 * sin(theta + theta1 + PI/2));
	glVertex2f(SCREEN_W / 2 + L1 * cos(theta - theta1 + PI/2),
		SCREEN_H / 2 + L1 * sin(theta - theta1 + PI/2));
	glVertex2f(SCREEN_W / 2 + L2 * cos(theta + theta2 + 3 * PI/2),
		SCREEN_H / 2 + L2 * sin(theta + theta2 + 3 * PI/2));
	glVertex2f(SCREEN_W / 2 + L2 * cos(theta - theta2 + 3 * PI/2),
		SCREEN_H / 2 + L2 * sin(theta - theta2 + 3 * PI/2));
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(SCREEN_W / 2 + L1 * cos(theta + theta1 + PI / 2),
		SCREEN_H / 2 + L1 * sin(theta + theta1 + PI / 2));
	glVertex2f(SCREEN_W / 2 + L1 * cos(theta - theta1 + PI / 2),
		SCREEN_H / 2 + L1 * sin(theta - theta1 + PI / 2));
	glVertex2f(SCREEN_W / 2 + L2 * cos(theta + theta2 + 3 * PI / 2),
		SCREEN_H / 2 + L2 * sin(theta + theta2 + 3 * PI / 2));
	glVertex2f(SCREEN_W / 2 + L2 * cos(theta - theta2 + 3 * PI / 2),
		SCREEN_H / 2 + L2 * sin(theta - theta2 + 3 * PI / 2));	
	glEnd();
}

void draw_button()
{

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(SCREEN_W / 2, SCREEN_H / 2);
	for (GLfloat i = 0; i <= 361; i += 1)
	{
		glVertex2f(SCREEN_W / 2 + 10 * cos(i / 360 * 2 * PI),
			SCREEN_H / 2 + 10 * sin(i / 360 * 2 * PI));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (GLfloat i = 0; i <= 361; i++)
	{
		glVertex2f(SCREEN_W / 2 + 10 * cos(i / 360 * 2 * PI),
			SCREEN_H / 2 + 10 * sin(i / 360 * 2 * PI));
	}
	glEnd();
}

void myIdle()
{
	struct tm localTime;
	time_t curTime;
	time(&curTime);
	localtime_s(&localTime,&curTime);
	sec = localTime.tm_sec;
	min = localTime.tm_min;
	hour = localTime.tm_hour;

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Clock");
	init();
	//注册函数
	glutReshapeFunc(myreshape);
	glutDisplayFunc(mydisplaly);
	glutIdleFunc(myIdle);

	glutMainLoop();
}
