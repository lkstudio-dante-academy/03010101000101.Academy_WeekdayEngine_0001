#pragma once

#include "../../Define/KGlobalDefine.h"

//! ���ҽ� ������
class CResourceManager
{
public:			// getter

	//! �޽ø� ��ȯ�Ѵ�
	LPD3DXMESH getMeshForKey(const std::string& a_rKey);

	//! ��Ų�� �޽ø� ��ȯ�Ѵ�
	STSkinnedMesh getSkinnedMeshForKey(const std::string& a_rKey);

	//! ���� �޽ø� ��ȯ�Ѵ�
	STStaticMesh getStaticMeshForKey(const std::string& a_rKey, bool a_bIsCreateEnable = true);

	//! ����Ʈ�� ��ȯ�Ѵ�
	LPD3DXEFFECT getEffectForKey(const std::string& a_rKey, bool a_bIsCreateEnable = true);

	//! �ؽ�ó�� ��ȯ�Ѵ�
	LPDIRECT3DTEXTURE9 getTextureForKey(const std::string& a_rKey, bool a_bIsCreateEnable = true);

	//! ��������Ʈ �ؽ�ó�� ��ȯ�Ѵ�
	LPDIRECT3DTEXTURE9 getSpriteTextureForKey(const std::string& a_rKey, bool a_bIsCreateEnable = true);

	//! ť�� �ؽ�ó�� ��ȯ�Ѵ�
	LPDIRECT3DCUBETEXTURE9 getCubeTextureForKey(const std::string& a_rKey, bool a_bIsCreateEnable = true);

	//! ���̺� ���带 ��ȯ�Ѵ�
	STWaveSound getWaveSoundForKey(const std::string& a_rKey, bool a_bIsCreateEnable = true);

public:			// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CResourceManager);

	//! �޽ø� �߰��Ѵ�
	void addMeshForKey(const std::string& a_rKey, LPD3DXMESH a_pMesh);

	//! ���� �޽ø� �߰��Ѵ�
	void addStaticMeshForKey(const std::string& a_rKey, const STStaticMesh& a_rstStaticMesh);

	//! ��Ų�� �޽ø� �߰��Ѵ�
	void addSkinnedMeshForKey(const std::string& a_rKey, const STSkinnedMesh& a_rstSkinnedMesh);

	//! ����Ʈ�� �߰��Ѵ�
	void addEffectForKey(const std::string& a_rKey, LPD3DXEFFECT a_pEffect);

	//! �ؽ�ó�� �߰��Ѵ�
	void addTextureForKey(const std::string& a_rKey, LPDIRECT3DTEXTURE9 a_pTexture);

	//! ��������Ʈ �ؽ�ó�� �߰��Ѵ�
	void addSpriteTextureForKey(const std::string& a_rKey, LPDIRECT3DTEXTURE9 a_pTexture);

	//! ť�� �ؽ�ó�� �߰��Ѵ�
	void addCubeTextureForKey(const std::string& a_rKey, LPDIRECT3DCUBETEXTURE9 a_pCubeTexture);

	//! ���̺� ���带 �߰��Ѵ�
	void addWaveSoundForKey(const std::string& a_rKey, const STWaveSound& a_rstWaveSound);

	//! �޽ø� �����Ѵ�
	void removeMeshForKey(const std::string& a_rKey);

	//! ���� �޽ø� �����Ѵ�
	void removeStaticMeshForKey(const std::string& a_rKey);

	//! ��Ų�� �޽ø� �����Ѵ�
	void removeSkinnedMeshForKey(const std::string& a_rKey);

	//! ����Ʈ�� �����Ѵ�
	void removeEffectForKey(const std::string& a_rKey);

	//! �ؽ�ó�� �����Ѵ�
	void removeTextureForKey(const std::string& a_rKey);

	//! ť�� �ؽ�ó�� �����Ѵ�
	void removeCubeTextureForKey(const std::string& a_rKey);

	//! ���̺� ���带 �����Ѵ�
	void removeWaveSoundForKey(const std::string& a_rKey);

private:			// private �Լ�

	//! ���� �޽ø� �����Ѵ�
	STStaticMesh createStaticMeshFromFile(const std::string& a_rFilepath);

	//! ����Ʈ�� �����Ѵ�
	LPD3DXEFFECT createEffectFromFile(const std::string& a_rFilepath);

	//! �ؽ�ó�� �����Ѵ�
	LPDIRECT3DTEXTURE9 createTextureFromFile(const std::string& a_rFilepath);

	//! ��������Ʈ �ؽ�ó�� �����Ѵ�
	LPDIRECT3DTEXTURE9 createSpriteTextureFromFile(const std::string& a_rFilepath);

	//! ť�� �ؽ�ó�� �����Ѵ�
	LPDIRECT3DCUBETEXTURE9 createCubeTextureFromFile(const std::string& a_rFilepath);

	//! ���̺� ���带 �����Ѵ�
	STWaveSound createWaveSoundFromFile(const std::string& a_rFilepath);

private:			// �Ҹ���

	//! �Ҹ���
	virtual ~CResourceManager(void);

private:			// private ����

	std::unordered_map<std::string, STWaveSound> m_oWaveSoundList;
	std::unordered_map<std::string, STStaticMesh> m_oStaticMeshList;
	std::unordered_map<std::string, STSkinnedMesh> m_oSkinnedMeshList;

	std::unordered_map<std::string, LPD3DXMESH> m_oMeshList;
	std::unordered_map<std::string, LPD3DXEFFECT> m_oEffectList;
	std::unordered_map<std::string, LPDIRECT3DTEXTURE9> m_oTextureList;
	std::unordered_map<std::string, LPDIRECT3DCUBETEXTURE9> m_oCubeTextureList;
};
