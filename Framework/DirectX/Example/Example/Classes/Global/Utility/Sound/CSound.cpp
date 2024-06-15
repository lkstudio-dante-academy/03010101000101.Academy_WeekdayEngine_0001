#include "CSound.h"
#include "../../Function/GlobalFunction.h"
#include "../Manager/CSoundManager.h"
#include "../Manager/CResourceManager.h"

CSound::CSound(const std::string& a_rFilepath)
{
	m_stWaveSound = GET_WAVE_SOUND(a_rFilepath);
	m_pSoundBuffer = this->createSoundBuffer();

	this->resetSound(a_rFilepath);
}

CSound::~CSound(void)
{
	SAFE_RELEASE(m_pSoundBuffer);
}

DWORD CSound::getStatus(void)
{
	DWORD nStatus = 0;
	m_pSoundBuffer->GetStatus(&nStatus);

	return nStatus;
}

void CSound::setVolume(float a_fVolume)
{
	a_fVolume = ClampFloatValue(a_fVolume, 0.0f, 1.0f);
	m_pSoundBuffer->SetVolume((1.0f - a_fVolume) * DSBVOLUME_MIN);
}

void CSound::playSound(bool a_bIsLoop)
{
	DWORD nFlags = a_bIsLoop ? DSBPLAY_LOOPING : 0;

	m_pSoundBuffer->SetCurrentPosition(m_nPausePosition);
	m_pSoundBuffer->Play(0, 0, nFlags);
}

void CSound::stopSound(void)
{
	m_nPausePosition = 0;
	m_pSoundBuffer->Stop();
}

void CSound::pauseSound(void)
{
	m_pSoundBuffer->GetCurrentPosition(&m_nPausePosition, NULL);
	m_pSoundBuffer->Stop();
}

bool CSound::isLoop(void)
{
	DWORD nStatus = this->getStatus();
	return nStatus & DSBSTATUS_LOOPING;
}

bool CSound::isPlaying(void)
{
	DWORD nStatus = this->getStatus();
	return nStatus & DSBSTATUS_PLAYING;
}

void CSound::resetSound(const std::string& a_rFilepath)
{
	m_stWaveSound = GET_WAVE_SOUND(a_rFilepath);

	this->stopSound();
	m_pSoundBuffer->SetFormat(&m_stWaveSound.m_stWaveFormat);

	/** VS Input */�� �����Ѵ�
	// {
	BYTE* pnBytesA = nullptr;
	BYTE* pnBytesB = nullptr;

	DWORD nNumBytesA = 0;
	DWORD nNumBytesB = 0;

	if(SUCCEEDED(m_pSoundBuffer->Lock(0, m_stWaveSound.m_nNumBytes, (void**)&pnBytesA, &nNumBytesA, (void**)&pnBytesB, &nNumBytesB, 0)))
	{
		CopyMemory(pnBytesA, m_stWaveSound.m_pnBytes, m_stWaveSound.m_nNumBytes);
		m_pSoundBuffer->Unlock(NULL, 0, NULL, 0);
	}
	// }
}

LPDIRECTSOUNDBUFFER CSound::createSoundBuffer(void)
{
	DSBUFFERDESC stBufferDesc;
	ZeroMemory(&stBufferDesc, sizeof(stBufferDesc));

	stBufferDesc.dwSize = sizeof(stBufferDesc);
	stBufferDesc.dwBufferBytes = m_stWaveSound.m_nNumBytes;
	stBufferDesc.guid3DAlgorithm = GUID_NULL;
	stBufferDesc.lpwfxFormat = &m_stWaveSound.m_stWaveFormat;
	stBufferDesc.dwFlags = DSBCAPS_STATIC | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLVOLUME;

	LPDIRECTSOUNDBUFFER pSoundBuffer = nullptr;
	GET_DIRECT_SOUND()->CreateSoundBuffer(&stBufferDesc, &pSoundBuffer, NULL);

	return pSoundBuffer;
}
