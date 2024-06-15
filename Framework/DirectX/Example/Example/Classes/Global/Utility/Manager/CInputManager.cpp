#include "CInputManager.h"
#include "CWindowManager.h"

CInputManager::CInputManager(void)
{
	ZeroMemory(m_anKeyboardState, sizeof(m_anKeyboardState));
	ZeroMemory(m_anPrevKeyboardState, sizeof(m_anPrevKeyboardState));

	ZeroMemory(&m_stMouseState, sizeof(m_stMouseState));
	ZeroMemory(&m_stPrevMouseState, sizeof(m_stPrevMouseState));
}

CInputManager::~CInputManager(void)
{
	SAFE_UNACQUIRE(m_pKeyboardDevice);
	SAFE_UNACQUIRE(m_pMouseDevice);

	SAFE_RELEASE(m_pDirectInput);
}

void CInputManager::init(HINSTANCE a_hInstance, HWND a_hWindow)
{
	m_pDirectInput = this->createDirectInput(a_hInstance);
	m_pKeyboardDevice = this->createKeyboardDevice(a_hWindow);
	m_pMouseDevice = this->createMouseDevice(a_hWindow);
}

void CInputManager::update(void)
{
	CopyMemory(m_anPrevKeyboardState, m_anKeyboardState, sizeof(m_anKeyboardState));
	CopyMemory(&m_stPrevMouseState, &m_stMouseState, sizeof(m_stMouseState));

	m_pKeyboardDevice->GetDeviceState(sizeof(m_anKeyboardState), m_anKeyboardState);
	m_pMouseDevice->GetDeviceState(sizeof(m_stMouseState), &m_stMouseState);
}

int CInputManager::getMouseWheel(void)
{
	return m_stMouseState.lZ;
}

POINT CInputManager::getMousePosition(void)
{
	POINT stMousePosition;
	GetCursorPos(&stMousePosition);
	ScreenToClient(GET_WINDOW_HANDLE(), &stMousePosition);

	return stMousePosition;
}

bool CInputManager::isKeyDown(int a_nKeyCode)
{
	return m_anKeyboardState[a_nKeyCode] & 0x80;
}

bool CInputManager::isKeyPressed(int a_nKeyCode)
{
	return (m_anKeyboardState[a_nKeyCode] & 0x80) && !(m_anPrevKeyboardState[a_nKeyCode] & 0x80);
}

bool CInputManager::isKeyReleased(int a_nKeyCode)
{
	return !(m_anKeyboardState[a_nKeyCode] & 0x80) && (m_anPrevKeyboardState[a_nKeyCode] & 0x80);
}

bool CInputManager::isMouseButtonDown(const EMouseButton a_eMouseButton)
{
	int nInput = (int)a_eMouseButton;
	return m_stMouseState.rgbButtons[nInput] & 0x80;
}

bool CInputManager::isMouseButtonPressed(const EMouseButton a_eMouseButton)
{
	int nInput = (int)a_eMouseButton;
	return (m_stMouseState.rgbButtons[nInput] & 0x80) && !(m_stPrevMouseState.rgbButtons[nInput] & 0x80);
}

bool CInputManager::isMouseButtonReleased(const EMouseButton a_eMouseButton)
{
	int nInput = (int)a_eMouseButton;
	return !(m_stMouseState.rgbButtons[nInput] & 0x80) && (m_stPrevMouseState.rgbButtons[nInput] & 0x80);
}

LPDIRECTINPUT8 CInputManager::createDirectInput(HINSTANCE a_hInstance)
{
	LPDIRECTINPUT8 pDirectInput = nullptr;
	DirectInput8Create(a_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pDirectInput, NULL);

	return pDirectInput;
}

LPDIRECTINPUTDEVICE8 CInputManager::createKeyboardDevice(HWND a_hWindow)
{
	LPDIRECTINPUTDEVICE8 pKeyboardDevice = nullptr;
	m_pDirectInput->CreateDevice(GUID_SysKeyboard, &pKeyboardDevice, NULL);

	pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	pKeyboardDevice->SetCooperativeLevel(a_hWindow, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	pKeyboardDevice->Acquire();

	return pKeyboardDevice;
}

LPDIRECTINPUTDEVICE8 CInputManager::createMouseDevice(HWND a_hWindow)
{
	LPDIRECTINPUTDEVICE8 pMouseDevice = nullptr;
	m_pDirectInput->CreateDevice(GUID_SysMouse, &pMouseDevice, NULL);

	pMouseDevice->SetDataFormat(&c_dfDIMouse);
	pMouseDevice->SetCooperativeLevel(a_hWindow, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	pMouseDevice->Acquire();

	return pMouseDevice;
}
