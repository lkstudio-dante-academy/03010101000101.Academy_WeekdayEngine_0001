#include "CResourceManager.h"
#include "CDeviceManager.h"
#include "../../Function/GlobalFunction.h"
#include "../Animation/CAllocateHierarchy.h"

CResourceManager::~CResourceManager(void)
{
	for(auto& rValueType : m_oWaveSoundList)
	{
		SAFE_FREE(rValueType.second.m_pnBytes);
	}

	for(auto& rValueType : m_oMeshList)
	{
		SAFE_RELEASE(rValueType.second);
	}

	for(auto& rValueType : m_oEffectList)
	{
		SAFE_RELEASE(rValueType.second);
	}

	for(auto& rValueType : m_oTextureList)
	{
		SAFE_RELEASE(rValueType.second);
	}

	for(auto& rValueType : m_oCubeTextureList)
	{
		SAFE_RELEASE(rValueType.second);
	}

	for(auto& rValueType : m_oSkinnedMeshList)
	{
		for(auto& rstBoneCombination : rValueType.second.m_oBoneCombinationList)
		{
			SAFE_FREE(rstBoneCombination.BoneId);
		}

		SAFE_FREE(rValueType.second.m_pnAdjacency);
	}
}

LPD3DXMESH CResourceManager::getMeshForKey(const std::string& a_rKey)
{
	auto oIterator = m_oMeshList.find(a_rKey);
	return (oIterator == m_oMeshList.end()) ? nullptr : oIterator->second;
}

STSkinnedMesh CResourceManager::getSkinnedMeshForKey(const std::string& a_rKey)
{
	auto oIterator = m_oSkinnedMeshList.find(a_rKey);
	assert(oIterator != m_oSkinnedMeshList.end());

	return oIterator->second;
}

STStaticMesh CResourceManager::getStaticMeshForKey(const std::string& a_rKey, bool a_bIsCreateEnable)
{
	auto oIterator = m_oStaticMeshList.find(a_rKey);

	if(oIterator == m_oStaticMeshList.end())
	{
		assert(a_bIsCreateEnable);
		auto stStaticMesh = this->createStaticMeshFromFile(a_rKey);

		this->addMeshForKey(a_rKey, stStaticMesh.m_pMesh);
		this->addStaticMeshForKey(a_rKey, stStaticMesh);

		return stStaticMesh;
	}

	return oIterator->second;
}

LPD3DXEFFECT CResourceManager::getEffectForKey(const std::string& a_rKey, bool a_bIsCreateEnable)
{
	auto oIterator = m_oEffectList.find(a_rKey);

	if(oIterator == m_oEffectList.end())
	{
		LPD3DXEFFECT pEffect = nullptr;

		if(a_bIsCreateEnable)
		{
			pEffect = this->createEffectFromFile(a_rKey);
			this->addEffectForKey(a_rKey, pEffect);
		}

		return pEffect;
	}

	return oIterator->second;
}

LPDIRECT3DTEXTURE9 CResourceManager::getTextureForKey(const std::string& a_rKey, bool a_bIsCreateEnable)
{
	auto oIterator = m_oTextureList.find(a_rKey);

	if(oIterator == m_oTextureList.end())
	{
		LPDIRECT3DTEXTURE9 pTexture = nullptr;

		if(a_bIsCreateEnable)
		{
			pTexture = this->createTextureFromFile(a_rKey);
			this->addTextureForKey(a_rKey, pTexture);
		}

		return pTexture;
	}

	return oIterator->second;
}

LPDIRECT3DTEXTURE9 CResourceManager::getSpriteTextureForKey(const std::string& a_rKey, bool a_bIsCreateEnable)
{
	auto oIterator = m_oTextureList.find(a_rKey);

	if(oIterator == m_oTextureList.end())
	{
		LPDIRECT3DTEXTURE9 pSpriteTexture = nullptr;

		if(a_bIsCreateEnable)
		{
			pSpriteTexture = this->createSpriteTextureFromFile(a_rKey);
			this->addSpriteTextureForKey(a_rKey, pSpriteTexture);
		}

		return pSpriteTexture;
	}

	return oIterator->second;
}

LPDIRECT3DCUBETEXTURE9 CResourceManager::getCubeTextureForKey(const std::string& a_rKey, bool a_bIsCreateEnable)
{
	auto oIterator = m_oCubeTextureList.find(a_rKey);

	if(oIterator == m_oCubeTextureList.end())
	{
		LPDIRECT3DCUBETEXTURE9 pCubeTexture = nullptr;

		if(a_bIsCreateEnable)
		{
			pCubeTexture = this->createCubeTextureFromFile(a_rKey);
			this->addCubeTextureForKey(a_rKey, pCubeTexture);
		}

		return pCubeTexture;
	}

	return oIterator->second;
}

STWaveSound CResourceManager::getWaveSoundForKey(const std::string& a_rKey, bool a_bIsCreateEnable)
{
	auto oIterator = m_oWaveSoundList.find(a_rKey);

	if(oIterator == m_oWaveSoundList.end())
	{
		STWaveSound stWaveSound;

		if(a_bIsCreateEnable)
		{
			stWaveSound = this->createWaveSoundFromFile(a_rKey);
			this->addWaveSoundForKey(a_rKey, stWaveSound);
		}

		return stWaveSound;
	}

	return oIterator->second;
}

void CResourceManager::addMeshForKey(const std::string& a_rKey, LPD3DXMESH a_pMesh)
{
	auto oIterator = m_oMeshList.find(a_rKey);

	if(oIterator == m_oMeshList.end())
	{
		m_oMeshList.insert(decltype(m_oMeshList)::value_type(a_rKey, a_pMesh));
	}
}

void CResourceManager::addStaticMeshForKey(const std::string& a_rKey, const STStaticMesh& a_rstStaticMesh)
{
	auto oIterator = m_oStaticMeshList.find(a_rKey);

	if(oIterator == m_oStaticMeshList.end())
	{
		m_oStaticMeshList.insert(decltype(m_oStaticMeshList)::value_type(a_rKey, a_rstStaticMesh));
	}
}

void CResourceManager::addSkinnedMeshForKey(const std::string& a_rKey, const STSkinnedMesh& a_rstSkinnedMesh)
{
	auto oIterator = m_oSkinnedMeshList.find(a_rKey);

	if(oIterator == m_oSkinnedMeshList.end())
	{
		m_oSkinnedMeshList.insert(decltype(m_oSkinnedMeshList)::value_type(a_rKey, a_rstSkinnedMesh));
	}
}

void CResourceManager::addEffectForKey(const std::string& a_rKey, LPD3DXEFFECT a_pEffect)
{
	auto oIterator = m_oEffectList.find(a_rKey);

	if(oIterator == m_oEffectList.end())
	{
		m_oEffectList.insert(decltype(m_oEffectList)::value_type(a_rKey, a_pEffect));
	}
}

void CResourceManager::addTextureForKey(const std::string& a_rKey, LPDIRECT3DTEXTURE9 a_pTexture)
{
	auto oIterator = m_oTextureList.find(a_rKey);

	if(oIterator == m_oTextureList.end())
	{
		m_oTextureList.insert(decltype(m_oTextureList)::value_type(a_rKey, a_pTexture));
	}
}

void CResourceManager::addSpriteTextureForKey(const std::string& a_rKey, LPDIRECT3DTEXTURE9 a_pTexture)
{
	this->addTextureForKey(a_rKey, a_pTexture);
}

void CResourceManager::addCubeTextureForKey(const std::string& a_rKey, LPDIRECT3DCUBETEXTURE9 a_pCubeTexture)
{
	auto oIterator = m_oCubeTextureList.find(a_rKey);

	if(oIterator == m_oCubeTextureList.end())
	{
		m_oCubeTextureList.insert(decltype(m_oCubeTextureList)::value_type(a_rKey, a_pCubeTexture));
	}
}

void CResourceManager::addWaveSoundForKey(const std::string& a_rKey, const STWaveSound& a_rstWaveSound)
{
	auto oIterator = m_oWaveSoundList.find(a_rKey);

	if(oIterator == m_oWaveSoundList.end())
	{
		m_oWaveSoundList.insert(decltype(m_oWaveSoundList)::value_type(a_rKey, a_rstWaveSound));
	}
}

void CResourceManager::removeMeshForKey(const std::string& a_rKey)
{
	m_oMeshList.erase(a_rKey);
}

void CResourceManager::removeStaticMeshForKey(const std::string& a_rKey)
{
	m_oStaticMeshList.erase(a_rKey);
}

void CResourceManager::removeSkinnedMeshForKey(const std::string& a_rKey)
{
	m_oSkinnedMeshList.erase(a_rKey);
}

void CResourceManager::removeEffectForKey(const std::string& a_rKey)
{
	m_oEffectList.erase(a_rKey);
}

void CResourceManager::removeTextureForKey(const std::string& a_rKey)
{
	m_oTextureList.erase(a_rKey);
}

void CResourceManager::removeCubeTextureForKey(const std::string& a_rKey)
{
	m_oCubeTextureList.erase(a_rKey);
}

void CResourceManager::removeWaveSoundForKey(const std::string& a_rKey)
{
	m_oWaveSoundList.erase(a_rKey);
}

STStaticMesh CResourceManager::createStaticMeshFromFile(const std::string& a_rFilepath)
{
	STStaticMesh stStaticMesh;

	LPD3DXBUFFER pAdjacency = nullptr;
	LPD3DXBUFFER pMaterialBuffer = nullptr;

	// �޽ø� �����Ѵ�
	D3DXLoadMeshFromXA(a_rFilepath.c_str(),
		D3DXMESH_MANAGED,
		GET_DEVICE(),
		&pAdjacency,
		&pMaterialBuffer,
		NULL,
		&stStaticMesh.m_nNumMaterials,
		&stStaticMesh.m_pMesh);

	/** VS Input */�� �����Ѵ�
	// {
	D3DVERTEXELEMENT9 astElements[] = {
		0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0,
		0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0,
		0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0,
		0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0,
		0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0,
		D3DDECL_END()
	};

	auto pOriginMesh = stStaticMesh.m_pMesh;

	// �޽ø� �����Ѵ�
	pOriginMesh->CloneMesh(pOriginMesh->GetOptions(),
		astElements,
		GET_DEVICE(),
		&stStaticMesh.m_pMesh);

	SAFE_RELEASE(pOriginMesh);
	// }

	/** VS Input */�� �����Ѵ�
	// {
	std::string oBasePath = "";
	LPD3DXMATERIAL pXMaterials = (LPD3DXMATERIAL)(pMaterialBuffer->GetBufferPointer());

	if(a_rFilepath.rfind('/') != std::string::npos)
	{
		oBasePath = a_rFilepath.substr(0, a_rFilepath.rfind('/'));
	}

	for(int i = 0; i < stStaticMesh.m_nNumMaterials; ++i)
	{
		D3DMATERIAL9 stMaterial = pXMaterials[i].MatD3D;
		LPDIRECT3DTEXTURE9 pTexture = nullptr;

		// �ؽ�ó ������ ���� ���
		if(pXMaterials[i].pTextureFilename != nullptr)
		{
			char szTextureFilepath[MAX_PATH] = "";
			sprintf(szTextureFilepath, "%s/%s", oBasePath.c_str(), pXMaterials[i].pTextureFilename);

			pTexture = this->getTextureForKey(szTextureFilepath);
		}

		stStaticMesh.m_oMaterialList.push_back(stMaterial);
		stStaticMesh.m_oTextureList.push_back(pTexture);
	}
	// }

	/** VS Input */�� �����Ѵ�
	D3DXComputeNormals(stStaticMesh.m_pMesh, (DWORD*)(pAdjacency->GetBufferPointer()));

	// ����, ������ ������ ����Ѵ�
	D3DXComputeTangent(stStaticMesh.m_pMesh, 0, 0, 0, TRUE, (DWORD*)(pAdjacency->GetBufferPointer()));

	SAFE_RELEASE(pAdjacency);
	return stStaticMesh;
}

LPD3DXEFFECT CResourceManager::createEffectFromFile(const std::string& a_rFilepath)
{
	LPD3DXEFFECT pEffect = nullptr;
	LPD3DXBUFFER pErrorBuffer = nullptr;

	// ����Ʈ�� �����Ѵ�
	D3DXCreateEffectFromFileA(GET_DEVICE(),
		a_rFilepath.c_str(),
		NULL,
		NULL,
		0,
		NULL,
		&pEffect,
		&pErrorBuffer);

	if(pErrorBuffer != nullptr)
	{
		char* pszErrorMessage = (char*)(pErrorBuffer->GetBufferPointer());
		printf("CResourceManager.createEffectFromFile: %s\n", pszErrorMessage);

		SAFE_RELEASE(pErrorBuffer);
	}

	return pEffect;
}

LPDIRECT3DTEXTURE9 CResourceManager::createTextureFromFile(const std::string& a_rFilepath)
{
	LPDIRECT3DTEXTURE9 pTexture = nullptr;

	// �ؽ�ó�� �����Ѵ�
	D3DXCreateTextureFromFileA(GET_DEVICE(),
		a_rFilepath.c_str(),
		&pTexture);

	return pTexture;
}

LPDIRECT3DTEXTURE9 CResourceManager::createSpriteTextureFromFile(const std::string& a_rFilepath)
{
	LPDIRECT3DTEXTURE9 pSpriteTexture = nullptr;

	// �ؽ�ó�� �����Ѵ�
	D3DXCreateTextureFromFileExA(GET_DEVICE(),
		a_rFilepath.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(0, 0, 0, 0),
		NULL,
		NULL,
		&pSpriteTexture);

	return pSpriteTexture;
}

LPDIRECT3DCUBETEXTURE9 CResourceManager::createCubeTextureFromFile(const std::string& a_rFilepath)
{
	LPDIRECT3DCUBETEXTURE9 pCubeTexture = nullptr;

	// �ؽ�ó�� �����Ѵ�
	D3DXCreateCubeTextureFromFileA(GET_DEVICE(),
		a_rFilepath.c_str(),
		&pCubeTexture);

	return pCubeTexture;
}

STWaveSound CResourceManager::createWaveSoundFromFile(const std::string& a_rFilepath)
{
	STWaveSound stWaveSound;
	ZeroMemory(&stWaveSound, sizeof(stWaveSound));

	/** VS Input */�� �����Ѵ�
	// {
	HMMIO hWaveFile = mmioOpenA((char*)(a_rFilepath.c_str()), NULL, MMIO_READ);

	if(hWaveFile != nullptr)
	{
		MMCKINFO stChunkInfo;
		ZeroMemory(&stChunkInfo, sizeof(stChunkInfo));

		stChunkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hWaveFile, &stChunkInfo, NULL, MMIO_FINDRIFF);

		MMCKINFO stSubChunkInfo;
		ZeroMemory(&stSubChunkInfo, sizeof(stSubChunkInfo));

		stSubChunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hWaveFile, &stSubChunkInfo, &stChunkInfo, MMIO_FINDCHUNK);

		/** VS Input */�� �����Ѵ�
		mmioRead(hWaveFile, (char*)(&stWaveSound.m_stWaveFormat), sizeof(stWaveSound.m_stWaveFormat));
		mmioAscend(hWaveFile, &stSubChunkInfo, 0);

		stSubChunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hWaveFile, &stSubChunkInfo, &stChunkInfo, MMIO_FINDCHUNK);

		stWaveSound.m_nNumBytes = stSubChunkInfo.cksize;
		stWaveSound.m_pnBytes = (BYTE*)malloc(sizeof(BYTE) * stSubChunkInfo.cksize);

		/** VS Input */�� �����Ѵ�
		mmioRead(hWaveFile, (char*)(stWaveSound.m_pnBytes), stSubChunkInfo.cksize);
		mmioClose(hWaveFile, 0);
	}
	// }

	return stWaveSound;
}
