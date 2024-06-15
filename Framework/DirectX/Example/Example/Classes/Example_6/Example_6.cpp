#include "Example_6.h"
#include "../Global/Utility/Math/C3DVector.h"

void Example_6(void)
{
	C3DVector oVectorA(1.0f, 0.0f, 0.0f);
	C3DVector oVectorB(0.0f, 1.0f, 0.0f);

	printf("===== ���� =====\n");
	printf("���� A �� ����: %f\n", oVectorA.getLength());
	printf("���� B �� ����: %f\n", oVectorB.getLength());

	printf("\n===== ���� =====\n");
	printf("���� A �� ���� B �� ����: %f\n", oVectorA.getDotVector(oVectorB));

	printf("\n===== ���� =====\n");
	C3DVector oCrossVector(oVectorA.getCrossVector(oVectorB));

	printf("���� A �� ���� B �� ����: %f, %f, %f\n", oCrossVector.m_fX,
		oCrossVector.m_fY,
		oCrossVector.m_fZ);

	printf("\n===== ���� =====\n");
	C3DVector oAddVector(oVectorA.getAddVector(oVectorB));

	printf("���� A �� ���� B �� ����: %f, %f, %f\n", oAddVector.m_fX,
		oAddVector.m_fY,
		oAddVector.m_fZ);

	printf("\n===== ���� =====\n");
	C3DVector oSubVector(oVectorA.getSubVector(oVectorB));

	printf("���� A �� ���� B �� ����: %f, %f, %f\n", oSubVector.m_fX,
		oSubVector.m_fY,
		oSubVector.m_fZ);

	printf("\n===== ��Į�� ���� =====\n");
	C3DVector oMulVector(oVectorA.getMulVector(10.0f));

	printf("���� A �� ��Į�� ����: %f, %f, %f\n", oMulVector.m_fX,
		oMulVector.m_fY,
		oMulVector.m_fZ);
}
