#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IWindowMessageHandler.h"

//! ������ ������
class CWindowManager : public IWindowMessageHandler
{
public:			// �������̽� ����

	//! ������ �޼����� ó���Ѵ�
	virtual LRESULT handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam) override;

public:			// getter

	//! ������ ũ�⸦ ��ȯ�Ѵ�
	SIZE getWindowSize(void);

	//! ������ �ڵ��� ��ȯ�Ѵ�
	HWND getWindowHandle(void);

	//! �ν��Ͻ� �ڵ��� ��ȯ�Ѵ�
	HINSTANCE getInstanceHandle(void);

public:			// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CWindowManager);

	//! �ʱ�ȭ
	void init(HINSTANCE a_hInstance, const SIZE& a_rstWindowSize, IWindowMessageHandler* a_pMessageHandler);

private:			// private �Լ�

	//! �����츦 �����Ѵ�
	HWND createWindow(HINSTANCE a_hInstance, const SIZE& a_rstWindowSize);

private:			// ������, �Ҹ���

	//! ������
	CWindowManager(void);

	//! �Ҹ���
	virtual ~CWindowManager(void);

private:			// private ����

	SIZE m_stWindowSize;

	HWND m_hWindow = nullptr;
	HINSTANCE m_hInstance = nullptr;

	TCHAR* m_pszClassName = nullptr;
	IWindowMessageHandler* m_pMessageHandler = nullptr;
};
