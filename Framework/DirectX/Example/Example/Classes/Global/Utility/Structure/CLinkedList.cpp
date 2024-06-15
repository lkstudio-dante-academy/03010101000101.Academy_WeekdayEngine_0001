#include "CLinkedList.h"

CLinkedList::~CLinkedList(void)
{
	auto pstNextNode = m_pstHeadNode;

	while(pstNextNode != nullptr)
	{
		auto pstRemoveNode = pstNextNode;
		pstNextNode = pstNextNode->m_pstNextNode;

		delete pstRemoveNode;
	}
}

int CLinkedList::getValue(int a_nIndex)
{
	if(a_nIndex < 0 || a_nIndex >= this->getCount())
	{
		return INVALID_VALUE;
	}

	auto pstCurrentNode = m_pstHeadNode;

	for(int i = 0; i < a_nIndex; ++i)
	{
		pstCurrentNode = pstCurrentNode->m_pstNextNode;
	}

	return pstCurrentNode->m_nValue;
}

int CLinkedList::getCount(void)
{
	int nCount = 0;
	auto pstCurrentNode = m_pstHeadNode;

	while(pstCurrentNode != nullptr)
	{
		nCount += 1;
		pstCurrentNode = pstCurrentNode->m_pstNextNode;
	}

	return nCount;
}

void CLinkedList::addValue(int a_nValue)
{
	auto pstNewNode = this->createNode(a_nValue);

	// ó�� ���� �߰����� ���
	if(m_pstHeadNode == nullptr)
	{
		m_pstHeadNode = pstNewNode;
		m_pstTailNode = pstNewNode;
	}
	else
	{
		m_pstTailNode->m_pstNextNode = pstNewNode;
		m_pstTailNode = pstNewNode;
	}
}

void CLinkedList::insertValue(int a_nIndex, int a_nValue)
{
	if(a_nIndex < 0 || a_nIndex >= this->getCount())
	{
		return;
	}

	auto pstNewNode = this->createNode(a_nValue);

	// ��忡 �߰� �� ���
	if(a_nIndex <= 0)
	{
		pstNewNode->m_pstNextNode = m_pstHeadNode;
		m_pstHeadNode = pstNewNode;
	}
	else
	{
		auto pstPrevNode = m_pstHeadNode;

		// �߰� �ϱ� ���� ���� ������ ����Ʈ�� Ž���Ѵ�.
		for(int i = 0; i < a_nIndex - 1; ++i)
		{
			pstPrevNode = pstPrevNode->m_pstNextNode;
		}

		pstNewNode->m_pstNextNode = pstPrevNode->m_pstNextNode;
		pstPrevNode->m_pstNextNode = pstNewNode;
	}
}

void CLinkedList::removeValue(int a_nValue)
{
	STNode* pstPrevNode = nullptr;
	auto pstRemoveNode = m_pstHeadNode;

	// ���� ���ϰ� �ִ� ��带 Ž���Ѵ�
	while(pstRemoveNode != nullptr &&
		pstRemoveNode->m_nValue != a_nValue)
	{
		pstPrevNode = pstRemoveNode;
		pstRemoveNode = pstRemoveNode->m_pstNextNode;
	}

	// ���� ã�� ������ ���
	if(pstRemoveNode == nullptr)
	{
		return;
	}

	/** VS Input */�� ���� �� ���
	// (��, ������ 1�� ���)
	if(pstRemoveNode == m_pstHeadNode &&
		pstRemoveNode == m_pstTailNode)
	{
		m_pstHeadNode = nullptr;
		m_pstTailNode = nullptr;
	}
	// ��带 �����ؾ� �� ���
	else if(pstRemoveNode == m_pstHeadNode)
	{
		m_pstHeadNode = pstRemoveNode->m_pstNextNode;
	}
	// ������ �����ؾ� �� ���
	else if(pstRemoveNode == m_pstTailNode)
	{
		m_pstTailNode = pstPrevNode;
		m_pstTailNode->m_pstNextNode = nullptr;
	}
	// �߰� ��带 ���� �� ���
	else
	{
		pstPrevNode->m_pstNextNode = pstRemoveNode->m_pstNextNode;
	}

	delete pstRemoveNode;
}

bool CLinkedList::isContainValue(int a_nValue)
{
	auto pstCurrentNode = m_pstHeadNode;

	while(pstCurrentNode != nullptr &&
		pstCurrentNode->m_nValue != a_nValue)
	{
		pstCurrentNode = pstCurrentNode->m_pstNextNode;
	}

	return pstCurrentNode != nullptr;
}

CLinkedList::STNode* CLinkedList::createNode(int a_nValue)
{
	auto pstNode = new STNode();
	pstNode->m_nValue = a_nValue;
	pstNode->m_pstNextNode = nullptr;

	return pstNode;
}
