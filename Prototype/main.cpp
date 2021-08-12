#include "Headers.h"
#include "PrototypeManager.h"
#include "Object.h"

Object* pObjList[3];

void Init(string _str)
{
	//���� ��ü ã��
	Object* pObj = GETSINGLETON(PrototypeManager)->FindObject(_str);

	//ã�� ��ü�� ���ٸ� �����޼��� ��� �� �Լ� ����
	if (pObj == nullptr)
	{
		COORD Pos = { 50, 15 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

		cout << " ������ ���� ��ü�� ���� " << endl;
		return; //�Լ� ����
	}
	else //ã�� ��ü�� �ִٸ� ����
	{
		for (int i = 0; i < 3; ++i)
		{
			pObjList[i] = pObj->Clone(); //������ ���� ��ü�� ���纻 �ѱ�

			pObjList[i]->Initialize(); //���纻 �ʱ�ȭ
			pObjList[i]->SetIndex(i + 1); //���纻�� �ε������� ����
		}
	}
}

int main(void)
{
	/*
	* �뷮 ������ ���� �������
	* objectpool�� ����� �����ϴ� �Ͱ� ����
	* ������ prototype�� ��� ��踦 �鿩���� �Ͱ� ����
	*/

	//Index 1, 2, 3���� ���

	//prototype manager �ʱ�ȭ
	GETSINGLETON(PrototypeManager)->Initialize();

	Init("Object"); //�׳� ������ ���� �� ��� ���ٸ� ������ �� ���̱� ������

	for (int i = 0; i < 3; ++i)
		if(pObjList[i])
			pObjList[i]->Render(i);

	for (int i = 0; i < 3; ++i)
	{
		SAFE_DELETE(pObjList[i]);
	}

	return 0;
}

/*
* �ʱⱸ��
* ������׿� ���� ����
* ��� ����
* ����
*/