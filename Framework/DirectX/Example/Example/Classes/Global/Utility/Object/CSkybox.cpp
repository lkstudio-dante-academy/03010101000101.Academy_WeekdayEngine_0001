#include "CSkybox.h"
#include "../../Function/GlobalFunction.h"
#include "../Base/CDirect3DApplication.h"
#include "../Object/CCamera.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CResourceManager.h"

CSkybox::CSkybox(const STParameters& a_rstParameters)
	:
	m_stParameters(a_rstParameters)
{
	// Do Nothing
}

CSkybox::~CSkybox(void)
{
	SAFE_RELEASE(m_pMesh);
}

void CSkybox::init(void)
{
	CRenderObject::init();

	m_pMesh = this->createMesh();
	m_pEffect = GET_EFFECT(m_stParameters.m_oEffectFilepath);
	m_pCubeTexture = GET_CUBE_TEXTURE(m_stParameters.m_oCubeTextureFilepath);
}

void CSkybox::doDrawObject(void)
{
	CRenderObject::doDrawObject();

	/** VS Output */�� �����Ѵ�
	// {
	auto stWorldMatrix = this->getWorldMatrix();
	auto stViewMatrix = GET_CAMERA()->getViewMatrix();
	auto stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	m_pEffect->SetMatrix("g_stViewMatrix", &stViewMatrix);
	m_pEffect->SetMatrix("g_stProjectionMatrix", &stProjectionMatrix);
	// }

	m_pEffect->SetTexture("g_pCubeTexture", m_pCubeTexture);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		m_pMesh->DrawSubset(0);
	});
}

LPD3DXMESH CSkybox::createMesh(void)
{
	LPD3DXMESH pMesh = nullptr;
	LPD3DXBUFFER pAdjacency = nullptr;

	// �޽ø� �����Ѵ�
	D3DXCreateSphere(GET_DEVICE(),
		m_stParameters.m_fRadius,
		m_stParameters.m_nSlices,
		m_stParameters.m_nStacks,
		&pMesh,
		&pAdjacency);

	/** VS Input */�� ����Ѵ�
	D3DXComputeNormals(pMesh, (DWORD*)(pAdjacency->GetBufferPointer()));

	SAFE_RELEASE(pAdjacency);
	return pMesh;
}
