#include "CBinaryTree.h"

//! ��� ��带 �����Ѵ�
static void RemoveAllNodes(CBinaryTree::STNode* a_pstRootNode)
{
	if(a_pstRootNode != nullptr)
	{
		RemoveAllNodes(a_pstRootNode->m_pstLChild);
		RemoveAllNodes(a_pstRootNode->m_pstRChild);

		SAFE_DELETE(a_pstRootNode);
	}
}

CBinaryTree::~CBinaryTree(void)
{
	RemoveAllNodes(m_pstRootNode);
}

void CBinaryTree::addValue(int a_nValue)
{
	auto pstNewNode = this->createNode(a_nValue);

	if(this->isEmpty())
	{
		m_pstRootNode = pstNewNode;
	}
	else
	{
		STNode* pstParentNode = nullptr;
		auto pstCurrentNode = m_pstRootNode;

		while(pstCurrentNode != nullptr)
		{
			pstParentNode = pstCurrentNode;

			/** VS Input */� �� ���� ���� ���
			if(a_nValue < pstCurrentNode->m_nValue)
			{
				pstCurrentNode = pstCurrentNode->m_pstLChild;
			}
			else
			{
				pstCurrentNode = pstCurrentNode->m_pstRChild;
			}
		}

		// �θ� ����� �� ���� ���� ���
		if(a_nValue < pstParentNode->m_nValue)
		{
			pstParentNode->m_pstLChild = pstNewNode;
		}
		else
		{
			pstParentNode->m_pstRChild = pstNewNode;
		}
	}
}

void CBinaryTree::removeValue(int a_nValue)
{
	STNode* pstParentNode = nullptr;
	auto pstRemoveNode = m_pstRootNode;

	while(pstRemoveNode != nullptr &&
		pstRemoveNode->m_nValue != a_nValue)
	{
		pstParentNode = pstRemoveNode;

		/** VS Input */� �� ���� ���� ���
		if(a_nValue < pstRemoveNode->m_nValue)
		{
			pstRemoveNode = pstRemoveNode->m_pstLChild;
		}
		else
		{
			pstRemoveNode = pstRemoveNode->m_pstRChild;
		}
	}

	// ���� ã�� ������ ���
	if(pstRemoveNode == nullptr)
	{
		return;
	}

	// �ڽ��� �ΰ� �� ���
	if(pstRemoveNode->m_pstLChild != nullptr &&
		pstRemoveNode->m_pstRChild != nullptr)
	{
		STNode* pstTempParentNode = pstRemoveNode;
		auto pstTempRemoveNode = pstRemoveNode->m_pstLChild;

		// �ļ� ��带 Ž���Ѵ�
		while(pstTempRemoveNode->m_pstRChild != nullptr)
		{
			pstTempParentNode = pstTempRemoveNode;
			pstTempRemoveNode = pstTempRemoveNode->m_pstRChild;
		}

		pstRemoveNode->m_nValue = pstTempRemoveNode->m_nValue;

		pstParentNode = pstTempParentNode;
		pstRemoveNode = pstTempRemoveNode;
	}

	// �θ� ��尡 ���� ���
	if(pstParentNode == nullptr)
	{
		if(pstRemoveNode->m_pstLChild != nullptr)
		{
			m_pstRootNode = pstRemoveNode->m_pstLChild;
		}
		else
		{
			m_pstRootNode = pstRemoveNode->m_pstRChild;
		}
	}
	else
	{
		// ���� ��尡 �θ� ����� ���� �ڽ� �� ���
		if(pstParentNode->m_pstLChild == pstRemoveNode)
		{
			if(pstRemoveNode->m_pstLChild != nullptr)
			{
				pstParentNode->m_pstLChild = pstRemoveNode->m_pstLChild;
			}
			else
			{
				pstParentNode->m_pstLChild = pstRemoveNode->m_pstRChild;
			}
		}
		else
		{
			if(pstRemoveNode->m_pstLChild != nullptr)
			{
				pstParentNode->m_pstRChild = pstRemoveNode->m_pstLChild;
			}
			else
			{
				pstParentNode->m_pstRChild = pstRemoveNode->m_pstRChild;
			}
		}
	}

	delete pstRemoveNode;
}

bool CBinaryTree::isEmpty(void)
{
	return m_pstRootNode == nullptr;
}

bool CBinaryTree::isContainValue(int a_nValue)
{
	auto pstCurrentNode = m_pstRootNode;

	while(pstCurrentNode != nullptr &&
		pstCurrentNode->m_nValue != a_nValue)
	{
		if(a_nValue < pstCurrentNode->m_nValue)
		{
			pstCurrentNode = pstCurrentNode->m_pstLChild;
		}
		else
		{
			pstCurrentNode = pstCurrentNode->m_pstRChild;
		}
	}

	return pstCurrentNode != nullptr;
}

void CBinaryTree::printAllNodes(EPrintOrder a_ePrintOrder)
{
	switch(a_ePrintOrder)
	{
		case EPrintOrder::PRE_ORDER:
		{
			this->printPreOrder(m_pstRootNode);
			break;
		}
		case EPrintOrder::IN_ORDER:
		{
			this->printInOrder(m_pstRootNode);
			break;
		}
		case EPrintOrder::POST_ORDER:
		{
			this->printPostOrder(m_pstRootNode);
			break;
		}
	}
}

void CBinaryTree::printPreOrder(STNode* a_pstRootNode)
{
	if(a_pstRootNode != nullptr)
	{
		printf("Value: %d\n", a_pstRootNode->m_nValue);

		this->printPreOrder(a_pstRootNode->m_pstLChild);
		this->printPreOrder(a_pstRootNode->m_pstRChild);
	}
}

void CBinaryTree::printInOrder(STNode* a_pstRootNode)
{
	if(a_pstRootNode != nullptr)
	{
		this->printInOrder(a_pstRootNode->m_pstLChild);

		printf("Value: %d\n", a_pstRootNode->m_nValue);
		this->printInOrder(a_pstRootNode->m_pstRChild);
	}
}

void CBinaryTree::printPostOrder(STNode* a_pstRootNode)
{
	if(a_pstRootNode != nullptr)
	{
		this->printPostOrder(a_pstRootNode->m_pstLChild);
		this->printPostOrder(a_pstRootNode->m_pstRChild);

		printf("Value: %d\n", a_pstRootNode->m_nValue);
	}
}

CBinaryTree::STNode* CBinaryTree::createNode(int a_nValue)
{
	auto pstNode = new STNode();
	pstNode->m_nValue = a_nValue;
	pstNode->m_pstLChild = nullptr;
	pstNode->m_pstRChild = nullptr;

	return pstNode;
}
