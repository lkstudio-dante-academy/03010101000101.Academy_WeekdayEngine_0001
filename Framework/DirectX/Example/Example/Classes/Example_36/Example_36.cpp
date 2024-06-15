#include "Example_36.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CSoundManager.h"

Example_36::Example_36(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

void Example_36::initApplication(void)
{
	CDirect3DApplication::initApplication();
}

void Example_36::update(void)
{
	CDirect3DApplication::update();

	if(IS_KEY_PRESSED(DIK_1))
	{
		PLAY_EFFECT_SOUND("Resources/Sounds/Effect1.wav");
	}
	else if(IS_KEY_PRESSED(DIK_2))
	{
		PLAY_EFFECT_SOUND("Resources/Sounds/Effect2.wav");
	}
	else if(IS_KEY_PRESSED(DIK_3))
	{
		PLAY_BACKGROUND_SOUND("Resources/Sounds/Background.wav");
	}
}

void Example_36::draw(void)
{
	CDirect3DApplication::draw();
}
