#include "CTerrain.h"
#include "../../Function/GlobalFunction.h"
#include "../Base/CDirect3DApplication.h"
#include "../Object/CLight.h"
#include "../Object/CCamera.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CResourceManager.h"

CTerrain::CTerrain(const STParameters& a_rstParameters)
	:
	m_stParameters(a_rstParameters)
{
	ZeroMemory(&m_stMapSize, sizeof(m_stMapSize));
	ZeroMemory(&m_stTileSize, sizeof(m_stTileSize));
	ZeroMemory(&m_stTotalSize, sizeof(m_stTotalSize));
}

CTerrain::~CTerrain(void)
{
	SAFE_RELEASE(m_pMesh);
}

void CTerrain::init(void)
{
	CRenderObject::init();
	this->setupTerrainInfo(m_stParameters);

	m_pEffect = GET_EFFECT(m_stParameters.m_oEffectFilepath);
	m_pMesh = this->createTerrainMesh(m_stParameters);
	m_oTextureList = this->createTerrainTextures(m_stParameters, &m_pSplatTexture);
}

float CTerrain::getHeightAtPosition(const D3DXVECTOR3& a_rstPosition)
{
	float fMapPositionX = ((m_stTotalSize.cx / 2.0f) + a_rstPosition.x) / m_stTileSize.cx;
	float fMapPositionZ = ((m_stTotalSize.cy / 2.0f) - a_rstPosition.z) / m_stTileSize.cy;

	int nMapIndexX = (int)fMapPositionX;
	int nMapIndexZ = (int)fMapPositionZ;
	int nBaseIndex = (nMapIndexZ * m_stMapSize.cx) + nMapIndexX;

	float fLTHeight = m_oHeightList[nBaseIndex];
	float fRTHeight = m_oHeightList[nBaseIndex + 1];
	float fLBHeight = m_oHeightList[nBaseIndex + m_stMapSize.cx];
	float fRBHeight = m_oHeightList[nBaseIndex + m_stMapSize.cx + 1];

	float fDeltaX = fMapPositionX - nMapIndexX;
	float fDeltaZ = fMapPositionZ - nMapIndexZ;

	// ���� �ﰢ���� ���� ���
	if(1.0f - fDeltaX > fDeltaZ)
	{
		float fDeltaHeightX = (fRTHeight - fLTHeight) * fDeltaX;
		float fDeltaHeightZ = (fLBHeight - fLTHeight) * fDeltaZ;

		return fLTHeight + fDeltaHeightX + fDeltaHeightZ;
	}

	float fDeltaHeightX = (fLBHeight - fRBHeight) * (1.0f - fDeltaX);
	float fDeltaHeightZ = (fRTHeight - fRBHeight) * (1.0f - fDeltaZ);

	return fRBHeight + fDeltaHeightX + fDeltaHeightZ;
}

D3DXVECTOR3 CTerrain::getIntersectPointByRay(const STRay& a_rstRay)
{
	BOOL bIsHit = FALSE;
	LPD3DXBUFFER pHitBuffer = nullptr;

	D3DXVECTOR3 stIntersectPoint;
	ZeroMemory(&stIntersectPoint, sizeof(stIntersectPoint));

	if(SUCCEEDED(D3DXIntersect(m_pMesh,
		&a_rstRay.m_stOrigin, &a_rstRay.m_stDirection, &bIsHit, NULL, NULL, NULL, NULL, NULL, NULL)))
	{
	}

	return stIntersectPoint;
}

void CTerrain::doDrawObject(void)
{
	CRenderObject::doDrawObject();

	/** VS Output */�� �����Ѵ�
	// {
	auto stWorldMatrix = this->getFinalWorldMatrix();
	auto stViewMatrix = GET_CAMERA()->getViewMatrix();
	auto stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	m_pEffect->SetMatrix("g_stViewMatrix", &stViewMatrix);
	m_pEffect->SetMatrix("g_stProjectionMatrix", &stProjectionMatrix);
	// }

	// �ؽ�ó ������ �����Ѵ�
	// {
	for(int i = 0; i < m_oTextureList.size(); ++i)
	{
		char szTextureVariable[MAX_PATH] = "";
		sprintf(szTextureVariable, "g_pTexture%c", 'A' + i);

		m_pEffect->SetTexture(szTextureVariable, m_oTextureList[i]);
	}

	m_pEffect->SetTexture("g_pSplatTexture", m_pSplatTexture);
	// }

	D3DXVECTOR4 stViewPosition(GET_CAMERA()->getPosition(), 1.0f);
	D3DXVECTOR4 stLightDirection(GET_LIGHT()->getForwardDirection(), 0.0f);

	m_pEffect->SetVector("g_stViewPosition", &stViewPosition);
	m_pEffect->SetVector("g_stLightDirection", &stLightDirection);

	RunEffectLoop(m_pEffect, "MyTechnique", [=](int a_nPassNumber) -> void
	{
		m_pMesh->DrawSubset(0);
	});
}

void CTerrain::smoothTerrainMesh(int a_nSmoothLevel)
{
	for(int i = 0; i < a_nSmoothLevel; ++i)
	{
		std::vector<float> oSmoothHeightList;
		std::vector<float> oAdjacencyHeightList;

		for(int j = 0; j < m_stMapSize.cy; ++j)
		{
			for(int k = 0; k < m_stMapSize.cx; ++k)
			{
				int nIndex = (j * m_stMapSize.cx) + k;
				oAdjacencyHeightList.clear();

				/** VS Input */
				if(k - 1 >= 0)
				{
					float fHeight = m_oHeightList[nIndex - 1];
					oAdjacencyHeightList.push_back(fHeight);
				}

				// ������ ����
				if(k + 1 < m_stMapSize.cx)
				{
					float fHeight = m_oHeightList[nIndex + 1];
					oAdjacencyHeightList.push_back(fHeight);
				}

				/** VS Input */
				if(j - 1 >= 0)
				{
					float fHeight = m_oHeightList[nIndex - m_stMapSize.cx];
					oAdjacencyHeightList.push_back(fHeight);

					/** VS Input */
					if(k - 1 >= 0)
					{
						float fHeight = m_oHeightList[nIndex - m_stMapSize.cx - 1];
						oAdjacencyHeightList.push_back(fHeight);
					}

					// ������ ����
					if(k + 1 < m_stMapSize.cx)
					{
						float fHeight = m_oHeightList[nIndex - m_stMapSize.cx + 1];
						oAdjacencyHeightList.push_back(fHeight);
					}
				}

				// �Ʒ��� ����
				if(j + 1 < m_stMapSize.cy)
				{
					float fHeight = m_oHeightList[nIndex + m_stMapSize.cy];
					oAdjacencyHeightList.push_back(fHeight);

					/** VS Input */
					if(k - 1 >= 0)
					{
						float fHeight = m_oHeightList[nIndex + m_stMapSize.cx - 1];
						oAdjacencyHeightList.push_back(fHeight);
					}

					// ������ ����
					if(k + 1 < m_stMapSize.cx)
					{
						float fHeight = m_oHeightList[nIndex + m_stMapSize.cx + 1];
						oAdjacencyHeightList.push_back(fHeight);
					}
				}

				float fHeight = m_oHeightList[nIndex];
				float fTotalHeight = std::accumulate(oAdjacencyHeightList.begin(), oAdjacencyHeightList.end(), 0.0f);

				oSmoothHeightList.push_back((fHeight + (fTotalHeight / oAdjacencyHeightList.size())) * 0.5f);
			}
		}

		m_oHeightList.assign(oSmoothHeightList.begin(), oSmoothHeightList.end());
	}
}

void CTerrain::setupTerrainInfo(const STParameters& a_rstParameters)
{
	// ũ�� ������ �����Ѵ�
	// {
	m_stMapSize.cx = a_rstParameters.m_stMapSize.cx;
	m_stMapSize.cy = a_rstParameters.m_stMapSize.cy;

	m_stTileSize.cx = a_rstParameters.m_stTileSize.cx;
	m_stTileSize.cy = a_rstParameters.m_stTileSize.cy;

	m_stTotalSize.cx = m_stMapSize.cx * m_stTileSize.cx;
	m_stTotalSize.cy = m_stMapSize.cy * m_stTileSize.cy;

	m_fHeightScale = a_rstParameters.m_fHeightScale;
	// }

	/** VS Input */�� �����Ѵ�
	// {
	if(a_rstParameters.m_oHeightFilepath.rfind(".raw") != std::string::npos)
	{
		auto oReadStreamPtr = std::shared_ptr<FILE>(fopen(a_rstParameters.m_oHeightFilepath.c_str(), "rb"), [=](FILE* a_pstFileStream) -> void
		{
			SAFE_CLOSE(a_pstFileStream);
		});

		for(int i = 0; i < m_stMapSize.cy; ++i)
		{
			for(int j = 0; j < m_stMapSize.cx; ++j)
			{
				USHORT nHeight = 0;
				fread(&nHeight, sizeof(nHeight), 1, oReadStreamPtr.get());

				m_oHeightList.push_back(nHeight * m_fHeightScale);
			}
		}
	}
	else
	{
		D3DLOCKED_RECT stLockedRect;
		auto pHeightTexture = GET_TEXTURE(a_rstParameters.m_oHeightFilepath.c_str());

		if(SUCCEEDED(pHeightTexture->LockRect(0, &stLockedRect, NULL, 0)))
		{
			D3DCOLOR* pnBytes = (D3DCOLOR*)stLockedRect.pBits;

			for(int i = 0; i < m_stMapSize.cy; ++i)
			{
				for(int j = 0; j < m_stMapSize.cx; ++j)
				{
					int nIndex = (i * m_stMapSize.cx) + j;
					D3DCOLOR nColor = pnBytes[nIndex];

					int nRedColor = (nColor >> 16) & 0xff;
					int nGreenColor = (nColor >> 8) & 0xff;
					int nBlueColor = (nColor >> 0) & 0xff;

					float fHeight = nRedColor + nGreenColor + nBlueColor;
					m_oHeightList.push_back(fHeight * m_fHeightScale);
				}
			}

			pHeightTexture->UnlockRect(0);
		}
	}
	// }

	// ������ �ε巴���Ѵ�
	this->smoothTerrainMesh(a_rstParameters.m_nSmoothLevel);
}

LPD3DXMESH CTerrain::createTerrainMesh(const STParameters& a_rstParameters)
{
	D3DVERTEXELEMENT9 astElements[] = {
		0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0,
		0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0,
		0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0,
		0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0,
		0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0,
		D3DDECL_END()
	};

	// �޽ø� �����Ѵ�
	D3DXCreateMesh((m_stMapSize.cx * m_stMapSize.cy) * 2,
		m_stMapSize.cx * m_stMapSize.cy,
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		astElements,
		GET_DEVICE(),
		&m_pMesh);

	/** VS Input */�� �����Ѵ�
	// {
	STVertex* pstVertices = nullptr;

	if(SUCCEEDED(m_pMesh->LockVertexBuffer(0, (void**)&pstVertices)))
	{
		D3DXVECTOR3 stBasePosition = {
			(m_stTotalSize.cx / -2.0f) + (m_stTileSize.cx / 2.0f),
			0.0f,
			(m_stTotalSize.cy / 2.0f) - (m_stTileSize.cy / 2.0f)
		};

		for(int i = 0; i < m_stMapSize.cy; ++i)
		{
			for(int j = 0; j < m_stMapSize.cx; ++j)
			{
				int nIndex = (i * m_stMapSize.cx) + j;

				pstVertices[nIndex].m_stPosition = stBasePosition + D3DXVECTOR3(j * m_stTileSize.cx,
					m_oHeightList[nIndex],
					i * -m_stTileSize.cy);

				pstVertices[nIndex].m_stUV = D3DXVECTOR2(j / (float)(m_stMapSize.cx - 1), i / (float)(m_stMapSize.cy - 1));
			}
		}

		m_pMesh->UnlockVertexBuffer();
	}
	// }

	// �ε��� ������ �����Ѵ�
	// {
	DWORD* pnIndices = nullptr;

	if(SUCCEEDED(m_pMesh->LockIndexBuffer(0, (void**)&pnIndices)))
	{
		for(int i = 0; i < m_stMapSize.cy - 1; ++i)
		{
			for(int j = 0; j < m_stMapSize.cx - 1; ++j)
			{
				int nVertexIndex = (i * m_stMapSize.cx) + j;
				int nIndex = nVertexIndex * 6;

				// ���� �ﰢ��
				pnIndices[nIndex + 0] = nVertexIndex;
				pnIndices[nIndex + 1] = nVertexIndex + 1;
				pnIndices[nIndex + 2] = nVertexIndex + m_stMapSize.cx;

				// ������ �ﰢ��
				pnIndices[nIndex + 3] = nVertexIndex + m_stMapSize.cx;
				pnIndices[nIndex + 4] = nVertexIndex + 1;
				pnIndices[nIndex + 5] = nVertexIndex + m_stMapSize.cx + 1;
			}
		}

		m_pMesh->UnlockIndexBuffer();
	}
	// }

	/** VS Input */�� ����Ѵ�
	D3DXComputeNormals(m_pMesh, NULL);

	// ����, ������ ������ ����Ѵ�
	D3DXComputeTangent(m_pMesh, 0, 0, 0, TRUE, NULL);

	return m_pMesh;
}

std::vector<LPDIRECT3DTEXTURE9> CTerrain::createTerrainTextures(const STParameters& a_rstParameters, LPDIRECT3DTEXTURE9* a_pOutSplatTexture)
{
	std::vector<LPDIRECT3DTEXTURE9> oTextureList;
	*a_pOutSplatTexture = GET_TEXTURE(a_rstParameters.m_oSplatTextureFilepath);

	for(const std::string& rTextureFilepath : a_rstParameters.m_oTextureFilepathList)
	{
		auto pTexture = GET_TEXTURE(rTextureFilepath);
		oTextureList.push_back(pTexture);
	}

	return oTextureList;
}
