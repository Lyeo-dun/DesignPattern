#include "ObjectpoolManager.h"
#include "PrototypeManager.h"


void Output(float _x, float _y, string _str);

int main(void)
{
	GETSINGLETON(ObjectpoolManager)->Initialize();

	
	//** DesableList �� ������ ������Ʈ�� �ִ��� Ȯ�� �ϰ� ���ٸ�...
	if (GETSINGLETON(ObjectpoolManager)->GetDesableList()->empty())
	{
		GETSINGLETON(ObjectpoolManager)->AddDesObjList("Object");
	}

	GETSINGLETON(ObjectpoolManager)->Update();
	GETSINGLETON(ObjectpoolManager)->Render();
	//** �ʱ�ȭ �� ����� ����Ʈ�� �߰�.
	GETSINGLETON(ObjectpoolManager)->AddEnalbeList(Vector3(4.0f, 15.0f));		

	{
		list<Object*> TmpList = *GETSINGLETON(ObjectpoolManager)->GetDesableList();
		//** ���� ����Ʈ�� �����ִ� ������Ʈ�� ���� Ȯ��. (DesableList)
		string Buffer = "DesableList : " + to_string(TmpList.size());
		Output(10, 1, Buffer);
		Buffer.clear();

		TmpList = *GETSINGLETON(ObjectpoolManager)->GetEnableList();
		//** ���� ����Ʈ�� �����ִ� ������Ʈ�� ���� Ȯ��. (EnableList)
		Buffer = "EnableList : " + to_string(TmpList.size());
		Output(10, 2, Buffer);
	}

	//** DesableList ���� ����
	//** EnableList ���� ����


	return 0;
}

void Output(float _x, float _y, string _str)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	cout << _str << endl;
}