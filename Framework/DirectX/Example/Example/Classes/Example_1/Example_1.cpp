#include "Example_1.h"
#include "../Global/Utility/Structure/CArrayList.h"
#include "../Global/Utility/Structure/CLinkedList.h"

#define EXAMPLE_TYPE_ARRAY_LIST				1
#define EXAMPLE_TYPE_LINKED_LIST			2

#define EXAMPLE_TYPE			EXAMPLE_TYPE_LINKED_LIST

void Example_1(void)
{
#if EXAMPLE_TYPE == EXAMPLE_TYPE_ARRAY_LIST
	CArrayList oArrayList(5);

	for(int i = 0; i < 10; ++i)
	{
		oArrayList.addValue(i + 1);
	}

	oArrayList.removeValue(3);
	oArrayList.removeValue(5);
	oArrayList.insertValue(4, 100);

	printf("===== �迭 ����Ʈ ���� =====\n");

	for(int i = 0; i < oArrayList.getCount(); ++i)
	{
		printf("Index %d: %d\n", i, oArrayList.getValue(i));
	}
#else
	CLinkedList oLinkedList;

	for(int i = 0; i < 10; ++i)
	{
		oLinkedList.addValue(i + 1);
	}

	oLinkedList.removeValue(1);
	oLinkedList.removeValue(5);
	oLinkedList.removeValue(10);
	oLinkedList.insertValue(0, 300);
	oLinkedList.insertValue(4, 100);
	oLinkedList.insertValue(7, 200);

	printf("===== ���� ����Ʈ ���� =====\n");

	for(int i = 0; i < oLinkedList.getCount(); ++i)
	{
		printf("Index %d: %d\n", i, oLinkedList.getValue(i));
	}
#endif			// #if EXAMPLE_TYPE == EXAMPLE_TYPE_ARRAY_LIST
}
