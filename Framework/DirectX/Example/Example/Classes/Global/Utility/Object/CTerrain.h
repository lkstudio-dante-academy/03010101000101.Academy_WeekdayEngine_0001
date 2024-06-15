#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

//! ����
class CTerrain : public CRenderObject
{
public:

	enum
	{
		MAX_NUM_TEXTURES = 4
	};

	//! ����
	struct STVertex
	{
		D3DXVECTOR3 m_stPosition;
		D3DXVECTOR3 m_stNormal;
		D3DXVECTOR3 m_stTangent;
		D3DXVECTOR3 m_stBinormal;
		D3DXVECTOR2 m_stUV;
	};

	//! ���
	struct STNode
	{
		D3DXVECTOR2 m_stLTPosition;
		D3DXVECTOR2 m_stRBPosition;

		STNode* m_pstLTChildNode;
		STNode* m_pstRTChildNode;
		STNode* m_pstLBChildNode;
		STNode* m_pstRBChildNode;
	};

	//! �Ű�����
	struct STParameters
	{
		int m_nSmoothLevel;
		float m_fHeightScale;

		std::string m_oEffectFilepath;
		std::string m_oHeightFilepath;
		std::string m_oSplatTextureFilepath;

		SIZE m_stMapSize;
		SIZE m_stTileSize;
		std::array<std::string, MAX_NUM_TEXTURES> m_oTextureFilepathList;
	};

public:			// getter

	//! ���̸� ��ȯ�Ѵ�
	float getHeightAtPosition(const D3DXVECTOR3& a_rstPosition);

	//! ���� ��ġ�� ��ȯ�Ѵ�
	D3DXVECTOR3 getIntersectPointByRay(const STRay& a_rstRay);

public:			// public �Լ�

	//! �ʱ�ȭ
	virtual void init(void) override;

	//! ��ü�� �׸���
	virtual void doDrawObject(void) override;

public:			// ������, �Ҹ���

	//! ������
	CTerrain(const STParameters& a_rstParameters);

	//! �Ҹ���
	virtual ~CTerrain(void);

private:			// private �Լ�

	//! ������ �ε巴�� �����
	void smoothTerrainMesh(int a_nSmoothLevel);

	//! ���� ������ �����Ѵ�
	void setupTerrainInfo(const STParameters& a_rstParameters);

	//! ���� �޽ø� �����Ѵ�
	LPD3DXMESH createTerrainMesh(const STParameters& a_rstParameters);

	//! ���� �ؽ�ó�� �����Ѵ�
	std::vector<LPDIRECT3DTEXTURE9> createTerrainTextures(const STParameters& a_rstParameters, LPDIRECT3DTEXTURE9* a_pOutSplatTexture);

private:			// private ����

	SIZE m_stMapSize;
	SIZE m_stTileSize;
	SIZE m_stTotalSize;

	LPD3DXMESH m_pMesh = nullptr;
	LPD3DXEFFECT m_pEffect = nullptr;
	LPDIRECT3DTEXTURE9 m_pSplatTexture = nullptr;

	float m_fHeightScale = 0.0f;
	STNode* m_pstTerrainNode = nullptr;

	STParameters m_stParameters;
	std::vector<float> m_oHeightList;
	std::vector<LPDIRECT3DTEXTURE9> m_oTextureList;
};
