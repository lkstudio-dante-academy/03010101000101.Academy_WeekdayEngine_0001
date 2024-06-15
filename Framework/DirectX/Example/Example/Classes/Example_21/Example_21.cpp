#include "Example_21.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CLight.h"
#include "../Global/Utility/Object/CCamera.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"
#include "../Global/Utility/Manager/CResourceManager.h"

Example_21::Example_21(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_21::~Example_21(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

void Example_21::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pVertexBuffer = this->createVertexBuffer();
	m_pIndexBuffer = this->createIndexBuffer();

	m_pEffect = GET_EFFECT("Resources/Effects/Example_21.fx");
	m_pTexture = GET_TEXTURE("Resources/Textures/HelloWorld.png");
}

void Example_21::update(void)
{
	CDirect3DApplication::update();
	m_fOffset += 1.0f * GET_DELTA_TIME();

	if(IS_KEY_PRESSED(DIK_1))
	{
		m_bIsToonShading = !m_bIsToonShading;
	}

	if(IS_KEY_DOWN(DIK_UP))
	{
		GET_LIGHT()->rotateByXAxis(90.0f * GET_DELTA_TIME(), false);
	}
	else if(IS_KEY_DOWN(DIK_DOWN))
	{
		GET_LIGHT()->rotateByXAxis(-90.0f * GET_DELTA_TIME(), false);
	}

	if(IS_KEY_DOWN(DIK_LEFT))
	{
		GET_LIGHT()->rotateByYAxis(-90.0f * GET_DELTA_TIME(), false);
	}
	else if(IS_KEY_DOWN(DIK_RIGHT))
	{
		GET_LIGHT()->rotateByYAxis(90.0f * GET_DELTA_TIME(), false);
	}
}

void Example_21::draw(void)
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

	D3DXVECTOR4 stLightDirection(GET_LIGHT()->getForwardDirection(), 0.0f);
	m_pEffect->SetVector("g_stLightDirection", &stLightDirection);

	m_pEffect->SetFloat("g_fOffset", m_fOffset);
	m_pEffect->SetBool("g_bIsToonShading", m_bIsToonShading);
	m_pEffect->SetTexture("g_pTexture", m_pTexture);

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetIndices(m_pIndexBuffer);
	GET_DEVICE()->SetFVF(STVertex::FVF);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	});
}

LPDIRECT3DVERTEXBUFFER9 Example_21::createVertexBuffer(void)
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
		pstVertices[0].m_stNormal = D3DXVECTOR3(-0.707f, 0.707f, -0.707f);
		pstVertices[0].m_stUV = D3DXVECTOR2(0.0f, 0.0f);

		pstVertices[1].m_stPosition = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		pstVertices[1].m_stNormal = D3DXVECTOR3(0.707f, 0.707f, -0.707f);
		pstVertices[1].m_stUV = D3DXVECTOR2(1.0f, 0.0f);

		pstVertices[2].m_stPosition = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		pstVertices[2].m_stNormal = D3DXVECTOR3(0.707f, -0.707f, -0.707f);
		pstVertices[2].m_stUV = D3DXVECTOR2(1.0f, 1.0f);

		pstVertices[3].m_stPosition = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		pstVertices[3].m_stNormal = D3DXVECTOR3(-0.707f, -0.707f, -0.707f);
		pstVertices[3].m_stUV = D3DXVECTOR2(0.0f, 1.0f);

		pVertexBuffer->Unlock();
	}
	// }

	return pVertexBuffer;
}

LPDIRECT3DINDEXBUFFER9 Example_21::createIndexBuffer(void)
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
