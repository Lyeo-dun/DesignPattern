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
	void Release();

private:
	list<Object*> EnableList; //실제 사용한 오브젝트 리스트(랜더링 될 오브젝트 리스트)
	list<Object*> DesableList; //사용을 마친 오브젝트 리스트
	
public:
	list<Object*>* GetDesableList() { return &DesableList; }
	void AddEnalbeList(string, Vector3);
	list<Object*>* GetEnableList() { return &EnableList; }
	
private:
	void AddDesObjList(string);

public:
	ObjectpoolManager();
	~ObjectpoolManager();
};

