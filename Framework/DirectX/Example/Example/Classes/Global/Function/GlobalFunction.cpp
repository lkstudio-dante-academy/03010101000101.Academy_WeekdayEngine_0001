#include "GlobalFunction.h"
#include "../Utility/Base/CDirect3DApplication.h"
#include "../Utility/Animation/CAllocateHierarchy.h"
#include "../Utility/Object/CCamera.h"
#include "../Utility/Manager/CInputManager.h"
#include "../Utility/Manager/CDeviceManager.h"

DWORD FloatToDWORD(float a_fValue)
{
	float* pfValue = &a_fValue;
	return *((DWORD*)pfValue);
}

STBoundingBox ObjectBoxToBox(const STObjectBoundingBox& a_rstObjectBoundingBox)
{
	STBoundingBox stBoundingBox;
	ZeroMemory(&stBoundingBox, sizeof(stBoundingBox));

	stBoundingBox.m_stMinPosition = a_rstObjectBoundingBox.m_stCenterPosition;
	stBoundingBox.m_stMaxPosition = a_rstObjectBoundingBox.m_stCenterPosition;

	auto stCenterPosition = a_rstObjectBoundingBox.m_stCenterPosition;
	auto stRightDirection = a_rstObjectBoundingBox.m_astDirections[(int)EDirection::RIGHT] * a_rstObjectBoundingBox.m_afHelfLengths[(int)EDirection::RIGHT];
	auto stUpDirection = a_rstObjectBoundingBox.m_astDirections[(int)EDirection::UP] * a_rstObjectBoundingBox.m_afHelfLengths[(int)EDirection::UP];
	auto stForwardDirection = a_rstObjectBoundingBox.m_astDirections[(int)EDirection::FORWARD] * a_rstObjectBoundingBox.m_afHelfLengths[(int)EDirection::FORWARD];

	D3DXVECTOR3 astPositions[] = {
		stCenterPosition + stRightDirection + stUpDirection + stForwardDirection,
		stCenterPosition - stRightDirection + stUpDirection + stForwardDirection,
		stCenterPosition + stRightDirection - stUpDirection + stForwardDirection,
		stCenterPosition - stRightDirection - stUpDirection + stForwardDirection,

		stCenterPosition + stRightDirection + stUpDirection - stForwardDirection,
		stCenterPosition - stRightDirection + stUpDirection - stForwardDirection,
		stCenterPosition + stRightDirection - stUpDirection - stForwardDirection,
		stCenterPosition - stRightDirection - stUpDirection - stForwardDirection
	};

	for(int i = 0; i < sizeof(astPositions) / sizeof(astPositions[0]); ++i)
	{
		auto stPosition = astPositions[i];

		// X ��ġ
		// {
		if(stPosition.x < stBoundingBox.m_stMinPosition.x)
		{
			stBoundingBox.m_stMinPosition.x = stPosition.x;
		}

		if(stPosition.x >= stBoundingBox.m_stMaxPosition.x)
		{
			stBoundingBox.m_stMaxPosition.x = stPosition.x;
		}
		// }

		// Y ��ġ
		// {
		if(stPosition.y < stBoundingBox.m_stMinPosition.y)
		{
			stBoundingBox.m_stMinPosition.y = stPosition.y;
		}

		if(stPosition.y >= stBoundingBox.m_stMaxPosition.y)
		{
			stBoundingBox.m_stMaxPosition.y = stPosition.y;
		}
		// }

		// Z ��ġ
		// {
		if(stPosition.z < stBoundingBox.m_stMinPosition.z)
		{
			stBoundingBox.m_stMinPosition.z = stPosition.z;
		}

		if(stPosition.z >= stBoundingBox.m_stMaxPosition.z)
		{
			stBoundingBox.m_stMaxPosition.z = stPosition.z;
		}
		// }
	}

	return stBoundingBox;
}

int ClampIntValue(int a_nValue, int a_nMin, int a_nMax)
{
	int nMin = (a_nMin < a_nMax) ? a_nMin : a_nMax;
	int nMax = (a_nMax > a_nMin) ? a_nMax : a_nMin;

	return (a_nValue < a_nMin) ? a_nMin :
		(a_nValue > a_nMax) ? a_nMax : a_nValue;
}

float ClampFloatValue(float a_fValue, float a_fMin, float a_fMax)
{
	float fMin = (a_fMin < a_fMax) ? a_fMin : a_fMax;
	float fMax = (a_fMax > a_fMin) ? a_fMax : a_fMin;

	return (a_fValue < a_fMin) ? a_fMin :
		(a_fValue > a_fMax) ? a_fMax : a_fValue;
}

int CreateIntRandomValue(int a_nMin, int a_nMax)
{
	std::random_device oRandomDevice;
	std::uniform_int_distribution<int> oUniformRandom(a_nMin, a_nMax);

	return oUniformRandom(oRandomDevice);
}

float CreateFloatRandomValue(float a_fMin, float a_fMax)
{
	std::random_device oRandomDevice;
	std::uniform_real_distribution<float> oUniformRandom(a_fMin, a_fMax);

	return oUniformRandom(oRandomDevice);
}

STRay CreateRay(const POINT& a_rstPoint)
{
	D3DVIEWPORT9 stViewport;
	GET_DEVICE()->GetViewport(&stViewport);

	float fDirectionX = ((a_rstPoint.x * 2.0f) / stViewport.Width) - 1.0f;
	float fDirectionY = ((a_rstPoint.y * -2.0f) / stViewport.Height) + 1.0f;

	D3DXMATRIXA16 stViewMatrix = GET_CAMERA()->getViewMatrix();
	D3DXMATRIXA16 stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();

	STRay stRay = {
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(fDirectionX / stProjectionMatrix(0, 0), fDirectionY / stProjectionMatrix(1, 1), 1.0f)
	};

	D3DXMATRIXA16 stInverseMatrix;
	D3DXMatrixInverse(&stInverseMatrix, NULL, &stViewMatrix);

	D3DXVec3TransformCoord(&stRay.m_stOrigin, &stRay.m_stOrigin, &stInverseMatrix);
	D3DXVec3TransformNormal(&stRay.m_stDirection, &stRay.m_stDirection, &stInverseMatrix);

	D3DXVec3Normalize(&stRay.m_stDirection, &stRay.m_stDirection);
	return stRay;
}

STBoundingBox CreateBoundingBox(LPD3DXMESH a_pMesh)
{
	STBoundingBox stBoundingBox;
	ZeroMemory(&stBoundingBox, sizeof(stBoundingBox));

	/** VS Output */ ������ ����Ѵ�
	// {
	BYTE* pnVertices = nullptr;

	if(SUCCEEDED(a_pMesh->LockVertexBuffer(0, (void**)&pnVertices)))
	{
		D3DXComputeBoundingBox((D3DXVECTOR3*)pnVertices,
			a_pMesh->GetNumVertices(),
			a_pMesh->GetNumBytesPerVertex(),
			&stBoundingBox.m_stMinPosition,
			&stBoundingBox.m_stMaxPosition);

		a_pMesh->UnlockVertexBuffer();
	}
	// }

	return stBoundingBox;
}

STBoundingSphere CreateBoundingSphere(LPD3DXMESH a_pMesh)
{
	STBoundingSphere stBoundingSphere;
	ZeroMemory(&stBoundingSphere, sizeof(stBoundingSphere));

	// ��� �� ������ ����Ѵ�
	// {
	BYTE* pnVertices = nullptr;

	if(SUCCEEDED(a_pMesh->LockVertexBuffer(0, (void**)&pnVertices)))
	{
		D3DXComputeBoundingSphere((D3DXVECTOR3*)pnVertices,
			a_pMesh->GetNumVertices(),
			a_pMesh->GetNumBytesPerVertex(),
			&stBoundingSphere.m_stCenterPosition,
			&stBoundingSphere.m_fRadius);

		a_pMesh->UnlockVertexBuffer();
	}
	// }

	return stBoundingSphere;
}

LPDIRECT3DVERTEXBUFFER9 CreateVertexBuffer(int a_nSize, DWORD a_nUsage, DWORD a_nFVF, D3DPOOL a_ePool)
{
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = nullptr;

	// ���� ���۸� �����Ѵ�
	GET_DEVICE()->CreateVertexBuffer(a_nSize,
		a_nUsage,
		a_nFVF,
		a_ePool,
		&pVertexBuffer,
		NULL);

	return pVertexBuffer;
}

LPDIRECT3DINDEXBUFFER9 CreateIndexBuffer(int a_nSize, DWORD a_nUsage, D3DFORMAT a_eFormat, D3DPOOL a_ePool)
{
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer = nullptr;

	// �ε��� ���۸� �����Ѵ�
	GET_DEVICE()->CreateIndexBuffer(a_nSize,
		a_nUsage,
		a_eFormat,
		a_ePool,
		&pIndexBuffer,
		NULL);

	return pIndexBuffer;
}

bool IsIntersectBox(const STBoundingBox& a_rstLhs, const STBoundingBox& a_rstRhs)
{
	if(a_rstLhs.m_stMinPosition.x > a_rstRhs.m_stMaxPosition.x ||
		a_rstLhs.m_stMaxPosition.x < a_rstRhs.m_stMinPosition.x)
	{
		return false;
	}

	if(a_rstLhs.m_stMinPosition.y > a_rstRhs.m_stMaxPosition.y ||
		a_rstLhs.m_stMaxPosition.y < a_rstRhs.m_stMinPosition.y)
	{
		return false;
	}

	if(a_rstLhs.m_stMinPosition.z > a_rstRhs.m_stMaxPosition.z ||
		a_rstLhs.m_stMaxPosition.z < a_rstRhs.m_stMinPosition.z)
	{
		return false;
	}

	return true;
}

bool IsIntersectObjectBox(const STObjectBoundingBox& a_rstLhs, const STObjectBoundingBox& a_rstRhs)
{
	float fCutOffValue = 0.99999f;
	float afDeltaDotValues[NUM_DIRECTIONS] = { 0.0f };

	float afCosValues[NUM_DIRECTIONS][NUM_DIRECTIONS] = { 0.0f };
	float afAbsCosValues[NUM_DIRECTIONS][NUM_DIRECTIONS] = { 0.0f };

	D3DXVECTOR3 stDelta = a_rstRhs.m_stCenterPosition - a_rstLhs.m_stCenterPosition;

	float fDotValueA = 0.0f;
	float fDotValueB = 0.0f;
	float fTotalDotValue = 0.0f;

	bool bIsExistParallel = false;

	for(int i = 0; i < NUM_DIRECTIONS; ++i)
	{
		for(int j = 0; j < NUM_DIRECTIONS; ++j)
		{
			afCosValues[i][j] = D3DXVec3Dot(&a_rstLhs.m_astDirections[i], &a_rstRhs.m_astDirections[j]);
			afAbsCosValues[i][j] = fabsf(afCosValues[i][j]);

			// ���� �� ���� ���� ���
			if(afAbsCosValues[i][j] > fCutOffValue)
			{
				bIsExistParallel = true;
			}
		}

		afDeltaDotValues[i] = D3DXVec3Dot(&a_rstLhs.m_astDirections[i], &stDelta);
	}

	// Lhs ��� ����(A) �� ���� �������� �˻��Ѵ�
	// {
	// X �� �˻�
	fTotalDotValue = fabsf(afDeltaDotValues[(int)EDirection::RIGHT]);
	fDotValueA = a_rstLhs.m_afHelfLengths[(int)EDirection::RIGHT];

	fDotValueB = (afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::RIGHT] * a_rstRhs.m_afHelfLengths[(int)EDirection::RIGHT]) +
		(afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::UP] * a_rstRhs.m_afHelfLengths[(int)EDirection::UP]) +
		(afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::FORWARD] * a_rstRhs.m_afHelfLengths[(int)EDirection::FORWARD]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}

	// Y �� �˻�
	fTotalDotValue = fabsf(afDeltaDotValues[(int)EDirection::UP]);
	fDotValueA = a_rstLhs.m_afHelfLengths[(int)EDirection::UP];

	fDotValueB = (afAbsCosValues[(int)EDirection::UP][(int)EDirection::RIGHT] * a_rstRhs.m_afHelfLengths[(int)EDirection::RIGHT]) +
		(afAbsCosValues[(int)EDirection::UP][(int)EDirection::UP] * a_rstRhs.m_afHelfLengths[(int)EDirection::UP]) +
		(afAbsCosValues[(int)EDirection::UP][(int)EDirection::FORWARD] * a_rstRhs.m_afHelfLengths[(int)EDirection::FORWARD]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}

	// Z �� �˻�
	fTotalDotValue = fabsf(afDeltaDotValues[(int)EDirection::FORWARD]);
	fDotValueA = a_rstLhs.m_afHelfLengths[(int)EDirection::FORWARD];

	fDotValueB = (afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::RIGHT] * a_rstRhs.m_afHelfLengths[(int)EDirection::RIGHT]) +
		(afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::UP] * a_rstRhs.m_afHelfLengths[(int)EDirection::UP]) +
		(afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::FORWARD] * a_rstRhs.m_afHelfLengths[(int)EDirection::FORWARD]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}
	// }

	// Rhs ��� ����(B) �� ���� �������� �˻��Ѵ�
	// {
	// X �� �˻�
	fTotalDotValue = fabsf(D3DXVec3Dot(&a_rstRhs.m_astDirections[(int)EDirection::RIGHT], &stDelta));
	fDotValueB = a_rstRhs.m_afHelfLengths[(int)EDirection::RIGHT];

	fDotValueA = (afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::RIGHT] * a_rstLhs.m_afHelfLengths[(int)EDirection::RIGHT]) +
		(afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::UP] * a_rstLhs.m_afHelfLengths[(int)EDirection::UP]) +
		(afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::FORWARD] * a_rstLhs.m_afHelfLengths[(int)EDirection::FORWARD]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}

	// Y �� �˻�
	fTotalDotValue = fabsf(D3DXVec3Dot(&a_rstRhs.m_astDirections[(int)EDirection::UP], &stDelta));
	fDotValueB = a_rstRhs.m_afHelfLengths[(int)EDirection::UP];

	fDotValueA = (afAbsCosValues[(int)EDirection::UP][(int)EDirection::RIGHT] * a_rstLhs.m_afHelfLengths[(int)EDirection::RIGHT]) +
		(afAbsCosValues[(int)EDirection::UP][(int)EDirection::UP] * a_rstLhs.m_afHelfLengths[(int)EDirection::UP]) +
		(afAbsCosValues[(int)EDirection::UP][(int)EDirection::FORWARD] * a_rstLhs.m_afHelfLengths[(int)EDirection::FORWARD]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}

	// Z �� �˻�
	fTotalDotValue = fabsf(D3DXVec3Dot(&a_rstRhs.m_astDirections[(int)EDirection::FORWARD], &stDelta));
	fDotValueB = a_rstRhs.m_afHelfLengths[(int)EDirection::FORWARD];

	fDotValueA = (afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::RIGHT] * a_rstLhs.m_afHelfLengths[(int)EDirection::RIGHT]) +
		(afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::UP] * a_rstLhs.m_afHelfLengths[(int)EDirection::UP]) +
		(afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::FORWARD] * a_rstLhs.m_afHelfLengths[(int)EDirection::FORWARD]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}
	// }

	// �� ���̶� ���� �� ���
	if(bIsExistParallel)
	{
		return true;
	}

	/** VS Output */(A) �� �𼭸��� �������� �˻��Ѵ�
	// {
	// X(A), X(B) �𼭸��� �˻��Ѵ�
	fTotalDotValue = fabsf((afDeltaDotValues[(int)EDirection::FORWARD] * afCosValues[(int)EDirection::UP][(int)EDirection::RIGHT]) -
		(afDeltaDotValues[(int)EDirection::UP] * afCosValues[(int)EDirection::FORWARD][(int)EDirection::RIGHT]));

	fDotValueA = (a_rstLhs.m_afHelfLengths[(int)EDirection::UP] * afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::RIGHT]) +
		(a_rstLhs.m_afHelfLengths[(int)EDirection::FORWARD] * afAbsCosValues[(int)EDirection::UP][(int)EDirection::RIGHT]);

	fDotValueB = (a_rstRhs.m_afHelfLengths[(int)EDirection::UP] * afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::FORWARD]) +
		(a_rstRhs.m_afHelfLengths[(int)EDirection::FORWARD] * afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::UP]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}

	// X(A), Y(B) �𼭸��� �˻��Ѵ�
	fTotalDotValue = fabsf((afDeltaDotValues[(int)EDirection::FORWARD] * afCosValues[(int)EDirection::UP][(int)EDirection::UP]) -
		(afDeltaDotValues[(int)EDirection::UP] * afCosValues[(int)EDirection::FORWARD][(int)EDirection::UP]));

	fDotValueA = (a_rstLhs.m_afHelfLengths[(int)EDirection::UP] * afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::UP]) +
		(a_rstLhs.m_afHelfLengths[(int)EDirection::FORWARD] * afAbsCosValues[(int)EDirection::UP][(int)EDirection::UP]);

	fDotValueB = (a_rstRhs.m_afHelfLengths[(int)EDirection::RIGHT] * afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::FORWARD]) +
		(a_rstRhs.m_afHelfLengths[(int)EDirection::FORWARD] * afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::RIGHT]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}

	// X(A), Z(B) �𼭸��� �˻��Ѵ�
	fTotalDotValue = fabsf((afDeltaDotValues[(int)EDirection::FORWARD] * afCosValues[(int)EDirection::UP][(int)EDirection::FORWARD]) -
		(afDeltaDotValues[(int)EDirection::UP] * afCosValues[(int)EDirection::FORWARD][(int)EDirection::FORWARD]));

	fDotValueA = (a_rstLhs.m_afHelfLengths[(int)EDirection::UP] * afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::FORWARD]) +
		(a_rstLhs.m_afHelfLengths[(int)EDirection::FORWARD] * afAbsCosValues[(int)EDirection::UP][(int)EDirection::FORWARD]);

	fDotValueB = (a_rstRhs.m_afHelfLengths[(int)EDirection::RIGHT] * afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::UP]) +
		(a_rstRhs.m_afHelfLengths[(int)EDirection::UP] * afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::RIGHT]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}

	// Y(A), X(B) �𼭸��� �˻��Ѵ�
	fTotalDotValue = fabsf((afDeltaDotValues[(int)EDirection::RIGHT] * afCosValues[(int)EDirection::FORWARD][(int)EDirection::RIGHT]) -
		(afDeltaDotValues[(int)EDirection::FORWARD] * afCosValues[(int)EDirection::RIGHT][(int)EDirection::RIGHT]));

	fDotValueA = (a_rstLhs.m_afHelfLengths[(int)EDirection::RIGHT] * afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::RIGHT]) +
		(a_rstLhs.m_afHelfLengths[(int)EDirection::FORWARD] * afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::RIGHT]);

	fDotValueB = (a_rstRhs.m_afHelfLengths[(int)EDirection::UP] * afAbsCosValues[(int)EDirection::UP][(int)EDirection::FORWARD]) +
		(a_rstRhs.m_afHelfLengths[(int)EDirection::FORWARD] * afAbsCosValues[(int)EDirection::UP][(int)EDirection::UP]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}

	// Y(A), Y(B) �𼭸��� �˻��Ѵ�
	fTotalDotValue = fabsf((afDeltaDotValues[(int)EDirection::RIGHT] * afCosValues[(int)EDirection::FORWARD][(int)EDirection::UP]) -
		(afDeltaDotValues[(int)EDirection::FORWARD] * afCosValues[(int)EDirection::RIGHT][(int)EDirection::UP]));

	fDotValueA = (a_rstLhs.m_afHelfLengths[(int)EDirection::RIGHT] * afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::UP]) +
		(a_rstLhs.m_afHelfLengths[(int)EDirection::FORWARD] * afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::UP]);

	fDotValueB = (a_rstRhs.m_afHelfLengths[(int)EDirection::RIGHT] * afAbsCosValues[(int)EDirection::UP][(int)EDirection::FORWARD]) +
		(a_rstRhs.m_afHelfLengths[(int)EDirection::FORWARD] * afAbsCosValues[(int)EDirection::UP][(int)EDirection::RIGHT]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}

	// Y(A), Z(B) �𼭸��� �˻��Ѵ�
	fTotalDotValue = fabsf((afDeltaDotValues[(int)EDirection::RIGHT] * afCosValues[(int)EDirection::FORWARD][(int)EDirection::FORWARD]) -
		(afDeltaDotValues[(int)EDirection::FORWARD] * afCosValues[(int)EDirection::RIGHT][(int)EDirection::FORWARD]));

	fDotValueA = (a_rstLhs.m_afHelfLengths[(int)EDirection::RIGHT] * afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::FORWARD]) +
		(a_rstLhs.m_afHelfLengths[(int)EDirection::FORWARD] * afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::FORWARD]);

	fDotValueB = (a_rstRhs.m_afHelfLengths[(int)EDirection::RIGHT] * afAbsCosValues[(int)EDirection::UP][(int)EDirection::UP]) +
		(a_rstRhs.m_afHelfLengths[(int)EDirection::UP] * afAbsCosValues[(int)EDirection::UP][(int)EDirection::RIGHT]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}

	// Z(A), X(B) �𼭸��� �˻��Ѵ�
	fTotalDotValue = fabsf((afDeltaDotValues[(int)EDirection::UP] * afCosValues[(int)EDirection::RIGHT][(int)EDirection::RIGHT]) -
		(afDeltaDotValues[(int)EDirection::RIGHT] * afCosValues[(int)EDirection::UP][(int)EDirection::RIGHT]));

	fDotValueA = (a_rstLhs.m_afHelfLengths[(int)EDirection::RIGHT] * afAbsCosValues[(int)EDirection::UP][(int)EDirection::RIGHT]) +
		(a_rstLhs.m_afHelfLengths[(int)EDirection::UP] * afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::RIGHT]);

	fDotValueB = (a_rstRhs.m_afHelfLengths[(int)EDirection::UP] * afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::FORWARD]) +
		(a_rstRhs.m_afHelfLengths[(int)EDirection::FORWARD] * afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::UP]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}

	// Z(A), Y(B) �𼭸��� �˻��Ѵ�
	fTotalDotValue = fabsf((afDeltaDotValues[(int)EDirection::UP] * afCosValues[(int)EDirection::RIGHT][(int)EDirection::UP]) -
		(afDeltaDotValues[(int)EDirection::RIGHT] * afCosValues[(int)EDirection::UP][(int)EDirection::UP]));

	fDotValueA = (a_rstLhs.m_afHelfLengths[(int)EDirection::RIGHT] * afAbsCosValues[(int)EDirection::UP][(int)EDirection::UP]) +
		(a_rstLhs.m_afHelfLengths[(int)EDirection::UP] * afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::UP]);

	fDotValueB = (a_rstRhs.m_afHelfLengths[(int)EDirection::RIGHT] * afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::FORWARD]) +
		(a_rstRhs.m_afHelfLengths[(int)EDirection::FORWARD] * afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::RIGHT]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}

	// Z(A), Z(B) �𼭸��� �˻��Ѵ�
	fTotalDotValue = fabsf((afDeltaDotValues[(int)EDirection::UP] * afCosValues[(int)EDirection::RIGHT][(int)EDirection::FORWARD]) -
		(afDeltaDotValues[(int)EDirection::RIGHT] * afCosValues[(int)EDirection::UP][(int)EDirection::FORWARD]));

	fDotValueA = (a_rstLhs.m_afHelfLengths[(int)EDirection::RIGHT] * afAbsCosValues[(int)EDirection::UP][(int)EDirection::FORWARD]) +
		(a_rstLhs.m_afHelfLengths[(int)EDirection::UP] * afAbsCosValues[(int)EDirection::RIGHT][(int)EDirection::FORWARD]);

	fDotValueB = (a_rstRhs.m_afHelfLengths[(int)EDirection::RIGHT] * afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::UP]) +
		(a_rstRhs.m_afHelfLengths[(int)EDirection::UP] * afAbsCosValues[(int)EDirection::FORWARD][(int)EDirection::RIGHT]);

	if(fTotalDotValue > fDotValueA + fDotValueB)
	{
		return false;
	}
	// }

	return true;
}

bool IsIntersectSphere(const STBoundingSphere& a_rstLhs, const STBoundingSphere& a_rstRhs)
{
	D3DXVECTOR3 stDelta = a_rstLhs.m_stCenterPosition - a_rstRhs.m_stCenterPosition;
	return D3DXVec3Length(&stDelta) <= (a_rstLhs.m_fRadius + a_rstRhs.m_fRadius);
}

bool IsIntersectRayBox(const STBoundingBox& a_rstBoundingBox, const STRay& a_rstRay)
{
	float fMaxS = -FLT_MAX;
	float fMinT = FLT_MAX;

	// X �� �˻�
	// {
	if(fabsf(a_rstRay.m_stDirection.x) <= FLT_EPSILON)
	{
		if(a_rstRay.m_stOrigin.x < a_rstBoundingBox.m_stMinPosition.x ||
			a_rstRay.m_stOrigin.x > a_rstBoundingBox.m_stMaxPosition.x)
		{
			return false;
		}
	}
	else
	{
		float fS = (a_rstBoundingBox.m_stMinPosition.x - a_rstRay.m_stOrigin.x) / a_rstRay.m_stDirection.x;
		float fT = (a_rstBoundingBox.m_stMaxPosition.x - a_rstRay.m_stOrigin.x) / a_rstRay.m_stDirection.x;

		if(fT < fS)
		{
			std::swap(fS, fT);
		}

		if(fS > fMaxS)
		{
			fMaxS = fS;
		}

		if(fT < fMinT)
		{
			fMinT = fT;
		}

		if(fMinT < 0.0f || fMaxS > fMinT)
		{
			return false;
		}
	}
	// }

	// Y �� �˻�
	// {
	if(fabsf(a_rstRay.m_stDirection.y) <= FLT_EPSILON)
	{
		if(a_rstRay.m_stOrigin.y < a_rstBoundingBox.m_stMinPosition.y ||
			a_rstRay.m_stOrigin.y > a_rstBoundingBox.m_stMaxPosition.y)
		{
			return false;
		}
	}
	else
	{
		float fS = (a_rstBoundingBox.m_stMinPosition.y - a_rstRay.m_stOrigin.y) / a_rstRay.m_stDirection.y;
		float fT = (a_rstBoundingBox.m_stMaxPosition.y - a_rstRay.m_stOrigin.y) / a_rstRay.m_stDirection.y;

		if(fT < fS)
		{
			std::swap(fS, fT);
		}

		if(fS > fMaxS)
		{
			fMaxS = fS;
		}

		if(fT < fMinT)
		{
			fMinT = fT;
		}

		if(fMinT < 0.0f || fMaxS > fMinT)
		{
			return false;
		}
	}
	// }

	// Z �� �˻�
	// {
	if(fabsf(a_rstRay.m_stDirection.z) <= FLT_EPSILON)
	{
		if(a_rstRay.m_stOrigin.z < a_rstBoundingBox.m_stMinPosition.z ||
			a_rstRay.m_stOrigin.z > a_rstBoundingBox.m_stMaxPosition.z)
		{
			return false;
		}
	}
	else
	{
		float fS = (a_rstBoundingBox.m_stMinPosition.z - a_rstRay.m_stOrigin.z) / a_rstRay.m_stDirection.z;
		float fT = (a_rstBoundingBox.m_stMaxPosition.z - a_rstRay.m_stOrigin.z) / a_rstRay.m_stDirection.z;

		if(fT < fS)
		{
			std::swap(fS, fT);
		}

		if(fS > fMaxS)
		{
			fMaxS = fS;
		}

		if(fT < fMinT)
		{
			fMinT = fT;
		}

		if(fMinT < 0.0f || fMaxS > fMinT)
		{
			return false;
		}
	}
	// }

	return true;
}

bool IsIntersectRaySphere(const STBoundingSphere& a_rstBoundingSphere, const STRay& a_rstRay)
{
	D3DXVECTOR3 stW = a_rstBoundingSphere.m_stCenterPosition - a_rstRay.m_stOrigin;
	D3DXVECTOR3 stDirection = a_rstRay.m_stDirection;

	// ���� ���͸� ����ȭ�Ѵ�
	D3DXVec3Normalize(&stDirection, &stDirection);

	float fWsq = D3DXVec3Dot(&stW, &stW);
	float fRsq = pow(a_rstBoundingSphere.m_fRadius, 2);
	float fProj = D3DXVec3Dot(&stW, &stDirection);

	if(fProj < 0.0f && fWsq > fRsq)
	{
		return false;
	}

	float fVsq = D3DXVec3Dot(&stDirection, &stDirection);
	return (fVsq * fWsq) - (fProj * fProj) <= fVsq * fRsq;
}

bool IsContainPoint(const RECT& a_rstRect, const POINT& a_rstPoint)
{
	return (a_rstPoint.x >= a_rstRect.left && a_rstPoint.x <= a_rstRect.right) &&
		(a_rstPoint.y >= a_rstRect.top && a_rstPoint.y <= a_rstRect.bottom);
}

void RunEffectLoop(LPD3DXEFFECT a_pEffect, const std::string& a_rTechniqueName, const std::function<void(int)>& a_rCallback)
{
	a_pEffect->SetTechnique(a_rTechniqueName.c_str());

	UINT nNumPasses = 0;
	a_pEffect->Begin(&nNumPasses, 0);

	for(int i = 0; i < nNumPasses; ++i)
	{
		a_pEffect->BeginPass(i);

		a_rCallback(i);
		a_pEffect->EndPass();
	}

	a_pEffect->End();
}
