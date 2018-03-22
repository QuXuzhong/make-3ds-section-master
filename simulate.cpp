#include <GL/glut.h>
#include <math.h>
#include "simulate.h"
#include "getplane.h" 
  //���Ľ�����/2
using namespace std;
extern int SECTION_NUM;
extern Plane3DS section;
extern t3DModel g_3DModel;
int j = 0;
static GLfloat xRot = 0.0f, yRot = 0.0f;
void SetupRC()
{
	//������ɫ����
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//���Ƶĵ�����Ϊ��ɫ
	glColor3f(1.0, 1.0, 1.0);
}
void drawvexel(void)
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);//����ģʽ
					   //��ʼ��g_View Modeģʽ���� 
					   //GL.gl Point Size(1.5f);          //���� �������ش�С        
		// ������ƽ������������ 

		list<CVector2_int>::iterator i;
		for (i = section.pVexelOFplane[j].begin(); i != section.pVexelOFplane[j].end(); i++)
		{
			glVertex2f((*i).x, (*i).y);
		}
	glEnd();                // ���ƽ��� 
	glFlush();
}
void draw3D(void)
{
	//�������
	glClear(GL_COLOR_BUFFER_BIT);
	//�������״̬��������ת
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	//glortho(-32,32,-32,32,32,-32);
	//gluLookAt(0,0,-32, 0, 0, 0, 0.2, 0.8, 0);
	glBegin(GL_POINTS);//����ģʽ
	list<CVector3_int>::iterator i;
	for(int j=0;j<=section._numofplane;j++)
	for (i =section._3dVexel[j].begin(); i != section._3dVexel[j].end(); i++)
	{
		glVertex3f((*i).x, (*i).y,(*i).z);
	}
	//}	
	glEnd();                // ���ƽ��� 
	//�ظ��任
	glPopMatrix();
	//ˢ�»�ͼ����
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
void special(int key, int x, int y)//�������¼��л�����һƽ��
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
		
		if (j >= (2 * SECTION_NUM-1))//ѭ�������е����ʹ�ͷ��ʼ
			j = 0;
		else
			j++;
		break;
	case GLUT_KEY_UP://����������л�����һƽ��
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
	//��ֹ��0����
	if (h == 0)
		h = 1;
	//���ݴ��ڴ�С�����ӿ�
	glViewport(0, 0, w, h);
	//����ͶӰ�����ջ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
	//����ģ����ͼ�����ջ
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity;
}
//ʹ��opengl����3dģ�͵ĺ���
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
//ʹ��opengl���Ƹ�������ĺ���
int glmain() {
	//�Դ��ڵĴ�С���г�ʼ��00
	glutInitWindowSize(800,800);
	//��ʼ������չʾģʽ
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("simulate of openGL");
	gluOrtho2D(0, 31, 0, 31);
	//Ϊ��ǰ�������ú����ص������ڻ�ͼ
	glutDisplayFunc(drawvexel);
	glutSpecialFunc(special);
	SetupRC();
	glutMainLoop();
	return 0;
}