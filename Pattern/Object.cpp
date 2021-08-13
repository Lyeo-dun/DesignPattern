#include "Object.h"


void Object::Render()
{
	COORD Pos = { (SHORT)Transinfo.Position.x, (SHORT)Transinfo.Position.y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	cout << Texture << endl;
}