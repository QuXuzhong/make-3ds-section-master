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
#define FILE_NAME  "square_blue.3ds"	//ע����3dmax����ʱ�����в�����Ϣ����
//���Ľ�����/2
#define RATIO 1.2 //���Χ�ڵı���
CLoad3DS g_Load3ds;									
t3DModel g_3DModel;
int SECTION_NUM = 100;
Plane3DS section(SECTION_NUM);
using namespace std;
int Res = 32;//�������ķֱ���
char save[32][32] = { 0x0 };//��Ӧ�ֱ������ڱ������ݵ�����
int main(int argc, char** argv)
{

	bool c;
	c = g_Load3ds.Import3DS(&g_3DModel, FILE_NAME);			// ��3ds�ļ�װ�뵽ģ�ͽṹ����
	//trans(g_3DModel, 8.98, RATIO);//ģ�ʹ�Сת��
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
			float l = sqrt(pow((pVerts + j)->x, 2) + pow((pVerts + j)->z, 2));                //���ڵó��仯����
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
	ccc = trans(g_3DModel, KP , RATIO);//ģ�ʹ�Сת��


	//*********************************************************************************************************************************************************************************************************
	//������͵����ʾ�ļ�
	ofstream mcfile;  
	mcfile.open("D:\\data\\mingci.txt"); //�ļ���ַ  
	std::cout << "����������" << g_3DModel.numOfObjects << std::endl;
	std::cout << "����������" << g_3DModel.numOfMaterials << std::endl;

	for (int i = 0; i < g_3DModel.numOfObjects; i++)//�Ե�i�������еĴ���
	{
		cout << "output begin" << endl;
		CVector3 *pVerts = g_3DModel.pObject[i].pVerts;//*(pVerts+j)��ʾ����Ϊj�ĵ㣬jΪ������ֵ
		tFace *vertIndex = g_3DModel.pObject[i].pFaces;//*(vertIndex+j)��ʾ��j���棬(vertIndex+j)->vertIndex[0]��ʾ�����0���������ֵ
		BYTE *pColor = g_3DModel.pMaterials[g_3DModel.pObject[i].materialID].color;//g_3DModel.pObject[i].materialID�ҵ������һ������ֻ��һ��rgb����������Ҫ����ͼ����ȡ��ɫ(�������ɫ������Ҫ����ͼ����opencv�������������)
		std::cout << "\t��" << i << "�������ж�������" << g_3DModel.pObject[i].numOfVerts << std::endl;
		std::cout << "\t��" << i << "�������е�������" << g_3DModel.pObject[i].numOfFaces << std::endl;
		std::cout << "\t��" << i << "�������е�����ID" << g_3DModel.pObject[i].materialID << std::endl;
		std::cout << "\t��" << i << "�����������ӳ��" << g_3DModel.pMaterials[i].strFile << std::endl;
		//mcfile << "��" << i << "���������ɫ(RGB)��" << "\t{"
		//	<< setw(4) << right << int(pColor[0]) << ","
		//	<< setw(4) << right << int(pColor[1]) << ","
		//	<< setw(4) << right << int(pColor[2]) << " }\n";	
		////��������uv����
		//if (g_3DModel.pObject[i].bHasTexture)
		//{
		//	mcfile << "�������ƣ�" << g_3DModel.pMaterials[g_3DModel.pObject[i].materialID].strName<<endl;
		//	mcfile << "�����ļ���" << g_3DModel.pMaterials[g_3DModel.pObject[i].materialID].strFile<< endl;
		//	mcfile << "uƫ��" << g_3DModel.pMaterials[g_3DModel.pObject[i].materialID].uOffset <<"\tvƫ��"<< g_3DModel.pMaterials[g_3DModel.pObject[i].materialID].vOffset<< endl;
		//	for (int k = 0; k < g_3DModel.pObject[i].numTexVertex; k++)
		//	{
		//		CVector2 *pTexVerts = g_3DModel.pObject[i].pTexVerts;
		//		mcfile << "����ĵ�" << k << "��uv����:" << pTexVerts->x << "," << pTexVerts->y << endl;
		//		pTexVerts++;
		//	}
		//}
		//else
		//	mcfile << "ģ��û������ӳ��" << endl;
		////�г�������꼰������
		//
	//	for (int j = 0; j < g_3DModel.pObject[i].numOfVerts; j++)//һ����j���㣬��jӦ�þ��ǵ������
	//	{
	//		mcfile << "\tpoint index:" << j << "\t{"
	//			<< setw(10) << right << (pVerts + j)->x << ","
	//			<< setw(10) << right << (*(pVerts + j)).y << ","
	//			<< setw(10) << right << (pVerts + j)->z << " }\n";
	//	}
	//	//�����������ֵ
	//	for (int j = 0; j < g_3DModel.pObject[i].numOfFaces; j++)//һ����j���㣬��jӦ�þ��ǵ������
	//	{
	//		mcfile << "\t��" << j << "\tindex: {"
	//			<< setw(10) << right << (vertIndex + j)->vertIndex[0] << ","//A�������ֵ                                                       
	//			<< setw(10) << right << (vertIndex + j)->vertIndex[1] << ","//B������ֵ
	//			<< setw(10) << right << (vertIndex + j)->vertIndex[2] << " }\n";//C������ֵ

	//	}

	//	mcfile << endl;
	}
	cout << "mingci.txt������" << endl;
	mcfile.close(); //�ر�
	//*********************************************************************************************************************************************************************************************************
	//�������������ļ���
	//Plane3DS section(SECTION_NUM);//���ý�����Ϊ100
	section.ProcessVoxelDataModel(g_3DModel);//������
	ofstream sectionfile; //��������洢�ļ��ļ� 
	//sectionfile.open("D:\\data\\section.txt"); //�ļ���ַ
	//for (int i = 0; i < 2*SECTION_NUM; i++)//����ÿ��list
	//{
	//	list<CVector2_int>::iterator iter;
	//	sectionfile << "section index:" << i << "\n" ;
	//	for (iter = section.pVexelOFplane[i].begin(); iter != section.pVexelOFplane[i].end() ; iter++)
	//	{
	//		sectionfile << "\t{" << setw(10) << right << (*iter).x << "," << setw(10) << right << (*iter).y << "}\n";
	//	}
	//	sectionfile <<  "\n\n" ;
	//}
	//cout << "section.txt������" << endl;
	//sectionfile.close();
	//**********************************************************************************************************************************************************************************************************
	
	//ת��Ϊ�������ݴ洢��sd����
	
	ofstream sdfile; //��������洢�ļ��ļ� 
	sdfile.open("D:\\data\\sd.txt"); //�ļ���ַ
	for (int i = 0; i < 2 * SECTION_NUM; i++)//����ÿ��list
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
	cout << "sd.txt������" << endl;
	sdfile.close();
	//��ʼ��GLUT library
	cout << "��0ѡ������ģʽ����1ѡ��3d����" << endl;
	char cc;
	cc = getchar();
	glutInit(&argc, argv);
	if(cc=='0')
	glmain();
	else
	glmain3d();
	//********************************************
	std::cout << "����������˳���";
	_getch();
	return 0;
	//********************************************
}

