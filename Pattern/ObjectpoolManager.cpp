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

void ObjectpoolManager::Update()
{
	for (auto iter = EnableList.begin();iter != EnableList.end();)
	{
		(*iter)->Update();

		if ((*iter)->GetPosition().x >= 100)
		{
			//** 현재 리스트에서 삭제.
			DesableList.push_back((*iter));

			//** 현재 리스트의 다음 리스트의 iter를 줌
			iter = EnableList.erase(iter);
		}
		else
			++iter;
	}
}

void ObjectpoolManager::Render()
{
	for (auto iter = EnableList.begin(); iter != EnableList.end() ; ++iter)
	{
		(*iter)->Render();
	}
}

void ObjectpoolManager::Release()
{
	auto iter = EnableList.begin();
	for (iter = EnableList.begin(); iter != EnableList.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	for (iter = DesableList.begin(); iter != DesableList.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}

	EnableList.clear();
	DesableList.clear();
}

void ObjectpoolManager::AddDesObjList(string _Str)
{
	Object* Obj = GETSINGLETON(PrototypeManager)->FindObject(_Str);
	
	if (Obj == nullptr)
	{
		COORD Pos = { (SHORT)80, (SHORT)30 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

		cout << "현재 찾는 오브젝트를 찾을 수 없습니다!" << endl;
		return;
	}

	for (int i = 0; i < 5; ++i)
	{
		Object* TmpObj = Obj->Clone();
		DesableList.push_back(TmpObj);
	}
}

void ObjectpoolManager::AddEnalbeList(Vector3 _pos)
{
	auto iter = DesableList.begin();

	(*iter)->Initialize();
	(*iter)->SetPosition(_pos);

	EnableList.push_back((*iter));
	DesableList.erase(iter);
}

