#include "Example_10.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Manager/CDeviceManager.h"

Example_10::Example_10(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_10::~Example_10(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
}

void Example_10::initApplication(void)
{
	CDirect3DApplication::initApplication();
	m_pVertexBuffer = this->createVertexBuffer();
}

void Example_10::update(void)
{
	CDirect3DApplication::update();
}

void Example_10::draw(void)
{
	CDirect3DApplication::draw();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetFVF(STVertex::FVF);

	GET_DEVICE()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
}

LPDIRECT3DVERTEXBUFFER9 Example_10::createVertexBuffer(void)
{
	auto pVertexBuffer = CreateVertexBuffer(sizeof(STVertex) * 3,
		D3DUSAGE_WRITEONLY,
		STVertex::FVF,
		D3DPOOL_MANAGED);

	/** VS Input */�� �����Ѵ�
	// {
	STVertex* pstVertices = nullptr;

	if(SUCCEEDED(pVertexBuffer->Lock(0, 0, (void**)&pstVertices, 0)))
	{
		pstVertices[0].m_stPosition = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		pstVertices[0].m_nColor = D3DCOLOR_XRGB(255, 0, 0);

		pstVertices[1].m_stPosition = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pstVertices[1].m_nColor = D3DCOLOR_XRGB(0, 255, 0);

		pstVertices[2].m_stPosition = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		pstVertices[2].m_nColor = D3DCOLOR_XRGB(0, 0, 255);

		pVertexBuffer->Unlock();
	}
	// }

	return pVertexBuffer;
}
