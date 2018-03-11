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
using namespace std;
class Plane3DS
{
public:
	list<CVector2_int> *pVexelOFplane;//截面
	//Plane3DS();
	Plane3DS(int numofplane);//设置截面数
	~Plane3DS();
	void ProcessVoxelDataModel(t3DModel Model);//用“面方法”来得到截面的list
	char RGB_get(t3DModel model);
	int _numofplane;
	list <CVector3_int> *_3dVexel;

private:

	#define PI 3.1415926
	struct LinePara
	{
		float k;
		float b;
	};//直线
	void CalculateVoxelOfFace(CVector3 V1, CVector3 V2, CVector3 V3);//“面方法”内核函数
	int PlaneandPoint(CVector3 V1, CVector3 V2, float K, CVector3 &pt1, CVector3 &pt2);//判断出线和面的交点
	int round(float number);
	int round2(float number);
	void linepoint(CVector3 pt01, CVector3 pt11,int iii);
	int max_float(float a, float b, float c);
	CVector3_int convert(CVector3 cv);
};


#endif
