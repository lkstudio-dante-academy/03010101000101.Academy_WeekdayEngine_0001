#pragma once

#include "../../Define/KGlobalDefine.h"

//! �迭 ����Ʈ
class CArrayList
{
public:

	enum
	{
		INVALID_VALUE = -1
	};

public:			// getter

	//! ���� ��ȯ�Ѵ�
	int getValue(int a_nIndex);

	//! ���� ������ ��ȯ�Ѵ�
	int getCount(void);

public:			// public �Լ�

	//! ���� �߰��Ѵ�
	void addValue(int a_nValue);

	//! ���� �߰��Ѵ�
	void insertValue(int a_nIndex, int a_nValue);

	//! ���� �����Ѵ�
	void replaceValue(int a_nIndex, int a_nValue);

	//! ���� �����Ѵ�
	void removeValue(int a_nValue);

	//! �ش� �ε����� �����Ѵ�
	void removeIndex(int a_nIndex);

public:			// ������, �Ҹ���

	//! ������
	CArrayList(int a_nSize);

	//! �Ҹ���
	virtual ~CArrayList(void);

private:			// private ����

	int m_nCount = 0;			/** VS Input */ ���� ������ ����
	int m_nSize = 0;			/** VS Input */�� ũ��

	int* m_pnValues = nullptr;
};
