#include "Example_22.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CCamera.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"
#include "../Global/Utility/Manager/CResourceManager.h"

#define BILLBOARD_TYPE_SPHERE			1
#define BILLBOARD_TYPE_Y_AXIS			2

#define BILLBOARD_TYPE			BILLBOARD_TYPE_SPHERE

Example_22::Example_22(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize),

	m_fOpacity(1.0f)
{
	// Do Nothing
}

Example_22::~Example_22(void)
{
	SAFE_DELETE(m_pObject);

	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

void Example_22::initApplication(void)
{
	CDirect3DApplication::initApplication();
	m_pObject = CreateObject<CObject>();

	m_pVertexBuffer = this->createVertexBuffer();
	m_pIndexBuffer = this->createIndexBuffer();

	m_pEffect = GET_EFFECT("Resources/Effects/Example_22.fx");
	m_pTexture = GET_TEXTURE("Resources/Textures/HelloWorld.png");
}

void Example_22::update(void)
{
	CDirect3DApplication::update();
	m_pObject->update();

#if BILLBOARD_TYPE == BILLBOARD_TYPE_SPHERE
	m_pObject->rotateByPosition(GET_CAMERA()->getPosition());
#else
	m_pObject->rotateByPosition(GET_CAMERA()->getPosition(), false);
#endif			// #if BILLBOARD_TYPE == BILLBOARD_TYPE_SPHERE

	m_pObject->rotateByYAxis(-180.0f);

	if(IS_KEY_DOWN(DIK_UP))
	{
		m_fOpacity += 1.0f * GET_DELTA_TIME();
	}
	else if(IS_KEY_DOWN(DIK_DOWN))
	{
		m_fOpacity -= 1.0f * GET_DELTA_TIME();
	}

	m_fOpacity = ClampFloatValue(m_fOpacity, 0.0f, 1.0f);
}

void Example_22::draw(void)
{
	CDirect3DApplication::draw();

	// ����� �����Ѵ�
	// {
	auto stWorldMatrix = m_pObject->getWorldMatrix();
	auto stViewMatrix = GET_CAMERA()->getViewMatrix();
	auto stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	m_pEffect->SetMatrix("g_stViewMatrix", &stViewMatrix);
	m_pEffect->SetMatrix("g_stProjectionMatrix", &stProjectionMatrix);
	// }

	m_pEffect->SetFloat("g_fOpacity", m_fOpacity);
	m_pEffect->SetTexture("g_pTexture", m_pTexture);

	m_pEffect->SetTechnique("MyTechnique");

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetIndices(m_pIndexBuffer);
	GET_DEVICE()->SetFVF(STVertex::FVF);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	});
}

LPDIRECT3DVERTEXBUFFER9 Example_22::createVertexBuffer(void)
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

LPDIRECT3DINDEXBUFFER9 Example_22::createIndexBuffer(void)
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
