#pragma once

#include "../../Define/KGlobalDefine.h"

//! ������ �޼��� ó���� �������̽�
class IWindowMessageHandler
{
public:			// �������̽�

	//! ������ �޼����� ó���Ѵ�
	virtual LRESULT handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam) = 0;
};
