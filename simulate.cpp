#include <GL/glut.h>
#include <math.h>
#include "simulate.h"
#include "getplane.h" 
  //���Ľ�����/2
using namespace std;
extern int SECTION_NUM;
extern Plane3DS section;
	int j = 1;
void drawvexel(void)
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);//����ģʽ
					   //��ʼ��g_View Modeģʽ���� 
					   //GL.gl Point Size(1.5f);          //���� �������ش�С        
					   // �������еĽ�ƽ�� 
	//for (int j = 0; j < 2 * section._numofplane; j++)
	//{
		// ������ƽ������������ 

		float sita = PI / float(section._numofplane)*j;
		float K = tan(sita);
		list<CVector2_int>::iterator i;
		for (i = section.pVexelOFplane[j].begin(); i != section.pVexelOFplane[j].end(); i++)
		{
			int z = int(K*((*i).x));
			glVertex2f((*i).x, (*i).y);
		}
	//}	
	glEnd();                // ���ƽ��� 
	glFlush();

}

void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
		j++;
		if (j >= 2*SECTION_NUM)
		{
			j = 1;
		}
		glutPostRedisplay();
		break;
	}
}
int glmain() {

	//��ʼ��GLUT library

	//�Դ��ڵĴ�С���г�ʼ��00
	glutInitWindowSize(1024,1980);
	// ���ô��ڳ��ֵ�λ��
	//glutInitWindowPosition(int x, int y);
	//��ʼ������չʾģʽ
	//glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("simulate of openGL");
	glColor3f(1.0, 1.0, 1.0);
	gluOrtho2D(0, 63, 0, 63);
		//Ϊ��ǰ�������ú����ص������ڻ�ͼ
	glutDisplayFunc(drawvexel);
	glutSpecialFunc(special);
	////���ڸı�ʱ�ĺ���
	//glutReshapeFunc(threeD);
	glutMainLoop();
	return 0;
} 