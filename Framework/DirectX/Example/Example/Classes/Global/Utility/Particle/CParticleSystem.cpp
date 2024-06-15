#include "CParticleSystem.h"
#include "../../Function/GlobalFunction.h"
#include "../Manager/CTimeManager.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CResourceManager.h"

CParticleSystem::CParticleSystem(const STParameters& a_rstParameters)
	:
	m_stParameters(a_rstParameters)
{
	// Do Nothing
}

CParticleSystem::~CParticleSystem(void)
{
	SAFE_DELETE(m_pParticleEmitter);
	SAFE_RELEASE(m_pVertexBuffer);
}

void CParticleSystem::init(void)
{
	CRenderObject::init();

	m_pVertexBuffer = this->createVertexBuffer();
	m_pTexture = GET_TEXTURE(m_stParameters.m_oTextureFilepath);

	m_pParticleEmitter = CreateInstance<CParticleEmitter>(m_stParameters.m_stEmitterParameters);
}

void CParticleSystem::setParticleType(const EParticleType a_eParticleType)
{
	m_pParticleEmitter->setParticleType(a_eParticleType);
}

void CParticleSystem::setBoundingBox(const STBoundingBox& a_rstBoundingBox)
{
	CRenderObject::setBoundingBox(a_rstBoundingBox);
	m_pParticleEmitter->setBoundingBox(a_rstBoundingBox);
}

void CParticleSystem::update(void)
{
	CRenderObject::update();
	m_pParticleEmitter->update();

	if(m_bIsEmitEnable)
	{
		m_fLeftActiveTime -= GET_DELTA_TIME();

		if(m_fLeftActiveTime <= 0.0f)
		{
			this->stopParticleEmit();
		}
	}
}

void CParticleSystem::preDrawObject(void)
{
	CRenderObject::preDrawObject();

	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);
	GET_DEVICE()->SetRenderState(D3DRS_ZWRITEENABLE, false);

	GET_DEVICE()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	GET_DEVICE()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GET_DEVICE()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

void CParticleSystem::postDrawObject(void)
{
	CRenderObject::postDrawObject();
	GET_DEVICE()->SetTexture(0, NULL);

	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
	GET_DEVICE()->SetRenderState(D3DRS_ZWRITEENABLE, true);
	GET_DEVICE()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void CParticleSystem::startParticleEmit(float a_fActiveTime)
{
	m_bIsEmitEnable = true;
	m_fLeftActiveTime = a_fActiveTime;

	m_pParticleEmitter->setEmitEnable(true);
}

void CParticleSystem::stopParticleEmit(void)
{
	m_bIsEmitEnable = false;
	m_fLeftActiveTime = 0.0f;

	m_pParticleEmitter->setEmitEnable(false);
}
