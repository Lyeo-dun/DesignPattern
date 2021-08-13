#include "ObjectpoolManager.h"
#include "PrototypeManager.h"
#include "Object.h"


ObjectpoolManager::~ObjectpoolManager()
{
}

ObjectpoolManager::ObjectpoolManager()
{
}

void ObjectpoolManager::Initialize()
{
	GETSINGLETON(PrototypeManager)->Initialize();
}

void ObjectpoolManager::AddDesObjList(string _Str)
{
	Object* Obj = GETSINGLETON(PrototypeManager)->FindObject(_Str);
	
	if (Obj == nullptr)
	{
		COORD Pos = { (SHORT)80, (SHORT)30 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

		cout << "���� ã�� ������Ʈ�� ã�� �� �����ϴ�!" << endl;
		return;
	}

	for (int i = 0; i < 5; ++i)
	{
		Object* TmpObj = Obj->Clone();
		TmpObj->Initialize();

		DesableList.push_back(TmpObj);
	}
}

