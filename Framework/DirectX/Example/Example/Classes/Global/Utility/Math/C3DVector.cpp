#include "C3DVector.h"

C3DVector::C3DVector(float a_fX, float a_fY, float a_fZ)
	:
	m_fX(a_fX),
	m_fY(a_fY),
	m_fZ(a_fZ)
{
	// Do Nothing
}

float C3DVector::getLength(void)
{
	return sqrtf(powf(m_fX, 2) + powf(m_fY, 2) + powf(m_fZ, 2));
}

C3DVector C3DVector::getNormalizeVector(void)
{
	float fLength = this->getLength();
	return C3DVector(m_fX / fLength, m_fY / fLength, m_fZ / fLength);
}

C3DVector C3DVector::getMulVector(float a_fScalar)
{
	return C3DVector(m_fX * a_fScalar, m_fY * a_fScalar, m_fZ * a_fScalar);
}

C3DVector C3DVector::getAddVector(const C3DVector& a_rVector)
{
	return C3DVector(m_fX + a_rVector.m_fX, m_fY + a_rVector.m_fY, m_fZ + a_rVector.m_fZ);
}

C3DVector C3DVector::getSubVector(const C3DVector& a_rVector)
{
	return C3DVector(m_fX - a_rVector.m_fX, m_fY - a_rVector.m_fY, m_fZ - a_rVector.m_fZ);
}

float C3DVector::getDotVector(const C3DVector& a_rVector)
{
	return (m_fX * a_rVector.m_fX) +
		(m_fY * a_rVector.m_fY) +
		(m_fZ * a_rVector.m_fZ);
}

C3DVector C3DVector::getCrossVector(const C3DVector& a_rVector)
{
	return C3DVector((m_fY * a_rVector.m_fZ) - (m_fZ * a_rVector.m_fY),
		(m_fZ * a_rVector.m_fX) - (m_fX * a_rVector.m_fZ),
		(m_fX * a_rVector.m_fY) - (m_fY * a_rVector.m_fX));
}

C3DVector C3DVector::getTransformVector(const C3DMatrix& a_rMatrix)
{
	C3DVector oColVector1(a_rMatrix(0, 0), a_rMatrix(1, 0), a_rMatrix(2, 0));
	C3DVector oColVector2(a_rMatrix(0, 1), a_rMatrix(1, 1), a_rMatrix(2, 1));
	C3DVector oColVector3(a_rMatrix(0, 2), a_rMatrix(1, 2), a_rMatrix(2, 2));

	return C3DVector(this->getDotVector(oColVector1),
		this->getDotVector(oColVector2),
		this->getDotVector(oColVector3));
}
