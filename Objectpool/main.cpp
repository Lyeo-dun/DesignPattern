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
	//�迭�� ����Ʈ, ������ #define safe delete
	list<Object*> EnableList; //���� ����� ������Ʈ ����Ʈ(������ �� ������Ʈ ����Ʈ)
	list<Object*> DesableList; //����� ��ģ ������Ʈ ����Ʈ

	while (true)
	{
		system("cls");

		check = false;

		//Ű �Է� �̺�Ʈ
		if (GetAsyncKeyState(VK_RETURN))
			check = true;//�ѹ��� �Է¹���

		if (check)
		{
			//DesableList�� �ִ��� Ȯ��
			if (DesableList.empty())
			{
				//���ٸ� ���ο� ������Ʈ�� �����
				for (int i = 0; i < 5; ++i)
				{
					DesableList.push_back(new Object(Count++, 0));
				}
			}

			//�߰��� ������Ʈ �ϳ� ����
			list<Object*>::iterator iter = DesableList.begin();
			//�ʱ�ȭ
			(*iter)->Value = 0;
			//����� ����Ʈ �߰�
			EnableList.push_back((*iter));
			//���� ����Ʈ������ ����
			DesableList.pop_front();

		}

		//Render
		cout << "EnableList" << endl;
		for (list<Object*>::iterator iter = EnableList.begin(); iter != EnableList.end();/*������ ���� ����*/)
		{
			(*iter)->Value++;
			cout << "Key: " << (*iter)->Key << ", Value: " << (*iter)->Value << endl << endl;

			//��µ� ������Ʈ�� value���� ���� �� �̻��� �ȴٸ� 
			if ((*iter)->Value >= 50)
			{
				//���� ����Ʈ���� DesableList�� �ű�
				DesableList.push_back((*iter));
				//���� ����Ʈ���� ����
				iter = EnableList.erase(iter);
			}
			else
				++iter; //������
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