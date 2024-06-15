#include "Example_27.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CSkybox.h"
#include "../Global/Utility/Manager/CDeviceManager.h"

Example_27::Example_27(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

void Example_27::initApplication(void)
{
	CDirect3DApplication::initApplication();

	auto pSkybox = this->createSkybox();
	this->setSkybox(pSkybox);
}

void Example_27::update(void)
{
	CDirect3DApplication::update();
}

void Example_27::draw(void)
{
	CDirect3DApplication::draw();
}

CSkybox* Example_27::createSkybox(void)
{
	CSkybox::STParameters stParameters = {
		100,
		100,
		500.0f,
		"Resources/Effects/Example_27.fx",
		"Resources/Textures/CubeMap.dds"
	};

	return CreateObject<CSkybox>(stParameters);
}
