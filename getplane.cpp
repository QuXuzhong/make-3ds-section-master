#include "getplane.h"
#include <math.h>
using namespace std;
extern int Res;

Plane3DS::Plane3DS(int numofplane)//����Ϊ��Ҫ���Ľ��棬����ʵ��180���������ķָ������ĽǶ���ʵ�ǶԳƵ�
{
	_numofplane = numofplane;//���Բ�����ķָ���
	pVexelOFplane = new list<CVector2_int>[2 * numofplane];//����Ķ�������
	_3dVexel = new list<CVector3_int>[2 * numofplane];
}
//��ȡ����RGBֵ�ĺ���
char Plane3DS::RGB_get(t3DModel model)
{
	char output = { 0 };
	for (int i = 0; i < model.numOfObjects; i++)
	{
		BYTE *pColor = model.pMaterials[model.pObject[i].materialID].color;

	}
	return output;
}
void Plane3DS::ProcessVoxelDataModel(t3DModel Model)
{
	for (int i = 0; i < Model.numOfObjects; i++)//�������ж���
	{
		if (Model.pObject.size() <= 0)
		{
			return;
		}
		t3DObject pObject = Model.pObject[i];

		for (int j = 0; j < pObject.numOfFaces; j++)
		{
			cout << " object:" << i << "\t num of face \t\t" << j << "\n";
			int  *index = new int[3];
			for (int k = 0; k < 3; k++)
			{
				index[k] = pObject.pFaces[j].vertIndex[k];
			}
			CalculateVoxelOfFace(pObject.pVerts[index[0]], pObject.pVerts[index[1]], pObject.pVerts[index[2]]);
			delete[]index;
		}
		
	}
	Symmetrical_trans();//�Ժ�벿�����Գ�
}

void Plane3DS::CalculateVoxelOfFace(CVector3 V1, CVector3 V2, CVector3 V3)//��Щ�������Ӧ������������ϵ���Ȱ�����������ϵ���������һ��ת��
{

	//*******************************************************************************************************************************************************
	//*******************************************************************************************************************************************************
	for (int iii = 0; iii < _numofplane; iii++)//����180����ÿһ����
	{
		//cout << "ing\t" << i << "\n";
		//�Ե�i��������ж�
		float sita = PI *float(iii) / float(_numofplane);//��i�����б�ʣ�ע����������������ϵ��,�Ҹ�����Ϊ��������ʵ���ϸ���ȡ����PI/2���Ͳ���������
		float K = tan(sita);//����ӦΪ z= tan(sita)*x
		CVector3 pt01, pt02, pt11, pt12, pt21, pt22;
		int flag0, flag1, flag2, flag;
		//----------------------------------------
		flag0 = PlaneandPoint(V2, V3, K, pt01, pt02);//��ʾV2��V3�Ľ������
		flag1 = PlaneandPoint(V1, V3, K, pt11, pt12);
		flag2 = PlaneandPoint(V1, V2, K, pt21, pt22);
		flag = 100 * flag2 + 10 * flag1 + flag0;
		//ͨ����������������������ߵĽ�������жϽ�������������Ĺ�ϵ��
		switch (flag)
		{
		case 0:
			break;
		case 222://�������ڽ����ڲ���ֻ�����������ϵĵ�
			linepoint(pt01, pt11, iii);//���ڽ�pt01��pt11֮���������ȫ������
			linepoint(pt11, pt21, iii);
			linepoint(pt01, pt21, iii);
			break;
		case 211://һ�����ڽ����ڣ������������ϵĵ�
			linepoint(pt21, pt22, iii);
			break;
		case 121:
			linepoint(pt11, pt12, iii);
			break;
		case 112:
			linepoint(pt01, pt02, iii);
			break;
		case 111:
			linepoint(pt01, pt11, iii);
			linepoint(pt11, pt21, iii);
			linepoint(pt01, pt21, iii);
			break;
		case 110:
			linepoint(pt21, pt11, iii);
			break;
		case 101:
			linepoint(pt21, pt01, iii);
			break;
		case 11:
			linepoint(pt11, pt01, iii);
			break;
		default:
			break;
		}
	}

	//*******************************************************************************************************************************************************
	//*******************************************************************************************************************************************************


}

void Plane3DS::Symmetrical_trans()
{
	for (int iii = _numofplane; iii < 2 * _numofplane; iii++)//ʣ�µĲ������Գ�
	{
		list<CVector2_int>::iterator iter;
		for (iter = pVexelOFplane[iii - _numofplane].begin(); iter != pVexelOFplane[iii - _numofplane].end(); iter++)
		{
			CVector2_int pt;
			pt.x = Res - 1 - (*iter).x;//���Ŀ��Ϊ32
			pt.y = (*iter).y;
			pVexelOFplane[iii].push_back(pt);

		}
	}
}

int Plane3DS::round(float number)//��������ĺ���
{
	return (number > 0) ? floor(number + 0.5) : ceil(number - 0.5);
}
int Plane3DS::round2(float number)//��������ĺ���
{
	return (number > Res / 2 - 0.5) ? floor(number + 0.5) : ceil(number - 0.5);
}









int Plane3DS::PlaneandPoint(CVector3 V1, CVector3 V2, float K, CVector3 &pt1, CVector3 &pt2)//�жϳ��ߺ���Ľ���
{
	//���������������ƽ�У��������غϣ���б�������������ƴ���б��10000��
	if (V2.x == V1.x && V2.z == V1.z)//��xzƽ����ӳ��Ϊһ������������
	{
		if (abs(V1.z - K*V1.x) <= 0.1)
		{
			pt1 = V1;
			pt2 = V2;
			return 2;//��ʾ�������غϣ����������˵������
		}
		else return 0;//��ʾ�������޽���

	}


	//��xzƽ����ӳ��Ϊ����������
	int m = 0;
	LinePara LP;
	m = V2.x - V1.x;
	if (0 == m)//б�ʴ�ֱ�����
	{
		LP.k = 10000;
		LP.b = V1.z - LP.k * V1.x;
		if (abs(K) < LP.k)//��ƽ��ʱ�Ľ������ֻ꣨����һ�����㣩
		{
			pt1.x = V1.x;
			pt1.z = K * pt1.x;
			pt1.y = V1.y + (pt1.z - V1.z) / (V2.z - V1.z) * (V2.y - V1.y);
			if ((pt1.x - V1.x)*(pt1.x - V2.x) <= 0 && (pt1.z - V1.z)*(pt1.z - V2.z) <= 0)//�жϽ����Ƿ��ڱ��ڲ�
			{
				//cout << "{" << pt1.x << "," << pt1.y << "," << pt1.z << "}" << K << "\t";
				//cout << "{" << V1.x << "," << V2.x << "," << pt1.z << "}" << K << endl;
				return 1;//��ʾ������һ������

			}
			else return 0;
		}
		else//ƽ��ʱ(��������������ı߶���ֱ��x�ᣩ
		{
			if (V1.x == 0)//��������
			{
				pt1 = V1;
				pt2 = V2;
				return 2;//��ʾ�������غϣ����������˵������
			}
			else return 0;//��ʾ���غϵ�
		}
	}



	else//һ�����
	{
		LP.k = (V2.z - V1.z) / (V2.x - V1.x);
		LP.b = V1.z - LP.k * V1.x;
		if (abs(LP.k - K) > 0.01)//��ƽ��ʱ�Ľ������ֻ꣨����һ�����㣩
		{
			pt1.x = (LP.b) / (K - LP.k);
			pt1.z = LP.k*pt1.x + LP.b;
			pt1.y = V1.y + (pt1.x - V1.x) / (V2.x - V1.x) * (V2.y - V1.y);
			if ((pt1.x - V1.x)*(pt1.x - V2.x) < 0 || (pt1.z - V1.z)*(pt1.z - V2.z) < 0)
			{
				//cout << "{" << pt1.x << "," << pt1.y << "," << pt1.z << "}"<<K<<"\t";
				//cout << "{" << V1.x << "," << V2.x << "," << pt1.z << "}" << K << endl;
				return 1;//��ʾ������һ������

			}
			else return 0;
		}
		else//ƽ��ʱ
		{
			if (abs(LP.b) <= 0.1)//��������
			{
				pt1 = V1;
				pt2 = V2;
				return 2;//��ʾ�������غϣ����������˵������
			}
			else return 0;//��ʾ���غϵ�
		}
	}


}
//������֮��ĵ㶼�����list��
void Plane3DS::linepoint(CVector3 pt01, CVector3 pt11, int iii)//��iii������
{
	CVector3 cv1, cv2;
	cv1 = pt01;
	cv2 = pt11;
	CVector2 pt, pt0;//��������
	CVector2_int pt00, pt000;//�任����֮���

	//���ȱ�����ά������Ϣ��_3dVexel
	CVector3_int pt3d, cv1_int, cv2_int;
	//��float������ת��Ϊint��
	cv1_int = convert(cv1);
	cv2_int = convert(cv2);
	//_3dVexel[iii].push_back(cv1_int);
	//_3dVexel[iii].push_back(cv2_int);
	if ((cv1_int.x == cv2_int.x) && (cv1.y == cv2.y) && (cv1.z == cv2.z))
	{
		pt3d.x = cv1_int.x;
		pt3d.y = cv1_int.y;
		pt3d.z = cv1_int.z;
		_3dVexel[iii].push_back(pt3d);
	}
	//else if ((max_3(abs(cv2_int.x - cv1_int.x), abs(000000c000000000000000000000v2_int.y - cv1_int.y),abs(cv2_int.z-cv2_int.z))==abs(cv2_int.x - cv1_int.x)))//���ػ�ֱ��1
	//{
	for (int k = min(cv1_int.x, cv2_int.x); k <= max(cv1_int.x, cv2_int.x); k++)
	{
		pt3d.x = k;
		pt3d.y = round((cv2_int.y - cv1_int.y) / float((cv2_int.x - cv1_int.x))*(pt3d.x - cv1_int.x) + cv1_int.y);
		pt3d.z = round((cv2_int.z - cv1_int.z) / float((cv2_int.x - cv1_int.x))*(pt3d.x - cv1_int.x) + cv1_int.z);
		_3dVexel[iii].push_back(pt3d);
	}
	//}
	//else if((max_3(abs(cv2_int.x - cv1_int.x), abs(cv2_int.y - cv1_int.y), abs(cv2_int.z - cv2_int.z)) == abs(cv2_int.y - cv1_int.y)))//���ػ�ֱ��2
	//{
	for (int k = min(cv1_int.y, cv2_int.y); k <= max(cv1_int.y, cv2_int.y); k++)
	{
		pt3d.y = k;
		pt3d.x = round((cv2_int.x - cv1_int.x) / float((cv2_int.y - cv1_int.y))*(pt3d.y - cv1_int.y) + cv1_int.x);
		pt3d.z = round((cv2_int.z - cv1_int.z) / float((cv2_int.y - cv1_int.y))*(pt3d.y - cv1_int.y) + cv1_int.z);
		_3dVexel[iii].push_back(pt3d);
	}
	//}
	//else 
	//{
	for (int k = min(cv1_int.z, cv2_int.z); k <= max(cv1_int.z, cv2_int.z); k++)
	{
		pt3d.z = k;
		pt3d.x = round((cv2_int.x - cv1_int.x) *(pt3d.z - cv1_int.z) / float((cv2_int.z - cv1_int.z)) + cv1_int.x);
		pt3d.y = round((cv2_int.y - cv1_int.y) *(pt3d.z - cv1_int.z) / float((cv2_int.z - cv1_int.z)) + cv1_int.y);
		_3dVexel[iii].push_back(pt3d);
	}
	//}


	//����2d����Ϣ
	if ((cv1.x >= 0 && cv1.z == 0) || (cv1.z > 0))
		pt.x = sqrt(pow(cv1.x, 2) + pow(cv1.z, 2));
	else
		pt.x = -sqrt(pow(cv1.x, 2) + pow(cv1.z, 2));
	pt.y = cv1.y;
	if ((cv2.x >= 0 && cv2.z == 0) || (cv2.z > 0))
		pt0.x = sqrt(pow(cv2.x, 2) + pow(cv2.z, 2));
	else
		pt0.x = -sqrt(pow(cv2.x, 2) + pow(cv2.z, 2));
	pt0.y = cv2.y;
	pt00.x = round2(pt.x + Res / 2 - 0.5);//Res����Ļ�ķֱ���
	pt00.y = round2(pt.y + Res / 2 - 0.5);
	//cout << "{" << pt00.x << "," << pt00.y << "}\n";
	pt000.x = round2(pt0.x + Res/2-0.5);
	pt000.y = round2(pt0.y + Res/2-0.5);
	//cout << "{" << pt000.x << "," << pt000.y << "}\n";
	//pVexelOFplane[iii].push_back(pt00);
	//pVexelOFplane[iii].push_back(pt000);

	CVector2_int ptu;
	if ((pt000.x == pt00.x) && (pt000.y == pt00.y))//����������������غϵ����
	{
		ptu.x = pt00.x;
		ptu.y = pt00.y;
		pVexelOFplane[iii].push_back(ptu);
	}
	else if (abs(pt000.x - pt00.x) > abs(pt000.y - pt00.y))//���ػ�ֱ��1
	{
		for (int k = min(pt00.x, pt000.x); k <= max(pt00.x, pt000.x); k++)
		{
			ptu.x = k;
			ptu.y = round((pt000.y - pt00.y) / float((pt000.x - pt00.x))*(ptu.x - pt00.x) + pt00.y);
			//cout << ptu.y << "\t";
			pVexelOFplane[iii].push_back(ptu);
		}
	}
	else//���ػ�ֱ��2
	{
		for (int k = min(pt00.y, pt000.y); k <= max(pt00.y, pt000.y); k++)
		{
			ptu.y = k;
			ptu.x = round((pt000.x - pt00.x) / float((pt000.y - pt00.y))*(ptu.y - pt00.y) + pt00.x);
			pVexelOFplane[iii].push_back(ptu);
		}
	}
}
int Plane3DS::max_3(float a, float b, float c)
{
	float t;
	t = (int)max(a, b);
	t = (int)max(t, c);
	return t;
}
CVector3_int Plane3DS::convert(CVector3 cv)
{
	CVector3_int cv_int;
	cv_int.x = round(cv.x);
	cv_int.y = round(cv.y);
	cv_int.z = round(cv.z);
	return cv_int;
}
Plane3DS::~Plane3DS()
{
	for (int i = 0; i < 2 * _numofplane; i++)
	{
		pVexelOFplane[i].clear();
	}
	//delete[] pVexelOFplane;
}