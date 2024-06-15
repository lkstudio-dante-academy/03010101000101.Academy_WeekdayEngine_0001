#include "Example_23.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CLight.h"
#include "../Global/Utility/Object/CCamera.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"
#include "../Global/Utility/Manager/CResourceManager.h"

Example_23::Example_23(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_23::~Example_23(void)
{
	SAFE_RELEASE(m_pBoxMesh);
	SAFE_RELEASE(m_pSphereMesh);
	SAFE_RELEASE(m_pTorusMesh);
	SAFE_RELEASE(m_pCylinderMesh);
	SAFE_RELEASE(m_pTeapotMesh);
}

void Example_23::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pBoxMesh = this->createBoxMesh();
	m_pSphereMesh = this->createSphereMesh();
	m_pTorusMesh = this->createTorusMesh();
	m_pCylinderMesh = this->createCylinderMesh();
	m_pTeapotMesh = this->createTeapotMesh();

	m_pEffect = GET_EFFECT("Resources/Effects/Example_23.fx");
}

void Example_23::update(void)
{
	CDirect3DApplication::update();

	if(IS_KEY_DOWN(DIK_UP))
	{
		GET_LIGHT()->moveByZAxis(10.0f * GET_DELTA_TIME());
	}
	else if(IS_KEY_DOWN(DIK_DOWN))
	{
		GET_LIGHT()->moveByZAxis(-10.0f * GET_DELTA_TIME());
	}

	if(IS_KEY_DOWN(DIK_LEFT))
	{
		GET_LIGHT()->moveByXAxis(-10.0f * GET_DELTA_TIME());
	}
	else if(IS_KEY_DOWN(DIK_RIGHT))
	{
		GET_LIGHT()->moveByXAxis(10.0f * GET_DELTA_TIME());
	}
}

void Example_23::draw(void)
{
	CDirect3DApplication::draw();

	// ����� �����Ѵ�
	// {
	auto stViewMatrix = GET_CAMERA()->getViewMatrix();
	auto stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();

	m_pEffect->SetMatrix("g_stViewMatrix", &stViewMatrix);
	m_pEffect->SetMatrix("g_stProjectionMatrix", &stProjectionMatrix);
	// }

	D3DXVECTOR4 stViewPosition(GET_CAMERA()->getPosition(), 1.0f);
	D3DXVECTOR4 stLightPosition(GET_LIGHT()->getPosition(), 1.0f);

	m_pEffect->SetVector("g_stViewPosition", &stViewPosition);
	m_pEffect->SetVector("g_stLightPosition", &stLightPosition);

	this->drawBoxMesh();
	this->drawSphereMesh();
	this->drawTorusMesh();
	this->drawCylinderMesh();
	this->drawTeapotMesh();
}

void Example_23::drawBoxMesh(void)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixTranslation(&stWorldMatrix, 3.0f, 0.0f, 0.0f);

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	// }

	D3DXVECTOR4 stDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_pEffect->SetVector("g_stDiffuseColor", &stDiffuseColor);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		m_pBoxMesh->DrawSubset(0);
	});
}

void Example_23::drawSphereMesh(void)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixTranslation(&stWorldMatrix, -3.0f, 0.0f, 0.0f);

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	// }

	D3DXVECTOR4 stDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);
	m_pEffect->SetVector("g_stDiffuseColor", &stDiffuseColor);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		m_pSphereMesh->DrawSubset(0);
	});
}

void Example_23::drawTorusMesh(void)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixTranslation(&stWorldMatrix, 0.0f, 3.0f, 0.0f);

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	// }

	D3DXVECTOR4 stDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);
	m_pEffect->SetVector("g_stDiffuseColor", &stDiffuseColor);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		m_pTorusMesh->DrawSubset(0);
	});
}

void Example_23::drawCylinderMesh(void)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixTranslation(&stWorldMatrix, 0.0f, -3.0f, 0.0f);

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	// }

	D3DXVECTOR4 stDiffuseColor(1.0f, 1.0f, 0.0f, 1.0f);
	m_pEffect->SetVector("g_stDiffuseColor", &stDiffuseColor);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		m_pCylinderMesh->DrawSubset(0);
	});
}

void Example_23::drawTeapotMesh(void)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixIdentity(&stWorldMatrix);

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	// }

	D3DXVECTOR4 stDiffuseColor(0.0f, 1.0f, 1.0f, 1.0f);
	m_pEffect->SetVector("g_stDiffuseColor", &stDiffuseColor);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		m_pTeapotMesh->DrawSubset(0);
	});
}

LPD3DXMESH Example_23::createBoxMesh(void)
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

LPD3DXMESH Example_23::createSphereMesh(void)
{
	LPD3DXMESH pMesh = nullptr;
	LPD3DXBUFFER pAdjacency = nullptr;

	// �޽ø� �����Ѵ�
	D3DXCreateSphere(GET_DEVICE(),
		1.5f,
		50,
		50,
		&pMesh,
		&pAdjacency);

	/** VS Input */�� ����Ѵ�
	D3DXComputeNormals(pMesh, (DWORD*)(pAdjacency->GetBufferPointer()));

	SAFE_RELEASE(pAdjacency);
	return pMesh;
}

LPD3DXMESH Example_23::createTorusMesh(void)
{
	LPD3DXMESH pMesh = nullptr;
	LPD3DXBUFFER pAdjacency = nullptr;

	// �޽ø� �����Ѵ�
	D3DXCreateTorus(GET_DEVICE(),
		0.5f,
		1.0f,
		50,
		50,
		&pMesh,
		&pAdjacency);

	/** VS Input */�� ����Ѵ�
	D3DXComputeNormals(pMesh, (DWORD*)(pAdjacency->GetBufferPointer()));

	SAFE_RELEASE(pAdjacency);
	return pMesh;
}

LPD3DXMESH Example_23::createCylinderMesh(void)
{
	LPD3DXMESH pMesh = nullptr;
	LPD3DXBUFFER pAdjacency = nullptr;

	// �޽ø� �����Ѵ�
	D3DXCreateCylinder(GET_DEVICE(),
		1.0f,
		1.0f,
		5.0f,
		50,
		50,
		&pMesh,
		&pAdjacency);

	/** VS Input */�� ����Ѵ�
	D3DXComputeNormals(pMesh, (DWORD*)(pAdjacency->GetBufferPointer()));

	SAFE_RELEASE(pAdjacency);
	return pMesh;
}

LPD3DXMESH Example_23::createTeapotMesh(void)
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
