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
	list<Object*> EnableList; //활성화 오브젝트 리스트
	list<Object*> DesableList; //비활성화 오브젝트 리스트
	
public:
	list<Object*>* GetDesableList() { return &DesableList; }
	void AddEnalbeList(string, Vector3);//활성화 리스트에 추가
	list<Object*>* GetEnableList() { return &EnableList; }
	
private:
	void AddDesObjList(string);//비활성화 리스트에 추가

public:
	ObjectpoolManager();
	~ObjectpoolManager();
};

