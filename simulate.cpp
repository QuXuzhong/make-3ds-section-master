#include <GL/glut.h>
#include <math.h>
#include "simulate.h"
#include "getplane.h" 
  //做的截面数/2
using namespace std;
extern int SECTION_NUM;
extern Plane3DS section;
extern t3DModel g_3DModel;
int j = 0;
static GLfloat xRot = 0.0f, yRot = 0.0f;
void SetupRC()
{
	//创建黑色背景
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//绘制的点设置为白色
	glColor3f(1.0, 1.0, 1.0);
}
void drawvexel(void)
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);//点阵模式
					   //开始以g_View Mode模式绘制 
					   //GL.gl Point Size(1.5f);          //可以 更改体素大小        
		// 遍历角平面中所有体素 

		list<CVector2_int>::iterator i;
		for (i = section.pVexelOFplane[j].begin(); i != section.pVexelOFplane[j].end(); i++)
		{
			glVertex2f((*i).x, (*i).y);
		}
	glEnd();                // 绘制结束 
	glFlush();
}
void draw3D(void)
{
	//清除窗口
	glClear(GL_COLOR_BUFFER_BIT);
	//保存矩阵状态并进行旋转
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	//glortho(-32,32,-32,32,32,-32);
	//gluLookAt(0,0,-32, 0, 0, 0, 0.2, 0.8, 0);
	glBegin(GL_POINTS);//点阵模式
	list<CVector3_int>::iterator i;
	for(int j=0;j<=section._numofplane;j++)
	for (i =section._3dVexel[j].begin(); i != section._3dVexel[j].end(); i++)
	{
		glVertex3f((*i).x, (*i).y,(*i).z);
	}
	//}	
	glEnd();                // 绘制结束 
	//回复变换
	glPopMatrix();
	//刷新绘图命令
	glutSwapBuffers();
	glFlush();
}
void SpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		xRot -= 1.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 1.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 1.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 1.0f;

	if (key > 356.0f) {
		xRot = 0.0f;
		yRot = 0.0f;
	}

	if (key < -1.0f) {
		xRot = 355.0f;
		yRot = 355.0f;
	}


	glutPostRedisplay();
}
void special(int key, int x, int y)//按方向下键切换到下一平面
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
		
		if (j >= (2 * SECTION_NUM-1))//循环完所有的面后就从头开始
			j = 0;
		else
			j++;
		break;
	case GLUT_KEY_UP://按方向键上切换到上一平面
		if (j <= 0)
				j = 0;
		else
				j--;	
		break;
	}
	glutPostRedisplay();
}
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 20.0f;
	//防止被0所除
	if (h == 0)
		h = 1;
	//根据窗口大小设置视口
	glViewport(0, 0, w, h);
	//重置投影矩阵堆栈
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
	//重置模型视图矩阵堆栈
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity;
}
//使用opengl绘制3d模型的函数
int glmain3d() {
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("simulate of openGL");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(draw3D);
	SetupRC();
	glutMainLoop();
	return 0;
}
//使用opengl绘制各个切面的函数
int glmain() {
	//对窗口的大小进行初始化00
	glutInitWindowSize(800,800);
	//初始化程序展示模式
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("simulate of openGL");
	gluOrtho2D(0, 31, 0, 31);
	//为当前窗口设置函数回调，用于画图
	glutDisplayFunc(drawvexel);
	glutSpecialFunc(special);
	SetupRC();
	glutMainLoop();
	return 0;
}