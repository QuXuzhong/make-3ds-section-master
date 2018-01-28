#include "getplane.h"
#include <math.h>
using namespace std;


Plane3DS::Plane3DS(int numofplane)//����Ϊ��Ҫ���Ľ��棬����ʵ��180���������ķָ������ĽǶ���ʵ�ǶԳƵ�
{
	_numofplane = numofplane;//���Բ�����ķָ���
	pVexelOFplane = new list<CVector2_int> [ 2 * numofplane ];//����Ķ�������
}

void Plane3DS::ProcessVoxelDataModel(t3DModel Model)
{
	for (int i = 0; i < Model.numOfObjects; i++)//�������ж���
	{
		if (Model.pObject.size() <= 0)
		{
			return ;
		}
		t3DObject pObject = Model.pObject[i];

		for (int j = 0; j < pObject.numOfFaces; j++)
		{
			cout << " object:" << i <<"\t num of face \t\t" << j << "\n";
			int  *index = new int[3];
			for (int k = 0; k < 3; k++)
			{
				index[k] = pObject.pFaces[j].vertIndex[k];
 			}
			CalculateVoxelOfFace( pObject.pVerts[index[0]], pObject.pVerts[index[1]], pObject.pVerts[index[2]]);
			delete []index;
		}
	}
} 

void Plane3DS::CalculateVoxelOfFace(CVector3 V1, CVector3 V2, CVector3 V3)//��Щ�������Ӧ������������ϵ���Ȱ�����������ϵ���������һ��ת��
{

	//*******************************************************************************************************************************************************
	//*******************************************************************************************************************************************************
	for (int iii = 0; iii < _numofplane; iii++)//����180����ÿһ����
	{
		//cout << "ing\t" << i << "\n";
		//�Ե�i��������ж�
		float sita = PI / float(_numofplane)*iii ;//��i�����б�ʣ�ע����������������ϵ��,�Ҹ�����Ϊ��������ʵ���ϸ���ȡ����PI/2���Ͳ���������
		float K = tan(sita) ;//����ӦΪ z= tan(sita)*x
		CVector3 pt01, pt02,pt11,pt12,pt21,pt22;
		int flag0,flag1,flag2,flag;
		//----------------------------------------
		flag0 = PlaneandPoint( V2, V3, K, pt01, pt02 );
		flag1 = PlaneandPoint( V1, V3, K, pt11, pt12 );
		flag2 = PlaneandPoint( V1, V2, K, pt21, pt22 );
		flag = 100 * flag2 + 10 * flag1 + flag0;
		switch (flag)
		{
		case 0:
			break;
		case 222:
			linepoint(pt01, pt11, iii);
			linepoint(pt11, pt21, iii);
			linepoint(pt01, pt21, iii);
			break;
		case 211:
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
	
	for (int iii = _numofplane; iii < 2 * _numofplane; iii++)//ʣ�µĲ������Գ�
	{
		list<CVector2_int>::iterator iter;
		for (iter = pVexelOFplane[iii-_numofplane].begin(); iter != pVexelOFplane[iii-_numofplane].end(); iter++)
		{
			CVector2_int pt;
			pt.x = 64-(*iter).x;
			pt.y = (*iter).y;
			pVexelOFplane[iii].push_back(pt);

		}
	}



}



int Plane3DS::round(float number)//��������ĺ���
{
	return ( number > 0.0) ? floor(number + 0.5) : ceil(number - 0.5);
}









int Plane3DS::PlaneandPoint(CVector3 V1, CVector3 V2, float K, CVector3 &pt1, CVector3 &pt2)//�жϳ��ߺ���Ľ���
{
	//���������������ƽ�У��������غϣ���б�������������ƴ���б��10000��
	if (V2.x == V1.x && V2.z == V1.z)//��xzƽ����ӳ��Ϊһ������������
	{
		if (V1.z == K*V1.x)
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
		LP.k = 10000.0;
		LP.b = V1.z - LP.k * V1.x;
		if ( abs(K) < LP.k)//��ƽ��ʱ�Ľ������ֻ꣨����һ�����㣩
		{
			pt1.x = V1.x;
			pt1.z = K * pt1.x;
			pt1.y = V1.y + (pt1.z - V1.z) / (V2.z - V1.z) * (V2.y - V1.y);
			if( (pt1.x-V1.x)*(pt1.x - V2.x)<=0 && (pt1.z - V1.z)*(pt1.z - V2.z) <= 0)
			{
				//cout << "{" << pt1.x << "," << pt1.y << "," << pt1.z << "}" << K << "\t";
				//cout << "{" << V1.x << "," << V2.x << "," << pt1.z << "}" << K << endl;
				return 1;//��ʾ������һ������

			}
			else return 0;
		}
		else//ƽ��ʱ
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
		if (abs(LP.k - K) > 0.05)//��ƽ��ʱ�Ľ������ֻ꣨����һ�����㣩
		{
			pt1.x = (LP.b) / (K - LP.k);
			pt1.z = LP.k*pt1.x + LP.b;
			pt1.y = V1.y + (pt1.x - V1.x) / (V2.x - V1.x) * (V2.y - V1.y);
			if ( (pt1.x - V1.x)*(pt1.x - V2.x) < 0 || (pt1.z - V1.z)*(pt1.z - V2.z) < 0)
			{
				//cout << "{" << pt1.x << "," << pt1.y << "," << pt1.z << "}"<<K<<"\t";
				//cout << "{" << V1.x << "," << V2.x << "," << pt1.z << "}" << K << endl;
				return 1;//��ʾ������һ������

			}
			else return 0;
		}
		else//ƽ��ʱ
		{
			if (V1.z == K*V1.x)//��������
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
void Plane3DS::linepoint(CVector3 pt01, CVector3 pt11,int iii)//��iii������
{
	CVector3 cv1, cv2;
	cv1 = pt01;
	cv2 = pt11;
	CVector2 pt, pt0;//��������
	CVector2_int pt00, pt000;//�任����֮���
	if ((cv1.x >= 0 && cv1.z == 0) || (cv1.z>0))
		pt.x = sqrt(pow(cv1.x, 2) + pow(cv1.z, 2));
	else
		pt.x = -sqrt(pow(cv1.x, 2) + pow(cv1.z, 2));
	pt.y = cv1.y;
	if ((cv2.x >= 0 && cv2.z == 0) || (cv2.z>0))
		pt0.x = sqrt(pow(cv2.x, 2) + pow(cv2.z, 2));
	else
		pt0.x = -sqrt(pow(cv2.x, 2) + pow(cv2.z, 2));
	pt0.y = cv2.y;

	pt00.x = round(pt.x + 31.5);
	pt00.y = round(pt.y + 31.5);
	//cout << "{" << pt00.x << "," << pt00.y << "}\n";
	pt000.x = round(pt0.x + 31.5);
	pt000.y = round(pt0.y + 31.5);
	//cout << "{" << pt000.x << "," << pt000.y << "}\n";

	CVector2_int ptu;
	if (abs(pt000.x - pt00.x) >= abs(pt000.y - pt00.y))//���ػ�ֱ��1
	{
		if ((pt000.x - pt00.x) == 0)
		{
			ptu.x = pt00.x;
			ptu.y = pt00.y;
			//cout << ptu.y << "\t";
			pVexelOFplane[iii].push_back(ptu);
		}
		else
		{
			for (int k = min(pt00.x, pt000.x); k != max(pt00.x, pt000.x); k++)
			{
				ptu.x = k;
				ptu.y = round((pt000.y - pt00.y) / float((pt000.x - pt00.x))*(ptu.x - pt00.x) + pt00.y);
				//cout << ptu.y << "\t";
				pVexelOFplane[iii].push_back(ptu);
			}
		}
	}


	else//���ػ�ֱ��2
	{
		if ((pt000.y - pt00.y) == 0)
		{
			ptu.x = pt00.x;
			ptu.y = pt00.y;
			pVexelOFplane[iii].push_back(ptu);
		}
		else
		{
			for (int k = min(pt00.y, pt000.y); k != max(pt00.y, pt000.y); k++)
			{
				ptu.y = k;
				ptu.x = round((pt000.x - pt00.x) / float((pt000.y - pt00.y))*(ptu.y - pt00.y) + pt00.x);
				pVexelOFplane[iii].push_back(ptu);
			}
		}
	}


}





Plane3DS::~Plane3DS()
{
	for (int i = 0; i < 2 * _numofplane; i++)
	{
		pVexelOFplane[i].clear();
	}
	//delete[] pVexelOFplane;
}