#include "Example_26.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CLight.h"
#include "../Global/Utility/Object/CCamera.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"
#include "../Global/Utility/Manager/CResourceManager.h"

Example_26::Example_26(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_26::~Example_26(void)
{
	SAFE_RELEASE(m_pBoxMesh);
	SAFE_RELEASE(m_pSphereMesh);
	SAFE_RELEASE(m_pTorusMesh);
	SAFE_RELEASE(m_pCylinderMesh);
	SAFE_RELEASE(m_pTeapotMesh);
}

void Example_26::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pBoxMesh = this->createBoxMesh();
	m_pSphereMesh = this->createSphereMesh();
	m_pTorusMesh = this->createTorusMesh();
	m_pCylinderMesh = this->createCylinderMesh();
	m_pTeapotMesh = this->createTeapotMesh();

	m_pEffect = GET_EFFECT("Resources/Effects/Example_26.fx");
	m_pCubeTexture = GET_CUBE_TEXTURE("Resources/Textures/CubeMap.dds");
}

void Example_26::update(void)
{
	CDirect3DApplication::update();

	if(IS_KEY_DOWN(DIK_LEFT))
	{
		m_fYaw -= 90.0f * GET_DELTA_TIME();
	}
	else if(IS_KEY_DOWN(DIK_RIGHT))
	{
		m_fYaw += 90.0f * GET_DELTA_TIME();
	}
}

void Example_26::draw(void)
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
	D3DXVECTOR4 stLightDirection(GET_LIGHT()->getForwardDirection(), 0.0f);

	m_pEffect->SetVector("g_stViewPosition", &stViewPosition);
	m_pEffect->SetVector("g_stLightDirection", &stLightDirection);

	m_pEffect->SetTexture("g_pCubeTexture", m_pCubeTexture);

	this->drawBoxMesh();
	this->drawSphereMesh();
	this->drawTorusMesh();
	this->drawCylinderMesh();
	this->drawTeapotMesh();
}

void Example_26::drawBoxMesh(void)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stRotation;
	D3DXMatrixRotationY(&stRotation, D3DXToRadian(m_fYaw));

	D3DXMATRIXA16 stTranslation;
	D3DXMatrixTranslation(&stTranslation, 3.0f, 0.0f, 0.0f);

	auto stWorldMatrix = stRotation * stTranslation;
	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	// }

	D3DXVECTOR4 stDiffuse(1.0f, 0.0f, 0.0f, 1.0f);
	m_pEffect->SetVector("g_stDiffuse", &stDiffuse);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		m_pBoxMesh->DrawSubset(0);
	});
}

void Example_26::drawSphereMesh(void)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stRotation;
	D3DXMatrixRotationY(&stRotation, D3DXToRadian(m_fYaw));

	D3DXMATRIXA16 stTranslation;
	D3DXMatrixTranslation(&stTranslation, -3.0f, 0.0f, 0.0f);

	auto stWorldMatrix = stRotation * stTranslation;
	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	// }

	D3DXVECTOR4 stDiffuse(0.0f, 1.0f, 0.0f, 1.0f);
	m_pEffect->SetVector("g_stDiffuse", &stDiffuse);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		m_pSphereMesh->DrawSubset(0);
	});
}

void Example_26::drawTorusMesh(void)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stRotation;
	D3DXMatrixRotationY(&stRotation, D3DXToRadian(m_fYaw));

	D3DXMATRIXA16 stTranslation;
	D3DXMatrixTranslation(&stTranslation, 0.0f, 3.0f, 0.0f);

	auto stWorldMatrix = stRotation * stTranslation;
	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	// }

	D3DXVECTOR4 stDiffuse(0.0f, 0.0f, 1.0f, 1.0f);
	m_pEffect->SetVector("g_stDiffuse", &stDiffuse);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		m_pTorusMesh->DrawSubset(0);
	});
}

void Example_26::drawCylinderMesh(void)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stRotation;
	D3DXMatrixRotationY(&stRotation, D3DXToRadian(m_fYaw));

	D3DXMATRIXA16 stTranslation;
	D3DXMatrixTranslation(&stTranslation, 0.0f, -3.0f, 0.0f);

	auto stWorldMatrix = stRotation * stTranslation;
	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	// }

	D3DXVECTOR4 stDiffuse(1.0f, 1.0f, 0.0f, 1.0f);
	m_pEffect->SetVector("g_stDiffuse", &stDiffuse);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		m_pCylinderMesh->DrawSubset(0);
	});
}

void Example_26::drawTeapotMesh(void)
{
	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stRotation;
	D3DXMatrixRotationY(&stRotation, D3DXToRadian(m_fYaw));

	D3DXMATRIXA16 stTranslation;
	D3DXMatrixTranslation(&stTranslation, 0.0f, 0.0f, 0.0f);

	auto stWorldMatrix = stRotation * stTranslation;
	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	// }

	D3DXVECTOR4 stDiffuse(0.0f, 1.0f, 1.0f, 1.0f);
	m_pEffect->SetVector("g_stDiffuse", &stDiffuse);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		m_pTeapotMesh->DrawSubset(0);
	});
}

LPD3DXMESH Example_26::createBoxMesh(void)
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

LPD3DXMESH Example_26::createSphereMesh(void)
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

LPD3DXMESH Example_26::createTorusMesh(void)
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

LPD3DXMESH Example_26::createCylinderMesh(void)
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

LPD3DXMESH Example_26::createTeapotMesh(void)
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
