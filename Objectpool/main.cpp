#include <iostream>
#include <Windows.h>
#include <list>

using namespace std;

template<typename T>
void Safe_Delete(T& _obj)
{
	delete (_obj);
	_obj = NULL;
}
#define SAFE_DELETE(type) Safe_Delete(type)

struct Object
{
	int Key;
	int Value;

	Object() : Key(0), Value(0) {}
	Object(int _Key, int _Value) : Key(_Key), Value(_Value) {}
	~Object() {}
};

bool check = false;
int Count = 0;

int main(void)
{
	//배열은 리스트, 삭제는 #define safe delete
	list<Object*> EnableList; //실제 사용한 오브젝트 리스트(랜더링 될 오브젝트 리스트)
	list<Object*> DesableList; //사용을 마친 오브젝트 리스트

	while (true)
	{
		system("cls");

		check = false;

		//키 입력 이벤트
		if (GetAsyncKeyState(VK_RETURN))
			check = true;//한번만 입력받음

		if (check)
		{
			//DesableList가 있는지 확인
			if (DesableList.empty())
			{
				//없다면 새로운 오브젝트를 만든다
				for (int i = 0; i < 5; ++i)
				{
					DesableList.push_back(new Object(Count++, 0));
				}
			}

			//추가된 오브젝트 하나 선택
			list<Object*>::iterator iter = DesableList.begin();
			//초기화
			(*iter)->Value = 0;
			//사용할 리스트 추가
			EnableList.push_back((*iter));
			//현재 리스트에서는 삭제
			DesableList.pop_front();

		}

		//Render
		cout << "EnableList" << endl;
		for (list<Object*>::iterator iter = EnableList.begin(); iter != EnableList.end();/*증감문 따로 제어*/)
		{
			(*iter)->Value++;
			cout << "Key: " << (*iter)->Key << ", Value: " << (*iter)->Value << endl << endl;

			//출력된 오브젝트의 value값이 일정 값 이상이 된다면 
			if ((*iter)->Value >= 50)
			{
				//현재 리스트에서 DesableList로 옮김
				DesableList.push_back((*iter));
				//현재 리스트에서 삭제
				iter = EnableList.erase(iter);
			}
			else
				++iter; //증감문
		}

		cout << "DesableList" << endl;
		for (list<Object*>::iterator iter = DesableList.begin(); iter != DesableList.end();++iter)
		{
			cout << "Key: " << (*iter)->Key << endl;
		}

		Sleep(50);
	}

	for (list<Object*>::iterator iter = DesableList.begin(); iter != DesableList.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	DesableList.clear();

	for (list<Object*>::iterator iter = EnableList.begin(); iter != EnableList.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	EnableList.clear();

	return 0;
}