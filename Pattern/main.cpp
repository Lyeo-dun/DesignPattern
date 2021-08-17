#include "ObjectpoolManager.h"
#include "PrototypeManager.h"

void Output(float _x, float _y, string _str);

int main(void)
{
	GETSINGLETON(PrototypeManager)->Initialize("Object");
	GETSINGLETON(ObjectpoolManager)->Initialize();

	bool Check = false;

	while (true)
	{
		system("cls");
		
		Check = false;

		if (GetAsyncKeyState(VK_RETURN))
			Check = true;

		if (Check)
		{
			//** �ʱ�ȭ �� ����� ����Ʈ�� �߰�.
			GETSINGLETON(ObjectpoolManager)->AddEnalbeList("Object", Vector3(4.0f, 15.0f));
		}

		GETSINGLETON(ObjectpoolManager)->Update();
		GETSINGLETON(ObjectpoolManager)->Render();

		{
			auto TmpList = GETSINGLETON(ObjectpoolManager)->GetDesableList();
			
			//** ���� ����Ʈ�� �����ִ� ������Ʈ�� ���� Ȯ��. (DesableList)
			auto Buffer = "DesableList : " + to_string(TmpList->size());
			Output(10, 1, Buffer);			
			
			Buffer.clear();
			TmpList = nullptr;

			TmpList = GETSINGLETON(ObjectpoolManager)->GetEnableList();
			//** ���� ����Ʈ�� �����ִ� ������Ʈ�� ���� Ȯ��. (EnableList)
			Buffer = "EnableList : " + to_string(TmpList->size());
			Output(10, 2, Buffer);
		}

		Sleep(50);
	}

	//** DesableList ���� ����
	//** EnableList ���� ����

	DESTROYSINGLETON(ObjectpoolManager);
	DESTROYSINGLETON(PrototypeManager);

	return 0;
}

void Output(float _x, float _y, string _str)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	cout << _str << endl;
}