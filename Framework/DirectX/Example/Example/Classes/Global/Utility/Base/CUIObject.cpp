#include "CUIObject.h"
#include "../Manager/CUIManager.h"

CUIObject::CUIObject(void)
	:
	m_bIsVisible(true),
	m_stColor(1.0f, 1.0f, 1.0f, 1.0f)
{
	// Do Nothing
}

CUIObject::~CUIObject(void)
{
	GET_UI_MANAGER()->removeUIObject(this);
}

void CUIObject::draw(void)
{
	// Do Nothing
}

void CUIObject::drawUI(void)
{
	if(m_bIsVisible)
	{
		this->doDrawUI();

		// �ڽ� ��ü�� �׸���
		for(auto pChildObject : m_oChildObjectList)
		{
			auto pUIObject = dynamic_cast<CUIObject*>(pChildObject);

			if(pUIObject != nullptr)
			{
				pUIObject->drawUI();
			}
		}
	}
}

LRESULT CUIObject::handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam)
{
	return 0;
}

SIZE CUIObject::getSize(void)
{
	SIZE stSize;
	ZeroMemory(&stSize, sizeof(stSize));

	return stSize;
}

void CUIObject::setVisible(bool a_bIsVisible)
{
	m_bIsVisible = a_bIsVisible;
}

void CUIObject::setColor(const D3DXCOLOR& a_rstColor)
{
	m_stColor = a_rstColor;
}

void CUIObject::doDrawUI(void)
{
	// Do Nothing
}
