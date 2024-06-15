#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CWindowApplication.h"
#include "../Global/Utility/Math/C3DVector.h"

/*
������ �����������̶�?
:
- 3 ���� �� ��ġ�Ǿ� �ִ� ��ü�� ���������� 2 ���� ȭ�鿡 ����ϱ� ����
���������� ��ġ�� �Ϸ��� �ܰ踦 �ǹ��Ѵ�

������ ������������ ���������� ũ�� 3 ������ �۾����� ������
1. ���� ���� (���� ���̴��� ���ؼ� ó���ȴ�)
2. �����Ͷ����� ���� (�׷��� ī�忡 ���ؼ� ó���ȴ�)
3. �ȼ� ���� (�ȼ� ���̴��� ���ؼ� ó���ȴ�)

1-1. ���� �����̶�?
:
- 3 ���� ��ü�� �̷�� ������ ��ġ�� 2 ���� �� �ش��ϴ� ��ǥ�� ��ȯ�ϴ� ������ �ǹ��Ѵ�.
(��, ���� ������ �Ϸ�Ǹ� 2 ���� �� ��ġ�ϴ� �������� ��ǥ�� ��� �� �� �ִ�.)

2-1. �����Ͷ����� �����̶�?
:
- ������ ������ �̿��ؼ� 3 ���� ��ü�� �鿡 �ش��ϴ� �ȼ��� ����ϴ� ������ �ǹ��Ѵ�.
(��, �����Ͷ����� ������ �Ϸ�Ǹ� 3 ���� ��ü�� �̷�� �ȼ��� ���������� ��� �� �� �ִ�.)

3-1. �ȼ� �����̶�?
:
- ȭ�� �� ��� �� �ȼ��� ������ �����ϴ� �ܰ踦 �ǹ��Ѵ�.
(��, �ȼ� ������ �Ϸ�Ǹ� ���������� ȭ�鿡 ��� �� �ȼ��� ������ ��� �� �� �ִ�.)

3 ���� ��ǥ�� 2 ���� ��ǥ�� ��ȯ�Ǵ� �ܰ�
:
- �� (����) ��ǥ
- ���� (����) ��ǥ
- �� (ī�޶�) ��ǥ
- ���� ��ǥ
- ���� ��ǥ
- ȭ�� ��ǥ
*/
//! Example 8
class Example_8 : public CWindowApplication
{
public:			// public �Լ�

	//! ���ø����̼��� �ʱ�ȭ�Ѵ�
	virtual void initApplication(void) override;

	//! ������ �޼����� ó���Ѵ�
	virtual LRESULT handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam) override;

public:			// ������, �Ҹ���

	//! ������
	Example_8(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_8(void);

private:			// private �Լ�

	//! Ÿ�̸� �޼����� ó���Ѵ�
	void handleTimerMessage(WPARAM a_wParam, LPARAM a_lParam);

	//! �׸��� �޼����� ó���Ѵ�
	void handlePaintMessage(WPARAM a_wParam, LPARAM a_lParam);

	//! ���콺 �޼����� ó���Ѵ�
	void handleMouseMessage(WPARAM a_wParam, LPARAM a_lParam);

private:			// private ����

	float m_fYaw = 0.0f;
	D3DXVECTOR3 m_astVertices[4];

	D3DXVECTOR3 m_stViewPosition;
	std::chrono::system_clock::time_point m_oPrevTimePoint;
};
