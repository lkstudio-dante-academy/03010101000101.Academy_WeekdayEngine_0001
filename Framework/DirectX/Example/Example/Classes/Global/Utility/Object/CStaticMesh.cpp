#include "CStaticMesh.h"
#include "../../Function/GlobalFunction.h"
#include "../Base/CDirect3DApplication.h"
#include "../../Utility/Object/CLight.h"
#include "../../Utility/Object/CCamera.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CResourceManager.h"

#define STATIC_MESH_TYPE_DEVICE			1
#define STATIC_MESH_TYPE_EFFECT			2

#define STATIC_MESH_TYPE			STATIC_MESH_TYPE_EFFECT

CStaticMesh::CStaticMesh(const STParameters& a_rstParameters)
	:
	m_stParameters(a_rstParameters)
{
	// Do Nothing
}

void CStaticMesh::init(void)
{
	CRenderObject::init();

	m_pEffect = GET_EFFECT(m_stParameters.m_oEffectFilepath);
	m_stStaticMesh = GET_STATIC_MESH(m_stParameters.m_oMeshFilepath);
}

void CStaticMesh::lateInit(void)
{
	auto stBoundingBox = CreateBoundingBox(m_stStaticMesh.m_pMesh);
	auto stBoundingSphere = CreateBoundingSphere(m_stStaticMesh.m_pMesh);

	this->setBoundingBox(stBoundingBox);
	this->setBoundingSphere(stBoundingSphere);
}

void CStaticMesh::doDrawObject(void)
{
	CRenderObject::doDrawObject();

	auto stWorldMatrix = this->getFinalWorldMatrix();
	this->drawStaticMesh(stWorldMatrix);
}

void CStaticMesh::postDrawObject(void)
{
	CRenderObject::postDrawObject();

#if STATIC_MESH_TYPE == STATIC_MESH_TYPE_DEVICE
	GET_DEVICE()->SetTexture(0, NULL);
#endif			// #if STATIC_MESH_TYPE == STATIC_MESH_TYPE_DEVICE
}

void CStaticMesh::doDrawShadow(void)
{
	CRenderObject::doDrawShadow();

	if(m_eShadowType == EShadowType::CIRCLE)
	{
		auto stWorldMatrix = m_stShadowMatrix * this->getFinalWorldMatrix();

		GET_DEVICE()->SetMaterial(&m_stShadowMaterial);
		GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);

		m_pShadowMesh->DrawSubset(0);
	}
	else
	{
		auto stWorldMatrix = this->getFinalWorldMatrix() * m_stShadowMatrix;
		this->drawStaticMesh(stWorldMatrix, true);
	}
}

void CStaticMesh::drawStaticMesh(const D3DXMATRIXA16& a_rstMatrix, bool a_bIsDrawingShadow)
{
#if STATIC_MESH_TYPE == STATIC_MESH_TYPE_DEVICE
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &a_rstMatrix);

	for(int i = 0; i < m_stStaticMesh.m_nNumMaterials; ++i)
	{
		if(a_bIsDrawingShadow)
		{
			GET_DEVICE()->SetMaterial(&m_stShadowMaterial);
		}
		else
		{
			GET_DEVICE()->SetMaterial(&m_stStaticMesh.m_oMaterialList[i]);
		}

		GET_DEVICE()->SetTexture(0, m_stStaticMesh.m_oTextureList[i]);
		m_stStaticMesh.m_pMesh->DrawSubset(i);
	}
#else
	// ����� �����Ѵ�
	// {
	auto stViewMatrix = GET_CAMERA()->getViewMatrix();
	auto stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();

	auto stLightViewMatrix = GET_LIGHT()->getViewMatrix();
	auto stLightProjectionMatrix = GET_LIGHT()->getProjectionMatrix();

	m_pEffect->SetMatrix("g_stWorldMatrix", &a_rstMatrix);
	m_pEffect->SetMatrix("g_stViewMatrix", &stViewMatrix);
	m_pEffect->SetMatrix("g_stProjectionMatrix", &stProjectionMatrix);

	m_pEffect->SetMatrix("g_stLightViewMatrix", &stLightViewMatrix);
	m_pEffect->SetMatrix("g_stLightProjectionMatrix", &stLightProjectionMatrix);
	// }

	D3DXVECTOR4 stViewPosition(GET_CAMERA()->getPosition(), 1.0f);
	D3DXVECTOR4 stLightDirection(GET_LIGHT()->getForwardDirection(), 0.0f);

	m_pEffect->SetVector("g_stViewPosition", &stViewPosition);
	m_pEffect->SetVector("g_stLightDirection", &stLightDirection);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		for(int i = 0; i < m_stStaticMesh.m_nNumMaterials; ++i)
		{
			D3DXVECTOR4 stDiffuse;
			ZeroMemory(&stDiffuse, sizeof(stDiffuse));

			if(a_bIsDrawingShadow)
			{
				CopyMemory(&stDiffuse, &m_stShadowMaterial.Diffuse, sizeof(stDiffuse));
			}
			else
			{
				CopyMemory(&stDiffuse, &m_stStaticMesh.m_oMaterialList[i].Diffuse, sizeof(stDiffuse));
			}

			m_pEffect->SetVector("g_stDiffuse", &stDiffuse);
			m_pEffect->SetTexture("g_pTexture", m_stStaticMesh.m_oTextureList[i]);

			m_pEffect->CommitChanges();
			m_stStaticMesh.m_pMesh->DrawSubset(i);
		}
	});
#endif			// #if STATIC_MESH_TYPE == STATIC_MESH_TYPE_DEVICE
}
