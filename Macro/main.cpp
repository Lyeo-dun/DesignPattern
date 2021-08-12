#include <iostream>
#include <string>

using namespace std;

//#define
/*
* 매크로성 키워드
* 기능을 저장할 때 쓰는 매크로
* (ex. 오토 마우스 or 게임의 퀵 바 등)
* 말 그대로 매크로
* define문 처럼 #이 붙으면 전처리기라고 함
* 전처리기를 가장 먼저 읽어 옴
* define은 한줄로 정의하게 되어있음
*/

//#define MAX 128
////정수이며 상수
////무언가를 상수화 시켜준다
////스태틱과는 확인히 다름
//
//#define Output(x, y) cout << (x + y) <<endl
//이 뒤에 세미콜론을 붙여주면 실행함수 내에서 사용할 때 세미콜론을 사용할 필요가 없어짐
//하지만 세미콜론을 붙여주지 않으면 들여쓰기가 되기도 하고 헷갈리기 때문에 보통은 세미콜론을 붙이지 않는다.
//define을 쓸 때에는 세미콜론이 없다

//#define Output(x, y)\
//{\
//	cout << (x + y) << endl;\
//} // \ => 현재 라인과 다음 라인을 이어줌, 현재의 라인과 다음 라인을 하나의 라인으로 인식시킴
////이런 방식으로 define문을 마치 함수처럼 사용이 가능하다
////마지막 한 줄은 제외

template<typename T>
inline void Safe_Release(T & _rObj)
{
	if (_rObj)
	{
		delete _rObj;
		_rObj = nullptr;
	}
}

#define SAFE_DELETE(obj) Safe_Release(obj)

//Singleton
#define DECLARE_SINGLETON(type)\
static type** GetInstance()\
{\
	static type* pInstance = new type;\
\
	if(pInstance == nullptr)\
		pInstance = new type;\
\
	return &pInstance;\
}\
static void DestroyInstance()\
{\
	type** ppInstance = GetInstance();\
\
	if ((*ppInstance) != nullptr)\
	{\
		delete *ppInstance; \
		ppInstance = nullptr; \
	}\
}

#define GETSINGLETON(type) (*type::GetInstance())
#define DESTROYSINGLETON(type) (*type::GetInstance())->DestroyInstance()

class Object
{
public:
	DECLARE_SINGLETON(Object)

public:
	int Number;

	void Render()
	{
		cout << "Object" << endl;
	}
public:
	Object() {}
	~Object() {}
};

int main(void)
{
	//배열의 길이는 정수이면서 상수(고정된 숫자)로만 정의된다
	//배열의 길이는 상수와 정수 두 가지 조건이 만족하는 경우에만 초기값으로 사용가능
	//int Array[MAX];

	//int Num1 = 10;
	//int Num2 = 20;
	//Output(Num1, Num2);

	//string str1 = "Hello ";
	//string str2 = "World!!";
	//Output(str1, str2)
	////문자열에 대한 알고리즘을 써야한다면 만드는 것보다 string을 쓰는게 낫다
	
	/*
	Object* pObj = new Object(3);
	pObj->Render();
	
	SAFE_DELETE(pObj);
	*/

	//pObj->Output();

	//if (pObj == NULL)
	//{
	//	cout << "null!" << endl;
	//}

	GETSINGLETON(Object)->Render();
	GETSINGLETON(Object)->Number = 10;

	cout << GETSINGLETON(Object)->Number << endl;

	DESTROYSINGLETON(Object);

	return 0;
}