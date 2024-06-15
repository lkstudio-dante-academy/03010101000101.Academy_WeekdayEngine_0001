#include "Example_17.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/UI/CLabel.h"
#include "../Global/Utility/UI/CButton.h"
#include "../Global/Utility/UI/CSprite.h"
#include "../Global/Utility/Manager/CWindowManager.h"
#include "../Global/Utility/Manager/CUIManager.h"

Example_17::Example_17(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_17::~Example_17(void)
{
	SAFE_DELETE(m_pLabel);
	SAFE_DELETE(m_pButton);
	SAFE_DELETE(m_pSprite);
}

void Example_17::initApplication(void)
{
	CDirect3DApplication::initApplication();

	/** VS Input */�Ѵ�
	// {
	m_pLabel = CREATE_LABEL("Hello, World!", 45);

	m_pLabel->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx - m_pLabel->getSize().cx) / 2.0f,
		(GET_WINDOW_SIZE().cy - m_pLabel->getSize().cy) / 2.0f,
		0.0f));
	// }

	// ��ư�� �����Ѵ�
	// {
	m_pButton = CREATE_BUTTON("Resources/Textures/NormalMap.jpg", std::bind(&Example_17::onClickButton, this, std::placeholders::_1));
	m_pButton->setColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	m_pButton->setPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx / 2.0f,
		GET_WINDOW_SIZE().cy / 2.0f,
		0.1f));
	// }

	// ��������Ʈ�� �����Ѵ�
	// {
	m_pSprite = CREATE_SPRITE("Resources/Textures/HelloWorld.png");

	m_pSprite->setPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx / 2.0f,
		GET_WINDOW_SIZE().cy / 2.0f,
		0.5f));
	// }
}

void Example_17::update(void)
{
	CDirect3DApplication::update();

	m_pLabel->update();
	m_pButton->update();
	m_pSprite->update();
}

void Example_17::drawUI(void)
{
	CDirect3DApplication::drawUI();

	m_pLabel->drawUI();
	m_pButton->drawUI();
	m_pSprite->drawUI();
}

void Example_17::onClickButton(CButton* a_pSender)
{
	printf("��ư�� Ŭ���߽��ϴ�.\n");
}
