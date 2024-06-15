#include "Example_33.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CQuadParticleSystem.h"
#include "../Global/Utility/Manager/CInputManager.h"

Example_33::Example_33(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_33::~Example_33(void)
{
	SAFE_DELETE(m_pQuadParticleSystem);
}

void Example_33::initApplication(void)
{
	CDirect3DApplication::initApplication();
	m_pQuadParticleSystem = this->createQuadParticleSystem();
}

void Example_33::update(void)
{
	CDirect3DApplication::update();
	m_pQuadParticleSystem->update();

	if(IS_KEY_DOWN(DIK_SPACE))
	{
		m_pQuadParticleSystem->startParticleEmit(0.0f);
	}
}

void Example_33::draw(void)
{
	CDirect3DApplication::draw();
	m_pQuadParticleSystem->draw();
}

CQuadParticleSystem* Example_33::createQuadParticleSystem(void)
{
	CQuadParticleSystem::STParameters stParameters = {
		"Resources/Textures/HelloWorld.png",
		1024,
		100,
		EParticleType::EXPLOSION
	};

	return CreateObject<CQuadParticleSystem>(stParameters);
}
