#include "Example_20.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CCamera.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"
#include "../Global/Utility/Manager/CResourceManager.h"

Example_20::Example_20(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize),

	m_fTileSizeX(1.0f),
	m_fTileSizeY(1.0f),
	m_bIsGrayscale(true)
{
	// Do Nothing
}

Example_20::~Example_20(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

void Example_20::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pVertexBuffer = this->createVertexBuffer();
	m_pIndexBuffer = this->createIndexBuffer();

	m_pEffect = GET_EFFECT("Resources/Effects/Example_20.fx");
	m_pTexture = GET_TEXTURE("Resources/Textures/HelloWorld.png");
}

void Example_20::update(void)
{
	CDirect3DApplication::update();

	if(IS_KEY_PRESSED(DIK_1))
	{
		m_bIsGrayscale = true;
	}
	else if(IS_KEY_PRESSED(DIK_2))
	{
		m_bIsGrayscale = false;
	}

	if(IS_KEY_PRESSED(DIK_UP))
	{
		m_fTileSizeY += 1.0f;
	}
	else if(IS_KEY_PRESSED(DIK_DOWN))
	{
		m_fTileSizeY -= 1.0f;
	}

	if(IS_KEY_PRESSED(DIK_LEFT))
	{
		m_fTileSizeX -= 1.0f;
	}
	else if(IS_KEY_PRESSED(DIK_RIGHT))
	{
		m_fTileSizeX += 1.0f;
	}

	m_fTileSizeX = ClampFloatValue(m_fTileSizeX, 1.0f, 5.0f);
	m_fTileSizeY = ClampFloatValue(m_fTileSizeY, 1.0f, 5.0f);
}

void Example_20::draw(void)
{
	CDirect3DApplication::draw();

	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixIdentity(&stWorldMatrix);

	auto stViewMatrix = GET_CAMERA()->getViewMatrix();
	auto stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	m_pEffect->SetMatrix("g_stViewMatrix", &stViewMatrix);
	m_pEffect->SetMatrix("g_stProjectionMatrix", &stProjectionMatrix);
	// }

	m_pEffect->SetFloat("g_fTileSizeX", m_fTileSizeX);
	m_pEffect->SetFloat("g_fTileSizeY", m_fTileSizeY);

	m_pEffect->SetBool("g_bIsGrayscale", m_bIsGrayscale);
	m_pEffect->SetTexture("g_pTexture", m_pTexture);

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetIndices(m_pIndexBuffer);
	GET_DEVICE()->SetFVF(STVertex::FVF);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	});
}

LPDIRECT3DVERTEXBUFFER9 Example_20::createVertexBuffer(void)
{
	auto pVertexBuffer = CreateVertexBuffer(sizeof(STVertex) * 4,
		D3DUSAGE_WRITEONLY,
		STVertex::FVF,
		D3DPOOL_MANAGED);

	/** VS Input */�� �����Ѵ�
	// {
	STVertex* pstVertices = nullptr;

	if(SUCCEEDED(pVertexBuffer->Lock(0, 0, (void**)&pstVertices, 0)))
	{
		pstVertices[0].m_stPosition = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		pstVertices[0].m_stUV = D3DXVECTOR2(0.0f, 0.0f);

		pstVertices[1].m_stPosition = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		pstVertices[1].m_stUV = D3DXVECTOR2(1.0f, 0.0f);

		pstVertices[2].m_stPosition = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		pstVertices[2].m_stUV = D3DXVECTOR2(1.0f, 1.0f);

		pstVertices[3].m_stPosition = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		pstVertices[3].m_stUV = D3DXVECTOR2(0.0f, 1.0f);

		pVertexBuffer->Unlock();
	}
	// }

	return pVertexBuffer;
}

LPDIRECT3DINDEXBUFFER9 Example_20::createIndexBuffer(void)
{
	auto pIndexBuffer = CreateIndexBuffer(sizeof(WORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED);

	// �ε��� ������ �����Ѵ�
	// {
	WORD* pnIndices = nullptr;

	if(SUCCEEDED(pIndexBuffer->Lock(0, 0, (void**)&pnIndices, 0)))
	{
		pnIndices[0] = 0;	pnIndices[1] = 1;	pnIndices[2] = 2;
		pnIndices[3] = 0;	pnIndices[4] = 2;	pnIndices[5] = 3;

		pIndexBuffer->Unlock();
	}
	// }

	return pIndexBuffer;
}
