#pragma once

#include "../../Define/KGlobalDefine.h"
#include "CArrayList.h"

//! ť
class CQueue
{
public:			// public �Լ�

	//! ���� �߰��Ѵ�
	void enqueueValue(int a_nValue);

	//! ���� �����Ѵ�
	int dequeueValue(void);

	//! ���۰� ������� �˻��Ѵ�
	bool isEmpty(void);

public:			// ������

	//! ������
	CQueue(int a_nSize);

private:			// private ����

	CArrayList m_oValueList;
};
