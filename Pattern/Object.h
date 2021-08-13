#pragma once
#include "../Common/Headers.h"

class Object
{
private:
	string Texture;
	Transform Transinfo;
public:
	Object* Clone() { return new Object(*this); }
	void Initialize();
	void Update();
	void Render();

	Vector3 GetPosition() { return Transinfo.Position; }
	void SetPosition(Vector3 _Pos) { Transinfo.Position = _Pos; }
	Vector3 GetScale() { return Transinfo.Scale; }
	void SetScale(Vector3 _Scale) { Transinfo.Scale = _Scale; }

public:
	Object() {}
	Object(const Transform& _TransInfo) : Transinfo(_TransInfo) {}
	~Object() {}
};
