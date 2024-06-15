#include "Example_15.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Debug/CGizmo.h"
#include "../Global/Utility/Object/CLight.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"

Example_15::Example_15(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_15::~Example_15(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

void Example_15::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pLightGizmo = CreateObject<CGizmo>();
	m_pLightGizmo->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	GET_LIGHT()->setPosition(D3DXVECTOR3(0.0f, 0.0f, -10.0f));
	GET_LIGHT()->setRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	GET_LIGHT()->addChildObject(m_pLightGizmo);

	m_pVertexBuffer = this->createVertexBuffer();
	m_pIndexBuffer = this->createIndexBuffer();
}

void Example_15::update(void)
{
	CDirect3DApplication::update();
	m_fYaw += 90.0f * GET_DELTA_TIME();

	if(IS_KEY_DOWN(DIK_UP))
	{
		GET_LIGHT()->rotateByXAxis(90.0f * GET_DELTA_TIME());
	}
	else if(IS_KEY_DOWN(DIK_DOWN))
	{
		GET_LIGHT()->rotateByXAxis(-90.0f * GET_DELTA_TIME());
	}

	if(IS_KEY_DOWN(DIK_LEFT))
	{
		GET_LIGHT()->rotateByYAxis(-90.0f * GET_DELTA_TIME());
	}
	else if(IS_KEY_DOWN(DIK_RIGHT))
	{
		GET_LIGHT()->rotateByYAxis(90.0f * GET_DELTA_TIME());
	}
}

void Example_15::draw(void)
{
	CDirect3DApplication::draw();
	m_pLightGizmo->draw();

	// ������ �����Ѵ�
	// {
	D3DMATERIAL9 stMaterial;
	ZeroMemory(&stMaterial, sizeof(stMaterial));

	stMaterial.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	stMaterial.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stMaterial.Power = 20.0f;

	GET_DEVICE()->SetMaterial(&stMaterial);
	// }

	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixRotationY(&stWorldMatrix, D3DXToRadian(m_fYaw));

	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	// }

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetIndices(m_pIndexBuffer);
	GET_DEVICE()->SetFVF(STVertex::FVF);

	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 4);
}

LPDIRECT3DVERTEXBUFFER9 Example_15::createVertexBuffer(void)
{
	auto pVertexBuffer = CreateVertexBuffer(sizeof(STVertex) * 5,
		D3DUSAGE_WRITEONLY,
		STVertex::FVF,
		D3DPOOL_MANAGED);

	/** VS Input */�� �����Ѵ�
	// {
	STVertex* pstVertices = nullptr;

	if(SUCCEEDED(pVertexBuffer->Lock(0, 0, (void**)&pstVertices, 0)))
	{
		pstVertices[0].m_stPosition = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pstVertices[0].m_stNormal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pstVertices[1].m_stPosition = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
		pstVertices[1].m_stNormal = D3DXVECTOR3(0.707f, 0.0f, -0.707f);

		pstVertices[2].m_stPosition = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
		pstVertices[2].m_stNormal = D3DXVECTOR3(-0.707f, 0.0f, -0.707f);

		pstVertices[3].m_stPosition = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
		pstVertices[3].m_stNormal = D3DXVECTOR3(-0.707f, 0.0f, 0.707f);

		pstVertices[4].m_stPosition = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
		pstVertices[4].m_stNormal = D3DXVECTOR3(0.707f, 0.0f, 0.707f);

		pVertexBuffer->Unlock();
	}
	// }

	return pVertexBuffer;
}

LPDIRECT3DINDEXBUFFER9 Example_15::createIndexBuffer(void)
{
	auto pIndexBuffer = CreateIndexBuffer(sizeof(WORD) * 12,
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
		pnIndices[6] = 0;	pnIndices[7] = 4;	pnIndices[8] = 1;
		pnIndices[9] = 0;	pnIndices[10] = 3;	pnIndices[11] = 4;

		pIndexBuffer->Unlock();
	}
	// }

	return pIndexBuffer;
}
