#include "CPointParticleSystem.h"
#include "../../Function/GlobalFunction.h"
#include "../Manager/CDeviceManager.h"

CPointParticleSystem::CPointParticleSystem(const STParameters& a_rstParameters)
	:
	CParticleSystem(a_rstParameters)
{
	// Do Nothing
}

void CPointParticleSystem::preDrawObject(void)
{
	CParticleSystem::preDrawObject();

	GET_DEVICE()->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	GET_DEVICE()->SetRenderState(D3DRS_POINTSPRITEENABLE, true);

	GET_DEVICE()->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDWORD(0.0f));
	GET_DEVICE()->SetRenderState(D3DRS_POINTSIZE_MAX, FloatToDWORD(1000.0f));

	GET_DEVICE()->SetRenderState(D3DRS_POINTSCALE_A, FloatToDWORD(0.0f));
	GET_DEVICE()->SetRenderState(D3DRS_POINTSCALE_B, FloatToDWORD(0.0f));
	GET_DEVICE()->SetRenderState(D3DRS_POINTSCALE_C, FloatToDWORD(1.0f));
}

void CPointParticleSystem::doDrawObject(void)
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
			pstVertices[i].m_stPosition = oParticleList[i].m_stPosition;
			pstVertices[i].m_fSize = oParticleList[i].m_fSize;
			pstVertices[i].m_nColor = oParticleList[i].m_stColor;
		}

		m_pVertexBuffer->Unlock();
	}
	// }

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetFVF(STVertex::FVF);
	GET_DEVICE()->SetTexture(0, m_pTexture);

	GET_DEVICE()->DrawPrimitive(D3DPT_POINTLIST, 0, oParticleList.size());
}

void CPointParticleSystem::postDrawObject(void)
{
	CParticleSystem::postDrawObject();

	GET_DEVICE()->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	GET_DEVICE()->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
}

LPDIRECT3DVERTEXBUFFER9 CPointParticleSystem::createVertexBuffer(void)
{
	return CreateVertexBuffer(sizeof(STVertex) * m_stParameters.m_stEmitterParameters.m_nMaxNumParticles,
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
		STVertex::FVF,
		D3DPOOL_SYSTEMMEM);
}
