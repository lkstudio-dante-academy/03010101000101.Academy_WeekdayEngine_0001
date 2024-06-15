#include "CSkinnedMesh.h"
#include "../../Function/GlobalFunction.h"
#include "../Base/CDirect3DApplication.h"
#include "../Animation/CAnimationController.h"
#include "../Object/CLight.h"
#include "../Object/CCamera.h"
#include "../Object/CTerrain.h"
#include "../Manager/CTimeManager.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CResourceManager.h"

#define SKINNED_MESH_TYPE_DEVICE			1
#define SKINNED_MESH_TYPE_EFFECT			2

#define SKINNED_MESH_TYPE			SKINNED_MESH_TYPE_DEVICE

CSkinnedMesh::CSkinnedMesh(const STParameters& a_rstParameters)
	:
	m_stParameters(a_rstParameters)
{
	if(a_rstParameters.m_oMeshFilepath.rfind('/') != std::string::npos)
	{
		m_oBasepath = a_rstParameters.m_oMeshFilepath.substr(0, a_rstParameters.m_oMeshFilepath.rfind('/'));
	}
}

CSkinnedMesh::~CSkinnedMesh(void)
{
	SAFE_DELETE(m_pAnimationController);

	CAllocateHierarchy::STParameters stParameters = {
		m_oBasepath, nullptr
	};

	CAllocateHierarchy oAllocateHierarchy(stParameters);
	D3DXFrameDestroy(m_pstRootBone, &oAllocateHierarchy);
}

void CSkinnedMesh::init(void)
{
	CRenderObject::init();

	m_pEffect = GET_EFFECT(m_stParameters.m_oEffectFilepath);
	m_pMesh = this->createSkinnedMeshFromX(m_stParameters.m_oMeshFilepath);
}

void CSkinnedMesh::lateInit(void)
{
	auto stBoundingBox = CreateBoundingBox(m_oMeshContainerList.front()->m_pSkinnedMesh);
	auto stBoundingSphere = CreateBoundingSphere(m_oMeshContainerList.front()->m_pSkinnedMesh);

	this->setBoundingBox(stBoundingBox);
	this->setBoundingSphere(stBoundingSphere);
}

std::string CSkinnedMesh::getBasepath(void)
{
	return m_oBasepath;
}

std::vector<std::string> CSkinnedMesh::getAnimationNameList(void)
{
	return m_pAnimationController->getAnimationNameList();
}

D3DXMATRIXA16 CSkinnedMesh::getBoundingWorldMatrix(void)
{
	if(m_pstDummyBone != nullptr)
	{
		auto stWorldMatrix = this->getFinalWorldMatrix();
		return m_pstDummyBone->TransformationMatrix * stWorldMatrix;
	}

	return CRenderObject::getBoundingWorldMatrix();
}

void CSkinnedMesh::setTimeScale(float a_fTimeScale)
{
	m_pAnimationController->setTimeScale(a_fTimeScale);
}

void CSkinnedMesh::setTerrain(CTerrain* a_pTerrain)
{
	m_pTerrain = a_pTerrain;
}

void CSkinnedMesh::update(void)
{
	CRenderObject::update();
	m_pAnimationController->update();

	auto stWorldMatrix = this->getFinalWorldMatrix();

	if(m_pTerrain != nullptr)
	{
		D3DXVECTOR3 stPosition;
		D3DXVECTOR3 stDummyPosition;

		CopyMemory(&stPosition, &stWorldMatrix(3, 0), sizeof(stPosition));
		CopyMemory(&stDummyPosition, &m_pstDummyBone->TransformationMatrix(3, 0), sizeof(stPosition));

		auto stFinalDummyPosition = stPosition + stDummyPosition;
		float fTerrainHeight = m_pTerrain->getHeightAtPosition(stFinalDummyPosition);

		if(fTerrainHeight > stFinalDummyPosition.y)
		{
			m_pstDummyBone->TransformationMatrix(3, 1) = fTerrainHeight - stPosition.y;
		}
	}

	this->updateBoneMatrix(m_pstRootBone, stWorldMatrix);
}

void CSkinnedMesh::doDrawObject(void)
{
	CRenderObject::doDrawObject();

#if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_DEVICE
	D3DXMATRIXA16 stWorldMatrix = this->getFinalWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
#endif			// #if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_DEVICE

	this->drawBone(m_pstRootBone);
}

void CSkinnedMesh::postDrawObject(void)
{
	CRenderObject::postDrawObject();

#if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_DEVICE
	GET_DEVICE()->SetTexture(0, NULL);
#endif			// #if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_DEVICE
}

void CSkinnedMesh::doDrawShadow(void)
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
#if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_DEVICE
		auto stWorldMatrix = this->getFinalWorldMatrix() * m_stShadowMatrix;
#else
		auto stWorldMatrix = this->getFinalWorldMatrix();
#endif			// #if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_DEVICE

		this->updateBoneMatrix(m_pstRootBone, stWorldMatrix);
		this->drawBone(m_pstRootBone, true);
	}
}

void CSkinnedMesh::drawBone(LPD3DXFRAME a_pstFrame, bool a_bIsDrawingShadow)
{
	auto pstMeshContainer = a_pstFrame->pMeshContainer;

	while(pstMeshContainer != nullptr)
	{
#if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_EFFECT
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

		if(a_bIsDrawingShadow)
		{
			m_pEffect->SetMatrix("g_stShadowMatrix", &m_stShadowMatrix);
		}
		// }

		D3DXVECTOR4 stViewPosition(GET_CAMERA()->getPosition(), 1.0f);
		D3DXVECTOR4 stLightDirection(GET_LIGHT()->getForwardDirection(), 0.0f);

		m_pEffect->SetVector("g_stViewPosition", &stViewPosition);
		m_pEffect->SetVector("g_stLightDirection", &stLightDirection);

		m_pEffect->SetBool("g_bIsDrawingShadow", a_bIsDrawingShadow);
#endif			// #if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_EFFECT

		this->drawMeshContainer(a_pstFrame, pstMeshContainer, a_bIsDrawingShadow);
		pstMeshContainer = pstMeshContainer->pNextMeshContainer;
	}

	if(a_pstFrame->pFrameSibling != nullptr)
	{
		this->drawBone(a_pstFrame->pFrameSibling, a_bIsDrawingShadow);
	}

	if(a_pstFrame->pFrameFirstChild != nullptr)
	{
		this->drawBone(a_pstFrame->pFrameFirstChild, a_bIsDrawingShadow);
	}
}

void CSkinnedMesh::drawMeshContainer(LPD3DXFRAME a_pstFrame, LPD3DXMESHCONTAINER a_pstMeshContainer, bool a_bIsDrawingShadow)
{
	if(a_pstMeshContainer->pSkinInfo != nullptr)
	{
#if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_DEVICE
		D3DCAPS9 stDeviceCaps;
		GET_DIRECT3D()->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stDeviceCaps);

		auto pstMeshContainer = static_cast<CAllocateHierarchy::STMeshContainer*>(a_pstMeshContainer);

		for(int i = 0; i < pstMeshContainer->m_oBoneCombinationList.size(); ++i)
		{
			int nNumBlends = 0;
			auto stBoneCombination = pstMeshContainer->m_oBoneCombinationList[i];

			// ����� ������ ���� ������ Ž���Ѵ�
			for(int j = 0; j < pstMeshContainer->m_nNumBlends; ++j)
			{
				if(stBoneCombination.BoneId[j] != UINT_MAX)
				{
					nNumBlends = j;
				}
			}

			if(nNumBlends < stDeviceCaps.MaxVertexBlendMatrices)
			{
				int nAttributeID = pstMeshContainer->m_oBoneCombinationList[i].AttribId;

				for(int j = 0; j < pstMeshContainer->m_nNumBlends; ++j)
				{
					if(stBoneCombination.BoneId[j] != UINT_MAX)
					{
						int nIndex = stBoneCombination.BoneId[j];
						auto pstBone = pstMeshContainer->m_oBoneList[nIndex];
						auto stBoneMatrix = pstMeshContainer->m_oBoneMatrixList[nIndex];

						auto stWorldMatrix = stBoneMatrix * pstBone->m_stCombineMatrix;
						GET_DEVICE()->SetTransform(D3DTS_WORLDMATRIX(j), &stWorldMatrix);
					}
				}

				if(a_bIsDrawingShadow)
				{
					GET_DEVICE()->SetMaterial(&m_stShadowMaterial);
				}
				else
				{
					GET_DEVICE()->SetMaterial(&pstMeshContainer->pMaterials[nAttributeID].MatD3D);
					GET_DEVICE()->SetTexture(0, pstMeshContainer->m_oTextureList[nAttributeID]);
				}

				GET_DEVICE()->SetRenderState(D3DRS_VERTEXBLEND, nNumBlends);
				pstMeshContainer->m_pSkinnedMesh->DrawSubset(i);
			}
		}

		/** VS Input */带 ��Ȱ��ȭ�Ѵ�
		GET_DEVICE()->SetRenderState(D3DRS_VERTEXBLEND, 0);
#else
		auto pstMeshContainer = static_cast<CAllocateHierarchy::STMeshContainer*>(a_pstMeshContainer);

		for(int i = 0; i < pstMeshContainer->m_oBoneCombinationList.size(); ++i)
		{
			int nNumBlends = 0;
			auto stBoneCombination = pstMeshContainer->m_oBoneCombinationList[i];

			// ����� ������ ���� ������ Ž���Ѵ�
			for(int j = 0; j < pstMeshContainer->m_nNumBlends; ++j)
			{
				if(stBoneCombination.BoneId[j] != UINT_MAX)
				{
					nNumBlends = j;
				}
			}

			// ����� �����Ѵ�
			// {
			int nAttributeID = stBoneCombination.AttribId;
			D3DXMATRIXA16 astBlendMatrices[MAX_NUM_BLENDS];

			for(int j = 0; j < pstMeshContainer->m_nNumBlends; ++j)
			{
				if(stBoneCombination.BoneId[j] == UINT_MAX)
				{
					D3DXMatrixIdentity(astBlendMatrices + j);
				}
				else
				{
					int nIndex = stBoneCombination.BoneId[j];
					auto pstBone = pstMeshContainer->m_oBoneList[nIndex];
					auto stBoneMatrix = pstMeshContainer->m_oBoneMatrixList[nIndex];

					astBlendMatrices[j] = stBoneMatrix * pstBone->m_stCombineMatrix;
				}
			}

			m_pEffect->SetInt("g_nNumBlends", nNumBlends);
			m_pEffect->SetMatrixArray("g_astBlendMatrices", astBlendMatrices, nNumBlends + 1);
			// }

			// ������ �����Ѵ�
			// {
			D3DXVECTOR4 stDiffuse;
			ZeroMemory(&stDiffuse, sizeof(stDiffuse));

			if(a_bIsDrawingShadow)
			{
				CopyMemory(&stDiffuse, &m_stShadowMaterial.Diffuse, sizeof(stDiffuse));
			}
			else
			{
				CopyMemory(&stDiffuse, &pstMeshContainer->pMaterials[nAttributeID].MatD3D.Diffuse, sizeof(stDiffuse));
			}

			m_pEffect->SetVector("g_stDiffuse", &stDiffuse);
			m_pEffect->SetTexture("g_pTexture", pstMeshContainer->m_oTextureList[nAttributeID]);
			// }

			RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
			{
				pstMeshContainer->m_pSkinnedMesh->DrawSubset(i);
			});
		}
#endif			// #if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_DEVICE
	}
}

void CSkinnedMesh::playAnimation(const std::string& a_rAnimationName, bool a_bIsLoop)
{
	m_pAnimationController->playAnimation(a_rAnimationName, a_bIsLoop);
}

void CSkinnedMesh::stopAnimation(void)
{
	m_pAnimationController->stopAnimation();
}

void CSkinnedMesh::setupBone(LPD3DXFRAME a_pstFrame)
{
	if(a_pstFrame->pMeshContainer != nullptr)
	{
		this->setupBoneOnMeshContainer(a_pstFrame->pMeshContainer);
	}

	if(a_pstFrame->pFrameSibling != nullptr)
	{
		this->setupBone(a_pstFrame->pFrameSibling);
	}

	if(a_pstFrame->pFrameFirstChild != nullptr)
	{
		this->setupBone(a_pstFrame->pFrameFirstChild);
	}
}

void CSkinnedMesh::setupBoneOnMeshContainer(LPD3DXMESHCONTAINER a_pstMeshContainer)
{
	auto pstMeshContainer = static_cast<CAllocateHierarchy::STMeshContainer*>(a_pstMeshContainer);

	if(pstMeshContainer->pSkinInfo != nullptr)
	{
		UINT nNumBones = pstMeshContainer->pSkinInfo->GetNumBones();

		for(int i = 0; i < nNumBones; ++i)
		{
			std::string oBoneName = pstMeshContainer->pSkinInfo->GetBoneName(i);
			auto pstBone = static_cast<CAllocateHierarchy::STBone*>(D3DXFrameFind(m_pstRootBone, oBoneName.c_str()));

			pstMeshContainer->m_oBoneList.push_back(pstBone);
		}
	}
}

void CSkinnedMesh::updateBoneMatrix(LPD3DXFRAME a_pstFrame, const D3DXMATRIXA16& a_rstMatrix)
{
	auto pstBone = static_cast<CAllocateHierarchy::STBone*>(a_pstFrame);
	pstBone->m_stCombineMatrix = pstBone->TransformationMatrix * a_rstMatrix;

	if(pstBone->pFrameSibling != nullptr)
	{
		this->updateBoneMatrix(pstBone->pFrameSibling, a_rstMatrix);
	}

	if(pstBone->pFrameFirstChild != nullptr)
	{
		this->updateBoneMatrix(pstBone->pFrameFirstChild, pstBone->m_stCombineMatrix);
	}
}

LPD3DXMESH CSkinnedMesh::createSkinnedMesh(LPD3DXMESHCONTAINER a_pstMeshContainer, int a_nMeshContainerNumber)
{
	auto pstMeshContainer = static_cast<CAllocateHierarchy::STMeshContainer*>(a_pstMeshContainer);

	char szMeshFilepath[MAX_PATH] = "";
	sprintf(szMeshFilepath, "%02d/%s", a_nMeshContainerNumber, m_stParameters.m_oMeshFilepath.c_str());

	if(GET_MESH(szMeshFilepath) == nullptr)
	{
		DWORD nNumBlends = 0;
		DWORD nNumBoneCombinations;

		LPD3DXMESH pMesh = nullptr;
		LPD3DXBUFFER pBoneCombination = nullptr;

		// ��Ų�� �޽ø� �����Ѵ�
		a_pstMeshContainer->pSkinInfo->ConvertToBlendedMesh(a_pstMeshContainer->MeshData.pMesh,
			D3DXMESH_MANAGED | D3DXMESHOPT_VERTEXCACHE,
			a_pstMeshContainer->pAdjacency,
			a_pstMeshContainer->pAdjacency,
			NULL,
			NULL,
			&nNumBlends,
			&nNumBoneCombinations,
			&pBoneCombination,
			&pMesh);

		D3DVERTEXELEMENT9 astElements[] = {
			0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0,
			0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0,
			0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0,
			0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0,
			0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0,
			0, 56, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0,
			D3DDECL_END()
		};

		auto pOriginMesh = pMesh;

		// �޽ø� �����Ѵ�
		pOriginMesh->CloneMesh(pOriginMesh->GetOptions(),
			astElements,
			GET_DEVICE(),
			&pMesh);

		/** VS Input */�� ����Ѵ�
		D3DXComputeNormals(pMesh, a_pstMeshContainer->pAdjacency);

		// ����, ������ ������ ����Ѵ�
		D3DXComputeTangent(pMesh, 0, 0, 0, TRUE, a_pstMeshContainer->pAdjacency);

		STSkinnedMesh stSkinnedMesh = {
			nNumBlends,
			pMesh
		};

		/** VS Input */�� �����Ѵ�
		stSkinnedMesh.m_pnAdjacency = (DWORD*)malloc(sizeof(DWORD) * (pMesh->GetNumFaces() * 3));
		CopyMemory(stSkinnedMesh.m_pnAdjacency, pstMeshContainer->pAdjacency, sizeof(DWORD) * (pMesh->GetNumFaces() * 3));

		// �� ���� ������ �����Ѵ�
		for(int i = 0; i < nNumBoneCombinations; ++i)
		{
			auto pstBoneCombinations = static_cast<LPD3DXBONECOMBINATION>(pBoneCombination->GetBufferPointer());

			auto stBoneCombination = pstBoneCombinations[i];
			stBoneCombination.BoneId = (DWORD*)malloc(sizeof(DWORD) * nNumBlends);

			CopyMemory(stBoneCombination.BoneId, pstBoneCombinations[i].BoneId, sizeof(DWORD) * nNumBlends);
			stSkinnedMesh.m_oBoneCombinationList.push_back(stBoneCombination);
		}

		SAFE_RELEASE(pOriginMesh);
		SAFE_RELEASE(pBoneCombination);

		// �޽� ������ �߰��Ѵ�
		GET_RESOURCE_MANAGER()->addMeshForKey(szMeshFilepath, stSkinnedMesh.m_pMesh);
		GET_RESOURCE_MANAGER()->addSkinnedMeshForKey(szMeshFilepath, stSkinnedMesh);
	}

	SAFE_FREE(a_pstMeshContainer->pAdjacency);
	auto stSkinnedMesh = GET_SKINNED_MESH(szMeshFilepath);

	pstMeshContainer->pAdjacency = stSkinnedMesh.m_pnAdjacency;
	pstMeshContainer->m_nNumBlends = stSkinnedMesh.m_nNumBlends;
	pstMeshContainer->m_oBoneCombinationList = stSkinnedMesh.m_oBoneCombinationList;

	m_oMeshContainerList.push_back(pstMeshContainer);
	return stSkinnedMesh.m_pMesh;
}

LPD3DXMESH CSkinnedMesh::createSkinnedMeshFromX(const std::string& a_rFilepath)
{
	CAllocateHierarchy::STParameters stParameters = {
		m_oBasepath,
		std::bind(&CSkinnedMesh::createSkinnedMesh, this, std::placeholders::_1, std::placeholders::_2)
	};

	CAllocateHierarchy oAllocateHierarchy(stParameters);
	LPD3DXANIMATIONCONTROLLER pAnimationController = nullptr;

	// �޽� ������ �����Ѵ�
	D3DXLoadMeshHierarchyFromXA(a_rFilepath.c_str(),
		D3DXMESH_MANAGED,
		GET_DEVICE(),
		&oAllocateHierarchy,
		NULL,
		(LPD3DXFRAME*)&m_pstRootBone,
		&pAnimationController);

	/** VS Input */�Ѵ�
	this->setupBone(m_pstRootBone);

	// �ִϸ��̼� ��Ʈ�ѷ��� �����Ѵ�
	m_pAnimationController = CreateInstance<CAnimationController>(pAnimationController);

	auto pstDummyFrame = D3DXFrameFind(m_pstRootBone, m_stParameters.m_oDummyBoneName.c_str());
	m_pstDummyBone = static_cast<CAllocateHierarchy::STBone*>(pstDummyFrame);

	return m_oMeshContainerList.front()->m_pSkinnedMesh;
}
