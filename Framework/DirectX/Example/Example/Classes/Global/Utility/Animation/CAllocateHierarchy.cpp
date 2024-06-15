#include "CAllocateHierarchy.h"
#include "../Object/CSkinnedMesh.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CResourceManager.h"

CAllocateHierarchy::CAllocateHierarchy(const STParameters& a_rstParameters)
	:
	m_stParameters(a_rstParameters)
{
	// Do Nothing
}

HRESULT CALLBACK CAllocateHierarchy::CreateFrame(const char* a_pszName, LPD3DXFRAME* a_pstOutFrame)
{
	auto pstBone = new STBone();

	if(a_pszName != nullptr)
	{
		pstBone->Name = (char*)malloc(sizeof(char) * (strlen(a_pszName) + 1));
		strcpy(pstBone->Name, a_pszName);
	}

	D3DXMatrixIdentity(&pstBone->m_stCombineMatrix);
	D3DXMatrixIdentity(&pstBone->TransformationMatrix);

	*a_pstOutFrame = pstBone;
	return S_OK;
}

HRESULT CAllocateHierarchy::CreateMeshContainer(const char* a_pszName,
	const D3DXMESHDATA* a_pstMeshData,
	const D3DXMATERIAL* a_pstXMaterials,
	const D3DXEFFECTINSTANCE* a_pstEffectInstances,
	DWORD a_nNumMaterials,
	const DWORD* a_pnAdjacency,
	LPD3DXSKININFO a_pstSkinInfo,
	LPD3DXMESHCONTAINER* a_pstOutMeshContainer)
{
	auto pstMeshContainer = new STMeshContainer();

	// �Ϲ� �޽� �� ���
	if(a_pstMeshData->Type == D3DXMESHDATATYPE::D3DXMESHTYPE_MESH)
	{
		pstMeshContainer->MeshData = *a_pstMeshData;
		pstMeshContainer->MeshData.pMesh->AddRef();

		pstMeshContainer->pAdjacency = (DWORD*)malloc(sizeof(DWORD) * (a_pstMeshData->pMesh->GetNumFaces() * 3));
		CopyMemory(pstMeshContainer->pAdjacency, a_pnAdjacency, sizeof(DWORD) * (a_pstMeshData->pMesh->GetNumFaces() * 3));

		if(a_pszName != nullptr)
		{
			pstMeshContainer->Name = (char*)malloc(sizeof(char) * (strlen(a_pszName) + 1));
			strcpy(pstMeshContainer->Name, a_pszName);
		}

		/** VS Input */�� �����Ѵ�
		// {
		pstMeshContainer->NumMaterials = a_nNumMaterials;

		pstMeshContainer->pMaterials = (D3DXMATERIAL*)malloc(sizeof(D3DXMATERIAL) * a_nNumMaterials);
		CopyMemory(pstMeshContainer->pMaterials, a_pstXMaterials, sizeof(D3DXMATERIAL) * a_nNumMaterials);

		for(int i = 0; i < a_nNumMaterials; ++i)
		{
			LPDIRECT3DTEXTURE9 pTexture = nullptr;

			if(a_pstXMaterials[i].pTextureFilename != nullptr)
			{
				char szTextureFilepath[MAX_PATH] = "";
				sprintf(szTextureFilepath, "%s/%s", m_stParameters.m_oBasepath.c_str(), a_pstXMaterials[i].pTextureFilename);

				pTexture = GET_TEXTURE(szTextureFilepath);
			}

			pstMeshContainer->m_oTextureList.push_back(pTexture);
		}
		// }

		// ��Ų ������ �����Ѵ�
		// {
		if(a_pstSkinInfo != nullptr)
		{
			pstMeshContainer->pSkinInfo = a_pstSkinInfo;
			pstMeshContainer->pSkinInfo->AddRef();

			for(int i = 0; i < a_pstSkinInfo->GetNumBones(); ++i)
			{
				auto stBoneMatrix = *a_pstSkinInfo->GetBoneOffsetMatrix(i);
				pstMeshContainer->m_oBoneMatrixList.push_back(stBoneMatrix);
			}

			m_nMeshContainerNumber += 1;
			pstMeshContainer->m_pSkinnedMesh = m_stParameters.m_oSkinnedMeshCreator(pstMeshContainer, m_nMeshContainerNumber);
		}
		// }
	}

	*a_pstOutMeshContainer = pstMeshContainer;
	return S_OK;
}

HRESULT CALLBACK CAllocateHierarchy::DestroyFrame(LPD3DXFRAME a_pstFrame)
{
	SAFE_FREE(a_pstFrame->Name);
	SAFE_DELETE(a_pstFrame);

	return S_OK;
}

HRESULT CALLBACK CAllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER a_pMeshContainer)
{
	auto pstMeshContainer = static_cast<STMeshContainer*>(a_pMeshContainer);

	SAFE_FREE(pstMeshContainer->Name);
	SAFE_FREE(pstMeshContainer->pMaterials);

	SAFE_RELEASE(pstMeshContainer->pSkinInfo);
	SAFE_RELEASE(pstMeshContainer->MeshData.pMesh);

	SAFE_DELETE(pstMeshContainer);
	return S_OK;
}
