#include "Example_13.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Base/CObject.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"

#define ROTATION_TYPE_EULER					1
#define ROTATION_TYPE_TRACKBALL				2
#define ROTATION_TYPE_QUATERNION			3

#define ROTATION_TYPE			ROTATION_TYPE_TRACKBALL

Example_13::Example_13(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize),

	m_stRotation(0.0f, 0.0f, 0.0f)
{
	ZeroMemory(&m_stPrevMousePosition, sizeof(m_stPrevMousePosition));
}

Example_13::~Example_13(void)
{
	SAFE_DELETE(m_pObject);

	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

void Example_13::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pObject = CreateObject<CObject>();
	m_pVertexBuffer = this->createVertexBuffer();
	m_pIndexBuffer = this->createIndexBuffer();
}

void Example_13::update(void)
{
	CDirect3DApplication::update();
	m_pObject->update();

#if ROTATION_TYPE == ROTATION_TYPE_TRACKBALL
	if(IS_MOUSE_BUTTON_DOWN(EMouseButton::LEFT))
	{
		if(IS_MOUSE_BUTTON_PRESSED(EMouseButton::LEFT))
		{
			m_stPrevMousePosition = GET_MOUSE_POSITION();
		}

		auto stMousePosition = GET_MOUSE_POSITION();

		D3DVIEWPORT9 stViewport;
		GET_DEVICE()->GetViewport(&stViewport);

		float fOffsetX = (stViewport.Width - stViewport.Height) / -2.0f;

		float fNormalizeX = (((stMousePosition.x + fOffsetX) * 2.0f) / stViewport.Height) - 1.0f;
		float fNormalizeY = ((stMousePosition.y * -2.0f) / stViewport.Height) + 1.0f;
		float fNormalizeZ = 0.0f;

		float fPrevNormalizeX = (((m_stPrevMousePosition.x + fOffsetX) * 2.0f) / stViewport.Height) - 1.0f;
		float fPrevNormalizeY = ((m_stPrevMousePosition.y * -2.0f) / stViewport.Height) + 1.0f;
		float fPrevNormalizeZ = 0.0f;

		if(sqrtf(powf(fNormalizeX, 2) + powf(fNormalizeY, 2)) < 1.0f &&
			sqrtf(powf(fPrevNormalizeX, 2) + powf(fPrevNormalizeY, 2)) < 1.0f)
		{
			fNormalizeZ = sqrt(1.0f - (powf(fNormalizeX, 2) + powf(fNormalizeY, 2)));
			fPrevNormalizeZ = sqrt(1.0f - (powf(fPrevNormalizeX, 2) + powf(fPrevNormalizeY, 2)));
		}

		D3DXVECTOR3 stDirection(fNormalizeX, fNormalizeY, fNormalizeZ);
		D3DXVECTOR3 stPrevDirection(fPrevNormalizeX, fPrevNormalizeY, fPrevNormalizeZ);

		D3DXVec3Normalize(&stDirection, &stDirection);
		D3DXVec3Normalize(&stPrevDirection, &stPrevDirection);

		D3DXVECTOR3 stRotationDirection;
		D3DXVec3Cross(&stRotationDirection, &stDirection, &stPrevDirection);

		float fAngle = asinf(D3DXVec3Length(&stRotationDirection));

		D3DXQUATERNION stQuaternion;
		D3DXQuaternionRotationAxis(&stQuaternion, &stRotationDirection, fAngle);

		D3DXMATRIXA16 stRotation;
		D3DXMatrixRotationQuaternion(&stRotation, &stQuaternion);

		m_pObject->rotateByMatrix(stRotation);
		m_stPrevMousePosition = stMousePosition;
	}
#else
	if(IS_KEY_DOWN(DIK_UP))
	{
		m_stRotation.x += 90.0f * GET_DELTA_TIME();
	}
	else if(IS_KEY_DOWN(DIK_DOWN))
	{
		m_stRotation.x -= 90.0f * GET_DELTA_TIME();
	}

	if(IS_KEY_DOWN(DIK_LEFT))
	{
		m_stRotation.y += 90.0f * GET_DELTA_TIME();
	}
	else if(IS_KEY_DOWN(DIK_RIGHT))
	{
		m_stRotation.y -= 90.0f * GET_DELTA_TIME();
	}

	if(IS_KEY_DOWN(DIK_A))
	{
		m_stRotation.z += 90.0f * GET_DELTA_TIME();
	}
	else if(IS_KEY_DOWN(DIK_D))
	{
		m_stRotation.z -= 90.0f * GET_DELTA_TIME();
	}
#endif			// #if ROTATE_TYPE == ROTATION_TYPE_TRACKBALL
}

void Example_13::draw(void)
{
	CDirect3DApplication::draw();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);

	// ����� �����Ѵ�
	// {
#if ROTATION_TYPE == ROTATION_TYPE_EULER
	D3DXMATRIXA16 stRotationX;
	D3DXMatrixRotationX(&stRotationX, D3DXToRadian(m_stRotation.x));

	D3DXMATRIXA16 stRotationY;
	D3DXMatrixRotationY(&stRotationY, D3DXToRadian(m_stRotation.y));

	D3DXMATRIXA16 stRotationZ;
	D3DXMatrixRotationZ(&stRotationZ, D3DXToRadian(m_stRotation.z));

	auto stWorldMatrix = stRotationY * stRotationX * stRotationZ;
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
#elif ROTATION_TYPE == ROTATION_TYPE_TRACKBALL
	auto stWorldMatrix = m_pObject->getFinalWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
#else
	D3DXQUATERNION stQuaternion;
	D3DXQuaternionRotationYawPitchRoll(&stQuaternion, D3DXToRadian(m_stRotation.y), D3DXToRadian(m_stRotation.x), D3DXToRadian(m_stRotation.z));

	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixRotationQuaternion(&stWorldMatrix, &stQuaternion);

	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
#endif			// #if ROTATION_TYPE == ROTATION_TYPE_EULER
	// }

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetIndices(m_pIndexBuffer);
	GET_DEVICE()->SetFVF(STVertex::FVF);

	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
}

LPDIRECT3DVERTEXBUFFER9 Example_13::createVertexBuffer(void)
{
	auto pVertexBuffer = CreateVertexBuffer(sizeof(STVertex) * 8,
		D3DUSAGE_WRITEONLY,
		STVertex::FVF,
		D3DPOOL_MANAGED);

	/** VS Input */�� �����Ѵ�
	// {
	STVertex* pstVertices = nullptr;

	if(SUCCEEDED(pVertexBuffer->Lock(0, 0, (void**)&pstVertices, 0)))
	{
		// ����
		// {
		pstVertices[0].m_stPosition = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
		pstVertices[0].m_nColor = D3DCOLOR_XRGB(255, 0, 0);

		pstVertices[1].m_stPosition = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
		pstVertices[1].m_nColor = D3DCOLOR_XRGB(0, 255, 0);

		pstVertices[2].m_stPosition = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
		pstVertices[2].m_nColor = D3DCOLOR_XRGB(0, 0, 255);

		pstVertices[3].m_stPosition = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
		pstVertices[3].m_nColor = D3DCOLOR_XRGB(0, 255, 255);
		// }

		// �ĸ�
		// {
		pstVertices[4].m_stPosition = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
		pstVertices[4].m_nColor = D3DCOLOR_XRGB(255, 0, 0);

		pstVertices[5].m_stPosition = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pstVertices[5].m_nColor = D3DCOLOR_XRGB(0, 255, 0);

		pstVertices[6].m_stPosition = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
		pstVertices[6].m_nColor = D3DCOLOR_XRGB(0, 0, 255);

		pstVertices[7].m_stPosition = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
		pstVertices[7].m_nColor = D3DCOLOR_XRGB(0, 255, 255);
		// }

		pVertexBuffer->Unlock();
	}
	// }

	return pVertexBuffer;
}

LPDIRECT3DINDEXBUFFER9 Example_13::createIndexBuffer(void)
{
	auto pIndexBuffer = CreateIndexBuffer(sizeof(WORD) * 36,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED);

	// �ε� ������ �����Ѵ�
	// {
	WORD* pnIndices = nullptr;

	if(SUCCEEDED(pIndexBuffer->Lock(0, 0, (void**)&pnIndices, 0)))
	{
		// ����
		pnIndices[0] = 0;	pnIndices[1] = 1;	pnIndices[2] = 2;
		pnIndices[3] = 0;	pnIndices[4] = 2;	pnIndices[5] = 3;

		// �ĸ�
		pnIndices[6] = 5;	pnIndices[7] = 4;	pnIndices[8] = 6;
		pnIndices[9] = 6;	pnIndices[10] = 4;	pnIndices[11] = 7;

		/** VS Input */
		pnIndices[12] = 4;	pnIndices[13] = 0;	pnIndices[14] = 7;
		pnIndices[15] = 7;	pnIndices[16] = 0;	pnIndices[17] = 3;

		// ������ ����
		pnIndices[18] = 1;	pnIndices[19] = 5;	pnIndices[20] = 2;
		pnIndices[21] = 2;	pnIndices[22] = 5;	pnIndices[23] = 6;

		// ����
		pnIndices[24] = 4;	pnIndices[25] = 5;	pnIndices[26] = 0;
		pnIndices[27] = 0;	pnIndices[28] = 5;	pnIndices[29] = 1;

		// �Ʒ���
		pnIndices[30] = 3;	pnIndices[31] = 2;	pnIndices[32] = 7;
		pnIndices[33] = 7;	pnIndices[34] = 2;	pnIndices[35] = 6;

		pIndexBuffer->Unlock();
	}
	// }

	return pIndexBuffer;
}
