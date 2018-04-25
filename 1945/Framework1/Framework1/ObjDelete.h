#pragma once
template<typename T>
void ObjDelete(T& Obj) {
	if (Obj) {
		delete Obj;
		Obj = nullptr;

	}
}