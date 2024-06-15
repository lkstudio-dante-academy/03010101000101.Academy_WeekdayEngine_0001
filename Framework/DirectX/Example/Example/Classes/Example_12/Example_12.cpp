#include "Example_12.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"

Example_12::Example_12(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize),

	m_stPosition(0.0f, 0.0f, 0.0f),
	m_stScale(1.0f, 1.0f, 1.0f)
{
	// Do Nothing
}

Example_12::~Example_12(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

void Example_12::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pVertexBuffer = this->createVertexBuffer();
	m_pIndexBuffer = this->createIndexBuffer();
}

void Example_12::update(void)
{
	CDirect3DApplication::update();

	if(IS_KEY_DOWN(DIK_UP))
	{
		m_stPosition.y += 2.0f * GET_DELTA_TIME();
	}
	else if(IS_KEY_DOWN(DIK_DOWN))
	{
		m_stPosition.y -= 2.0f * GET_DELTA_TIME();
	}

	if(IS_KEY_DOWN(DIK_LEFT))
	{
		m_stPosition.x -= 2.0f * GET_DELTA_TIME();
	}
	else if(IS_KEY_DOWN(DIK_RIGHT))
	{
		m_stPosition.x += 2.0f * GET_DELTA_TIME();
	}

	if(IS_KEY_DOWN(DIK_A))
	{
		m_stScale.x -= 2.0f * GET_DELTA_TIME();
	}
	else if(IS_KEY_DOWN(DIK_D))
	{
		m_stScale.x += 2.0f * GET_DELTA_TIME();
	}

	m_stScale.x = ClampFloatValue(m_stScale.x, 0.1f, 2.0f);
}

void Example_12::draw(void)
{
	CDirect3DApplication::draw();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);

	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stTranslation;
	D3DXMatrixTranslation(&stTranslation, m_stPosition.x, m_stPosition.y, m_stPosition.z);

	D3DXMATRIXA16 stScale;
	D3DXMatrixScaling(&stScale, m_stScale.x, m_stScale.y, m_stScale.z);

	auto stWorldMatrix = stScale * stTranslation;
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	// }

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetIndices(m_pIndexBuffer);
	GET_DEVICE()->SetFVF(STVertex::FVF);

	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
}

LPDIRECT3DVERTEXBUFFER9 Example_12::createVertexBuffer(void)
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

LPDIRECT3DINDEXBUFFER9 Example_12::createIndexBuffer(void)
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
