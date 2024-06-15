#pragma once

#include "../../Define/KGlobalDefine.h"

//! ����
class CSound
{
public:			// getter, setter

	//! ���¸� ��ȯ�Ѵ�
	DWORD getStatus(void);

	//! ������ �����Ѵ�
	void setVolume(float a_fVolume);

public:			// public �Լ�

	//! ���带 ����Ѵ�
	void playSound(bool a_bIsLoop);

	//! ���带 �����Ѵ�
	void stopSound(void);

	//! ���带 �����Ѵ�
	void pauseSound(void);

	//! ���� ���θ� ��ȯ�Ѵ�
	bool isLoop(void);

	//! ��� ���θ� �˻��Ѵ�
	bool isPlaying(void);

	//! ���带 �����Ѵ�
	void resetSound(const std::string& a_rFilepath);

public:			// ������, �Ҹ���

	//! ������
	CSound(const std::string& a_rFilepath);

	//! �Ҹ���
	virtual ~CSound(void);

private:			// private �Լ�

	//! ���� ���۸� �����Ѵ�
	LPDIRECTSOUNDBUFFER createSoundBuffer(void);

private:			// private ����

	DWORD m_nPausePosition = 0;
	STWaveSound m_stWaveSound;

	LPDIRECTSOUNDBUFFER m_pSoundBuffer = nullptr;
};
