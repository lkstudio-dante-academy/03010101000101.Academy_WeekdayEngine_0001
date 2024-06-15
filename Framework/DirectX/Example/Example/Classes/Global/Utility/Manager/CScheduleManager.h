#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! ������ ������
class CScheduleManager : public IUpdateable
{
public:

	//! ������
	struct STSchedule
	{
		float m_fDelayTime;
		float m_fLeftDelayTime;

		bool m_bIsLoop;
		std::function<void(const std::string&)> m_oCallback;
	};

public:			// �������̽� ����

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CScheduleManager);

	//! �������� ����Ѵ�
	void addSchedule(const std::string& a_rKey, const std::function<void(const std::string&)>& a_rCallback, float a_fDelayTime = 0.0f, bool a_bIsLoop = false);

	//! �������� �����Ѵ�
	void removeSchedule(const std::string& a_rKey);

private:			// private ����

	std::unordered_map<std::string, STSchedule> m_oScheduleList;
};
