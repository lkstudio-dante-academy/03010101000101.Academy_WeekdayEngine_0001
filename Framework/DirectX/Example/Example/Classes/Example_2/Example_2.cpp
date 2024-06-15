#include "Example_2.h"
#include "../Global/Utility/Structure/CStack.h"
#include "../Global/Utility/Structure/CQueue.h"

#define EXAMPLE_TYPE_STACK			1
#define EXAMPLE_TYPE_QUEUE			2

#define EXAMPLE_TYPE			EXAMPLE_TYPE_QUEUE

void Example_2(void)
{
#if EXAMPLE_TYPE == EXAMPLE_TYPE_STACK
	CStack oStack(5);

	for(int i = 0; i < 10; ++i)
	{
		oStack.pushValue(i + 1);
	}

	printf("===== ���� ���� =====\n");

	while(!oStack.isEmpty())
	{
		printf("Value: %d\n", oStack.popValue());
	}
#else
	CQueue oQueue(5);

	for(int i = 0; i < 10; ++i)
	{
		oQueue.enqueueValue(i + 1);
	}

	printf("===== ť ���� =====\n");

	while(!oQueue.isEmpty())
	{
		printf("Value: %d\n", oQueue.dequeueValue());
	}
#endif			// #if EXAMPLE_TYPE == EXAMPLE_TYPE_STACK
}
