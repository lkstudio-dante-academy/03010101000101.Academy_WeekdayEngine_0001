#include "CDeviceManager.h"

CDeviceManager::~CDeviceManager(void)
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pDirect3D);
}

void CDeviceManager::init(HWND a_hWindow, const SIZE& a_rstWindowSize)
{
	m_pDirect3D = this->createDirect3D();
	m_pDevice = this->createDevice(a_hWindow, a_rstWindowSize);
}

LPDIRECT3D9 CDeviceManager::getDirect3D(void)
{
	return m_pDirect3D;
}

LPDIRECT3DDEVICE9 CDeviceManager::getDevice(void)
{
	return m_pDevice;
}

LPDIRECT3D9 CDeviceManager::createDirect3D(void)
{
	return Direct3DCreate9(D3D_SDK_VERSION);
}

LPDIRECT3DDEVICE9 CDeviceManager::createDevice(HWND a_hWindow, const SIZE& a_rstWindowSize)
{
	D3DCAPS9 stDeviceCaps;
	m_pDirect3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stDeviceCaps);

	DWORD nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// �ϵ���� ������ ���� �� ���
	if(stDeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS stParameters = {
		a_rstWindowSize.cx,
		a_rstWindowSize.cy,
		D3DFMT_A8R8G8B8,
		1,
		D3DMULTISAMPLE_NONE,
		0,
		D3DSWAPEFFECT_DISCARD,
		a_hWindow,
		true,
		true,
		D3DFMT_D24S8,
		0,
		D3DPRESENT_RATE_DEFAULT,
		D3DPRESENT_INTERVAL_IMMEDIATE
	};

	LPDIRECT3DDEVICE9 pDevice = nullptr;

	// ����̽��� �����Ѵ�
	m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		a_hWindow,
		nVertexProcessing,
		&stParameters,
		&pDevice);

	printf("MaxActiveLights: %d\n", stDeviceCaps.MaxActiveLights);
	printf("MaxVertexBlendMatrices: %d\n", stDeviceCaps.MaxVertexBlendMatrices);
	printf("MaxTextureBlendStages: %d\n", stDeviceCaps.MaxTextureBlendStages);
	printf("MaxSimultaneousTextures: %d\n\n", stDeviceCaps.MaxSimultaneousTextures);

	return pDevice;
}
