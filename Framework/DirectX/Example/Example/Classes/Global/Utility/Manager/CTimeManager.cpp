#include "CTimeManager.h"

#define DELTA_TIME_TYPE_TICK				1
#define DELTA_TIME_TYPE_TIME_POINT			2

#define DELTA_TIME_TYPE			DELTA_TIME_TYPE_TICK

CTimeManager::CTimeManager(void)
	:
	m_fTimeScale(1.0f)
{
	// Do Nothing
}

void CTimeManager::init(int a_nTargetFPS)
{
	m_nTargetFPS = a_nTargetFPS;

#if DELTA_TIME_TYPE == DELTA_TIME_TYPE_TICK
	QueryPerformanceFrequency(&m_stFrequency);

	QueryPerformanceCounter(&m_stPrevCounter);
	QueryPerformanceCounter(&m_stStartCounter);
#else
	m_oPrevTimePoint = std::chrono::system_clock::now();
	m_oStartTimePoint = std::chrono::system_clock::now();
#endif			// #if DELTA_TIME_TYPE == DELTA_TIME_TYPE_TICK
}

void CTimeManager::update(void)
{
	float fFrameRate = (1.0f / m_nTargetFPS) - m_fOverTime;

#if DELTA_TIME_TYPE == DELTA_TIME_TYPE_TICK
	LARGE_INTEGER stLastCounter;
	QueryPerformanceCounter(&stLastCounter);

	while(fFrameRate > 0.0f)
	{
		LARGE_INTEGER stCounter;
		QueryPerformanceCounter(&stCounter);

		fFrameRate -= this->calculateDeltaTime(stCounter, stLastCounter);
		stLastCounter = stCounter;
	}

	m_fDeltaTime = this->calculateDeltaTime(stLastCounter, m_stPrevCounter);
	m_fRunningTime = this->calculateDeltaTime(stLastCounter, m_stStartCounter);

	m_fOverTime = fabsf(fFrameRate);
	m_stPrevCounter = stLastCounter;
#else
	auto oLastTimePoint = std::chrono::system_clock::now();

	while(fFrameRate > 0.0f)
	{
		auto oTimePoint = std::chrono::system_clock::now();
		fFrameRate -= this->calculateDeltaTime(oTimePoint, oLastTimePoint);

		oLastTimePoint = oTimePoint;
	}

	m_fDeltaTime = this->calculateDeltaTime(oLastTimePoint, m_oPrevTimePoint);
	m_fRunningTime = this->calculateDeltaTime(oLastTimePoint, m_oStartTimePoint);

	m_fOverTime = fabsf(fFrameRate);
	m_oPrevTimePoint = oLastTimePoint;
#endif			// #if DELTA_TIME_TYPE == DELTA_TIME_TYPE_TICK
}

int CTimeManager::getFPS(void)
{
	return 1.0f / m_fDeltaTime;
}

int CTimeManager::getTargetFPS(void)
{
	return m_nTargetFPS;
}

float CTimeManager::getDeltaTime(void)
{
	return m_fDeltaTime;
}

float CTimeManager::getRunningTime(void)
{
	return m_fRunningTime;
}

void CTimeManager::setTimeScale(float a_fTimeScale)
{
	m_fTimeScale = a_fTimeScale;
}

float CTimeManager::calculateDeltaTime(const LARGE_INTEGER& a_rstCurrentCounter, const LARGE_INTEGER& a_rstPrevCounter)
{
	float fDeltaTime = (a_rstCurrentCounter.QuadPart - a_rstPrevCounter.QuadPart) / (float)m_stFrequency.QuadPart;
	return fDeltaTime * m_fTimeScale;
}

float CTimeManager::calculateDeltaTime(const TTimePoint& a_rCurrentTimePoint, const TTimePoint& a_rPrevTimePoint)
{
	std::chrono::duration<float> oDeltaTime(a_rCurrentTimePoint - a_rPrevTimePoint);
	return oDeltaTime.count() * m_fTimeScale;
}
