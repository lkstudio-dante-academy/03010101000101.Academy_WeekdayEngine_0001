#pragma once

#include "../../Define/KGlobalDefine.h"

class CSound;

//! ���� ������
class CSoundManager
{
public:

	enum
	{
		MAX_NUM_DUPLICATE_EFFECT_SOUNDS = 5
	};

	// Ÿ�� ������
	// {
	typedef std::array<CSound*,
		MAX_NUM_DUPLICATE_EFFECT_SOUNDS> TEffectSoundList;

	typedef std::unordered_map<std::string,
		TEffectSoundList> TEffectSoundListContainer;
	// }

public:			// getter

	//! ���̷�Ʈ ���带 ��ȯ�Ѵ�
	LPDIRECTSOUND getDirectSound(void);

	//! �� ���� ���۸� ��ȯ�Ѵ�
	LPDIRECTSOUNDBUFFER getPrimarySoundBuffer(void);

	//! ȿ���� ������ �����Ѵ�
	void setEffectSoundVolume(float a_fVolume);

	//! ����� ������ �����Ѵ�
	void setBackgroundSoundVolume(float a_fVolume);

public:			// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CSoundManager);

	//! �ʱ�ȭ
	void init(HWND a_hWindow);

	//! ȿ������ ����Ѵ�
	CSound* playEffectSound(const std::string& a_rFilepath, bool a_bIsLoop = false);

	//! ȿ������ �����Ѵ�
	void pauseEffectSound(CSound* a_pEffectSound);

	//! ȿ������ �����Ѵ�
	void stopEffectSound(CSound* a_pEffectSound);

	//! ��� ȿ������ ����Ѵ�
	void playAllEffectSounds(void);

	//! ��� ȿ������ �����Ѵ�
	void pauseAllEffectSounds(void);

	//! ��� ȿ������ �����Ѵ�
	void stopAllEffectSounds(void);

	//! ������� ����Ѵ�
	CSound* playBackgroundSound(const std::string& a_rFilepath, bool a_bIsLoop = false);

	//! ������� �����Ѵ�
	void pauseBackgroundSound(void);

	//! ������� �����Ѵ�
	void stopBackgroundSound(void);

private:			// private �Լ�

	//! ���̷�Ʈ ���带 �����Ѵ�
	LPDIRECTSOUND createDirectSound(HWND a_hWindow);

	//! �� ���� ���۸� �����Ѵ�
	LPDIRECTSOUNDBUFFER createPrimarySoundBuffer(void);

	//! ��� ������ ȿ������ Ž���Ѵ�
	CSound* findPlayableEffectSound(const std::string& a_rKey);

private:			// ������, �Ҹ���

	//! ������
	CSoundManager(void);

	//! �Ҹ���
	virtual ~CSoundManager(void);

private:			// private ����

	float m_fEffectSoundVolume = 0.0f;
	float m_fBackgroundSoundVolume = 0.0f;

	LPDIRECTSOUND m_pDirectSound = nullptr;
	LPDIRECTSOUNDBUFFER m_pPrimarySoundBuffer = nullptr;

	CSound* m_pBackgroundSound = nullptr;
	TEffectSoundListContainer m_oEffectSoundListContainer;
};
