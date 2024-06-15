#pragma once

#include "../../Define/KGlobalDefine.h"

//! ���� ����Ʈ
class CLinkedList
{
public:

	enum
	{
		INVALID_VALUE = -1
	};

	// ���
	struct STNode
	{
		int m_nValue;
		struct STNode* m_pstNextNode;
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
	void removeValue(int a_nValue);

	//! ���� �ִ��� �˻��Ѵ�
	bool isContainValue(int a_nValue);

public:			// �Ҹ���

	//! �Ҹ���
	virtual ~CLinkedList(void);

private:			// private �Լ�

	//! ��带 �����Ѵ�
	STNode* createNode(int a_nValue);

private:			// private ����

	STNode* m_pstHeadNode = nullptr;
	STNode* m_pstTailNode = nullptr;
};
