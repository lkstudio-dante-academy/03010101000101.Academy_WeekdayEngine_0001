#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CObject.h"
#include "../Interface/IRenderable.h"
#include "../Interface/IWindowMessageHandler.h"

//! UI ��ü
class CUIObject : public CObject,
	public IRenderable,
	public IWindowMessageHandler
{
public:			// �������̽� ����

	//! ȭ���� �׸���
	virtual void draw(void) final override;

	//! UI ȭ���� �׸���
	virtual void drawUI(void) final override;

	//! ������ �޼����� ó���Ѵ�
	virtual LRESULT handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam) final override;

public:			// getter, setter

	//! ũ�⸦ ��ȯ�Ѵ�
	virtual SIZE getSize(void);

	//! �׸��� ���θ� �����Ѵ�
	virtual void setVisible(bool a_bIsVisible);

	//! ������ �����Ѵ�
	virtual void setColor(const D3DXCOLOR& a_rstColor);

public:			// ������, �Ҹ���

	//! ������
	CUIObject(void);

	//! �Ҹ���
	virtual ~CUIObject(void);

protected:			// protected �Լ�

	//! UI �� �׸���
	virtual void doDrawUI(void);

protected:			// protected ����

	bool m_bIsVisible = false;
	D3DXCOLOR m_stColor;
};
