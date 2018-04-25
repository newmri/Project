#pragma once

#include "../inc/fmod.h"
#pragma comment (lib, "../lib/fmodex_vc.lib")

enum SOUNDKIND
{
	MAINMENUBGM = 0,
	STARTBGM,
	STAGE1BGM,
	SD_END
};

enum EFFSOUNDKIND
{
	PLAYER_DIE_EFSD = 0,
	DIE_EFSD,
	ITEM_DROP_EFSD,
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
