#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! �ð� ������
class CTimeManager : public IUpdateable
{
public:

	// Ÿ���� �������Ѵ�
	typedef std::chrono::system_clock::time_point TTimePoint;

public:			// �������̽� ����

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// getter, setter

	//! FPS �� ��ȯ�Ѵ�
	int getFPS(void);

	//! ��ǥ FPS �� ��ȯ�Ѵ�
	int getTargetFPS(void);

	//! �ð� ������ ��ȯ�Ѵ�
	float getDeltaTime(void);

	//! ���� �ð��� ��ȯ�Ѵ�
	float getRunningTime(void);

	//! �ð� ������ �����Ѵ�
	void setTimeScale(float a_fTimeScale);

public:			// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CTimeManager);

	//! �ʱ�ȭ
	void init(int a_nTargetFPS = 60);

	//! �ð� ������ ����Ѵ�
	float calculateDeltaTime(const LARGE_INTEGER& a_rstCurrentCounter, const LARGE_INTEGER& a_rstPrevCounter);

	//! �ð� ������ ����Ѵ�
	float calculateDeltaTime(const TTimePoint& a_rCurrentTimePoint, const TTimePoint& a_rPrevTimePoint);

private:			// ������

	//! ������
	CTimeManager(void);

private:			// private ����

	int m_nTargetFPS = 0;

	float m_fOverTime = 0.0f;
	float m_fTimeScale = 0.0f;
	float m_fDeltaTime = 0.0f;
	float m_fRunningTime = 0.0f;

	LARGE_INTEGER m_stFrequency;
	LARGE_INTEGER m_stPrevCounter;
	LARGE_INTEGER m_stStartCounter;

	TTimePoint m_oPrevTimePoint;
	TTimePoint m_oStartTimePoint;
};
