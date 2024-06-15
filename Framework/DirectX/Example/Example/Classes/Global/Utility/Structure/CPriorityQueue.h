#pragma once

#include "../../Define/KGlobalDefine.h"
#include "CArrayList.h"

//! �켱���� ť
class CPriorityQueue
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
	CPriorityQueue(int a_nSize);

private:			// private �Լ�

	//! ���� �籸���Ѵ�
	void reheapUp(void);

	//! ���� �籸���Ѵ�
	void reheapDown(void);

private:			// private ����

	CArrayList m_oValueList;
};
