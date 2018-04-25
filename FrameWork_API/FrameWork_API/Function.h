#pragma once
template<typename T>
void SafeDelete(T& Obj) {
	if (Obj) {
		delete Obj;
		Obj = nullptr;

	}
}