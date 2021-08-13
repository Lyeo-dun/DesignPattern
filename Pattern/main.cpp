#include "ObjectpoolManager.h"
#include "PrototypeManager.h"

void Output(float _x, float _y, string _str);

int main(void)
{
	GETSINGLETON(PrototypeManager)->Initialize();
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
			//** 초기화 및 사용할 리스트에 추가.
			GETSINGLETON(ObjectpoolManager)->AddEnalbeList("Object", Vector3(4.0f, 15.0f));
		}

		GETSINGLETON(ObjectpoolManager)->Update();
		GETSINGLETON(ObjectpoolManager)->Render();

		{
			list<Object*> TmpList = *GETSINGLETON(ObjectpoolManager)->GetDesableList();
			//** 현재 리스트에 남아있는 오브젝트의 개수 확인. (DesableList)
			string Buffer = "DesableList : " + to_string(TmpList.size());
			Output(10, 1, Buffer);
			Buffer.clear();

			TmpList = *GETSINGLETON(ObjectpoolManager)->GetEnableList();
			//** 현재 리스트에 남아있는 오브젝트의 개수 확인. (EnableList)
			Buffer = "EnableList : " + to_string(TmpList.size());
			Output(10, 2, Buffer);
		}

		Sleep(50);
	}

	//** DesableList 전제 삭제
	//** EnableList 전제 삭제
	GETSINGLETON(ObjectpoolManager)->Release();
	GETSINGLETON(PrototypeManager)->Release();

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