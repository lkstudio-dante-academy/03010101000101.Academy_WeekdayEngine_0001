#include "Example_35.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CLight.h"
#include "../Global/Utility/Object/CCamera.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"
#include "../Global/Utility/Manager/CResourceManager.h"

Example_35::Example_35(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize),

	m_stPosition(0.0f, 3.0f, 0.0f)
{
	// Do Nothing
}

Example_35::~Example_35(void)
{
	SAFE_RELEASE(m_pBoxMesh);
	SAFE_RELEASE(m_pTeapotMesh);
	SAFE_RELEASE(m_pGroundMesh);

	SAFE_RELEASE(m_pRenderTarget);
	SAFE_RELEASE(m_pDepthStencil);
}

void Example_35::initApplication(void)
{
	CDirect3DApplication::initApplication();
	m_pEffect = GET_EFFECT("Resources/Effects/Example_35.fx");

	m_pBoxMesh = this->createBoxMesh();
	m_pTeapotMesh = this->createTeapotMesh();
	m_pGroundMesh = this->createGroundMesh();

	m_pRenderTarget = this->createRenderTarget();
	m_pDepthStencil = this->createDepthStencil();
}

void Example_35::update(void)
{
	CDirect3DApplication::update();

	GET_LIGHT()->setPosition(D3DXVECTOR3(0.0f, 25.0f, -25.0f));
	GET_LIGHT()->rotateByPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if(IS_KEY_DOWN(DIK_UP))
	{
		m_stPosition.z += 10.0f * GET_DELTA_TIME();
	}
	else if(IS_KEY_DOWN(DIK_DOWN))
	{
		m_stPosition.z -= 10.0f * GET_DELTA_TIME();
	}

	if(IS_KEY_DOWN(DIK_LEFT))
	{
		m_stPosition.x -= 10.0f * GET_DELTA_TIME();
	}
	else if(IS_KEY_DOWN(DIK_RIGHT))
	{
		m_stPosition.x += 10.0f * GET_DELTA_TIME();
	}
}

void Example_35::draw(void)
{
	CDirect3DApplication::draw();

	// ����� �����Ѵ�
	// {
	auto stViewMatrix = GET_CAMERA()->getViewMatrix();
	auto stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();

	auto stLightViewMatrix = GET_LIGHT()->getViewMatrix();
	auto stLightProjectionMatrix = GET_LIGHT()->getProjectionMatrix();

	m_pEffect->SetMatrix("g_stViewMatrix", &stViewMatrix);
	m_pEffect->SetMatrix("g_stProjectionMatrix", &stProjectionMatrix);

	m_pEffect->SetMatrix("g_stLightViewMatrix", &stLightViewMatrix);
	m_pEffect->SetMatrix("g_stLightProjectionMatrix", &stLightProjectionMatrix);
	// }

	D3DXVECTOR4 stViewPosition(GET_CAMERA()->getPosition(), 1.0f);
	D3DXVECTOR4 stLightDirection(GET_LIGHT()->getForwardDirection(), 0.0f);

	m_pEffect->SetVector("g_stViewPosition", &stViewPosition);
	m_pEffect->SetVector("g_stLightDirection", &stLightDirection);

	this->drawShadow();
	this->drawBoxMesh("ApplyShadow");
	this->drawTeapotMesh("ApplyShadow");
	this->drawGroundMesh("ApplyShadow");
}

void Example_35::drawShadow(void)
{
	D3DVIEWPORT9 stOriginViewport;
	LPDIRECT3DSURFACE9 pOriginRenderTarget = nullptr;
	LPDIRECT3DSURFACE9 pOriginDepthStencil = nullptr;

	GET_DEVICE()->GetViewport(&stOriginViewport);
	GET_DEVICE()->GetRenderTarget(0, &pOriginRenderTarget);
	GET_DEVICE()->GetDepthStencilSurface(&pOriginDepthStencil);

	// ����Ʈ�� �����Ѵ�
	// {
	D3DVIEWPORT9 stViewport = {
		0,
		0,
		2048,
		2048,
		0.0f,
		1.0f
	};

	GET_DEVICE()->SetViewport(&stViewport);
	// }

	// ���� Ÿ���� �����Ѵ�
	// {
	LPDIRECT3DSURFACE9 pRenderTarget = nullptr;

	if(SUCCEEDED(m_pRenderTarget->GetSurfaceLevel(0, &pRenderTarget)))
	{
		GET_DEVICE()->SetRenderTarget(0, pRenderTarget);
		SAFE_RELEASE(pRenderTarget);
	}
	// }

	// ���� ���ٽ��� �����Ѵ�
	GET_DEVICE()->SetDepthStencilSurface(m_pDepthStencil);

	// ���۸� �����
	GET_DEVICE()->Clear(0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 255, 255),
		1.0f,
		0);

	this->drawBoxMesh("CreateShadow");
	this->drawTeapotMesh("CreateShadow");
	this->drawGroundMesh("CreateShadow");

	GET_DEVICE()->SetViewport(&stOriginViewport);
	GET_DEVICE()->SetRenderTarget(0, pOriginRenderTarget);
	GET_DEVICE()->SetDepthStencilSurface(pOriginDepthStencil);

	SAFE_RELEASE(pOriginRenderTarget);
	SAFE_RELEASE(pOriginDepthStencil);
}

void Example_35::drawBoxMesh(const std::string& a_rTechniqueName)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixIdentity(&stWorldMatrix);

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	// }

	if(a_rTechniqueName == "ApplyShadow")
	{
		D3DXVECTOR4 stDiffuse = {
			0.0f, 0.0f, 1.0f, 1.0f
		};

		m_pEffect->SetVector("g_stDiffuse", &stDiffuse);
		m_pEffect->SetTexture("g_pShadowTexture", m_pRenderTarget);
	}

	RunEffectLoop(m_pEffect, a_rTechniqueName, [=](int a_nPassNumber) -> void
	{
		m_pBoxMesh->DrawSubset(0);
	});
}

void Example_35::drawTeapotMesh(const std::string& a_rTechniqueName)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixTranslation(&stWorldMatrix, m_stPosition.x, m_stPosition.y, m_stPosition.z);

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	// }

	if(a_rTechniqueName == "ApplyShadow")
	{
		D3DXVECTOR4 stDiffuse = {
			1.0f, 0.0f, 0.0f, 1.0f
		};

		m_pEffect->SetVector("g_stDiffuse", &stDiffuse);
		m_pEffect->SetTexture("g_pShadowTexture", m_pRenderTarget);
	}

	RunEffectLoop(m_pEffect, a_rTechniqueName, [=](int a_nPassNumber) -> void
	{
		m_pTeapotMesh->DrawSubset(0);
	});
}

void Example_35::drawGroundMesh(const std::string& a_rTechniqueName)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixTranslation(&stWorldMatrix, 0, -1.25f, 0.0f);

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	// }

	if(a_rTechniqueName == "ApplyShadow")
	{
		D3DXVECTOR4 stDiffuse = {
			1.0f, 1.0f, 1.0f, 1.0f
		};

		m_pEffect->SetVector("g_stDiffuse", &stDiffuse);
		m_pEffect->SetTexture("g_pShadowTexture", m_pRenderTarget);
	}

	RunEffectLoop(m_pEffect, a_rTechniqueName, [=](int a_nPassNumber) -> void
	{
		m_pGroundMesh->DrawSubset(0);
	});
}

LPD3DXMESH Example_35::createBoxMesh(void)
{
	LPD3DXMESH pMesh = nullptr;
	LPD3DXBUFFER pAdjacency = nullptr;

	// �޽ø� �����Ѵ�
	D3DXCreateBox(GET_DEVICE(),
		2.0f,
		2.0f,
		2.0f,
		&pMesh,
		&pAdjacency);

	/** VS Input */�� ����Ѵ�
	D3DXComputeNormals(pMesh, (DWORD*)(pAdjacency->GetBufferPointer()));

	SAFE_RELEASE(pAdjacency);
	return pMesh;
}

LPD3DXMESH Example_35::createTeapotMesh(void)
{
	LPD3DXMESH pMesh = nullptr;
	LPD3DXBUFFER pAdjacency = nullptr;

	// �޽ø� �����Ѵ�
	D3DXCreateTeapot(GET_DEVICE(),
		&pMesh,
		&pAdjacency);

	/** VS Input */�� ����Ѵ�
	D3DXComputeNormals(pMesh, (DWORD*)(pAdjacency->GetBufferPointer()));

	SAFE_RELEASE(pAdjacency);
	return pMesh;
}

LPD3DXMESH Example_35::createGroundMesh(void)
{
	LPD3DXMESH pMesh = nullptr;
	LPD3DXBUFFER pAdjacency = nullptr;

	// �޽ø� �����Ѵ�
	D3DXCreateBox(GET_DEVICE(),
		100.0f,
		0.5f,
		100.0f,
		&pMesh,
		&pAdjacency);

	/** VS Input */�� ����Ѵ�
	D3DXComputeNormals(pMesh, (DWORD*)(pAdjacency->GetBufferPointer()));

	SAFE_RELEASE(pAdjacency);
	return pMesh;

}

LPDIRECT3DTEXTURE9 Example_35::createRenderTarget(void)
{
	LPDIRECT3DTEXTURE9 pRenderTarget = nullptr;

	// ���� Ÿ���� �����Ѵ�
	GET_DEVICE()->CreateTexture(2048,
		2048,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_R32F,
		D3DPOOL_DEFAULT,
		&pRenderTarget,
		NULL);

	return pRenderTarget;
}

LPDIRECT3DSURFACE9 Example_35::createDepthStencil(void)
{
	LPDIRECT3DSURFACE9 pDepthStencil = nullptr;

	// ���� ���ٽ��� �����Ѵ�
	GET_DEVICE()->CreateDepthStencilSurface(2048,
		2048,
		D3DFMT_D24X8,
		D3DMULTISAMPLE_NONE,
		0,
		true,
		&pDepthStencil,
		NULL);

	return pDepthStencil;
}
