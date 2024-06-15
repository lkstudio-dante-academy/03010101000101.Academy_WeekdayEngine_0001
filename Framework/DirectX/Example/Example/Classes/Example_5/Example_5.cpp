#include "Example_5.h"
#include "../Global/Utility/Structure/CHash.h"

void Example_5(void)
{
	CHash oHash;

	for(int i = 0; i < 10; ++i)
	{
		oHash.addValue(i + 1);
	}

	printf("===== �ؽ� ���� =====\n");

	printf("%d�� ���� ����: %s\n", 1, oHash.isContainValue(1) ? "true" : "false");
	printf("%d�� ���� ����: %s\n", 5, oHash.isContainValue(5) ? "true" : "false");
	printf("%d�� ���� ����: %s\n", 50, oHash.isContainValue(50) ? "true" : "false");
}
