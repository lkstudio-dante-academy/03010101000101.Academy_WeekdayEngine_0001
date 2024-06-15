#include "CScheduleManager.h"
#include "CTimeManager.h"

void CScheduleManager::update(void)
{
	auto oIterator = m_oScheduleList.begin();

	while(oIterator != m_oScheduleList.end())
	{
		oIterator->second.m_fLeftDelayTime -= GET_DELTA_TIME();

		if(oIterator->second.m_fLeftDelayTime > 0.0f)
		{
			++oIterator;
		}
		else
		{
			oIterator->second.m_oCallback(oIterator->first);
			oIterator->second.m_fLeftDelayTime = oIterator->second.m_fDelayTime;

			if(oIterator->second.m_bIsLoop)
			{
				++oIterator;
			}
			else
			{
				oIterator = m_oScheduleList.erase(oIterator);
			}
		}
	}
}

void CScheduleManager::addSchedule(const std::string& a_rKey, const std::function<void(const std::string&)>& a_rCallback, float a_fDelayTime, bool a_bIsLoop)
{
	auto oIterator = m_oScheduleList.find(a_rKey);

	if(oIterator == m_oScheduleList.end())
	{
		STSchedule stSchedule = {
			a_fDelayTime,
			a_fDelayTime,
			a_bIsLoop,
			a_rCallback
		};

		m_oScheduleList.insert(decltype(m_oScheduleList)::value_type(a_rKey, stSchedule));
	}
}

void CScheduleManager::removeSchedule(const std::string& a_rKey)
{
	m_oScheduleList.erase(a_rKey);
}
