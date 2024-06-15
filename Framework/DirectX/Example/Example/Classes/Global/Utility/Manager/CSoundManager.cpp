#include "CSoundManager.h"
#include "../../Function/GlobalFunction.h"
#include "../Sound/CSound.h"

CSoundManager::CSoundManager(void)
	:
	m_fEffectSoundVolume(1.0f),
	m_fBackgroundSoundVolume(1.0f)
{
	// Do Nothing
}

CSoundManager::~CSoundManager(void)
{
	SAFE_RELEASE(m_pDirectSound);
}

void CSoundManager::init(HWND a_hWindow)
{
	m_pDirectSound = this->createDirectSound(a_hWindow);
	m_pPrimarySoundBuffer = this->createPrimarySoundBuffer();
}

LPDIRECTSOUND CSoundManager::getDirectSound(void)
{
	return m_pDirectSound;
}

LPDIRECTSOUNDBUFFER CSoundManager::getPrimarySoundBuffer(void)
{
	return m_pPrimarySoundBuffer;
}

void CSoundManager::setEffectSoundVolume(float a_fVolume)
{
	m_fEffectSoundVolume = a_fVolume;

	for(auto& rValueType : m_oEffectSoundListContainer)
	{
		for(auto pSound : rValueType.second)
		{
			if(pSound != nullptr)
			{
				pSound->setVolume(a_fVolume);
			}
		}
	}
}

void CSoundManager::setBackgroundSoundVolume(float a_fVolume)
{
	m_fBackgroundSoundVolume = a_fVolume;

	if(m_pBackgroundSound != nullptr)
	{
		m_pBackgroundSound->setVolume(m_fBackgroundSoundVolume);
	}
}

CSound* CSoundManager::playEffectSound(const std::string& a_rFilepath, bool a_bIsLoop)
{
	auto pSound = this->findPlayableEffectSound(a_rFilepath);

	if(pSound != nullptr)
	{
		pSound->playSound(a_bIsLoop);
		this->setEffectSoundVolume(m_fEffectSoundVolume);
	}

	return pSound;
}

void CSoundManager::pauseEffectSound(CSound* a_pEffectSound)
{
	if(a_pEffectSound != nullptr)
	{
		a_pEffectSound->pauseSound();
	}
}

void CSoundManager::stopEffectSound(CSound* a_pEffectSound)
{
	if(a_pEffectSound != nullptr)
	{
		a_pEffectSound->stopSound();
	}
}

void CSoundManager::playAllEffectSounds(void)
{
	for(auto& rValueType : m_oEffectSoundListContainer)
	{
		for(int i = 0; i < rValueType.second.size(); ++i)
		{
			auto pSound = rValueType.second[i];

			if(pSound != nullptr)
			{
				bool bIsLoop = pSound->isLoop();
				pSound->playSound(bIsLoop);
			}
		}
	}
}

void CSoundManager::pauseAllEffectSounds(void)
{
	for(auto& rValueType : m_oEffectSoundListContainer)
	{
		for(int i = 0; i < rValueType.second.size(); ++i)
		{
			auto pSound = rValueType.second[i];

			if(pSound != nullptr)
			{
				pSound->pauseSound();
			}
		}
	}
}

void CSoundManager::stopAllEffectSounds(void)
{
	for(auto& rValueType : m_oEffectSoundListContainer)
	{
		for(int i = 0; i < rValueType.second.size(); ++i)
		{
			auto pSound = rValueType.second[i];

			if(pSound != nullptr)
			{
				pSound->stopSound();
			}
		}
	}
}

CSound* CSoundManager::playBackgroundSound(const std::string& a_rFilepath, bool a_bIsLoop)
{
	if(m_pBackgroundSound != nullptr)
	{
		m_pBackgroundSound->stopSound();
		SAFE_DELETE(m_pBackgroundSound);
	}

	m_pBackgroundSound = CreateInstance<CSound>(a_rFilepath);
	m_pBackgroundSound->playSound(a_bIsLoop);

	this->setBackgroundSoundVolume(m_fBackgroundSoundVolume);
	return m_pBackgroundSound;
}

void CSoundManager::pauseBackgroundSound(void)
{
	if(m_pBackgroundSound != nullptr)
	{
		m_pBackgroundSound->pauseSound();
	}
}

void CSoundManager::stopBackgroundSound(void)
{
	if(m_pBackgroundSound != nullptr)
	{
		m_pBackgroundSound->stopSound();
	}
}

LPDIRECTSOUND CSoundManager::createDirectSound(HWND a_hWindow)
{
	LPDIRECTSOUND pDirectSound = nullptr;
	DirectSoundCreate(NULL, &pDirectSound, NULL);

	pDirectSound->SetCooperativeLevel(a_hWindow, DSSCL_PRIORITY);
	return pDirectSound;
}

LPDIRECTSOUNDBUFFER CSoundManager::createPrimarySoundBuffer(void)
{
	DSBUFFERDESC stBufferDesc;
	ZeroMemory(&stBufferDesc, sizeof(stBufferDesc));

	stBufferDesc.dwSize = sizeof(stBufferDesc);
	stBufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;

	LPDIRECTSOUNDBUFFER pSoundBuffer = nullptr;
	m_pDirectSound->CreateSoundBuffer(&stBufferDesc, &pSoundBuffer, NULL);

	/** VS Input */�� �����Ѵ�
	// {
	WAVEFORMATEX stWaveFormat;
	ZeroMemory(&stWaveFormat, sizeof(stWaveFormat));

	stWaveFormat.cbSize = sizeof(stWaveFormat);
	stWaveFormat.wFormatTag = WAVE_FORMAT_PCM;
	stWaveFormat.nChannels = 2;
	stWaveFormat.nSamplesPerSec = 22050;
	stWaveFormat.wBitsPerSample = 16;
	stWaveFormat.nBlockAlign = (stWaveFormat.wBitsPerSample / 8) * stWaveFormat.nChannels;
	stWaveFormat.nAvgBytesPerSec = stWaveFormat.nSamplesPerSec * stWaveFormat.nBlockAlign;

	pSoundBuffer->SetFormat(&stWaveFormat);
	// }

	return pSoundBuffer;
}

CSound* CSoundManager::findPlayableEffectSound(const std::string& a_rKey)
{
	if(m_oEffectSoundListContainer.find(a_rKey) == m_oEffectSoundListContainer.end())
	{
		TEffectSoundList oEffectSoundList{
			nullptr
		};

		m_oEffectSoundListContainer.insert(decltype(m_oEffectSoundListContainer)::value_type(a_rKey, oEffectSoundList));
	}

	auto oIterator = m_oEffectSoundListContainer.find(a_rKey);

	// ���带 Ž���Ѵ�
	auto oSoundIterator = std::find_if(oIterator->second.begin(), oIterator->second.end(), [=](CSound* a_pSound) -> bool
	{
		return a_pSound == nullptr || !a_pSound->isPlaying();
	});

	/** VS Output */ �� ���尡 ���� ���
	if(oSoundIterator != oIterator->second.end())
	{
		// ���� �� ���尡 ���� ���
		if(*oSoundIterator != nullptr)
		{
			return *oSoundIterator;
		}

		return CreateInstance<CSound>(a_rKey);
	}

	return nullptr;
}
