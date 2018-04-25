#include "stdafx.h"
#include "MainGame.h"
#include "Obj.h"
#include "Player.h"

MainGame::MainGame()
{
}

void MainGame::Initialize()
{
	BITMAPMANAGER->Initialize();
	SCENEMANAGER->Initialize();
	srand(unsigned(time));
}

void MainGame::Update()
{
	SCENEMANAGER->Update();
}

void MainGame::LateUpdate()
{
	SCENEMANAGER->LateUpdate();
}

void MainGame::Render()
{
	SCENEMANAGER->Render();
	RENDERMANAGER->Render();
}

void MainGame::Release()
{

}


MainGame::~MainGame()
{
}
