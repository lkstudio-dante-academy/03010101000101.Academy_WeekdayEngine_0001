#include "CQueue.h"

CQueue::CQueue(int a_nSize)
	:
	m_oValueList(a_nSize)
{
	// Do Nothing
}

void CQueue::enqueueValue(int a_nValue)
{
	m_oValueList.addValue(a_nValue);
}

int CQueue::dequeueValue(void)
{
	if(this->isEmpty())
	{
		return CArrayList::INVALID_VALUE;
	}

	int nValue = m_oValueList.getValue(0);
	m_oValueList.removeIndex(0);

	return nValue;
}

bool CQueue::isEmpty(void)
{
	return m_oValueList.getCount() <= 0;
}
