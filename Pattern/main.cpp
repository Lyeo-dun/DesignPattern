#include "ObjectpoolManager.h"
#include "PrototypeManager.h"


void Output(float _x, float _y, string _str);

int main(void)
{
	GETSINGLETON(ObjectpoolManager)->Initialize();

	
	//** DesableList 에 여분의 오브젝트가 있는지 확인 하고 없다면...
	if (GETSINGLETON(ObjectpoolManager)->GetDesableList()->empty())
	{
		GETSINGLETON(ObjectpoolManager)->AddDesObjList("Object");
	}

	GETSINGLETON(ObjectpoolManager)->Update();
	GETSINGLETON(ObjectpoolManager)->Render();
	//** 초기화 및 사용할 리스트에 추가.
	GETSINGLETON(ObjectpoolManager)->AddEnalbeList(Vector3(4.0f, 15.0f));		

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

	//** DesableList 전제 삭제
	//** EnableList 전제 삭제


	return 0;
}

void Output(float _x, float _y, string _str)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	cout << _str << endl;
}