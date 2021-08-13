#pragma once
#include "Headers.h"
#include "Define.h"

class Object;
class PrototypeManager
{
public:
	DECLARE_SINGLETON(PrototypeManager)

private:
	map<string, Object*> PrototypeList;//원본 저장 리스트

public:
	void Initialize(string);
	void Release();
	Object* FindObject(string _str);

private:
	PrototypeManager();
public:
	~PrototypeManager();
};

