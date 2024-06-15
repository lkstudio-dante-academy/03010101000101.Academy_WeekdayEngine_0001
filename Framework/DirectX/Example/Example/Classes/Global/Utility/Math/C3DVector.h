#pragma once

#include "../../Define/KGlobalDefine.h"
#include "C3DMatrix.h"

//! 3���� ����
class C3DVector
{
public:			// public �Լ�

	//! ���̸� ��ȯ�Ѵ�
	float getLength(void);

	//! ���� ����� ��ȯ�Ѵ�
	C3DVector getNormalizeVector(void);

	//! ��Į�� ������ ��ȯ�Ѵ�
	C3DVector getMulVector(float a_fScalar);

	//! ������ ��ȯ�Ѵ�
	C3DVector getAddVector(const C3DVector& a_rVector);

	//! ������ ��ȯ�Ѵ�
	C3DVector getSubVector(const C3DVector& a_rVector);

	//! ������ ��ȯ�Ѵ�
	float getDotVector(const C3DVector& a_rVector);

	//! ������ ��ȯ�Ѵ�
	C3DVector getCrossVector(const C3DVector& a_rVector);

	//! ��� ��ȯ ����� ��ȯ�Ѵ�
	C3DVector getTransformVector(const C3DMatrix& a_rMatrix);

public:			// ������

	//! ������
	C3DVector(float a_fX = 0.0f, float a_fY = 0.0f, float a_fZ = 0.0f);

public:			// public ����

	float m_fX = 0.0f;
	float m_fY = 0.0f;
	float m_fZ = 0.0f;
};
