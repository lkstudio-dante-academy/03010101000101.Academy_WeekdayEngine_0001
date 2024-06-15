#pragma once

#include "../../Define/KGlobalDefine.h"
#include "CWindowApplication.h"
#include "../Interface/IUpdateable.h"
#include "../Interface/IRenderable.h"

class CGrid;
class CGizmo;
class CLabel;
class CLight;
class CCamera;
class CSkybox;

//! ���̷�Ʈ 3D ���ø����̼�
class CDirect3DApplication : public CWindowApplication,
	public IUpdateable,
	public IRenderable
{
public:			// �������̽� ����

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

	//! ȭ���� �׸���
	virtual void draw(void) override;

	//! UI ȭ���� �׸���
	virtual void drawUI(void) override;

public:			// getter, setter

	//! ������ ��ȯ�Ѵ�
	CLight* getLight(void);

	//! ī�޶� ��ȯ�Ѵ�
	CCamera* getCamera(void);

	//! ��ī�� �ڽ��� ��ȯ�Ѵ�
	CSkybox* getSkybox(void);

	//! ��������Ʈ�� ��ȯ�Ѵ�
	LPD3DXSPRITE getSprite(void);

	//! ��ī�� �ڽ��� �����Ѵ�
	virtual void setSkybox(CSkybox* a_pSkybox);

	//! ������ ũ�⸦ �����Ѵ�
	virtual void setWindowSize(SIZE a_stWindowSize) override;

public:			// public �Լ�

	//! ���ø����̼��� �ʱ�ȭ�Ѵ�
	virtual void initApplication(void) override;

	//! ���� ������ �����Ѵ�
	virtual int runMainLoop(void) override;

	//! ������ �޼����� ó���Ѵ�
	virtual LRESULT handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam) override;

protected:			// protected �Լ�

	//! ��������Ʈ�� �����Ѵ�
	virtual LPD3DXSPRITE createSprite(void);

protected:			// ������, �Ҹ���

	//! ������
	CDirect3DApplication(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~CDirect3DApplication(void);

protected:			// protected ����

	POINT m_stPrevMousePosition;

	CGrid* m_pGrid = nullptr;
	CGizmo* m_pGizmo = nullptr;
	CLight* m_pLight = nullptr;
	CCamera* m_pCamera = nullptr;
	CLabel* m_pTimeLabel = nullptr;

	CSkybox* m_pSkybox = nullptr;
	LPD3DXSPRITE m_pSprite = nullptr;
};
