#include "Example_7.h"
#include "../Global/Utility/Math/C3DVector.h"
#include "../Global/Utility/Math/C3DMatrix.h"

#define EXAMPLE_TYPE_MATRIX					1
#define EXAMPLE_TYPE_TRANSFORMATION			2

#define EXAMPLE_TYPE			EXAMPLE_TYPE_TRANSFORMATION

void Example_7(void)
{
#if EXAMPLE_TYPE == EXAMPLE_TYPE_MATRIX
	C3DMatrix oMatrixA;
	C3DMatrix oMatrixB;

	oMatrixA = oMatrixA.getIdentityMatrix();
	oMatrixA(2, 0) = 5.0f;
	oMatrixA(2, 1) = 5.0f;

	oMatrixB = oMatrixB.getIdentityMatrix();
	oMatrixB(0, 0) = 0.5f;
	oMatrixB(1, 1) = 0.5f;

	printf("===== ��� A =====\n");
	for(int i = 0; i < C3DMatrix::SIZE; ++i)
	{
		for(int j = 0; j < C3DMatrix::SIZE; ++j)
		{
			printf("%f ", oMatrixA(i, j));
		}

		printf("\n");
	}

	printf("\n===== ��� B =====\n");
	for(int i = 0; i < C3DMatrix::SIZE; ++i)
	{
		for(int j = 0; j < C3DMatrix::SIZE; ++j)
		{
			printf("%f ", oMatrixB(i, j));
		}

		printf("\n");
	}

	printf("\n===== ���� ��� =====\n");
	C3DMatrix oIdentityMatrix = oMatrixA.getIdentityMatrix();

	for(int i = 0; i < C3DMatrix::SIZE; ++i)
	{
		for(int j = 0; j < C3DMatrix::SIZE; ++j)
		{
			printf("%f ", oIdentityMatrix(i, j));
		}

		printf("\n");
	}

	printf("\n===== ���� =====\n");
	C3DMatrix oAddMatrix(oMatrixA.getAddMatrix(oMatrixB));

	for(int i = 0; i < C3DMatrix::SIZE; ++i)
	{
		for(int j = 0; j < C3DMatrix::SIZE; ++j)
		{
			printf("%f ", oAddMatrix(i, j));
		}

		printf("\n");
	}

	printf("\n===== ���� =====\n");
	C3DMatrix oSubMatrix(oMatrixA.getSubMatrix(oMatrixB));

	for(int i = 0; i < C3DMatrix::SIZE; ++i)
	{
		for(int j = 0; j < C3DMatrix::SIZE; ++j)
		{
			printf("%f ", oSubMatrix(i, j));
		}

		printf("\n");
	}

	printf("\n===== ���� =====\n");
	C3DMatrix oMulMatrix(oMatrixA.getMulMatrix(oMatrixB));

	for(int i = 0; i < C3DMatrix::SIZE; ++i)
	{
		for(int j = 0; j < C3DMatrix::SIZE; ++j)
		{
			printf("%f ", oMulMatrix(i, j));
		}

		printf("\n");
	}

	printf("\n===== ��Į�� ���� =====\n");
	C3DMatrix oScalarMulMatrix(oMatrixA.getScalarMulMatrix(5.0f));

	for(int i = 0; i < C3DMatrix::SIZE; ++i)
	{
		for(int j = 0; j < C3DMatrix::SIZE; ++j)
		{
			printf("%f ", oScalarMulMatrix(i, j));
		}

		printf("\n");
	}
#else
	C3DVector oPosition(1.0f, 1.0f, 1.0f);
	C3DVector oDirection(1.0f, 1.0f, 0.0f);

	printf("===== ���� ���� =====\n");
	printf("��ġ: %f, %f, %f\n", oPosition.m_fX, oPosition.m_fY, oPosition.m_fZ);
	printf("����: %f, %f, %f\n", oDirection.m_fX, oDirection.m_fY, oDirection.m_fZ);

	printf("\n===== �̵� ��ȯ =====\n");

	C3DMatrix oTranslation;
	oTranslation = oTranslation.getTranslationMatrix(10.0f, 10.0f);

	C3DVector oPositionResult = oPosition.getTransformVector(oTranslation);
	C3DVector oDirectionResult = oDirection.getTransformVector(oTranslation);

	printf("��ġ ���: %f, %f, %f\n", oPositionResult.m_fX, oPositionResult.m_fY, oPositionResult.m_fZ);
	printf("���� ���: %f, %f, %f\n", oDirectionResult.m_fX, oDirectionResult.m_fY, oDirectionResult.m_fZ);

	printf("\n===== ô�� ��ȯ =====\n");

	C3DMatrix oScale;
	oScale = oScale.getScaleMatrix(10.0f, 10.0f);

	oPositionResult = oPosition.getTransformVector(oScale);
	oDirectionResult = oDirection.getTransformVector(oScale);

	printf("��ġ ���: %f, %f, %f\n", oPositionResult.m_fX, oPositionResult.m_fY, oPositionResult.m_fZ);
	printf("���� ���: %f, %f, %f\n", oDirectionResult.m_fX, oDirectionResult.m_fY, oDirectionResult.m_fZ);

	printf("\n===== ȸ�� ��ȯ =====\n");

	C3DMatrix oRotation;
	oRotation = oRotation.getRotationMatrix(D3DXToRadian(45.0f));

	oPositionResult = oPosition.getTransformVector(oRotation);
	oDirectionResult = oDirection.getTransformVector(oRotation);

	printf("��ġ ���: %f, %f, %f\n", oPositionResult.m_fX, oPositionResult.m_fY, oPositionResult.m_fZ);
	printf("���� ���: %f, %f, %f\n", oDirectionResult.m_fX, oDirectionResult.m_fY, oDirectionResult.m_fZ);
#endif			// #if EXAMPLE_TYPE == EXAMPLE_TYPE_MATRIX
}
