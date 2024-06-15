#pragma once

#pragma once

#include "../../Define/KGlobalDefine.h"
#include "CLinkedList.h"

//! �ؽ�
class CHash
{
public:

	enum
	{
		TABLE_SIZE = 10
	};

public:			// public �Լ�

	//! ���� �߰��Ѵ�
	void addValue(int a_nValue);

	//! ���� �����Ѵ�
	void removeValue(int a_nValue);

	//! �ؽð� ������� �˻��Ѵ�
	bool isEmpty(void);

	//! ���� �ִ��� �˻��Ѵ�
	bool isContainValue(int a_nValue);

private:			// private �Լ�

	//! �ؽ� ���� �����Ѵ�
	int createHashValue(int a_nValue);

private:			// private ����

	CLinkedList m_astHashTable[TABLE_SIZE];
};
