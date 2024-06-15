#include "CPriorityQueue.h"

CPriorityQueue::CPriorityQueue(int a_nSize)
	:
	m_oValueList(a_nSize)
{
	// Do Nothing
}

void CPriorityQueue::enqueueValue(int a_nValue)
{
	m_oValueList.addValue(a_nValue);
	this->reheapUp();
}

int CPriorityQueue::dequeueValue(void)
{
	int nValue = m_oValueList.getValue(0);
	int nLastIndex = m_oValueList.getCount() - 1;

	m_oValueList.replaceValue(0, m_oValueList.getValue(nLastIndex));
	m_oValueList.removeIndex(nLastIndex);

	this->reheapDown();
	return nValue;
}

bool CPriorityQueue::isEmpty(void)
{
	return m_oValueList.getCount() <= 0;
}

void CPriorityQueue::reheapUp(void)
{
	int nIndex = m_oValueList.getCount() - 1;

	while(nIndex > 0)
	{
		int nParentIndex = (nIndex - 1) / 2;
		int nParentValue = m_oValueList.getValue(nParentIndex);

		int nCurrentValue = m_oValueList.getValue(nIndex);

		// �θ��� �� ���� Ŭ ���
		if(nCurrentValue >= nParentValue)
		{
			break;
		}

		m_oValueList.replaceValue(nIndex, nParentValue);
		m_oValueList.replaceValue(nParentIndex, nCurrentValue);

		nIndex = nParentIndex;
	}
}

void CPriorityQueue::reheapDown(void)
{
	int nIndex = 0;

	while(nIndex < m_oValueList.getCount() / 2)
	{
		int nLeftChildIndex = (nIndex * 2) + 1;
		int nRightChildIndex = nLeftChildIndex + 1;

		int nCompareIndex = nLeftChildIndex;
		int nCompareValue = m_oValueList.getValue(nLeftChildIndex);

		// ������ �ڽ��� ���� ���
		if(nRightChildIndex < m_oValueList.getCount())
		{
			int nRightChildValue = m_oValueList.getValue(nRightChildIndex);

			nCompareIndex = (nCompareValue < nRightChildValue) ?
				nCompareIndex : nRightChildIndex;

			nCompareValue = m_oValueList.getValue(nCompareIndex);
		}

		int nCurrentValue = m_oValueList.getValue(nIndex);

		// �ڽ��� �� ���� ���� ���
		if(nCurrentValue <= nCompareValue)
		{
			break;
		}

		m_oValueList.replaceValue(nIndex, nCompareValue);
		m_oValueList.replaceValue(nCompareIndex, nCurrentValue);

		nIndex = nCompareIndex;
	}
}
