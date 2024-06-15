#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IWindowMessageHandler.h"

//! ������ ���ø����̼�
class CWindowApplication : public IWindowMessageHandler
{
public:			// �������̽� ����

	//! ������ �޼����� ó���Ѵ�
	virtual LRESULT handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam) override;

public:			// getter, setter

	//! �ν��Ͻ��� ��ȯ�Ѵ�
	static CWindowApplication* getInstance(void);

	//! ������ ũ�⸦ �����Ѵ�
	virtual void setWindowSize(SIZE a_stWindowSize);

public:			// public �Լ�

	//! ���ø����̼��� �����Ѵ�
	int runApplication(void);

protected:			// protected �Լ�

	//! ���ø����̼��� �ʱ�ȭ�Ѵ�
	virtual void initApplication(void);

	//! ���� �޼����� ó���Ѵ�
	virtual void handleDestroyMessage(WPARAM a_wParam, LPARAM a_lParam);

	//! ���� ������ �����Ѵ�
	virtual int runMainLoop(void);

protected:			// ������, �Ҹ���

	//! ������
	CWindowApplication(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~CWindowApplication(void);

protected:			// protected ����

	int m_nOptions = 0;
	SIZE m_stWindowSize;
	HINSTANCE m_hInstance = nullptr;
};
