#include "stdafx.h"
#include "Scene.h"
#include "Boss.h"

void CScene::CreateNormalEnemy()
{
	for (int i = 0; i < (rand() % (NORMAL_ENEMY_MAX_SPAWN_NUM - NORMAL_ENEMY_MIN_SPAWN_NUM)) + NORMAL_ENEMY_MIN_SPAWN_NUM; ++i) {
		Obj* pObj = ObjMaker<CNormalEnemy>::Create(static_cast<float>((rand() % (W_MAX - 50)) + 50), static_cast<float>(rand() % 300), NORMAL_ENEMY_SPEED);
		dynamic_cast<CEnemy*>(pObj)->SetNormalBulletList(SCENEMANAGER->GetEnemyNormallBulletList());
		SCENEMANAGER->InsertObj(pObj, OBJ_ARR::ENEMY);
	}

}

void CScene::CreateBoss(char* name)
{
	Obj* pObj;
	if (!strcmp(name, "BOSS1")) pObj = ObjMaker<CBoss>::Create(120, 50, name);
	else pObj = ObjMaker<CBoss>::Create(-50, 50, name);
	dynamic_cast<CBoss*>(pObj)->SetNormalBulletList(SCENEMANAGER->GetEnemyNormallBulletList());
	SCENEMANAGER->InsertObj(pObj, OBJ_ARR::BOSS);
}
