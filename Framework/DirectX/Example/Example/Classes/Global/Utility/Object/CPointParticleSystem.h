#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"
#include "../Particle/CParticleSystem.h"

//! ����Ʈ ��ƼŬ �ý���
class CPointParticleSystem : public CParticleSystem
{
public:

	//! ����
	struct STVertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE
		};

		D3DXVECTOR3 m_stPosition;
		float m_fSize;
		D3DCOLOR m_nColor;
	};

public:			// public �Լ�

	//! ��ü�� �׸� ���
	virtual void preDrawObject(void) override;

	//! ��ü�� �׸���
	virtual void doDrawObject(void) override;

	//! ��ü�� �׷��� ���
	virtual void postDrawObject(void) override;

public:			// ������

	//! ������
	CPointParticleSystem(const STParameters& a_rstParameters);

protected:			// protected �Լ�

	//! ���� ���۸� �����Ѵ�
	virtual LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void) override;
};
