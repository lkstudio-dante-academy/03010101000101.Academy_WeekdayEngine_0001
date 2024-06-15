#include "Example_3.h"
#include "../Global/Utility/Structure/CBinaryTree.h"

void Example_3(void)
{
	CBinaryTree oBinaryTree;

	for(int i = 0; i < 10; ++i)
	{
		oBinaryTree.addValue(i + 1);
	}

	oBinaryTree.removeValue(1);
	oBinaryTree.removeValue(2);
	oBinaryTree.removeValue(7);

	printf("===== ���� ��ȸ =====\n");
	oBinaryTree.printAllNodes(CBinaryTree::PRE_ORDER);

	printf("===== ���� ��ȸ =====\n");
	oBinaryTree.printAllNodes(CBinaryTree::IN_ORDER);

	printf("===== ���� ��ȸ =====\n");
	oBinaryTree.printAllNodes(CBinaryTree::POST_ORDER);
}
