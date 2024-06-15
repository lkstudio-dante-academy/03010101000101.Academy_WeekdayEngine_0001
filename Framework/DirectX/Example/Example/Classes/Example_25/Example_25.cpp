#include "Example_25.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CLight.h"
#include "../Global/Utility/Object/CCamera.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"
#include "../Global/Utility/Manager/CResourceManager.h"

Example_25::Example_25(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_25::~Example_25(void)
{
	SAFE_RELEASE(m_pMesh);
}

void Example_25::initApplication(void)
{
	CDirect3DApplication::initApplication();
	GET_LIGHT()->setRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pMesh = this->createMesh();
	m_pEffect = GET_EFFECT("Resources/Effects/Example_25.fx");

	m_pDiffuseTexture = GET_TEXTURE("Resources/Textures/Stone.bmp");
	m_pNormalTexture = GET_TEXTURE("Resources/Textures/NormalMap.tga");
}

void Example_25::update(void)
{
	CDirect3DApplication::update();

	if(IS_KEY_DOWN(DIK_UP))
	{
		m_fParallax += 0.2f * GET_DELTA_TIME();
	}
	else if(IS_KEY_DOWN(DIK_DOWN))
	{
		m_fParallax -= 0.2f * GET_DELTA_TIME();
	}

	m_fParallax = ClampFloatValue(m_fParallax, 0.0f, 0.02f);

	if(IS_KEY_DOWN(DIK_LEFT))
	{
		GET_LIGHT()->rotateByYAxis(-90.0f * GET_DELTA_TIME());
	}
	else if(IS_KEY_DOWN(DIK_RIGHT))
	{
		GET_LIGHT()->rotateByYAxis(90.0f * GET_DELTA_TIME());
	}
}

void Example_25::draw(void)
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

	D3DXVECTOR4 stViewPosition(GET_CAMERA()->getPosition(), 1.0f);
	D3DXVECTOR4 stLightDirection(GET_LIGHT()->getForwardDirection(), 0.0f);

	m_pEffect->SetVector("g_stViewPosition", &stViewPosition);
	m_pEffect->SetVector("g_stLightDirection", &stLightDirection);

	m_pEffect->SetTexture("g_pDiffuseTexture", m_pDiffuseTexture);
	m_pEffect->SetTexture("g_pNormalTexture", m_pNormalTexture);

	m_pEffect->SetFloat("g_fParallax", m_fParallax);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		m_pMesh->DrawSubset(0);
	});
}

LPD3DXMESH Example_25::createMesh(void)
{
	D3DVERTEXELEMENT9 astElements[] = {
		0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0,
		0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0,
		0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0,
		0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0,
		0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0,
		D3DDECL_END()
	};

	LPD3DXMESH pMesh = nullptr;

	// �޽ø� �����Ѵ�
	D3DXCreateMesh(2,
		4,
		D3DXMESH_MANAGED,
		astElements,
		GET_DEVICE(),
		&pMesh);

	/** VS Input */�� �����Ѵ�
	// {
	STVertex* pstVertices = nullptr;

	if(SUCCEEDED(pMesh->LockVertexBuffer(0, (void**)&pstVertices)))
	{
		pstVertices[0].m_stPosition = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		pstVertices[0].m_stUV = D3DXVECTOR2(0.0f, 0.0f);

		pstVertices[1].m_stPosition = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		pstVertices[1].m_stUV = D3DXVECTOR2(1.0f, 0.0f);

		pstVertices[2].m_stPosition = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		pstVertices[2].m_stUV = D3DXVECTOR2(1.0f, 1.0f);

		pstVertices[3].m_stPosition = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		pstVertices[3].m_stUV = D3DXVECTOR2(0.0f, 1.0f);

		pMesh->UnlockVertexBuffer();
	}
	// }

	// �ε��� ������ �����Ѵ�
	// {
	WORD* pnIndices = nullptr;

	if(SUCCEEDED(pMesh->LockIndexBuffer(0, (void**)&pnIndices)))
	{
		pnIndices[0] = 0;	pnIndices[1] = 1;	pnIndices[2] = 2;
		pnIndices[3] = 0;	pnIndices[4] = 2;	pnIndices[5] = 3;

		pMesh->UnlockIndexBuffer();
	}
	// }

	/** VS Input */�� ����Ѵ�
	D3DXComputeNormals(pMesh, NULL);

	// ����, ������ ������ ����Ѵ�
	D3DXComputeTangent(pMesh, 0, 0, 0, TRUE, NULL);

	return pMesh;
}
