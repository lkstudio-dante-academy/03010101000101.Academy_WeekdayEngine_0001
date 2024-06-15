#include "CUIManager.h"
#include "../../Function/GlobalFunction.h"
#include "../UI/CLabel.h"
#include "../UI/CButton.h"
#include "../UI/CSprite.h"

LRESULT CUIManager::handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam)
{
	for(auto pUIObject : m_oUIObjectList)
	{
		pUIObject->handleWindowMessage(a_hWindow, a_nMessage, a_wParam, a_lParam);
	}

	return 0;
}

void CUIManager::addUIObject(CUIObject* a_pUIObject)
{
	auto oIterator = std::find(m_oUIObjectList.begin(), m_oUIObjectList.end(), a_pUIObject);

	if(oIterator == m_oUIObjectList.end())
	{
		m_oUIObjectList.push_back(a_pUIObject);
	}
}

void CUIManager::removeUIObject(CUIObject* a_pUIObject)
{
	auto oIterator = std::find(m_oUIObjectList.begin(), m_oUIObjectList.end(), a_pUIObject);

	if(oIterator != m_oUIObjectList.end())
	{
		m_oUIObjectList.erase(oIterator);
	}
}

CLabel* CUIManager::createLabel(const std::string& a_rString, int a_nFontSize, bool a_bIsAddEnable)
{
	auto pLabel = CreateObject<CLabel>(a_rString, a_nFontSize);

	if(a_bIsAddEnable)
	{
		this->addUIObject(pLabel);
	}

	return pLabel;
}

CButton* CUIManager::createButton(const std::string& a_rFilepath, const std::function<void(CButton*)>& a_rCallback, bool a_bIsAddEnable)
{
	auto pButton = CreateObject<CButton>(a_rFilepath, a_rCallback);

	if(a_bIsAddEnable)
	{
		this->addUIObject(pButton);
	}

	return pButton;
}

CSprite* CUIManager::createSprite(const std::string& a_rFilepath, bool a_bIsAddEnable)
{
	auto pSprite = CreateObject<CSprite>(a_rFilepath);

	if(a_bIsAddEnable)
	{
		this->addUIObject(pSprite);
	}

	return pSprite;
}
