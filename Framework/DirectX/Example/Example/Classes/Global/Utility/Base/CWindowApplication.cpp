#include "CWindowApplication.h"
#include "../Manager/CWindowManager.h"

/** VS Input */
static CWindowApplication* g_pWindowApplication = nullptr;

CWindowApplication::CWindowApplication(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	m_nOptions(a_nOptions),
	m_stWindowSize(a_rstWindowSize),
	m_hInstance(a_hInstance)
{
	g_pWindowApplication = this;

	if(AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
	}
}

CWindowApplication::~CWindowApplication(void)
{
	FreeConsole();
}

void CWindowApplication::initApplication(void)
{
	GET_WINDOW_MANAGER()->init(m_hInstance, m_stWindowSize, this);
}

LRESULT CWindowApplication::handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam)
{
	switch(a_nMessage)
	{
		case WM_DESTROY:
		{
			this->handleDestroyMessage(a_wParam, a_lParam);
			break;
		}
	}

	return DefWindowProc(a_hWindow, a_nMessage, a_wParam, a_lParam);
}

CWindowApplication* CWindowApplication::getInstance(void)
{
	return g_pWindowApplication;
}

void CWindowApplication::setWindowSize(SIZE a_stWindowSize)
{
	m_stWindowSize.cx = a_stWindowSize.cx;
	m_stWindowSize.cy = a_stWindowSize.cy;
}

int CWindowApplication::runApplication(void)
{
	this->initApplication();

	// �����츦 ����Ѵ�
	ShowWindow(GET_WINDOW_HANDLE(), m_nOptions);
	UpdateWindow(GET_WINDOW_HANDLE());

	return this->runMainLoop();
}

void CWindowApplication::handleDestroyMessage(WPARAM a_wParam, LPARAM a_lParam)
{
	PostQuitMessage(0);
}

int CWindowApplication::runMainLoop(void)
{
	MSG stMessage = { 0 };

	while(GetMessage(&stMessage, NULL, 0, 0))
	{
		TranslateMessage(&stMessage);
		DispatchMessage(&stMessage);
	}

	return (int)stMessage.wParam;
}
