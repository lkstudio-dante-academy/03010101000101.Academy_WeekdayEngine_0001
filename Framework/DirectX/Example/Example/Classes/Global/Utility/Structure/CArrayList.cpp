#include "CArrayList.h"

CArrayList::CArrayList(int a_nSize)
	:
	m_nSize(a_nSize)
{
	m_pnValues = new int[a_nSize];
}

CArrayList::~CArrayList(void)
{
	SAFE_DELETE_ARRAY(m_pnValues);
}

int CArrayList::getValue(int a_nIndex)
{
	if(a_nIndex < 0 || a_nIndex >= m_nCount)
	{
		return (int)INVALID_VALUE;
	}

	return m_pnValues[a_nIndex];
}

int CArrayList::getCount(void)
{
	return m_nCount;
}

void CArrayList::addValue(int a_nValue)
{
	// ���� �߰� �� �� ���� ���
	if(m_nCount < m_nSize)
	{
		m_pnValues[m_nCount] = a_nValue;
	}
	// ���۰� ���� á�� ���
	else
	{
		int nNewSize = m_nSize * 2;
		int* pnNewValues = new int[nNewSize];

		// �޸𸮸� Ȯ�� �� ���� �����͸� �����Ѵ�.
		memcpy(pnNewValues, m_pnValues, sizeof(int) * m_nSize);
		delete[] m_pnValues;

		// ���ο� �Ҵ��� ���� ������ ���� �����͸� �����Ѵ�.
		m_nSize = nNewSize;
		m_pnValues = pnNewValues;

		m_pnValues[m_nCount] = a_nValue;
	}

	m_nCount += 1;
}

void CArrayList::insertValue(int a_nIndex, int a_nValue)
{
	if(a_nIndex < 0 || a_nIndex >= m_nCount)
	{
		return;
	}

	// ���۰� ���� á�� ���
	if(m_nCount >= m_nSize)
	{
		int nNewSize = m_nSize * 2;
		int* pnNewValues = new int[nNewSize];

		// �޸𸮸� Ȯ�� �� ���� �����͸� �����Ѵ�.
		memcpy(pnNewValues, m_pnValues, sizeof(int) * m_nSize);
		delete[] m_pnValues;

		// ���ο� �Ҵ��� ���� ������ ���� �����͸� �����Ѵ�.
		m_nSize = nNewSize;
		m_pnValues = pnNewValues;
	}

	for(int i = m_nCount; i > a_nIndex; --i)
	{
		m_pnValues[i] = m_pnValues[i - 1];
	}

	m_nCount += 1;
	m_pnValues[a_nIndex] = a_nValue;
}

void CArrayList::replaceValue(int a_nIndex, int a_nValue)
{
	if(a_nIndex < 0 || a_nIndex >= m_nCount)
	{
		return;
	}

	m_pnValues[a_nIndex] = a_nValue;
}

void CArrayList::removeValue(int a_nValue)
{
	int nRemoveIndex = -1;

	// �����ؾ� �� ���� �ε����� Ž���Ѵ�.
	for(int i = 0; i < m_nCount; ++i)
	{
		if(m_pnValues[i] == a_nValue)
		{
			nRemoveIndex = i;
			break;
		}
	}

	// �ش� �ε����� �����Ѵ�
	this->removeIndex(nRemoveIndex);
}

void CArrayList::removeIndex(int a_nIndex)
{
	// ��ȿ�� �ε��� �� ��� 
	// (��, �ش� ���� ������ ���� ���� ���� ���)
	if(a_nIndex >= 0)
	{
		for(int i = a_nIndex; i < m_nCount - 1; ++i)
		{
			m_pnValues[i] = m_pnValues[i + 1];
		}

		m_nCount -= 1;
	}
}
