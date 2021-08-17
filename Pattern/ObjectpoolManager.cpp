#include "ObjectpoolManager.h"
#include "PrototypeManager.h"
#include "Object.h"


ObjectpoolManager::~ObjectpoolManager()
{
	Release();
}

ObjectpoolManager::ObjectpoolManager()
{
}

void ObjectpoolManager::Initialize()
{
}

void ObjectpoolManager::Update()
{
	//초기화 및 사용할 리스트에 추가.
	if (GetAsyncKeyState(VK_RETURN))
		AddEnalbeList("Object", Vector3(4.0f, 15.0f));


	for (auto iter = EnableList.begin();iter != EnableList.end();)
	{
		int Result = (*iter)->Update();

		if (Result) //일정 조건이 되었다면
		{
			DesableList.push_back((*iter)); //비활성화 리스트에 추가
			iter = EnableList.erase(iter); //활성화 리스트에서 삭제
		}
		else
			++iter;//for문의 증감문
	}
}

void ObjectpoolManager::Render()
{
	{
		auto TmpList = GetDesableList();

		//** 현재 리스트에 남아있는 오브젝트의 개수 확인. (DesableList)
		auto Buffer = "DesableList : " + to_string(TmpList->size());
		Output(10, 1, Buffer);

		Buffer.clear();
		TmpList = nullptr;

		TmpList = GetEnableList();
		//** 현재 리스트에 남아있는 오브젝트의 개수 확인. (EnableList)
		Buffer = "EnableList : " + to_string(TmpList->size());
		Output(10, 2, Buffer);
	}

	for (auto iter = EnableList.begin(); iter != EnableList.end() ; ++iter)
	{
		(*iter)->Render();//활성화 리스트에 있는 것만 렌더
	}
}

void ObjectpoolManager::Release()
{
	auto iter = EnableList.begin();

	for (iter = EnableList.begin(); iter != EnableList.end(); ++iter)
		SAFE_DELETE(*iter); //활성화 리스트 내의 오브젝트 삭제
	for (iter = DesableList.begin(); iter != DesableList.end(); ++iter)
		SAFE_DELETE(*iter); //비활성화 리스트 내의 오브젝트 삭제

	EnableList.clear(); //활성화 리스트 삭제
	DesableList.clear(); //비활성화 리스트 삭제
}

void ObjectpoolManager::AddDesObjList(string _Str)
{
	//프로토타입 매니저에 있는 원본 오브젝트 찾기
	auto Obj = GETSINGLETON(PrototypeManager)->FindObject(_Str);
	
	if (Obj == nullptr)//원본이 없다면
	{
		COORD Pos = { (SHORT)80, (SHORT)30 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

		cout << "현재 찾는 오브젝트를 찾을 수 없습니다!" << endl;
		return;//함수 종료
	}

	//원본이 있다면
	for (int i = 0; i < 5; ++i)
	{
		auto TmpObj = Obj->Clone(); //원본 복사
		DesableList.push_back(TmpObj); //비활성화 리스트에 추가
	}
}

void ObjectpoolManager::Output(float _x, float _y, string _str)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	cout << _str << endl;
}

void ObjectpoolManager::AddEnalbeList(string _str, Vector3 _pos)
{
	if (DesableList.empty())//비활성화 오브젝트에 활성화 시킬 오브젝트가 없다면
		AddDesObjList(_str); //비활성화 오브젝트를 만든다

	auto iter = DesableList.begin();

	(*iter)->Initialize();
	(*iter)->SetPosition(_pos);

	EnableList.push_back((*iter));
	DesableList.pop_front();
}

