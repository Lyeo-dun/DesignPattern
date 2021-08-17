#include "Object.h"


void Object::Initialize()
{
	Texture = "-->";
	Transinfo.Position = Vector3(4.0f, 15.0f);
	Transinfo.Scale = Vector3((float)Texture.length(), 1.0f);
}

int Object::Update()
{
	Transinfo.Position.x += 2.0f;

	if (Transinfo.Position.x >= 100)
		return 1;

	return 0;
}

void Object::Render()
{
	COORD Pos = { (SHORT)Transinfo.Position.x, (SHORT)Transinfo.Position.y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	cout << Texture << endl;
}
