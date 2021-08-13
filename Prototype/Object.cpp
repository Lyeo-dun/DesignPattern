#include "Object.h"

Object::Object()
{
}
Object::~Object()
{
}
void Object::Initialize()
{
	str = "Object";
	Transinfo.Position = Vector3(0.0f, 0.0f);
	Transinfo.Index = 0;
}
int Object::Update()
{
	return 0;
}
void Object::Render()
{
	COORD Pos = { (SHORT)Transinfo.Position.x, (SHORT)Transinfo.Position.y + Transinfo.Index };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	cout << Transinfo.Index << " : " << str << endl;
}