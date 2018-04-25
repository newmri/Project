#pragma once
class Obj;
template <typename T>
class ObjMaker
{
public:
	static Obj* Create() {
		Obj* newObj = new T;
		newObj->Init();
		return newObj;
	}
	static Obj* Create(float x, float y, float degree) {
		Obj* newObj = new T;
		newObj->Init();
		newObj->SetPos(x, y);
		newObj->SetDegre(degree);
		return newObj;
	}

	static Obj* Create(float x, float y) {
		Obj* newObj = new T;
		newObj->Init();
		newObj->SetPos(x, y);
		return newObj;
	}
	static Obj* Create(float x, float y, int speed) {
		Obj* newObj = new T;
		newObj->Init();
		newObj->SetPos(x, y);
		newObj->SetSpeed(speed);
		return newObj;
	}
	static Obj* Create(float x, float y, char* imageName) {
		Obj* newObj = new T;
		newObj->Init();
		newObj->SetPos(x, y);
		newObj->SetImageName(imageName);
		return newObj;
	}

	static Obj* Create(float x, float y, int speed, char* imageName) {
		Obj* newObj = new T;
		newObj->Init();
		newObj->SetPos(x, y);
		newObj->SetSpeed(speed);
		newObj->SetImageName(imageName);
		return newObj;
	}

};
