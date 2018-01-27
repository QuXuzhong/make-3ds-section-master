#pragma once
#ifndef getplane_h
#define getplane_h

#include "structof3ds.h"										
#include "3ds.h"	
#include <iostream>
#include "conio.h"
//#include "main.h"
#include <fstream>
#include <iomanip>
#include <list>

class Plane3DS
{
public:
	list<CVector2_int> *pVexelOFplane;//����
	//Plane3DS();
	Plane3DS(int numofplane);//���ý�����
	~Plane3DS();
	void ProcessVoxelDataModel(t3DModel Model);//�á��淽�������õ������list
	int _numofplane;



private:

	#define PI 3.1415926
	struct LinePara
	{
		float k;
		float b;
	};//ֱ��
	void CalculateVoxelOfFace(CVector3 V1, CVector3 V2, CVector3 V3);//���淽�����ں˺���
	int PlaneandPoint(CVector3 V1, CVector3 V2, float K, CVector3 &pt1, CVector3 &pt2);//�жϳ��ߺ���Ľ���
	int round(float number);
	void linepoint(CVector3 pt01, CVector3 pt11,int iii);
};


#endif
