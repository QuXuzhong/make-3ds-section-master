#include "basic.h"
#include "3ds.h"	
#include <iostream>
#include "conio.h"
#include <fstream>
//#include <iomanip>
#include <list>
#include "getplane.h"
#include "structof3ds.h"

bool trans(t3DModel &demo_Model, float KP , float RATIO)//根据屏幕大小转化的函数
{
	//(*demo_Model) = Model;
	for (int i = 0; i < demo_Model.numOfObjects; i++)//遍历所有对象
	{
		if (demo_Model.pObject.size() <= 0)
		{
			return false;
		}
		vector<t3DObject> demo_pObject = demo_Model.pObject;

		for (int j = 0; j < demo_Model.pObject[i].numOfVerts; j++)
		{
			demo_pObject[i].pVerts[j].x *= RATIO*KP;
			demo_pObject[i].pVerts[j].y *= RATIO*KP;
			demo_pObject[i].pVerts[j].z *= RATIO*KP;
		}
	}
}
