#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CUIObject.h"
#include "../Interface/IWindowMessageHandler.h"

class CSprite;

//! ��ư
class CButton : public CUIObject
{
public:			// getter, setter

	//! ũ�⸦ ��ȯ�Ѵ�
	virtual SIZE getSize(void) override;

	//! ������ �����Ѵ�
	virtual void setColor(const D3DXCOLOR& a_rstColor) override;

public:			// public �Լ�

	//! �ʱ�ȭ
	virtual void init(void) override;

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// ������, �Ҹ���

	//! ������
	CButton(const std::string& a_rFilepath, const std::function<void(CButton*)>& a_rCallback);

private:			// private ����

	bool m_bIsSelected = false;

	std::string m_oSpriteFilepath = "";
	std::function<void(CButton*)> m_oCallback = nullptr;

	CSprite* m_pNormalSprite = nullptr;
	CSprite* m_pSelectSprite = nullptr;
};
