#include "CQuadParticleSystem.h"
#include "../../Function/GlobalFunction.h"
#include "../Manager/CDeviceManager.h"

CQuadParticleSystem::CQuadParticleSystem(const STParameters& a_rstParameters)
	:
	CParticleSystem(a_rstParameters)
{
	// Do Nothing
}

void CQuadParticleSystem::doDrawObject(void)
{
	CParticleSystem::doDrawObject();

	// ����� �����Ѵ�
	// {
	auto stWorldMatrix = this->getFinalWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	// }

	/** VS Input */�� �����Ѵ�
	// {
	STVertex* pstVertices = nullptr;
	auto oParticleList = m_pParticleEmitter->getParticleList();

	if(SUCCEEDED(m_pVertexBuffer->Lock(0, 0, (void**)&pstVertices, 0)))
	{
		for(int i = 0; i < oParticleList.size(); ++i)
		{
			D3DXVECTOR3 astVertices[6] = {
				D3DXVECTOR3(-0.5f, 0.5f, 0.0f),
				D3DXVECTOR3(0.5f, 0.5f, 0.0f),
				D3DXVECTOR3(-0.5f, -0.5f, 0.0f),
				D3DXVECTOR3(-0.5f, -0.5f, 0.0f),
				D3DXVECTOR3(0.5f, 0.5f, 0.0f),
				D3DXVECTOR3(0.5f, -0.5f, 0.0f),
			};

			// ����� �����Ѵ�
			// {
			D3DXMATRIXA16 stScale;

			D3DXMatrixScaling(&stScale,
				oParticleList[i].m_fSize,
				oParticleList[i].m_fSize,
				oParticleList[i].m_fSize);

			D3DXMATRIXA16 stRotation;

			D3DXMatrixRotationYawPitchRoll(&stRotation,
				D3DXToRadian(oParticleList[i].m_stRotation.y),
				D3DXToRadian(oParticleList[i].m_stRotation.x),
				D3DXToRadian(oParticleList[i].m_stRotation.z));

			D3DXMATRIXA16 stTranslation;

			D3DXMatrixTranslation(&stTranslation,
				oParticleList[i].m_stPosition.x,
				oParticleList[i].m_stPosition.y,
				oParticleList[i].m_stPosition.z);

			auto stLocalMatrix = stScale * stRotation * stTranslation;

			D3DXVec3TransformCoordArray(astVertices,
				sizeof(D3DXVECTOR3),
				astVertices,
				sizeof(D3DXVECTOR3),
				&stLocalMatrix,
				6);
			// }

			int nIndex = i * 6;

			pstVertices[nIndex + 0].m_stPosition = astVertices[0];
			pstVertices[nIndex + 0].m_stUV = D3DXVECTOR2(0.0f, 0.0f);
			pstVertices[nIndex + 0].m_nColor = oParticleList[i].m_stColor;

			pstVertices[nIndex + 1].m_stPosition = astVertices[1];
			pstVertices[nIndex + 1].m_stUV = D3DXVECTOR2(1.0f, 0.0f);
			pstVertices[nIndex + 1].m_nColor = oParticleList[i].m_stColor;

			pstVertices[nIndex + 2].m_stPosition = astVertices[2];
			pstVertices[nIndex + 2].m_stUV = D3DXVECTOR2(0.0f, 1.0f);
			pstVertices[nIndex + 2].m_nColor = oParticleList[i].m_stColor;

			pstVertices[nIndex + 3].m_stPosition = astVertices[3];
			pstVertices[nIndex + 3].m_stUV = D3DXVECTOR2(0.0f, 1.0f);
			pstVertices[nIndex + 3].m_nColor = oParticleList[i].m_stColor;

			pstVertices[nIndex + 4].m_stPosition = astVertices[4];
			pstVertices[nIndex + 4].m_stUV = D3DXVECTOR2(1.0f, 0.0f);
			pstVertices[nIndex + 4].m_nColor = oParticleList[i].m_stColor;

			pstVertices[nIndex + 5].m_stPosition = astVertices[5];
			pstVertices[nIndex + 5].m_stUV = D3DXVECTOR2(1.0f, 1.0f);
			pstVertices[nIndex + 5].m_nColor = oParticleList[i].m_stColor;
		}

		m_pVertexBuffer->Unlock();
	}
	// }

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetFVF(STVertex::FVF);
	GET_DEVICE()->SetTexture(0, m_pTexture);

	GET_DEVICE()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, oParticleList.size() * 2);
}

LPDIRECT3DVERTEXBUFFER9 CQuadParticleSystem::createVertexBuffer(void)
{
	return CreateVertexBuffer(sizeof(STVertex) * m_stParameters.m_stEmitterParameters.m_nMaxNumParticles * 6,
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
		STVertex::FVF,
		D3DPOOL_SYSTEMMEM);
}
