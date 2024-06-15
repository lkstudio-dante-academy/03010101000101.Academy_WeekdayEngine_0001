#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IWindowMessageHandler.h"

class CLabel;
class CButton;
class CSprite;
class CUIObject;

//! UI ������
class CUIManager : public IWindowMessageHandler
{
public:			// �������̽� ����

	//! ������ �޼����� ó���Ѵ�
	virtual LRESULT handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam) override;

public:			// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CUIManager);

	//! UI ��ü�� �߰��Ѵ�
	void addUIObject(CUIObject* a_pUIObject);

	//! UI ��ü�� �����Ѵ�
	void removeUIObject(CUIObject* a_pUIObject);

	//! ���� �����Ѵ�
	CLabel* createLabel(const std::string& a_rString, int a_nFontSize, bool a_bIsAddEnable = true);

	//! ��ư�� �����Ѵ�
	CButton* createButton(const std::string& a_rFilepath, const std::function<void(CButton*)>& a_rCallback, bool a_bIsAddEnable = true);

	//! ��������Ʈ�� �����Ѵ�
	CSprite* createSprite(const std::string& a_rFilepath, bool a_bIsAddEnable = true);

private:			// private ����

	std::vector<CUIObject*> m_oUIObjectList;
};
