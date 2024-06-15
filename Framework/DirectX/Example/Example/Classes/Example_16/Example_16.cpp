#include "Example_16.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Base/CObject.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"
#include "../Global/Utility/Manager/CResourceManager.h"

Example_16::Example_16(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	ZeroMemory(&m_stPrevMousePosition, sizeof(m_stPrevMousePosition));
}

Example_16::~Example_16(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

void Example_16::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pObject = CreateObject<CObject>();
	m_pObject->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pVertexBuffer = this->createVertexBuffer();
	m_pIndexBuffer = this->createIndexBuffer();
	m_pTexture = GET_TEXTURE("Resources/Textures/HelloWorld.png");
}

void Example_16::update(void)
{
	CDirect3DApplication::update();
	m_pObject->update();

	if(IS_MOUSE_BUTTON_DOWN(EMouseButton::LEFT))
	{
		if(IS_MOUSE_BUTTON_PRESSED(EMouseButton::LEFT))
		{
			m_stPrevMousePosition = GET_MOUSE_POSITION();
		}

		auto stMousePosition = GET_MOUSE_POSITION();

		D3DVIEWPORT9 stViewport;
		GET_DEVICE()->GetViewport(&stViewport);

		float fOffsetX = (stViewport.Width - stViewport.Height) / -2.0f;

		float fNormalizeX = (((stMousePosition.x + fOffsetX) * 2.0f) / stViewport.Height) - 1.0f;
		float fNormalizeY = ((stMousePosition.y * -2.0f) / stViewport.Height) + 1.0f;
		float fNormalizeZ = 0.0f;

		float fPrevNormalizeX = (((m_stPrevMousePosition.x + fOffsetX) * 2.0f) / stViewport.Height) - 1.0f;
		float fPrevNormalizeY = ((m_stPrevMousePosition.y * -2.0f) / stViewport.Height) + 1.0f;
		float fPrevNormalizeZ = 0.0f;

		if(sqrtf(powf(fNormalizeX, 2) + powf(fNormalizeY, 2)) < 1.0f &&
			sqrtf(powf(fPrevNormalizeX, 2) + powf(fPrevNormalizeY, 2)) < 1.0f)
		{
			fNormalizeZ = sqrt(1.0f - (powf(fNormalizeX, 2) + powf(fNormalizeY, 2)));
			fPrevNormalizeZ = sqrt(1.0f - (powf(fPrevNormalizeX, 2) + powf(fPrevNormalizeY, 2)));
		}

		D3DXVECTOR3 stDirection(fNormalizeX, fNormalizeY, fNormalizeZ);
		D3DXVECTOR3 stPrevDirection(fPrevNormalizeX, fPrevNormalizeY, fPrevNormalizeZ);

		D3DXVec3Normalize(&stDirection, &stDirection);
		D3DXVec3Normalize(&stPrevDirection, &stPrevDirection);

		D3DXVECTOR3 stRotationDirection;
		D3DXVec3Cross(&stRotationDirection, &stDirection, &stPrevDirection);

		float fAngle = asinf(D3DXVec3Length(&stRotationDirection));

		D3DXQUATERNION stQuaternion;
		D3DXQuaternionRotationAxis(&stQuaternion, &stRotationDirection, fAngle);

		D3DXMATRIXA16 stRotation;
		D3DXMatrixRotationQuaternion(&stRotation, &stQuaternion);

		m_pObject->rotateByMatrix(stRotation);
		m_stPrevMousePosition = stMousePosition;
	}
}

void Example_16::draw(void)
{
	CDirect3DApplication::draw();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);

	// ����� �����Ѵ�
	// {
	auto stWorldMatrix = m_pObject->getFinalWorldMatrix();
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	// }

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetIndices(m_pIndexBuffer);
	GET_DEVICE()->SetFVF(STVertex::FVF);
	GET_DEVICE()->SetTexture(0, m_pTexture);

	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	GET_DEVICE()->SetTexture(0, NULL);
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
}

LPDIRECT3DVERTEXBUFFER9 Example_16::createVertexBuffer(void)
{
	auto pVertexBuffer = CreateVertexBuffer(sizeof(STVertex) * 4,
		D3DUSAGE_WRITEONLY,
		STVertex::FVF,
		D3DPOOL_MANAGED);

	/** VS Input */�� �����Ѵ�
	// {
	STVertex* pstVertices = nullptr;

	if(SUCCEEDED(pVertexBuffer->Lock(0, 0, (void**)&pstVertices, 0)))
	{
		pstVertices[0].m_stPosition = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		pstVertices[0].m_stUV = D3DXVECTOR2(0.0f, 0.0f);

		pstVertices[1].m_stPosition = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		pstVertices[1].m_stUV = D3DXVECTOR2(1.0f, 0.0f);

		pstVertices[2].m_stPosition = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		pstVertices[2].m_stUV = D3DXVECTOR2(1.0f, 1.0f);

		pstVertices[3].m_stPosition = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		pstVertices[3].m_stUV = D3DXVECTOR2(0.0f, 1.0f);

		pVertexBuffer->Unlock();
	}
	// }

	return pVertexBuffer;
}

LPDIRECT3DINDEXBUFFER9 Example_16::createIndexBuffer(void)
{
	auto pIndexBuffer = CreateIndexBuffer(sizeof(WORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED);

	// �ε��� ������ �����Ѵ�
	// {
	WORD* pnIndices = nullptr;

	if(SUCCEEDED(pIndexBuffer->Lock(0, 0, (void**)&pnIndices, 0)))
	{
		pnIndices[0] = 0;	pnIndices[1] = 1;	pnIndices[2] = 2;
		pnIndices[3] = 0;	pnIndices[4] = 2;	pnIndices[5] = 3;

		pIndexBuffer->Unlock();
	}
	// }

	return pIndexBuffer;
}
