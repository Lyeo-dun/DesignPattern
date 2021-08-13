#include "ObjectpoolManager.h"
#include "PrototypeManager.h"

int main(void)
{

	{
	
		list<Object*> TmpDesObjList = *GETSINGLETON(ObjectpoolManager)->GetDesableList();
		//** DesableList �� ������ ������Ʈ�� �ִ��� Ȯ�� �ϰ� ���ٸ�...
		if (TmpDesObjList.empty())
		{
			//** 5���� ������Ʈ�� �߰� ������ ��...
			GETSINGLETON(ObjectpoolManager)->AddObjList("Object");
		}

		//** �߰� ������ ������Ʈ �ϳ��� ����.
		list<Object*>::iterator iter = TmpDesObjList.begin();

		//** �ʱ�ȭ �� �ʿ��� ���� �ۼ�.
		(*iter)->Initialize();

		//** ����� ����Ʈ�� �߰�.
		EnableList.push_back((*iter));

		//** ���� ����Ʈ���� ����.
		DesableList.pop_front();

	}


	for (list<Object*>::iterator iter = EnableList.begin();
		iter != EnableList.end();)
	{
		int iResult = (*iter)->Update();
		(*iter)->Render();

		if (iResult == 1)
		{
			//** ���� ����Ʈ���� ����.
			DesableList.push_back((*iter));

			//** ����� ����Ʈ�� �߰�.
			iter = EnableList.erase(iter);
		}
		else
			++iter;
	}










	{
		//** ���� ����Ʈ�� �����ִ� ������Ʈ�� ���� Ȯ��. (DesableList)
		string Buffer = "DesableList : " + to_string(DesableList.size());
		Output(10, 1, Buffer);
		Buffer.clear();

		//** ���� ����Ʈ�� �����ִ� ������Ʈ�� ���� Ȯ��. (EnableList)
		Buffer = "EnableList : " + to_string(EnableList.size());
		Output(10, 2, Buffer);
	}

	//** DesableList ���� ����
	for (list<Object*>::iterator iter = DesableList.begin();
		iter != DesableList.end(); ++iter)
	{
		delete (*iter);
		(*iter) = nullptr;
	}
	DesableList.clear();


	//** EnableList ���� ����
	for (list<Object*>::iterator iter = EnableList.begin();
		iter != EnableList.end(); ++iter)
	{
		delete (*iter);
		(*iter) = nullptr;
	}
	EnableList.clear();

	return 0;
}