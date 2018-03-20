#include "structof3ds.h"										
#include "3ds.h"	
#include <iostream>
#include "conio.h"
#include <fstream>
#include <iomanip>
#include <list>
#include "simulate.h"
#include "getplane.h"
#include "basic.h"
#include "GL/glut.h"									
using namespace std;
#define FILE_NAME  "square_blue.3ds"	//注意用3dmax制作时必须有材质信息才行
//做的截面数/2
#define RATIO 1.2 //最大范围内的比例
CLoad3DS g_Load3ds;									
t3DModel g_3DModel;
int SECTION_NUM = 100;
Plane3DS section(SECTION_NUM);
using namespace std;
int Res = 32;//定义屏的分辨率
char save[32][32] = { 0x0 };//对应分辨率用于保存数据的数组
int main(int argc, char** argv)
{

	bool c;
	c = g_Load3ds.Import3DS(&g_3DModel, FILE_NAME);			// 将3ds文件装入到模型结构体中
	//trans(g_3DModel, 8.98, RATIO);//模型大小转化
	if (c)
		std::cout << "success!!!" << std::endl;
	else std::cout << "3ds function Eerror ???" << std::endl;
	//*********************************************************************************************************************************************************************************************************
	float KP = 0;
	CVector2 Max = { 0,0 };
	for (int i = 0; i < g_3DModel.numOfObjects; i++)
	{
		CVector3 *pVerts = g_3DModel.pObject[i].pVerts;
		for (int j = 0; j < g_3DModel.pObject[i].numOfVerts; j++)
		{
			float l = sqrt(pow((pVerts + j)->x, 2) + pow((pVerts + j)->z, 2));                //用于得出变化比例
			float h = abs((pVerts + j)->y);
			if (Max.x < l)
				Max.x = l;
			if (Max.y < h)
				Max.y = h;
		}
	}
	KP = min(12 / Max.x, 12 / Max.y);
	cout << "KP:\t" << KP << endl;
	//*********************************************************************************************************************************************************************************************************
	
	
	char ccc;
	ccc = trans(g_3DModel, KP , RATIO);//模型大小转化


	//*********************************************************************************************************************************************************************************************************
	//创建面和点的显示文件
	ofstream mcfile;  
	mcfile.open("D:\\data\\mingci.txt"); //文件地址  
	std::cout << "对象数量：" << g_3DModel.numOfObjects << std::endl;
	std::cout << "材质数量：" << g_3DModel.numOfMaterials << std::endl;

	for (int i = 0; i < g_3DModel.numOfObjects; i++)//对第i个对象中的处理
	{
		cout << "output begin" << endl;
		CVector3 *pVerts = g_3DModel.pObject[i].pVerts;//*(pVerts+j)表示序列为j的点，j为其索引值
		tFace *vertIndex = g_3DModel.pObject[i].pFaces;//*(vertIndex+j)表示第j个面，(vertIndex+j)->vertIndex[0]表示此面第0个点的索引值
		BYTE *pColor = g_3DModel.pMaterials[g_3DModel.pObject[i].materialID].color;//g_3DModel.pObject[i].materialID我的理解是一个对象只有一种rgb，其他的需要从贴图中提取颜色(更多的颜色可能是要从贴图中用opencv和纹理坐标求得)
		std::cout << "\t第" << i << "个对象中定点数量" << g_3DModel.pObject[i].numOfVerts << std::endl;
		std::cout << "\t第" << i << "个对象中的面数量" << g_3DModel.pObject[i].numOfFaces << std::endl;
		std::cout << "\t第" << i << "个对象中的纹理ID" << g_3DModel.pObject[i].materialID << std::endl;
		std::cout << "\t第" << i << "个对象的纹理映射" << g_3DModel.pMaterials[i].strFile << std::endl;
		//mcfile << "第" << i << "个对象的颜色(RGB)：" << "\t{"
		//	<< setw(4) << right << int(pColor[0]) << ","
		//	<< setw(4) << right << int(pColor[1]) << ","
		//	<< setw(4) << right << int(pColor[2]) << " }\n";	
		////输出纹理的uv坐标
		//if (g_3DModel.pObject[i].bHasTexture)
		//{
		//	mcfile << "纹理名称：" << g_3DModel.pMaterials[g_3DModel.pObject[i].materialID].strName<<endl;
		//	mcfile << "纹理文件：" << g_3DModel.pMaterials[g_3DModel.pObject[i].materialID].strFile<< endl;
		//	mcfile << "u偏移" << g_3DModel.pMaterials[g_3DModel.pObject[i].materialID].uOffset <<"\tv偏移"<< g_3DModel.pMaterials[g_3DModel.pObject[i].materialID].vOffset<< endl;
		//	for (int k = 0; k < g_3DModel.pObject[i].numTexVertex; k++)
		//	{
		//		CVector2 *pTexVerts = g_3DModel.pObject[i].pTexVerts;
		//		mcfile << "纹理的第" << k << "个uv坐标:" << pTexVerts->x << "," << pTexVerts->y << endl;
		//		pTexVerts++;
		//	}
		//}
		//else
		//	mcfile << "模型没有纹理映射" << endl;
		////列出点的坐标及其索引
		//
	//	for (int j = 0; j < g_3DModel.pObject[i].numOfVerts; j++)//一共有j个点，这j应该就是点的索引
	//	{
	//		mcfile << "\tpoint index:" << j << "\t{"
	//			<< setw(10) << right << (pVerts + j)->x << ","
	//			<< setw(10) << right << (*(pVerts + j)).y << ","
	//			<< setw(10) << right << (pVerts + j)->z << " }\n";
	//	}
	//	//给出面的索引值
	//	for (int j = 0; j < g_3DModel.pObject[i].numOfFaces; j++)//一共有j个点，这j应该就是点的索引
	//	{
	//		mcfile << "\t面" << j << "\tindex: {"
	//			<< setw(10) << right << (vertIndex + j)->vertIndex[0] << ","//A点的索引值                                                       
	//			<< setw(10) << right << (vertIndex + j)->vertIndex[1] << ","//B点索引值
	//			<< setw(10) << right << (vertIndex + j)->vertIndex[2] << " }\n";//C点索引值

	//	}

	//	mcfile << endl;
	}
	cout << "mingci.txt输出完成" << endl;
	mcfile.close(); //关闭
	//*********************************************************************************************************************************************************************************************************
	//将截面点输出到文件中
	//Plane3DS section(SECTION_NUM);//设置截面数为100
	section.ProcessVoxelDataModel(g_3DModel);//处理函数
	ofstream sectionfile; //创建截面存储文件文件 
	//sectionfile.open("D:\\data\\section.txt"); //文件地址
	//for (int i = 0; i < 2*SECTION_NUM; i++)//遍历每个list
	//{
	//	list<CVector2_int>::iterator iter;
	//	sectionfile << "section index:" << i << "\n" ;
	//	for (iter = section.pVexelOFplane[i].begin(); iter != section.pVexelOFplane[i].end() ; iter++)
	//	{
	//		sectionfile << "\t{" << setw(10) << right << (*iter).x << "," << setw(10) << right << (*iter).y << "}\n";
	//	}
	//	sectionfile <<  "\n\n" ;
	//}
	//cout << "section.txt输出完成" << endl;
	//sectionfile.close();
	//**********************************************************************************************************************************************************************************************************
	
	//转化为点阵数据存储在sd卡中
	
	ofstream sdfile; //创建截面存储文件文件 
	sdfile.open("D:\\data\\sd.txt"); //文件地址
	for (int i = 0; i < 2 * SECTION_NUM; i++)//遍历每个list
	{

		list<CVector2_int>::iterator iter;
		//sdfile << "section index:" << i << "\n";
		for (iter = section.pVexelOFplane[i].begin(); iter != section.pVexelOFplane[i].end(); iter++)
		{
			save[(*iter).y][(*iter).x] = 0x1;
			//sdfile << "\t{" << setw(10) << right << (*iter).x << "," << setw(10) << right << (*iter).y << "}\n";
		}
		for (int j = (Res-1); j >=0; j--)
		{
			for (int k = 0; k < Res; k++)
			{
				sdfile << save[j][k];
			}
		}

		//sdfile << save[0][0] ;
	}
	cout << "sd.txt输出完成" << endl;
	sdfile.close();
	//初始化GLUT library
	cout << "按0选择切面模式，按1选择3d点阵" << endl;
	char cc;
	cc = getchar();
	glutInit(&argc, argv);
	if(cc=='0')
	glmain();
	else
	glmain3d();
	//********************************************
	std::cout << "按下任意键退出：";
	_getch();
	return 0;
	//********************************************
}

