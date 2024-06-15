#include "CWindowManager.h"
#include "../Base/CWindowApplication.h"

//! ������ �޼����� ó���Ѵ�
static LRESULT CALLBACK WndProc(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam)
{
	static IWindowMessageHandler* pMessageHandler = nullptr;

	switch(a_nMessage)
	{
		case WM_CREATE:
		{
			auto pstCreateStruct = (CREATESTRUCT*)a_lParam;
			pMessageHandler = static_cast<IWindowMessageHandler*>(pstCreateStruct->lpCreateParams);

			break;
		}
	}

	if(pMessageHandler != nullptr)
	{
		return pMessageHandler->handleWindowMessage(a_hWindow, a_nMessage, a_wParam, a_lParam);
	}

	return DefWindowProc(a_hWindow, a_nMessage, a_wParam, a_lParam);
}

CWindowManager::CWindowManager(void)
	:
	m_pszClassName(const_cast<TCHAR*>(_T("Example")))
{
	ZeroMemory(&m_stWindowSize, sizeof(m_stWindowSize));
}

CWindowManager::~CWindowManager(void)
{
	UnregisterClass(m_pszClassName, m_hInstance);
}

void CWindowManager::init(HINSTANCE a_hInstance, const SIZE& a_rstWindowSize, IWindowMessageHandler* a_pMessageHandler)
{
	m_hInstance = a_hInstance;
	m_stWindowSize = a_rstWindowSize;
	m_pMessageHandler = a_pMessageHandler;

	m_hWindow = this->createWindow(a_hInstance, a_rstWindowSize);
}

LRESULT CWindowManager::handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam)
{
	switch(a_nMessage)
	{
		case WM_SIZE:
		{
			m_stWindowSize.cx = LOWORD(a_lParam);
			m_stWindowSize.cy = HIWORD(a_lParam);

			GET_WINDOW_APPLICATION()->setWindowSize(m_stWindowSize);
			break;
		}
	}

	return m_pMessageHandler->handleWindowMessage(a_hWindow, a_nMessage, a_wParam, a_lParam);
}

SIZE CWindowManager::getWindowSize(void)
{
	return m_stWindowSize;
}

HWND CWindowManager::getWindowHandle(void)
{
	return m_hWindow;
}

HINSTANCE CWindowManager::getInstanceHandle(void)
{
	return m_hInstance;
}

HWND CWindowManager::createWindow(HINSTANCE a_hInstance, const SIZE& a_rstWindowSize)
{
	WNDCLASS stWindowClass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		a_hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)GetStockObject(COLOR_WINDOW + 1),
		NULL,
		m_pszClassName
	};

	// Ŭ������ ����Ѵ�
	RegisterClass(&stWindowClass);

	RECT stWindowRect = {
		0, 0, a_rstWindowSize.cx, a_rstWindowSize.cy
	};

	// ������ ũ�⸦ ����Ѵ�
	AdjustWindowRect(&stWindowRect, WS_OVERLAPPEDWINDOW, false);

	// �����츦 �����Ѵ�
	return CreateWindow(stWindowClass.lpszClassName,
		stWindowClass.lpszClassName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		stWindowRect.right - stWindowRect.left,
		stWindowRect.bottom - stWindowRect.top,
		GetDesktopWindow(),
		NULL,
		a_hInstance,
		this);
}
