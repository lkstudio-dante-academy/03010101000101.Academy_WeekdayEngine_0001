#include "CStack.h"

CStack::CStack(int a_nSize)
	:
	m_oValueList(a_nSize)
{
	// Do Nothing
}

void CStack::pushValue(int a_nValue)
{
	m_oValueList.addValue(a_nValue);
}

int CStack::popValue(void)
{
	if(this->isEmpty())
	{
		return CArrayList::INVALID_VALUE;
	}

	int nLastIndex = m_oValueList.getCount() - 1;
	int nValue = m_oValueList.getValue(nLastIndex);

	m_oValueList.removeIndex(nLastIndex);
	return nValue;
}

bool CStack::isEmpty(void)
{
	return m_oValueList.getCount() <= 0;
}
