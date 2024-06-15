#pragma once

#include "../../Define/KGlobalDefine.h"
#include "CArrayList.h"

//! ����
class CStack
{
public:			// public �Լ�

	//! ���� �߰��Ѵ�
	void pushValue(int a_nValue);

	//! ���� �����Ѵ�
	int popValue(void);

	//! ���۰� ������� �˻��Ѵ�
	bool isEmpty(void);

public:			// ������

	//! ������
	CStack(int a_nSize);

private:			// private ����

	CArrayList m_oValueList;
};
