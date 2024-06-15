#include "Example_32.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CPointParticleSystem.h"
#include "../Global/Utility/Manager/CInputManager.h"

Example_32::Example_32(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_32::~Example_32(void)
{
	SAFE_DELETE(m_pPointParticleSystem);
}

void Example_32::initApplication(void)
{
	CDirect3DApplication::initApplication();
	m_pPointParticleSystem = this->createPointParticleSystem();
}

void Example_32::update(void)
{
	CDirect3DApplication::update();
	m_pPointParticleSystem->update();

	if(IS_KEY_DOWN(DIK_SPACE))
	{
		m_pPointParticleSystem->startParticleEmit(0.0f);
	}
}

void Example_32::draw(void)
{
	CDirect3DApplication::draw();
	m_pPointParticleSystem->draw();
}

CPointParticleSystem* Example_32::createPointParticleSystem(void)
{
	CPointParticleSystem::STParameters stParameters = {
		"Resources/Textures/HelloWorld.png",
		1024,
		100,
		EParticleType::EXPLOSION
	};

	return CreateObject<CPointParticleSystem>(stParameters);
}
