#include "CLabel.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CWindowManager.h"

CLabel::CLabel(const std::string& a_rString, int a_nFontSize)
	:
	m_nFontSize(a_nFontSize),
	m_oString(a_rString)
{
	// Do Nothing
}

CLabel::~CLabel(void)
{
	SAFE_RELEASE(m_pFont);
}

void CLabel::init(void)
{
	CUIObject::init();

	D3DXFONT_DESC stFontDesc;
	ZeroMemory(&stFontDesc, sizeof(stFontDesc));

	stFontDesc.Height = m_nFontSize;
	stFontDesc.Weight = 500;

	D3DXCreateFontIndirect(GET_DEVICE(), &stFontDesc, &m_pFont);
}

SIZE CLabel::getSize(void)
{
	RECT stRect = { 0 };
	m_pFont->DrawTextA(NULL, m_oString.c_str(), -1, &stRect, DT_TOP | DT_LEFT | DT_CALCRECT, m_stColor);

	SIZE stSize = {
		stRect.right - stRect.left,
		stRect.bottom - stRect.top
	};

	return stSize;
}

void CLabel::setString(const std::string& a_rString)
{
	m_oString = a_rString;
}

void CLabel::doDrawUI(void)
{
	CUIObject::doDrawUI();

	RECT stRect = {
		m_stPosition.x,
		m_stPosition.y
	};

	m_pFont->DrawTextA(NULL, m_oString.c_str(), -1, &stRect, DT_TOP | DT_LEFT | DT_CALCRECT, m_stColor);
	m_pFont->DrawTextA(NULL, m_oString.c_str(), -1, &stRect, DT_TOP | DT_LEFT, m_stColor);
}
