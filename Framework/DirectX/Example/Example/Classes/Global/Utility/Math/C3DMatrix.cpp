#include "C3DMatrix.h"

C3DMatrix::C3DMatrix(void)
{
	ZeroMemory(m_afValueMatrix, sizeof(m_afValueMatrix));
}

float& C3DMatrix::operator()(int a_nRow, int a_nCol)
{
	return m_afValueMatrix[a_nRow][a_nCol];
}

float C3DMatrix::operator()(int a_nRow, int a_nCol) const
{
	return m_afValueMatrix[a_nRow][a_nCol];
}

C3DMatrix C3DMatrix::getIdentityMatrix(void)
{
	C3DMatrix oMatrix;

	for(int i = 0; i < SIZE; ++i)
	{
		for(int j = 0; j < SIZE; ++j)
		{
			oMatrix(i, j) = (i == j) ? 1 : 0;
		}
	}

	return oMatrix;
}

C3DMatrix C3DMatrix::getTransposeMatrix(void)
{
	C3DMatrix oMatrix;

	for(int i = 0; i < SIZE; ++i)
	{
		for(int j = 0; j < SIZE; ++j)
		{
			oMatrix(j, i) = (*this)(i, j);
		}
	}

	return oMatrix;
}

C3DMatrix C3DMatrix::getTranslationMatrix(float a_fX, float a_fY)
{
	C3DMatrix oMatrix = this->getIdentityMatrix();
	oMatrix(2, 0) = a_fX;
	oMatrix(2, 1) = a_fY;

	return oMatrix;
}

C3DMatrix C3DMatrix::getScaleMatrix(float a_fScaleX, int a_fScaleY)
{
	C3DMatrix oMatrix = this->getIdentityMatrix();
	oMatrix(0, 0) = a_fScaleX;
	oMatrix(1, 1) = a_fScaleY;

	return oMatrix;
}

C3DMatrix C3DMatrix::getRotationMatrix(float a_fRoll)
{
	C3DMatrix oMatrix = this->getIdentityMatrix();
	oMatrix(0, 0) = cos(a_fRoll);
	oMatrix(1, 1) = cos(a_fRoll);
	oMatrix(0, 1) = sin(a_fRoll);
	oMatrix(1, 0) = -sin(a_fRoll);

	return oMatrix;
}

C3DMatrix C3DMatrix::getAddMatrix(const C3DMatrix& a_rstMatrix)
{
	C3DMatrix oMatrix;

	for(int i = 0; i < SIZE; ++i)
	{
		for(int j = 0; j < SIZE; ++j)
		{
			oMatrix(i, j) = (*this)(i, j) + a_rstMatrix(i, j);
		}
	}

	return oMatrix;
}

C3DMatrix C3DMatrix::getSubMatrix(const C3DMatrix& a_rstMatrix)
{
	C3DMatrix oMatrix;

	for(int i = 0; i < SIZE; ++i)
	{
		for(int j = 0; j < SIZE; ++j)
		{
			oMatrix(i, j) = (*this)(i, j) - a_rstMatrix(i, j);
		}
	}

	return oMatrix;
}

C3DMatrix C3DMatrix::getMulMatrix(const C3DMatrix& a_rstMatrix)
{
	C3DMatrix oMatrix;

	for(int i = 0; i < SIZE; ++i)
	{
		for(int j = 0; j < SIZE; ++j)
		{
			for(int k = 0; k < SIZE; ++k)
			{
				oMatrix(i, j) += (*this)(i, k) * a_rstMatrix(k, j);
			}
		}
	}

	return oMatrix;
}

C3DMatrix C3DMatrix::getScalarMulMatrix(float a_fScalar)
{
	C3DMatrix oMatrix;

	for(int i = 0; i < SIZE; ++i)
	{
		for(int j = 0; j < SIZE; ++j)
		{
			oMatrix(i, j) = (*this)(i, j) * a_fScalar;
		}
	}

	return oMatrix;
}
