#pragma once
#include "Headers.h"
#include "Define.h"

class Object;
class ObjectpoolManager
{
public:
	DECLARE_SINGLETON(ObjectpoolManager)

public:
	void Initialize();
	void Update();
	void Render();
private:
	list<Object*> EnableList; //���� ����� ������Ʈ ����Ʈ(������ �� ������Ʈ ����Ʈ)
	list<Object*> DesableList; //����� ��ģ ������Ʈ ����Ʈ
public:
	list<Object*>* GetDesableList() { return &DesableList; }
	void AddDesObjList(string);
	void AddEnalbeList(Vector3);
	list<Object*>* GetEnableList() { return &EnableList; }

public:
	ObjectpoolManager();
	~ObjectpoolManager();
};

