#include "stdafx.h"

CSoundManager* CSoundManager::m_instance = nullptr;

void CSoundManager::Initialize()
{
	SetUpSound();
	SetUpEffectSound();
}

void CSoundManager::Release()
{
	BGSoundOff();
	EffectSoundOff();

	for (int i = 0; i < SD_END; i++) FMOD_Sound_Release(g_psound[i]);
	for (int i = 0; i < EFFSD_END; i++) FMOD_Sound_Release(effg_psound[i]);

	FMOD_System_Close(g_psystem);
	FMOD_System_Release(g_psystem);

	ObjDelete(m_instance);
}
void CSoundManager::SetUpSound()
{
	//사운드 시스템 생성
	FMOD_System_Create(&g_psystem);
	//채널 수 , 모드, 0
	FMOD_System_Init(g_psystem, SD_END, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateStream(g_psystem, "Resources/Sound/BGM/Menu.mp3", FMOD_LOOP_NORMAL, 0, &g_psound[MAINMENUBGM]);
	FMOD_System_CreateStream(g_psystem, "Resources/Sound/BGM/Start.mp3", FMOD_LOOP_OFF, 0, &g_psound[STARTBGM]);

	char name[128];
	int NUM_OF_STAGE = 2;
	
	for (int i = 0; i < NUM_OF_STAGE; ++i) {
		sprintf_s(name, "Resources\\Sound\\BGM\\Stage%d.mp3", i + 1);
		FMOD_System_CreateStream(g_psystem, name, FMOD_LOOP_NORMAL, 0, &g_psound[i + 2]);
	}
	
}


void CSoundManager::PlayeSound(SOUNDKIND esound)
{

	BGSoundOff();
	FMOD_System_PlaySound(g_psystem, FMOD_CHANNEL_FREE, g_psound[esound], 0, &g_pchannel[esound]);
}

void CSoundManager::SetUpEffectSound()
{
	char str[128];

	//사운드 시스템 생성
	FMOD_System_Create(&effg_psystem);

	//채널 수 , 모드, 0
	FMOD_System_Init(effg_psystem, EFFSD_END, FMOD_INIT_NORMAL, NULL);

	//사운드 경로
	for (int i = 0; i<EFFSD_END; i++) {
		sprintf_s(str, "Sound/effsound%d.wav", i + 1);
		FMOD_System_CreateSound(effg_psystem, (const char*)str, FMOD_DEFAULT, 0, &effg_psound[i]);
	}
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Effect/Laser.mp3", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::NORMAL_BULLET_EFSD]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Effect/Missile.mp3", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::MISSILE_EFSD]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Effect/Skill.mp3", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::SKILL_EFSD]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Effect/PlayerDie.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::PLAYER_DIE_EFSD]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Effect/Die.mp3", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::DIE_EFSD]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Effect/ItemDrop.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::ITEM_DROP_EFSD]);
}

void CSoundManager::BGSoundOff()
{
	for (int i = 0; i < SD_END; i++)
		FMOD_Channel_Stop(g_pchannel[i]);
}

void CSoundManager::EffectSoundOff()
{
	for (int i = 0; i < EFFSD_END; i++)
		FMOD_Channel_Stop(effg_pchannel[i]);
}
void CSoundManager::PlayerEffectSound(EFFSOUNDKIND esound)
{

	FMOD_System_PlaySound(effg_psystem, FMOD_CHANNEL_FREE, effg_psound[esound], 0, &effg_pchannel[esound]);

}


CSoundManager::CSoundManager() { this->Initialize(); }

CSoundManager::~CSoundManager() { this->Release(); }