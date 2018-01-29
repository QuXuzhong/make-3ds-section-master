#include <GL/glut.h>
#include <math.h>
#include "simulate.h"
#include "getplane.h" 
  //做的截面数/2
using namespace std;
extern int SECTION_NUM;
extern Plane3DS section;
	int j = 1;
void drawvexel(void)
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);//点阵模式
					   //开始以g_View Mode模式绘制 
					   //GL.gl Point Size(1.5f);          //可以 更改体素大小        
					   // 遍历所有的角平面 
	//for (int j = 0; j < 2 * section._numofplane; j++)
	//{
		// 遍历角平面中所有体素 

		float sita = PI / float(section._numofplane)*j;
		float K = tan(sita);
		list<CVector2_int>::iterator i;
		for (i = section.pVexelOFplane[j].begin(); i != section.pVexelOFplane[j].end(); i++)
		{
			int z = int(K*((*i).x));
			glVertex2f((*i).x, (*i).y);
		}
	//}	
	glEnd();                // 绘制结束 
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

	//初始化GLUT library

	//对窗口的大小进行初始化00
	glutInitWindowSize(1024,1980);
	// 设置窗口出现的位置
	//glutInitWindowPosition(int x, int y);
	//初始化程序展示模式
	//glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("simulate of openGL");
	glColor3f(1.0, 1.0, 1.0);
	gluOrtho2D(0, 63, 0, 63);
		//为当前窗口设置函数回调，用于画图
	glutDisplayFunc(drawvexel);
	glutSpecialFunc(special);
	////窗口改变时的函数
	//glutReshapeFunc(threeD);
	glutMainLoop();
	return 0;
} 