#include "CButton.h"
#include "CSprite.h"
#include "../../Function/GlobalFunction.h"
#include "../Manager/CInputManager.h"

CButton::CButton(const std::string& a_rFilepath, const std::function<void(CButton*)>& a_rCallback)
	:
	m_oSpriteFilepath(a_rFilepath),
	m_oCallback(a_rCallback)
{
	// Do Nothing
}

void CButton::init(void)
{
	CUIObject::init();

	m_pNormalSprite = CreateObject<CSprite>(m_oSpriteFilepath);
	this->addChildObject(m_pNormalSprite);

	m_pSelectSprite = CreateObject<CSprite>(m_oSpriteFilepath);
	m_pSelectSprite->setColor(D3DXCOLOR(m_stColor.r / 2.0f, m_stColor.g / 2.0f, m_stColor.b / 2.0f, 1.0f));
	this->addChildObject(m_pSelectSprite);
}

SIZE CButton::getSize(void)
{
	return m_pNormalSprite->getSize();
}

void CButton::setColor(const D3DXCOLOR& a_rstColor)
{
	CUIObject::setColor(a_rstColor);

	m_pNormalSprite->setColor(a_rstColor);
	m_pSelectSprite->setColor(D3DXCOLOR(a_rstColor.r / 2.0f, a_rstColor.g / 2.0f, a_rstColor.b / 2.0f, a_rstColor.a));
}

void CButton::update(void)
{
	CUIObject::update();

	m_pNormalSprite->setVisible(!m_bIsSelected);
	m_pSelectSprite->setVisible(m_bIsSelected);

	RECT stRect = {
		m_stPosition.x - (this->getSize().cx / 2),
		m_stPosition.y - (this->getSize().cy / 2),
		m_stPosition.x + (this->getSize().cx / 2),
		m_stPosition.y + (this->getSize().cy / 2)
	};

	if(IS_MOUSE_BUTTON_PRESSED(EMouseButton::LEFT))
	{
		m_bIsSelected = IsContainPoint(stRect, GET_MOUSE_POSITION());
	}
	else if(IS_MOUSE_BUTTON_RELEASED(EMouseButton::LEFT))
	{
		if(m_bIsSelected && IsContainPoint(stRect, GET_MOUSE_POSITION()))
		{
			m_oCallback(this);
		}

		m_bIsSelected = false;
	}
}
