#pragma once

#include "../../Define/KGlobalDefine.h"

//! 3���� ���
class C3DMatrix
{
public:

	enum
	{
		SIZE = 3
	};

public:			// operator

	//! operator()
	float& operator()(int a_nRow, int a_nCol);

	//! operator() const
	float operator()(int a_nRow, int a_nCol) const;

public:			// public �Լ�

	//! ���� ����� ��ȯ�Ѵ�
	C3DMatrix getIdentityMatrix(void);

	//! ��ġ ����� ��ȯ�Ѵ�
	C3DMatrix getTransposeMatrix(void);

	//! �̵� ����� ��ȯ�Ѵ�
	C3DMatrix getTranslationMatrix(float a_fX, float a_fY);

	//! ô�� ����� ��ȯ�Ѵ�
	C3DMatrix getScaleMatrix(float a_fScaleX, int a_fScaleY);

	//! ȸ�� ����� ��ȯ�Ѵ�
	C3DMatrix getRotationMatrix(float a_fRoll);

	//! ������ ��ȯ�Ѵ�
	C3DMatrix getAddMatrix(const C3DMatrix& a_rstMatrix);

	//! ������ ��ȯ�Ѵ�
	C3DMatrix getSubMatrix(const C3DMatrix& a_rstMatrix);

	//! ������ ��ȯ�Ѵ�
	C3DMatrix getMulMatrix(const C3DMatrix& a_rstMatrix);

	//! ��Į�� ������ ��ȯ�Ѵ�
	C3DMatrix getScalarMulMatrix(float a_fScalar);

public:			// ������

	//! ������
	C3DMatrix(void);

public:			// public ����

	float m_afValueMatrix[SIZE][SIZE];
};
