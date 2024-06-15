#include "Example_4.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Structure/CPriorityQueue.h"

void Example_4(void)
{
	CPriorityQueue oPriorityQueue(5);

	for(int i = 0; i < 10; ++i)
	{
		oPriorityQueue.enqueueValue(CreateIntRandomValue(0, 100));
	}

	printf("===== �켱���� ť ���� =====\n");

	while(!oPriorityQueue.isEmpty())
	{
		printf("Value: %d\n", oPriorityQueue.dequeueValue());
	}
}
