#include "stdafx.h"

CSoundManager* CSoundManager::m_pInstance = nullptr;

void CSoundManager::Init()
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

	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CSoundManager::SetUpSound()
{
	//사운드 시스템 생성
	FMOD_System_Create(&g_psystem);
	//채널 수 , 모드, 0
	FMOD_System_Init(g_psystem, SD_END, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateStream(g_psystem, "Resources/Sound/BGM/Menu.wav", FMOD_LOOP_NORMAL, 0, &g_psound[MAINMENUBGM]);

	char name[STR_LEN];
	
	for (int i = 0; i < NUM_OF_STAGE; ++i) {
		sprintf_s(name, "Resources\\Sound\\BGM\\Stage%d.wav", i + 1);
		FMOD_System_CreateStream(g_psystem, name, FMOD_LOOP_NORMAL, 0, &g_psound[i + 2]);
	}
	
}


void CSoundManager::PlayeSound(SOUNDKIND eSound)
{
	BGSoundOff();
	FMOD_System_PlaySound(g_psystem, FMOD_CHANNEL_FREE, g_psound[eSound], 0, &g_pchannel[eSound]);
}

void CSoundManager::SetUpEffectSound()
{
	char str[STR_LEN];

	//사운드 시스템 생성
	FMOD_System_Create(&effg_psystem);

	//채널 수 , 모드, 0
	FMOD_System_Init(effg_psystem, EFFSD_END, FMOD_INIT_NORMAL, NULL);

	//사운드 경로
	for (int i = 0; i<EFFSD_END; i++) {
		sprintf_s(str, "Sound/effsound%d.wav", i + 1);
		FMOD_System_CreateSound(effg_psystem, (const char*)str, FMOD_DEFAULT, 0, &effg_psound[i]);
	}
	
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Effect/Start.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::START_EFSD]);
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
void CSoundManager::PlayerEffectSound(EFFSOUNDKIND eSound)
{
	FMOD_System_PlaySound(effg_psystem, FMOD_CHANNEL_FREE, effg_psound[eSound], 0, &effg_pchannel[eSound]);
}
