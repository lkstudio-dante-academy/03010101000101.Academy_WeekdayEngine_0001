#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"
#include "CParticleEmitter.h"

//! ��ƼŬ �ý���
class CParticleSystem : public CRenderObject
{
public:

	//! �Ű�����
	struct STParameters
	{
		std::string m_oTextureFilepath;
		CParticleEmitter::STParameters m_stEmitterParameters;
	};

public:			// setter

	//! ��ƼŬ Ÿ���� �����Ѵ�
	void setParticleType(const EParticleType a_eParticleType);

	//! ��� ������ �����Ѵ�
	virtual void setBoundingBox(const STBoundingBox& a_rstBoundingBox) override;

public:			// public �Լ�

	//! �ʱ�ȭ
	virtual void init(void) override;

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

	//! ��ü�� �׸� ���
	virtual void preDrawObject(void) override;

	//! ��ü�� �׷��� ���
	virtual void postDrawObject(void) override;

	//! ��ƼŬ ������ �����Ѵ�
	void startParticleEmit(float a_fActiveTime);

	//! ��ƼŬ ������ �����Ѵ�
	void stopParticleEmit(void);

public:			// ������

	//! ������
	CParticleSystem(const STParameters& a_rstParameters);

	//! �Ҹ���
	virtual ~CParticleSystem(void);

protected:			// protected �Լ�

	//! ���� ���۸� �����Ѵ�
	virtual LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void) = 0;

protected:			// protected ����

	bool m_bIsEmitEnable = false;
	float m_fLeftActiveTime = 0.0f;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer = nullptr;
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;

	STParameters m_stParameters;
	CParticleEmitter* m_pParticleEmitter = nullptr;
};
