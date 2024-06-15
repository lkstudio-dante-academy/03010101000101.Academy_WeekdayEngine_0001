#include "Example_8.h"
#include "../Global/Utility/Manager/CWindowManager.h"

Example_8::Example_8(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CWindowApplication(a_hInstance, a_nOptions, a_rstWindowSize),

	m_stViewPosition(0.0f, 0.0f, -3.0f)
{
	ZeroMemory(&m_astVertices, sizeof(m_astVertices));
}

Example_8::~Example_8(void)
{
	KillTimer(GET_WINDOW_HANDLE(), 0);
}

void Example_8::initApplication(void)
{
	CWindowApplication::initApplication();
	SetTimer(GET_WINDOW_HANDLE(), 0, 0, NULL);

	m_oPrevTimePoint = std::chrono::system_clock::now();
}

LRESULT Example_8::handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam)
{
	switch(a_nMessage)
	{
		case WM_TIMER:
		{
			this->handleTimerMessage(a_wParam, a_lParam);
			break;
		}
		case WM_PAINT:
		{
			this->handlePaintMessage(a_wParam, a_lParam);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			this->handleMouseMessage(a_wParam, a_lParam);
			break;
		}
	}

	return CWindowApplication::handleWindowMessage(a_hWindow, a_nMessage, a_wParam, a_lParam);
}

void Example_8::handleTimerMessage(WPARAM a_wParam, LPARAM a_lParam)
{
	auto oCurrentTimePoint = std::chrono::system_clock::now();
	float fDeltaTime = std::chrono::duration<float>(oCurrentTimePoint - m_oPrevTimePoint).count();

	m_fYaw += 90.0f * fDeltaTime;
	m_oPrevTimePoint = oCurrentTimePoint;

	/** VS Input */�� �����Ѵ�
	// {
	D3DXVECTOR3 astVertices[4];
	ZeroMemory(&astVertices, sizeof(astVertices));

	astVertices[0] = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	astVertices[1] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	astVertices[2] = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	astVertices[3] = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	// }

	/** VS Input */� �����Ѵ�
	// {
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixRotationY(&stWorldMatrix, D3DXToRadian(m_fYaw));
	// }

	/*
	�� ����� ��� (Right = X �� ���� ����, Up = Y �� ���� ����, Forward = Z �� ���� ����)

				  Right.x,				 Up.x,				 Forward.x, 0
				  Right.y,				 Up.y,				 Forward.y, 0
				  Right.z,				 Up.z,				 Forward.z, 0
	-(Position Dot Right), -(Position Dot Up), -(Position Dot Forward), 1
	*/
	// �� ����� �����Ѵ�
	// {
	D3DXVECTOR3 stLookPosition = {
		0.0f, 0.0f, 0.0f
	};

	D3DXVECTOR3 stUpDirection = {
		0.0f, 1.0f, 0.0f
	};

	D3DXMATRIXA16 stViewMatrix;
	D3DXMatrixLookAtLH(&stViewMatrix, &m_stViewPosition, &stLookPosition, &stUpDirection);
	// }

	/*
	���� ��� ��� (D = 1 / tan(Fov / 2), A = ��Ⱦ��, Near = ����ü�� ���� ���, Far = ����ü�� �Ĺ� ���)

	D / A, 0,							   0, 0
		0, D,							   0, 0
		0, 0,			  Far / (Far - Near), 0
		0, 0, (-(Far * Near) / (Far - Near)), 0
	*/
	/** VS Input */� �����Ѵ�
	// {
	D3DXMATRIXA16 stProjectionMatrix;
	D3DXMatrixPerspectiveFovLH(&stProjectionMatrix, D3DXToRadian(50.0f), m_stWindowSize.cx / (float)m_stWindowSize.cy, 0.1f, 1000.0f);
	// }

	/*
	����Ʈ ��� ���

		(Width / 2),				0,			   0, 0
				  0,	-(Height / 2),			   0, 0
				  0,				0, (MaxZ - MinZ), 0
	X + (Width / 2), Y + (Height / 2),			MinZ, 1
	*/
	// ����Ʈ ����� �����Ѵ�
	// {
	D3DVIEWPORT9 stViewport;
	ZeroMemory(&stViewport, sizeof(stViewport));

	stViewport.X = 0;
	stViewport.Y = 0;
	stViewport.Width = m_stWindowSize.cx;
	stViewport.Height = m_stWindowSize.cy;
	stViewport.MinZ = 0.0f;
	stViewport.MaxZ = 1.0f;

	D3DXMATRIXA16 stViewportMatrix;
	D3DXMatrixIdentity(&stViewportMatrix);

	stViewportMatrix(0, 0) = stViewport.Width / 2.0f;
	stViewportMatrix(1, 1) = stViewport.Height / -2.0f;
	stViewportMatrix(2, 2) = stViewport.MaxZ - stViewport.MinZ;

	stViewportMatrix(3, 0) = stViewport.X + (stViewport.Width / 2.0f);
	stViewportMatrix(3, 1) = stViewport.Y + (stViewport.Height / 2.0f);
	stViewportMatrix(3, 2) = stViewport.MinZ;
	// }

	// ���� ��ȯ ����� �����Ѵ�
	// {
	auto stTransformMatrix = stWorldMatrix * stViewMatrix * stProjectionMatrix * stViewportMatrix;

	D3DXVec3TransformCoordArray(astVertices,
		sizeof(D3DXVECTOR3),
		astVertices,
		sizeof(D3DXVECTOR3),
		&stTransformMatrix,
		4);
	// }

	InvalidateRect(GET_WINDOW_HANDLE(), NULL, true);
	CopyMemory(m_astVertices, astVertices, sizeof(astVertices));
}

void Example_8::handlePaintMessage(WPARAM a_wParam, LPARAM a_lParam)
{
	PAINTSTRUCT stPaintStruct;
	BeginPaint(GET_WINDOW_HANDLE(), &stPaintStruct);

	// ���� �ﰢ��
	MoveToEx(stPaintStruct.hdc, m_astVertices[0].x, m_astVertices[0].y, NULL);
	LineTo(stPaintStruct.hdc, m_astVertices[1].x, m_astVertices[1].y);
	LineTo(stPaintStruct.hdc, m_astVertices[3].x, m_astVertices[3].y);
	LineTo(stPaintStruct.hdc, m_astVertices[0].x, m_astVertices[0].y);

	// ������ �ﰢ��
	MoveToEx(stPaintStruct.hdc, m_astVertices[3].x, m_astVertices[3].y, NULL);
	LineTo(stPaintStruct.hdc, m_astVertices[1].x, m_astVertices[1].y);
	LineTo(stPaintStruct.hdc, m_astVertices[2].x, m_astVertices[2].y);
	LineTo(stPaintStruct.hdc, m_astVertices[3].x, m_astVertices[3].y);

	EndPaint(GET_WINDOW_HANDLE(), &stPaintStruct);
}

void Example_8::handleMouseMessage(WPARAM a_wParam, LPARAM a_lParam)
{
	int nWheelValue = GET_WHEEL_DELTA_WPARAM(a_wParam);
	m_stViewPosition.z += nWheelValue / 500.0f;

	m_stViewPosition.z = min(-3.0f, m_stViewPosition.z);
	m_stViewPosition.z = max(-10.0f, m_stViewPosition.z);
}
