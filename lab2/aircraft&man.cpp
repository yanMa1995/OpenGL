//Aircraft & Man
//created by yanshengjia & heyongdong & piao
//2015.11.1

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/GLUT.h>
using namespace std;

#define DELAY 12

bool flagView = false;

//飞机模型参数
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static double x_air = 1.0f;
static double y_air = 1.0f;
static double z_air = 1.0f;

//苦力怕
GLfloat crawler_x = 1;
GLfloat crawler_y = 0;
GLfloat crawler_z = -1;
GLint c_vangle = 0;

//人物模型常量
const double BASIC_SIZE = 0.25;
const double STRETCH_SCALE = 0.8;
const double JOINT_SPAN = 1.25;
const double HEAD_RADIUS = 0.1;
const double HAIR_SCALE_X = 0.5;
const double HAIR_SCALE_Y = 0.3;
const double HAIR_SCALE_Z = 0.75;
const double HEAD_SCALE_X = 0.5;
const double HEAD_SCALE_Y = 0.5;
const double HEAD_SCALE_Z = 0.75;
const double THIGH_SCALE_X = 1.4;
const double THIGH_SCALE_Y = 0.4;
const double THIGH_SCALE_Z = 0.4;
const double BODY_SCALE_X = 0.75;
const double BODY_SCALE_Y = 1.25;
const double BODY_SCALE_Z = 0.75;
const double ARM_SCALE_X = 1.3;
const double ARM_SCALE_Y = 0.3;
const double ARM_SCALE_Z = 0.3;

//相对坐标常量
const static double PI = acos(-1.0);
const double INCREMENT = 0.05;	
const int NUM_OF_LINE = 32;
const int BLOCK_SIZE = 1;

//人物模型参数
float head[3] = { 0.0f,BASIC_SIZE * (BODY_SCALE_Y + HEAD_SCALE_Y / 2),0.0f };
float hair[3] = { 0.0f,BASIC_SIZE * (BODY_SCALE_Y + HEAD_SCALE_Y + HAIR_SCALE_Y / 2),0.0f };
float body[3] = { 0.0f,BASIC_SIZE * BODY_SCALE_Y / 2,0.0f };
float thighL[3] = { BASIC_SIZE * THIGH_SCALE_X / 2,0.0f,0.5*BASIC_SIZE * THIGH_SCALE_Z };
float thighR[3] = { BASIC_SIZE * THIGH_SCALE_X / 2,0.0f,-0.5*BASIC_SIZE * THIGH_SCALE_Z };
float armL[3] = { BASIC_SIZE * ARM_SCALE_X / 2,0.0f,BASIC_SIZE * (ARM_SCALE_Z + BODY_SCALE_Z) / 2 };
float armR[3] = { BASIC_SIZE * ARM_SCALE_X / 2,0.0f,-BASIC_SIZE * (ARM_SCALE_Z + BODY_SCALE_Z) / 2 };

//相对坐标参数
bool left_forward = true;
bool right_forward = false;
bool look_from_left = true;
bool man_move = false;
double floor_move_x = 0.0;
double floor_move_y = 0.0;
double view_stretch = 5.0;
double near_sight = 1.0;
double far_sight = 200.0;
double lookatX = 5;
double lookatY = 5;
double lookatZ = 5;
double centerX = 0;
double centerY = 0;
double centerZ = 0;
GLfloat human_x = 0;
GLfloat human_y = 0;
GLfloat human_z = 0;
GLfloat dx = 0;
int scr_w;
int scr_h;
int vangle = 0;
float left_thigh_angle = -60;
float left_calf_angle = 30;
float left_foot_angle = 90;
float right_thigh_angle = -120;
float right_calf_angle = 30;
float right_foot_angle = 90;
float left_arm_angle = -115;
float left_forearm_angle = -30;
float right_arm_angle = -75;
float right_forearm_angle = -15;


// 人
void human()
{
	glPushMatrix();
	glTranslatef(human_x, human_y, human_z);
	glRotatef(vangle, 0, 1, 0);
	
	//Hair
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(hair[0], hair[1], hair[2]);
	glScalef(HAIR_SCALE_X, HAIR_SCALE_Y, HAIR_SCALE_Z);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();

	//Head
	//glColor3f(0.9f, 0.9f, 0.9f);
	glColor3f(139.0 / 255, 115.0 / 255, 85.0 / 255);
	glPushMatrix();
	glTranslatef(head[0], head[1], head[2]);
	glPushMatrix();
	glScalef(HEAD_SCALE_X, HEAD_SCALE_Y, HEAD_SCALE_Z);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();

	// left eye
	glColor3f(0.9f, 0.9f, 0.9f);
	glPushMatrix();
	glTranslatef(-0.05, 0.03, -0.05);
	glScalef(0.2, 0.1, 0.2);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();

	// right eye
	glPushMatrix();
	glTranslatef(-0.05, 0.03, 0.05);
	glScalef(0.2, 0.1, 0.2);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();

	// mouth
	glColor3f(1, 1, 1);
	glTranslatef(-0.03, -0.02, 0);
	glScalef(0.3, 0.1, 0.3);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();

	//Body
	glColor3f(0.0f, 206.0 / 255, 209.0 / 255);
	glPushMatrix();
	glTranslatef(body[0], body[1], body[2]);
	glScalef(BODY_SCALE_X, BODY_SCALE_Y, BODY_SCALE_Z);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();

	//Left leg
	glColor3f(67.0 / 255, 110.0 / 255, 238.0 / 255);
	glPushMatrix();
	
	//Thigh
	glRotatef((GLfloat)left_thigh_angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(thighL[0], thighL[1], thighL[2]);
	glScalef(THIGH_SCALE_X, THIGH_SCALE_Y, THIGH_SCALE_Z);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();


	//Left Arm
	glColor3f(139.0 / 255, 115.0 / 255, 85.0 / 255);
	glPushMatrix();
	glTranslatef(0.0f, BASIC_SIZE * BODY_SCALE_Y, 0.0f);
	glRotatef((GLfloat)left_arm_angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(armL[0], armL[1], armL[2]);
	glScalef(ARM_SCALE_X, ARM_SCALE_Y, ARM_SCALE_Z);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();

	//Right leg
	glColor3f(67.0 / 255, 110.0 / 255, 238.0 / 255);
	glPushMatrix();
	glRotatef((GLfloat)right_thigh_angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(thighR[0], thighR[1], thighR[2]);
	glScalef(THIGH_SCALE_X, THIGH_SCALE_Y, THIGH_SCALE_Z);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();

	//Right Arm
	glColor3f(139.0 / 255, 115.0 / 255, 85.0 / 255);
	glPushMatrix();
	glTranslatef(0.0f, BASIC_SIZE * BODY_SCALE_Y, 0.0f);
	//Arm
	glRotatef((GLfloat)right_arm_angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(armR[0], armR[1], armR[2]);
	glScalef(ARM_SCALE_X, ARM_SCALE_Y, ARM_SCALE_Z);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();

	glPopMatrix();
}


// 飞机
void plane()
{
	glPushMatrix();
	glTranslatef(x_air, y_air, z_air);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);  // 绕X轴旋转
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  // 绕Y轴旋转
	
	// 飞机
	glBegin(GL_TRIANGLES);
	// 机头 
	glColor3f(0.79f, 0.08f, 0.14f);  // 深红
	glVertex3f(-15.0f / 100, 0.0f / 100, 30.0f / 100);
	glVertex3f(15.0f / 100, 0.0f / 100, 30.0f / 100);
	glVertex3f(0.0f / 100, 0.0f / 100, 60.0f / 100);

	glColor3f(0.97f, 0.29f, 0.30f);  // 粉红
	glVertex3f(-15.0f / 100, 0.0f / 100, 30.0f / 100);
	glVertex3f(0.0f / 100, 0.0f / 100, 60.0f / 100);
	glVertex3f(0.0f / 100, 15.0f / 100, 30.0f / 100);

	glColor3f(1.0f, 0.51f, 0.0f);  // 橘黄
	glVertex3f(0.0f / 100, 0.0f / 100, 60.0f / 100);
	glVertex3f(15.0f / 100, 0.0f / 100, 30.0f / 100);
	glVertex3f(0.0f / 100, 15.0f / 100, 30.0f / 100);

	// 机身
	glColor3f(1.0f, 1.0f, 0.0f);  // 明黄
	glVertex3f(-15.0f / 100, 0.0f / 100, 30.0f / 100);
	glVertex3f(0.0f / 100, 15.0f / 100, 30.0f / 100);
	glVertex3f(0.0f / 100, 0.0f / 100, -53.0f / 100);

	glColor3f(1.0f, 1.0f, 0.0f);  // 明黄
	glVertex3f(0.0f / 100, 15.0f / 100, 30.0f / 100);
	glVertex3f(15.0f / 100, 0.0f / 100, 30.0f / 100);
	glVertex3f(0.0f / 100, 0.0f / 100, -53.0f / 100);

	glColor3f(0.73f, 0.0f, 0.57f);  // 紫色
	glVertex3f(15.0f / 100, 0.0f / 100, 30.0f / 100);
	glVertex3f(-15.0f / 100, 0.0f / 100, 30.0f / 100);
	glVertex3f(0.0f / 100, 0.0f / 100, -53.0f / 100);

	// 机尾巴
	glColor3f(0.79f, 0.08f, 0.14f);  // 深红
	glVertex3f(0.0f / 100, 0.0f / 100, -53.0f / 100);
	glVertex3f(0.0f / 100, 0.0f / 100, -70.0f / 100);
	glVertex3f(0.0f / 100, 15.0f / 100, -70.0f / 100);

	glColor3f(0.97f, 0.29f, 0.30f);  // 粉红
	glVertex3f(-15.0f / 100, 0.0f / 100, -70.0f / 100);
	glVertex3f(0.0f / 100, 0.0f / 100, -53.0f / 100);
	glVertex3f(0.0f / 100, 0.0f / 100, -70.0f / 100);

	glColor3f(1.0f, 0.51f, 0.0f);  // 橘黄
	glVertex3f(15.0f / 100, 0.0f / 100, -70.0f / 100);
	glVertex3f(0.0f / 100, 0.0f / 100, -70.0f / 100);
	glVertex3f(0.0f / 100, 0.0f / 100, -53.0f / 100);

	// 由于背面被消除，背面再画一次
	glColor3f(0.73f / 100, 0.0f / 100, 0.57f);  // 紫色
	glVertex3f(0.0f / 100, 0.0f / 100, -70.0f / 100);
	glVertex3f(0.0f / 100, 0.0f / 100, -53.0f / 100);
	glVertex3f(0.0f / 100, 15.0f / 100, -70.0f / 100);


	glColor3f(1.0f, 1.0f, 0.0f);  // 明黄
	glVertex3f(0.0f / 100, 0.0f / 100, -53.0f / 100);
	glVertex3f(-15.0f / 100, 0.0f / 100, -70.0f / 100);
	glVertex3f(0.0f / 100, 0.0f / 100, -70.0f / 100);

	glColor3f(1.0f, 1.0f, 0.0f);  // 明黄
	glVertex3f(0.0f / 100, 0.0f / 100, -70.0f / 100);
	glVertex3f(15.0f / 100, 0.0f / 100, -70.0f / 100);
	glVertex3f(0.0f / 100, 0.0f / 100, -53.0f / 100);

	// 机翼下侧面
	glColor3ub(158, 196, 246 / 100);  // 紫蓝
	glVertex3f(0.0f / 100, 2.0f / 100, 27.0f / 100);
	glVertex3f(-60.0f / 100, 2.0f / 100, -8.0f / 100);
	glVertex3f(60.0f / 100, 2.0f / 100, -8.0f / 100);

	// 左翼
	glColor3f(0.2f, 0.08f, 0.69f);  // 深蓝
	glVertex3f(60.0f / 100, 2.0f / 100, -8.0f / 100);
	glVertex3f(0.0f / 100, 7.0f / 100, -8.0f / 100);
	glVertex3f(0.0f / 100, 2.0f / 100, 27.0f / 100);

	// 右翼 
	glColor3f(0.2f, 0.08f, 0.69f);  // 深蓝
	glVertex3f(0.0f / 100, 2.0f / 100, 27.0f / 100);
	glVertex3f(0.0f / 100, 7.0f / 100, -8.0f / 100);
	glVertex3f(-60.0f / 100, 2.0f / 100, -8.0f / 100);

	// 机翼后侧面
	glColor3ub(192, 192, 192);
	glVertex3f(60.0f / 100, 2.0f / 100, -8.0f / 100);
	glVertex3f(-60.0f / 100, 2.0f / 100, -8.0f / 100);
	glVertex3f(0.0f / 100, 7.0f / 100, -8.0f / 100);

	glEnd();


	glPopMatrix();
}

// 苦力怕
void crawler()
{
	glPushMatrix();
	glRotatef(c_vangle, 0, 1, 0);
	glTranslatef(crawler_x, crawler_y, crawler_z);

	//head
	glColor3f(0.0f, 130.0/255, 0.0f);
	glPushMatrix();
	glTranslatef(hair[0], hair[1], hair[2]);
	glScalef(1, 1, 1);
	glutSolidCube(BASIC_SIZE);

	// left eye
	glColor3f(0,0,0);
	glPushMatrix();
	glTranslatef(-0.1, 0.03, -0.05);
	glScalef(0.3, 0.3, 0.3);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();

	// right eye
	glPushMatrix();
	glTranslatef(-0.1, 0.03, 0.05);
	glScalef(0.3, 0.3, 0.3);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();

	// mouth
	glColor3f(0, 0, 0);
	glTranslatef(-0.1, -0.1, 0);
	glScalef(0.3, 0.3, 0.3);
	glutSolidCube(BASIC_SIZE);

	glPopMatrix();

	//body
	glColor3f(0.0f, 130.0 / 255, 0.0f);
	glPushMatrix();
	glTranslatef(hair[0], hair[1]-0.3, hair[2]);
	glScalef(0.7, 3, 0.7);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();

	//leg
	glPushMatrix();
	glTranslatef(hair[0], hair[1]-0.7, hair[2]);
	glScalef(1, 1, 1);
	glutSolidCube(BASIC_SIZE);
	glPopMatrix();

	glPopMatrix();
}


// 地面
void floor()
{
	if (man_move)
	{
		floor_move_x += INCREMENT * cos((double)vangle / 180.0 * PI);
		x_air += INCREMENT * cos((double)vangle / 180.0 * PI);
		floor_move_y += INCREMENT * sin((double)vangle / 180.0 * PI);
		y_air += INCREMENT * sin((double)vangle / 180.0 * PI);
		if (floor_move_x >= BLOCK_SIZE)
		{
			floor_move_x -= BLOCK_SIZE;
		}	
		else if (floor_move_x <= -BLOCK_SIZE) {
			floor_move_x += BLOCK_SIZE;
		}
		if (floor_move_y >= BLOCK_SIZE) {
			floor_move_y -= BLOCK_SIZE;
		}
		else if (floor_move_y <= -BLOCK_SIZE)
		{
			floor_move_y += BLOCK_SIZE;
		}
		glPushMatrix();
		glTranslatef(centerX, centerY, centerZ);
		glPushMatrix();
		glRotatef(vangle, 0.0f, 1.0f, 0.0f);
	}
}


// 显示回调函数
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.3f, 1.0f, 0.3f);
	//Floor

	for (int i = 0; i < NUM_OF_LINE * 2; i++)
	{
		glBegin(GL_LINES);
		glVertex3f((NUM_OF_LINE - i) * BLOCK_SIZE + floor_move_x, -BASIC_SIZE * (BODY_SCALE_Y + THIGH_SCALE_X) / 2, NUM_OF_LINE * BLOCK_SIZE);
		glVertex3f((NUM_OF_LINE - i) * BLOCK_SIZE + floor_move_x, -BASIC_SIZE * (BODY_SCALE_Y + THIGH_SCALE_X) / 2, -NUM_OF_LINE * BLOCK_SIZE);
		glVertex3f(NUM_OF_LINE * BLOCK_SIZE, -BASIC_SIZE * (BODY_SCALE_Y + THIGH_SCALE_X) / 2, (NUM_OF_LINE - i) * BLOCK_SIZE - floor_move_y);
		glVertex3f(-NUM_OF_LINE * BLOCK_SIZE, -BASIC_SIZE * (BODY_SCALE_Y + THIGH_SCALE_X) / 2, (NUM_OF_LINE - i) * BLOCK_SIZE - floor_move_y);
		glEnd();
	}

	//floor();
	plane();
	human();
	crawler();
	
	glutSwapBuffers();
}


// 肢体摆动
void refresh(int c)
{
	centerY = -(1 - sin(-left_thigh_angle / 180.0 * PI)) * BASIC_SIZE * THIGH_SCALE_X;
	if (man_move)
	{
		if (left_thigh_angle < -120)
		{
			left_forward = false;
		}
		else if (left_thigh_angle > -60)
		{
			left_forward = true;
		}
		if (right_thigh_angle < -120)
		{
			right_forward = false;
		}
		else if (right_thigh_angle > -60)
		{
			right_forward = true;
		}
		if (left_forward)
		{
			left_thigh_angle--;
			if (left_thigh_angle < -90)
				left_calf_angle++;
			else left_calf_angle--;
			left_arm_angle += 1.0;
			left_forearm_angle += 0.5;
		}
		else
		{
			left_thigh_angle++;
			if (left_thigh_angle <= -180)
				left_calf_angle--;
			else left_calf_angle++;
			left_arm_angle -= 1.0;
			left_forearm_angle -= 0.5;
		}
		if (right_forward)
		{
			right_thigh_angle--;
			if (right_thigh_angle < -90)
				right_calf_angle++;
			else right_calf_angle--;
			right_arm_angle += 1.0;
			right_forearm_angle += 0.5;
		}
		else
		{
			right_thigh_angle++;
			if (right_thigh_angle <= -90)
				right_calf_angle--;
			else right_calf_angle++;
			right_arm_angle -= 1.0;
			right_forearm_angle -= 0.5;
		}
		
	}
	else {
		right_arm_angle = -90;
		left_arm_angle = -90;
		right_thigh_angle = -90;
		left_thigh_angle = -90;
	}
	glutTimerFunc(DELAY, refresh, 0);	// 注册一个回调函数,当指定时间值到达后,由GLUT调用注册的函数一次
	glutPostRedisplay();	// 重绘
}

// 窗口拉伸 图形保持不变
void reshape(int w, int h)
{
	scr_w = w;
	scr_h = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, (GLfloat)scr_w / (GLfloat)scr_h, near_sight * view_stretch, far_sight * view_stretch);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//切换视角
	//gluLookAt(lookatX,lookatY,lookatZ,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
	gluLookAt(lookatX, lookatY, lookatZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

// 鼠标操作
void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			// 左键选中 视角转换
			flagView = true;
			
			// 视角放大收缩
			if (near_sight * view_stretch > 0.5)
				view_stretch *= STRETCH_SCALE;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(75.0, (GLfloat)scr_w / (GLfloat)scr_h, near_sight * view_stretch, far_sight * view_stretch);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(lookatX * view_stretch, lookatY * view_stretch, lookatZ * view_stretch, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			// // 视角减小收缩
			if (far_sight * view_stretch < 1000.0)
				view_stretch /= STRETCH_SCALE;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(75.0, (GLfloat)scr_w / (GLfloat)scr_h, near_sight * view_stretch, far_sight * view_stretch);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(lookatX * view_stretch, lookatY * view_stretch, lookatZ * view_stretch, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		}
		break;
	}
}

// 鼠标移动回调函数
void motion(int x, int y)
{
	//glClear(GL_COLOR_BUFFER_BIT);
    
    if(flagView == true)
    {
        lookatX = -1.5 + (double)x / scr_w * 3;
		lookatY = 1 - (double)y / scr_h * 2;
		if (look_from_left)
			lookatZ = sqrt(2.25 - lookatX * lookatX);
		else 	lookatZ = -sqrt(2.25 - lookatX * lookatX);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(lookatX * view_stretch, lookatY * view_stretch, lookatZ * view_stretch, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    }
  
}

// 当鼠标在窗口中移动时的回调函数
void passiveMotion(int x, int y)
{
	lookatX = -1.5 + (double)x / scr_w * 3;
	lookatY = 1 - (double)y / scr_h * 2;
	if (look_from_left)
		lookatZ = sqrt(2.25 - lookatX * lookatX);
	else lookatZ = -sqrt(2.25 - lookatX * lookatX);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(lookatX * view_stretch, lookatY * view_stretch, lookatZ * view_stretch, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}


// 特殊按键操作（不能用ASCII码表示）
void specialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		// 飞机抬头
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		// 飞机低头
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
	    // 飞机左转
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		// 飞机右转
		yRot += 5.0f;

	if (key > 356.0f)
		xRot = 0.0f;

	if (key < -1.0f)
		xRot = 355.0f;

	if (key > 356.0f)
		yRot = 0.0f;

	if (key < -1.0f)
		yRot = 355.0f;

	// 刷新窗口
	glutPostRedisplay();
}


// 按键操作
void control(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ',':
		// 视角放大
		if (near_sight * view_stretch > 0.5)	view_stretch *= STRETCH_SCALE;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(75.0, (GLfloat)scr_w / (GLfloat)scr_h, near_sight * view_stretch, far_sight * view_stretch);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(lookatX * view_stretch, lookatY * view_stretch, lookatZ * view_stretch, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		break;
	case '.':
		// 视角缩小
		if (far_sight * view_stretch < 1000.0)	view_stretch /= STRETCH_SCALE;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(75.0, (GLfloat)scr_w / (GLfloat)scr_h, near_sight * view_stretch, far_sight * view_stretch);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(lookatX * view_stretch, lookatY * view_stretch, lookatZ * view_stretch, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		break;
	case 'a':	
		// 人左转
		man_move = true;
		vangle = (vangle + 3) % 360;
		break;
	case 'd':	
		// 人右转
		man_move = true;
		vangle = (vangle - 3) % 360;
		break;
	case 'w':	
		// 人前进
		man_move = true;
		human_x -= INCREMENT * cos((double)vangle / 180.0 * PI);
		human_z += INCREMENT * sin((double)vangle / 180.0 * PI);
		break;
	case 's':	
		// 人后退
		human_x += INCREMENT * cos((double)vangle / 180.0 * PI);
		human_z -= INCREMENT * sin((double)vangle / 180.0 * PI);
		man_move = true;
		break;
	case 'j':
		// 飞机沿X轴负向移动
		x_air -= 0.05;
		break;
	case 'l':
		// 飞机沿X轴正向移动
		x_air += 0.05;
		break;
	case 'i':
		// 飞机沿Z轴负向移动
		z_air -= 0.05;
		break;
	case 'k':
		// 飞机沿Z轴正向移动
		z_air += 0.05;
		break;
	case 'o':
		// 飞机沿Y轴正向移动
		y_air += 0.05;
		break;
	case 'p':
		// 飞机沿Y轴负向移动
		y_air -= 0.05;
		break;
	case 'r':
		// 飞机复位
		x_air = 1.0;
		y_air = 1.0;
		z_air = 1.0;
		break;
	case 'z':
		// 苦力怕绕世界坐标系Y轴逆时针转
		c_vangle = (c_vangle + 3) % 360;
		break;
	case 'x':
		// 苦力怕绕世界坐标系Y轴顺时针转
		c_vangle = (c_vangle - 3) % 360;
		break;
	case 'c':
		// 苦力怕沿世界坐标系X轴正向移动
		crawler_x += INCREMENT;
		break;
	case 'v':
		// 苦力怕沿世界坐标系Y轴正向移动
		crawler_x -= INCREMENT;
		break;
	case 27:
		// 退出
		exit(0);
	default:
		break;
	}

}

// 释放普通按键的回调函数
void controlup(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		man_move = false;
		break;
	case 's':
		man_move = false;
		break;
	case 'a':
		man_move = false;
		break;
	case 'd':
		man_move = false;
		break;
	}
}


//菜单函数
void menu(int id)
{
    switch(id)
    {
        case 1:
            //各位置复位
			x_air = 1.0;
			y_air = 1.0;
			z_air = 1.0;
            break;
            
        case 2:
            exit(0);
            break;
    }
    glutPostRedisplay();
}


// 初始化着色环境
void init()
{
	//glClearColor(1.0f, 1.0f, 1.0f, 0.0f);		// 白色背景
	glClearColor(0.745f, 1.0f, 0.973f, 0.0f);   // 天蓝色背景

	glShadeModel(GL_FLAT);
	
	// 打光
	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // 明亮的白光
	glEnable(GL_DEPTH_TEST);    // 影藏面消除
	glEnable(GL_CULL_FACE);        // Do not calculate inside of jet
	glFrontFace(GL_CCW);        // Counter clock-wise polygons face out

	glEnable(GL_COLOR_MATERIAL);  // 开启颜色追踪
	glEnable(GL_LIGHTING);

	 //设置混色函数取得半透明效果
	 //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	 //glShadeModel(GL_SMOOTH);
	 //glEnable(GL_BLEND);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight); // 设置光照模型

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  // 设置颜色追踪的材料属性以及多边形的面
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	// 设置程序的窗口大小
  	GLint windowWidth = 800;
  	GLint windowHeight = 600;
  	glutInitWindowSize(windowWidth, windowHeight);
	
	// 获取屏幕的宽和高
  	GLint SCREEN_WIDTH=glutGet(GLUT_SCREEN_WIDTH);    
  	GLint SCREEN_HEIGHT=glutGet(GLUT_SCREEN_HEIGHT);  
  
  	glutInitWindowPosition((SCREEN_WIDTH-windowWidth)/2,(SCREEN_HEIGHT-windowHeight)/2);
  
    glutCreateWindow("Aircraft & Man");
	
	// // 设置弹出式菜单
    // glutCreateMenu(menu);
    // glutAddMenuEntry("revoke", 1);
    // glutAddMenuEntry("quit", 2);
    // glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	init();
	refresh(0);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutMouseFunc(mouse);
	glutMotionFunc(motion);  
	//glutPassiveMotionFunc(passiveMotion);
	
	glutSpecialFunc(specialKeys);
	
	glutKeyboardUpFunc(controlup);
	glutKeyboardFunc(control);
	//glutIdleFunc(idle);

	glutMainLoop(); // 进入GLUT事件处理循环，让所有的与“事件”有关的函数调用无限循环。在一个GLUT程序中，这个例程被调用一次。一旦被调用，这个程序将永远不会返回 。它将调用必要的任何已注册的回调。
	return 0;
}