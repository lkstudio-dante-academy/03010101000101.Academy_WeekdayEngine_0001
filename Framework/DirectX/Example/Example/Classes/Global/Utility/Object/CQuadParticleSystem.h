#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"
#include "../Particle/CParticleSystem.h"

//! ���� ��ƼŬ �ý���
class CQuadParticleSystem : public CParticleSystem
{
public:

	//! ����
	struct STVertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1
		};

		D3DXVECTOR3 m_stPosition;
		D3DCOLOR m_nColor;
		D3DXVECTOR2 m_stUV;
	};

public:			// public �Լ�

	//! ��ü�� �׸���
	virtual void doDrawObject(void) override;

public:			// ������

	//! ������
	CQuadParticleSystem(const STParameters& a_rstParameters);

protected:			// protected �Լ�

	//! ���� ���۸� �����Ѵ�
	virtual LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void) override;
};
