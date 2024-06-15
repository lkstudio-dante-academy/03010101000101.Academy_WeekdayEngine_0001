#pragma once

#include "../../Define/KGlobalDefine.h"

//! ���� Ʈ��
class CBinaryTree
{
public:

	//! ��ȸ ����
	enum EPrintOrder
	{
		PRE_ORDER,
		IN_ORDER,
		POST_ORDER,
		NONE
	};

	//! ���
	struct STNode
	{
		int m_nValue;

		struct STNode* m_pstLChild;
		struct STNode* m_pstRChild;
	};

public:			// public �Լ�

	//! ���� �߰��Ѵ�
	void addValue(int a_nValue);

	//! ���� �����Ѵ�
	void removeValue(int a_nValue);

	//! Ʈ���� ������� �˻��Ѵ�
	bool isEmpty(void);

	//! ���� �ִ��� �˻��Ѵ�
	bool isContainValue(int a_nValue);

	//! Ʈ���� ��ȸ�Ѵ�
	void printAllNodes(EPrintOrder a_ePrintOrder);

private:			// private �Լ�

	//! ���� ��ȸ
	void printPreOrder(STNode* a_pstRootNode);

	//! ���� ��ȸ
	void printInOrder(STNode* a_pstRootNode);

	//! ���� ��ȸ
	void printPostOrder(STNode* a_pstRootNode);

	//! ��带 �����Ѵ�
	STNode* createNode(int a_nValue);

public:			// �Ҹ���

	//! �Ҹ���
	virtual ~CBinaryTree(void);

private:			// private ����

	STNode* m_pstRootNode = nullptr;
};
