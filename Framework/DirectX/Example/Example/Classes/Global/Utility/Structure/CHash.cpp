#include "CHash.h"

void CHash::addValue(int a_nValue)
{
	int nHashValue = this->createHashValue(a_nValue);
	m_astHashTable[nHashValue].addValue(a_nValue);
}

void CHash::removeValue(int a_nValue)
{
	int nHashValue = this->createHashValue(a_nValue);
	m_astHashTable[nHashValue].removeValue(a_nValue);
}

bool CHash::isEmpty(void)
{
	for(int i = 0; i < TABLE_SIZE; ++i)
	{
		if(m_astHashTable[i].getCount() >= 1)
		{
			return false;
		}
	}

	return true;
}

bool CHash::isContainValue(int a_nValue)
{
	int nHashValue = this->createHashValue(a_nValue);
	return m_astHashTable[nHashValue].isContainValue(a_nValue);
}

int CHash::createHashValue(int a_nValue)
{
	std::hash<int> oHash;
	return oHash(a_nValue) % TABLE_SIZE;
}
