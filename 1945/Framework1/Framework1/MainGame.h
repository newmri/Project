#pragma once
class Obj;
class MainGame
{
public:
	MainGame();

	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

	~MainGame();

};

