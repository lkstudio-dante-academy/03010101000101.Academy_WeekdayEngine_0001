#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"
#include "../Interface/IWindowMessageHandler.h"

//! �Է� ������
class CInputManager : public IUpdateable
{
public:			// �������̽� ����

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// getter

	//! ���콺 ���� ��ȯ�Ѵ�
	int getMouseWheel(void);

	//! ���콺 ��ġ�� ��ȯ�Ѵ�
	POINT getMousePosition(void);

public:			// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CInputManager);

	//! �ʱ�ȭ
	void init(HINSTANCE a_hInstance, HWND a_hWindow);

	//! Ű ���� ���θ� Ȯ���Ѵ�
	bool isKeyDown(int a_nKeyCode);

	//! Ű �Է� ���θ� Ȯ���Ѵ�
	bool isKeyPressed(int a_nKeyCode);

	//! Ű �Է� ���� ���θ� Ȯ���Ѵ�
	bool isKeyReleased(int a_nKeyCode);

	//! ���콺 ��ư ���� ���θ� Ȯ���Ѵ�
	bool isMouseButtonDown(const EMouseButton a_eMouseButton);

	//! ���콺 ��ư �Է� ���θ� Ȯ���Ѵ�
	bool isMouseButtonPressed(const EMouseButton a_eMouseButton);

	//! ���콺 ��ư �Է� ���� ���θ� Ȯ���Ѵ�
	bool isMouseButtonReleased(const EMouseButton a_eMouseButton);

private:			// private �Լ�

	//! ���̷�Ʈ �Է��� �����Ѵ�
	LPDIRECTINPUT8 createDirectInput(HINSTANCE a_hInstance);

	//! Ű���� ����̽��� �����Ѵ�
	LPDIRECTINPUTDEVICE8 createKeyboardDevice(HWND a_hWindow);

	//! ���콺 ����̽��� �����Ѵ�
	LPDIRECTINPUTDEVICE8 createMouseDevice(HWND a_hWindow);

private:			// ������, �Ҹ���

	//! ������
	CInputManager(void);

	//! �Ҹ���
	virtual ~CInputManager(void);

private:			// private ����

	BYTE m_anKeyboardState[UCHAR_MAX + 1];
	BYTE m_anPrevKeyboardState[UCHAR_MAX + 1];

	DIMOUSESTATE m_stMouseState;
	DIMOUSESTATE m_stPrevMouseState;

	LPDIRECTINPUT8 m_pDirectInput = nullptr;
	LPDIRECTINPUTDEVICE8 m_pMouseDevice = nullptr;
	LPDIRECTINPUTDEVICE8 m_pKeyboardDevice = nullptr;
};
