#include "CDirect3DApplication.h"
#include "../../Function/GlobalFunction.h"
#include "../Base/CSceneObject.h"
#include "../UI/CLabel.h"
#include "../Debug/CGrid.h"
#include "../Debug/CGizmo.h"
#include "../Object/CLight.h"
#include "../Object/CCamera.h"
#include "../Object/CSkybox.h"
#include "../Manager/CWindowManager.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CTimeManager.h"
#include "../Manager/CInputManager.h"
#include "../Manager/CSoundManager.h"
#include "../Manager/CScheduleManager.h"
#include "../Manager/CSceneManager.h"
#include "../Manager/CUIManager.h"

CDirect3DApplication::CDirect3DApplication(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CWindowApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

CDirect3DApplication::~CDirect3DApplication(void)
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pGizmo);
	SAFE_DELETE(m_pLight);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pTimeLabel);
	SAFE_DELETE(m_pSkybox);

	SAFE_RELEASE(m_pSprite);
}

void CDirect3DApplication::initApplication(void)
{
	CWindowApplication::initApplication();
	GET_DEVICE_MANAGER()->init(GET_WINDOW_HANDLE(), m_stWindowSize);

	m_pGrid = CreateObject<CGrid>(50);
	m_pGizmo = CreateObject<CGizmo>(25);
	m_pSprite = this->createSprite();

	m_pTimeLabel = CREATE_LABEL("", 25);
	m_pTimeLabel->setPosition(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

	m_pLight = CreateObject<CLight>(0);
	m_pLight->setPosition(D3DXVECTOR3(-10.0f, 10.0f, -10.0f));
	m_pLight->setRotation(D3DXVECTOR3(45.0f, 0.0f, 0.0f));
	m_pLight->setLightEnable(true);

	m_pCamera = CreateObject<CCamera>(m_stWindowSize.cx / (float)m_stWindowSize.cy);
	m_pCamera->setPosition(D3DXVECTOR3(0.0f, 0.0f, -5.0f));

	// ���� ���¸� �����Ѵ�
	GET_DEVICE()->SetRenderState(D3DRS_SPECULARENABLE, true);
	GET_DEVICE()->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	GET_DEVICE()->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255));

	// ���÷� ���¸� �����Ѵ�
	GET_DEVICE()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	GET_DEVICE()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	GET_DEVICE()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// �ؽ�ó �������� ���¸� �����Ѵ�
	// {
	GET_DEVICE()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	GET_DEVICE()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	GET_DEVICE()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);

	GET_DEVICE()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	GET_DEVICE()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	GET_DEVICE()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	// }
}

void CDirect3DApplication::update(void)
{
	if(m_pSkybox != nullptr)
	{
		m_pSkybox->update();
	}

	m_pGrid->update();
	m_pGizmo->update();
	m_pLight->update();
	m_pCamera->update();

	if(GET_SCENE_MANAGER()->getSceneObject() != nullptr)
	{
		GET_SCENE_MANAGER()->getSceneObject()->update();
	}

	// �� ���¸� �����Ѵ�
	// {
	char szString[256] = "";
	sprintf(szString, "FPS: %d fps\nDelta Time: %f sec\nRunning Time: %f sec", GET_FPS(), GET_DELTA_TIME(), GET_RUNNING_TIME());

	m_pTimeLabel->setString(szString);
	// }

	// ī�޶� ���¸� �����Ѵ�
	// {
	if(IS_MOUSE_BUTTON_DOWN(EMouseButton::RIGHT))
	{
		if(IS_KEY_DOWN(DIK_W))
		{
			m_pCamera->moveByZAxis(20.0f * GET_DELTA_TIME());
		}
		else if(IS_KEY_DOWN(DIK_S))
		{
			m_pCamera->moveByZAxis(-20.0f * GET_DELTA_TIME());
		}

		if(IS_KEY_DOWN(DIK_A))
		{
			m_pCamera->moveByXAxis(-20.0f * GET_DELTA_TIME());
		}
		else if(IS_KEY_DOWN(DIK_D))
		{
			m_pCamera->moveByXAxis(20.0f * GET_DELTA_TIME());
		}

		if(IS_KEY_DOWN(DIK_Q))
		{
			m_pCamera->rotateByYAxis(-90.0f * GET_DELTA_TIME(), false);
		}
		else if(IS_KEY_DOWN(DIK_E))
		{
			m_pCamera->rotateByYAxis(90.0f * GET_DELTA_TIME(), false);
		}

		if(IS_MOUSE_BUTTON_PRESSED(EMouseButton::RIGHT))
		{
			m_stPrevMousePosition = GET_MOUSE_POSITION();
		}

		auto stMousePosition = GET_MOUSE_POSITION();

		m_pCamera->rotateByXAxis(stMousePosition.y - m_stPrevMousePosition.y);
		m_pCamera->rotateByYAxis(stMousePosition.x - m_stPrevMousePosition.x, false);

		m_stPrevMousePosition = stMousePosition;

		int nMouseWheel = GET_MOUSE_WHEEL();
		m_pCamera->moveByZAxis(nMouseWheel / 50.0f);
	}
	// }
}

void CDirect3DApplication::draw(void)
{
	if(m_pSkybox != nullptr)
	{
		m_pSkybox->draw();
	}

	m_pGrid->draw();
	m_pGizmo->draw();

	if(GET_SCENE_MANAGER()->getSceneObject() != nullptr)
	{
		GET_SCENE_MANAGER()->getSceneObject()->draw();
	}
}

void CDirect3DApplication::drawUI(void)
{
	m_pTimeLabel->drawUI();

	if(GET_SCENE_MANAGER()->getSceneObject() != nullptr)
	{
		GET_SCENE_MANAGER()->getSceneObject()->drawUI();
	}
}

CLight* CDirect3DApplication::getLight(void)
{
	return m_pLight;
}

CCamera* CDirect3DApplication::getCamera(void)
{
	return m_pCamera;
}

CSkybox* CDirect3DApplication::getSkybox(void)
{
	return m_pSkybox;
}

LPD3DXSPRITE CDirect3DApplication::getSprite(void)
{
	return m_pSprite;
}

void CDirect3DApplication::setSkybox(CSkybox* a_pSkybox)
{
	SAFE_DELETE(m_pSkybox);
	m_pSkybox = a_pSkybox;
}

void CDirect3DApplication::setWindowSize(SIZE a_stWindowSize)
{
	CWindowApplication::setWindowSize(a_stWindowSize);
	m_pCamera->setAspect(a_stWindowSize.cx / (float)a_stWindowSize.cy);
}

int CDirect3DApplication::runMainLoop(void)
{
	// �ð�, �Է�, ���� �����ڸ� �ʱ�ȭ�Ѵ�
	GET_TIME_MANAGER()->init();
	GET_INPUT_MANAGER()->init(m_hInstance, GET_WINDOW_HANDLE());
	GET_SOUND_MANAGER()->init(GET_WINDOW_HANDLE());

	MSG stMessage;
	ZeroMemory(&stMessage, sizeof(stMessage));

	while(stMessage.message != WM_QUIT)
	{
		if(PeekMessage(&stMessage, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&stMessage);
			DispatchMessage(&stMessage);
		}

		// �ð�, �Է�, ������ ������ �����Ѵ�
		GET_TIME_MANAGER()->update();
		GET_INPUT_MANAGER()->update();
		GET_SCHEDULE_MANAGER()->update();

		// ���۸� �����
		GET_DEVICE()->Clear(0,
			NULL,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
			D3DCOLOR_XRGB(0, 0, 0),
			1.0f,
			0);

		if(SUCCEEDED(GET_DEVICE()->BeginScene()))
		{
			this->update();

			// ��ü�� �׸���
			GET_DEVICE()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			{
				this->draw();
			}
			GET_DEVICE()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			// UI �� �׸���
			GET_SPRITE()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
			{
				this->drawUI();
			}
			GET_SPRITE()->End();

			GET_DEVICE()->EndScene();
		}

		// ���۸� ��ü�Ѵ�
		GET_DEVICE()->Present(NULL, NULL, NULL, NULL);
	}

	return (int)stMessage.wParam;
}

LRESULT CDirect3DApplication::handleWindowMessage(HWND a_hWindow, UINT a_nMessage, WPARAM a_wParam, LPARAM a_lParam)
{
	GET_UI_MANAGER()->handleWindowMessage(a_hWindow, a_nMessage, a_wParam, a_lParam);
	return CWindowApplication::handleWindowMessage(a_hWindow, a_nMessage, a_wParam, a_lParam);
}

LPD3DXSPRITE CDirect3DApplication::createSprite(void)
{
	LPD3DXSPRITE pSprite = nullptr;

	//! ��������Ʈ�� �����Ѵ�
	D3DXCreateSprite(GET_DEVICE(),
		&pSprite);

	return pSprite;
}
