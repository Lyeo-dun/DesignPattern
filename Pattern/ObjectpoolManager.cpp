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
	for (auto iter = EnableList.begin();iter != EnableList.end();)
	{
		(*iter)->Update();

		if ((*iter)->GetPosition().x >= 100) //���� ������ �Ǿ��ٸ�
		{
			DesableList.push_back((*iter)); //��Ȱ��ȭ ����Ʈ�� �߰�
			iter = EnableList.erase(iter); //Ȱ��ȭ ����Ʈ���� ����
		}
		else
			++iter;//for���� ������
	}
}

void ObjectpoolManager::Render()
{
	for (auto iter = EnableList.begin(); iter != EnableList.end() ; ++iter)
	{
		(*iter)->Render();//Ȱ��ȭ ����Ʈ�� �ִ� �͸� ����
	}
}

void ObjectpoolManager::Release()
{
	auto iter = EnableList.begin();

	for (iter = EnableList.begin(); iter != EnableList.end(); ++iter)
		SAFE_DELETE(*iter); //Ȱ��ȭ ����Ʈ ���� ������Ʈ ����
	for (iter = DesableList.begin(); iter != DesableList.end(); ++iter)
		SAFE_DELETE(*iter); //��Ȱ��ȭ ����Ʈ ���� ������Ʈ ����

	EnableList.clear(); //Ȱ��ȭ ����Ʈ ����
	DesableList.clear(); //��Ȱ��ȭ ����Ʈ ����
}

void ObjectpoolManager::AddDesObjList(string _Str)
{
	//������Ÿ�� �Ŵ����� �ִ� ���� ������Ʈ ã��
	auto Obj = GETSINGLETON(PrototypeManager)->FindObject(_Str);
	
	if (Obj == nullptr)//������ ���ٸ�
	{
		COORD Pos = { (SHORT)80, (SHORT)30 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

		cout << "���� ã�� ������Ʈ�� ã�� �� �����ϴ�!" << endl;
		return;//�Լ� ����
	}

	//������ �ִٸ�
	for (int i = 0; i < 5; ++i)
	{
		auto TmpObj = Obj->Clone(); //���� ����
		DesableList.push_back(TmpObj); //��Ȱ��ȭ ����Ʈ�� �߰�
	}
}

void ObjectpoolManager::AddEnalbeList(string _str, Vector3 _pos)
{
	if (DesableList.empty())//��Ȱ��ȭ ������Ʈ�� Ȱ��ȭ ��ų ������Ʈ�� ���ٸ�
		AddDesObjList(_str); //��Ȱ��ȭ ������Ʈ�� �����

	auto iter = DesableList.begin();

	(*iter)->Initialize();
	(*iter)->SetPosition(_pos);

	EnableList.push_back((*iter));
	DesableList.pop_front();
}

