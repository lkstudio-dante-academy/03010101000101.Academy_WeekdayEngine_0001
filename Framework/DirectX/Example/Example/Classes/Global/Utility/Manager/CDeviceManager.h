#pragma once

#include "../../Define/KGlobalDefine.h"

//! ����̽� ������
class CDeviceManager
{
public:			// getter

	//! ���̷�Ʈ 3D �� ��ȯ�Ѵ�
	LPDIRECT3D9 getDirect3D(void);

	//! ����̽��� ��ȯ�Ѵ�
	LPDIRECT3DDEVICE9 getDevice(void);

public:			// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CDeviceManager);

	//! �ʱ�ȭ
	void init(HWND a_hWindow, const SIZE& a_rstWindowSize);

private:			// private �Լ�

	//! ���̷�Ʈ 3D �� �����Ѵ�
	LPDIRECT3D9 createDirect3D(void);

	//! ����̽��� �����Ѵ�
	LPDIRECT3DDEVICE9 createDevice(HWND a_hWindow, const SIZE& a_rstWindowSize);

private:			// �Ҹ���

	//! �Ҹ���
	virtual ~CDeviceManager(void);

private:			// private ����

	LPDIRECT3D9 m_pDirect3D = nullptr;
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
};
