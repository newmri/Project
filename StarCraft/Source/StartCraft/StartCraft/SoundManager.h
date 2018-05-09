#pragma once

#include "../inc/fmod.h"
#pragma comment (lib, "../lib/fmodex_vc.lib")

enum SOUNDKIND
{
	MAINMENUBGM = 0,
	TERRAN_BGM,
	STAGE1BGM,
	SD_END
};

enum EFFSOUNDKIND
{
	MAIN_MENU_CLICK = 0,
	ILLEGAL_CLICK,
	MORE_MINERAL,
	SCV_BORN,
	SCV_SELECT,
	SCV_MOVE,
	SCV_CANT_BUILD,
	SCV_BUILD_DONE,
	SCV_DEAD,
	SCV_BUILD_OK,
	SCV_DOING_BUILD,
	SCV_MINING,
	SELECT_BUILDING,
	MARINE_BORN,
	MARINE_ATTACK,
	MARINE_DEAD,
	MARINE_MOVE,
	MARINE_SELECT,
	MARINE_BULLET,
	GHOST_BORN,
	GHOST_ATTACK,
	GHOST_DEAD,
	GHOST_MOVE,
	GHOST_SELECT,
	GHOST_NUCLEAR,
	GHOST_BULLET,




	EFFSD_END
};

class CSoundManager
{
public:
	void Init();
	void Release();

public:
	void SetUpSound();
	void SetUpEffectSound();
	void PlayeSound(SOUNDKIND eSound);
	void EffectSoundOff();
	void BGSoundOff();
	void PlayerEffectSound(EFFSOUNDKIND eSound);

private:
	FMOD_SYSTEM* GetBgmSystem() { return g_psystem; }
	FMOD_SOUND** GetBgmSound() { return g_psound; }
	FMOD_CHANNEL** GetBgmChannel() { return g_pchannel; }

	FMOD_SYSTEM* GetEftSystem() { return effg_psystem; }
	FMOD_SOUND** GetEftSound() { return effg_psound; }
	FMOD_CHANNEL** GetEftChannel() { return effg_pchannel; }

public:
	static CSoundManager* GetInstance()
	{
		if (m_pInstance == nullptr) m_pInstance = new CSoundManager;
		return m_pInstance;
	}

private:
	CSoundManager() = default;
	~CSoundManager() = default;
	CSoundManager(const CSoundManager&) = delete;
	void operator=(const CSoundManager&) = delete;

private:
	static CSoundManager* m_pInstance;

private:
	FMOD_SYSTEM*	g_psystem;
	FMOD_SOUND*		g_psound[SD_END];
	FMOD_CHANNEL*	g_pchannel[SD_END];

	FMOD_SYSTEM*	effg_psystem;
	FMOD_SOUND*		effg_psound[EFFSD_END];
	FMOD_CHANNEL*	effg_pchannel[EFFSD_END];
};
