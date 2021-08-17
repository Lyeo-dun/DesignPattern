#include "PrototypeManager.h"
#include "Object.h"


PrototypeManager::PrototypeManager()
{
}

PrototypeManager::~PrototypeManager()
{
	Release();
}

void PrototypeManager::Initialize(string _Str)
{
	//기본적인 초기화(세부 초기화는 개별적으로 각자)
	Transform TransInfo;
	TransInfo.Position = Vector3(0.0f, 0.0f);

	PrototypeList[_Str] = new Object(TransInfo);//원본 리스트에 추가
}

void PrototypeManager::Release()
{
	for (auto iter = PrototypeList.begin(); iter != PrototypeList.end(); ++iter)
	{
		SAFE_DELETE((*iter).second); //원본 저장 리스트 내의 원본들 삭제
	}

	PrototypeList.clear();//원본 리스트 삭제
}

Object* PrototypeManager::FindObject(string _str)
{
	//원본 리스트에 원본 오브젝트가 있는지 확인
	auto iter = PrototypeList.find(_str);

	//찾는 오브젝트가 없다면 nullptr 반환
	if (iter == PrototypeList.end())
		return nullptr;

	//아니라면 찾은 오브젝트 반환
	return iter->second;
}