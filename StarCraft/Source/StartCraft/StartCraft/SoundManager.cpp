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

	FMOD_System_CreateStream(g_psystem, "Resources/Sound/MainMenu/MainMenu.mp3", FMOD_LOOP_NORMAL, 0, &g_psound[MAINMENUBGM]);
	FMOD_System_CreateStream(g_psystem, "Resources/Sound/Game/TerranBGM.mp3", FMOD_LOOP_NORMAL, 0, &g_psound[TERRAN_BGM]);

	
	
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
	for (int i = 0; i < EFFSD_END; i++) {
		sprintf_s(str, "Sound/effsound%d.wav", i + 1);
		FMOD_System_CreateSound(effg_psystem, (const char*)str, FMOD_DEFAULT, 0, &effg_psound[i]);
	}
	
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/MainMenu/MouseClick.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::MAIN_MENU_CLICK]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/IllegalClick.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::ILLEGAL_CLICK]);

	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/MoreMineral.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::MORE_MINERAL]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/ScvBorn.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::SCV_BORN]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/ScvSelect.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::SCV_SELECT]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/ScvMove.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::SCV_MOVE]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/ScvCantBuild.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::SCV_CANT_BUILD]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/ScvBuildDone.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::SCV_BUILD_DONE]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/ScvDead.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::SCV_DEAD]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/ScvBuildOK.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::SCV_BUILD_OK]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/ScvDoingBuild.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::SCV_DOING_BUILD]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/ScvMining.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::SCV_MINING]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/SelectBuilding.ogg", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::SELECT_BUILDING]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/MarineBorn.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::MARINE_BORN]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/MarineAttack.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::MARINE_ATTACK]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/MarineDead.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::MARINE_DEAD]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/MarineMove.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::MARINE_MOVE]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/MarineSelect.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::MARINE_SELECT]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/MarineBullet.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::MARINE_BULLET]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/GhostBorn.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::GHOST_BORN]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/GhostAttack.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::GHOST_ATTACK]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/GhostDead.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::GHOST_DEAD]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/GhostMove.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::GHOST_MOVE]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/GhostSelect.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::GHOST_SELECT]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/GhostNuclear.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::GHOST_NUCLEAR]);
	FMOD_System_CreateSound(effg_psystem, "Resources/Sound/Game/GhostBullet.wav", FMOD_DEFAULT, 0, &effg_psound[EFFSOUNDKIND::GHOST_BULLET]);






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
