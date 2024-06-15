#include "Example_14.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CCamera.h"
#include "../Global/Utility/Manager/CDeviceManager.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CResourceManager.h"

#define HIERARCHY_TYPE_ROTATION			1
#define HIERARCHY_TYPE_CUBE_MAN			2

#define HIERARCHY_TYPE			HIERARCHY_TYPE_ROTATION

Example_14::Example_14(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize),

	m_fPitchVelocity(1.0f)
{
	// Do Nothing
}

Example_14::~Example_14(void)
{
	SAFE_DELETE(m_pObject);

	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

void Example_14::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pObject = CreateObject<CObject>();
	m_pObject->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

#if HIERARCHY_TYPE == HIERARCHY_TYPE_ROTATION
	m_pChildObject = CreateObject<CObject>();
	m_pChildObject->setPosition(D3DXVECTOR3(2.0f, 0.0f, 0.0f));

	m_pGrandChildObject = CreateObject<CObject>();
	m_pGrandChildObject->setPosition(D3DXVECTOR3(0.0f, -2.0f, 0.0f));

	m_pObject->addChildObject(m_pChildObject);
	m_pChildObject->addChildObject(m_pGrandChildObject);
#else
	m_pBodyObject = CreateObject<CObject>();
	m_pBodyObject->setScale(D3DXVECTOR3(0.75f, 1.0f, 0.35f));

	// �Ӹ�
	// {
	D3DXMATRIXA16 stOffsetMatrix;
	D3DXMatrixTranslation(&stOffsetMatrix, 0.0f, 1.0f, 0.0f);

	m_pHeadObject = CreateObject<CObject>();
	m_pHeadObject->setScale(D3DXVECTOR3(0.5f, 0.35f, 0.35f));
	m_pHeadObject->setPosition(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pHeadObject->setOffsetMatrix(stOffsetMatrix);
	// }

	// ����
	// {
	D3DXMatrixTranslation(&stOffsetMatrix, -1.0f, -1.0f, 0.0f);

	m_pLeftArmObject = CreateObject<CObject>();
	m_pLeftArmObject->setScale(D3DXVECTOR3(0.35f, 0.75f, 0.35f));
	m_pLeftArmObject->setPosition(D3DXVECTOR3(-0.75f, 1.0f, 0.0f));
	m_pLeftArmObject->setOffsetMatrix(stOffsetMatrix);
	// }

	// ������
	// {
	D3DXMatrixTranslation(&stOffsetMatrix, 1.0f, -1.0f, 0.0f);

	m_pRightArmObject = CreateObject<CObject>();
	m_pRightArmObject->setScale(D3DXVECTOR3(0.35f, 0.75f, 0.35f));
	m_pRightArmObject->setPosition(D3DXVECTOR3(0.75f, 1.0f, 0.0f));
	m_pRightArmObject->setOffsetMatrix(stOffsetMatrix);
	// }

	// �޴ٸ�
	// {
	D3DXMatrixTranslation(&stOffsetMatrix, 1.0f, -1.0f, 0.0f);

	m_pLeftLegObject = CreateObject<CObject>();
	m_pLeftLegObject->setScale(D3DXVECTOR3(0.35, 1.0f, 0.35f));
	m_pLeftLegObject->setPosition(D3DXVECTOR3(-0.75f, -1.0f, 0.0f));
	m_pLeftLegObject->setOffsetMatrix(stOffsetMatrix);
	// }

	// �����ٸ�
	// {
	D3DXMatrixTranslation(&stOffsetMatrix, -1.0f, -1.0f, 0.0f);

	m_pRightLegObject = CreateObject<CObject>();
	m_pRightLegObject->setScale(D3DXVECTOR3(0.35, 1.0f, 0.35f));
	m_pRightLegObject->setPosition(D3DXVECTOR3(0.75f, -1.0f, 0.0f));
	m_pRightLegObject->setOffsetMatrix(stOffsetMatrix);
	// }

	m_pObject->addChildObject(m_pBodyObject);
	m_pObject->addChildObject(m_pHeadObject);
	m_pObject->addChildObject(m_pLeftArmObject);
	m_pObject->addChildObject(m_pRightArmObject);
	m_pObject->addChildObject(m_pLeftLegObject);
	m_pObject->addChildObject(m_pRightLegObject);

	GET_CAMERA()->setFollowObject(m_pObject, D3DXVECTOR3(0.0f, 10.0f, -15.0f));
#endif			// #if HIERARCHY_TYPE == HIERARCHY_TYPE_ROTATION

	m_pVertexBuffer = this->createVertexBuffer();
	m_pIndexBuffer = this->createIndexBuffer();
}

void Example_14::update(void)
{
	CDirect3DApplication::update();
	m_pObject->update();

	if(IS_KEY_DOWN(DIK_UP))
	{
		m_pObject->moveByZAxis(5.0f * GET_DELTA_TIME());
	}
	else if(IS_KEY_DOWN(DIK_DOWN))
	{
		m_pObject->moveByZAxis(-5.0f * GET_DELTA_TIME());
	}

#if HIERARCHY_TYPE == HIERARCHY_TYPE_ROTATION
	m_fPitch += 90.0f * GET_DELTA_TIME();
	m_fRoll += 90.0f * GET_DELTA_TIME();

	D3DXVECTOR3 stChildPosition = {
		cosf(D3DXToRadian(m_fRoll)),
		sinf(D3DXToRadian(m_fRoll)),
		0.0f
	};

	D3DXVECTOR3 stGrandChildPosition = {
		0.0f,
		sinf(D3DXToRadian(m_fPitch)),
		cosf(D3DXToRadian(m_fPitch))
	};

	if(IS_KEY_DOWN(DIK_LEFT))
	{
		m_pObject->moveByXAxis(-5.0f * GET_DELTA_TIME(), false);
	}
	else if(IS_KEY_DOWN(DIK_RIGHT))
	{
		m_pObject->moveByXAxis(5.0f * GET_DELTA_TIME(), false);
	}

	if(IS_KEY_DOWN(DIK_Q))
	{
		m_pObject->rotateByZAxis(90.0f * GET_DELTA_TIME());
	}
	else if(IS_KEY_DOWN(DIK_E))
	{
		m_pObject->rotateByZAxis(-90.0f * GET_DELTA_TIME());
	}

	m_pChildObject->setPosition(stChildPosition * 3.0f);
	m_pGrandChildObject->setPosition(stGrandChildPosition * 3.0f);
#else
	m_fPitch += (m_fPitchVelocity * 120.0f) * GET_DELTA_TIME();

	if(m_fPitch >= 30.0f && m_fPitchVelocity >= 1.0f)
	{
		m_fPitch = 30.0f;
		m_fPitchVelocity = -1.0f;
	}
	else if(m_fPitch <= -30.0f && m_fPitchVelocity <= 1.0f)
	{
		m_fPitch = -30.0f;
		m_fPitchVelocity = 1.0f;
	}

	if(IS_KEY_DOWN(DIK_LEFT))
	{
		m_pObject->rotateByYAxis(-90.0f * GET_DELTA_TIME());
	}
	else if(IS_KEY_DOWN(DIK_RIGHT))
	{
		m_pObject->rotateByYAxis(90.0f * GET_DELTA_TIME());
	}

	m_pLeftArmObject->setRotation(D3DXVECTOR3(m_fPitch, 0.0f, 0.0f));
	m_pRightArmObject->setRotation(D3DXVECTOR3(-m_fPitch, 0.0f, 0.0f));

	m_pLeftLegObject->setRotation(D3DXVECTOR3(-m_fPitch, 0.0f, 0.0f));
	m_pRightLegObject->setRotation(D3DXVECTOR3(m_fPitch, 0.0f, 0.0f));
#endif			// #if HIERARCHY_TYPE == HIERARCHY_TYPE_ROTATION
}

void Example_14::draw(void)
{
	CDirect3DApplication::draw();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetIndices(m_pIndexBuffer);
	GET_DEVICE()->SetFVF(STVertex::FVF);

#if HIERARCHY_TYPE == HIERARCHY_TYPE_ROTATION
	// �θ� ��ü�� �׸���
	// {
	auto stWorldMatrix = m_pObject->getFinalWorldMatrix();

	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	// }

	// �ڽ� ��ü�� �׸���
	// {
	stWorldMatrix = m_pChildObject->getFinalWorldMatrix();

	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	// }

	// ���� ��ü�� �׸���
	// {
	stWorldMatrix = m_pGrandChildObject->getFinalWorldMatrix();

	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	// }
#else
	// ���� �׸���
	// {
	auto stWorldMatrix = m_pBodyObject->getFinalWorldMatrix();

	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	// }

	// �Ӹ��� �׸���
	// {
	stWorldMatrix = m_pHeadObject->getFinalWorldMatrix();

	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	// }

	/** VS Input */ �׸���
	// {
	stWorldMatrix = m_pLeftArmObject->getFinalWorldMatrix();

	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	// }

	// ������ ���� �׸���
	// {
	stWorldMatrix = m_pRightArmObject->getFinalWorldMatrix();

	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	// }

	// ���� �ٸ��� �׸���
	// {
	stWorldMatrix = m_pLeftLegObject->getFinalWorldMatrix();

	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	// }

	// ������ �ٸ��� �׸���
	// {
	stWorldMatrix = m_pRightLegObject->getFinalWorldMatrix();

	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);
	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	// }
#endif			// #if HIERARCHY_TYPE == HIERARCHY_TYPE_ROTATION

	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
}

LPDIRECT3DVERTEXBUFFER9 Example_14::createVertexBuffer(void)
{
	auto pVertexBuffer = CreateVertexBuffer(sizeof(STVertex) * 8,
		D3DUSAGE_WRITEONLY,
		STVertex::FVF,
		D3DPOOL_MANAGED);

	/** VS Input */�� �����Ѵ�
	// {
	STVertex* pstVertices = nullptr;

	if(SUCCEEDED(pVertexBuffer->Lock(0, 0, (void**)&pstVertices, 0)))
	{
		// ����
		// {
		pstVertices[0].m_stPosition = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
		pstVertices[0].m_nColor = D3DCOLOR_XRGB(255, 0, 0);

		pstVertices[1].m_stPosition = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
		pstVertices[1].m_nColor = D3DCOLOR_XRGB(0, 255, 0);

		pstVertices[2].m_stPosition = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
		pstVertices[2].m_nColor = D3DCOLOR_XRGB(0, 0, 255);

		pstVertices[3].m_stPosition = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
		pstVertices[3].m_nColor = D3DCOLOR_XRGB(0, 255, 255);
		// }

		// �ĸ�
		// {
		pstVertices[4].m_stPosition = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
		pstVertices[4].m_nColor = D3DCOLOR_XRGB(255, 0, 0);

		pstVertices[5].m_stPosition = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pstVertices[5].m_nColor = D3DCOLOR_XRGB(0, 255, 0);

		pstVertices[6].m_stPosition = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
		pstVertices[6].m_nColor = D3DCOLOR_XRGB(0, 0, 255);

		pstVertices[7].m_stPosition = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
		pstVertices[7].m_nColor = D3DCOLOR_XRGB(0, 255, 255);
		// }

		pVertexBuffer->Unlock();
	}
	// }

	return pVertexBuffer;
}

LPDIRECT3DINDEXBUFFER9 Example_14::createIndexBuffer(void)
{
	auto pIndexBuffer = CreateIndexBuffer(sizeof(WORD) * 36,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED);

	// �ε� ������ �����Ѵ�
	// {
	WORD* pnIndices = nullptr;

	if(SUCCEEDED(pIndexBuffer->Lock(0, 0, (void**)&pnIndices, 0)))
	{
		// ����
		pnIndices[0] = 0;	pnIndices[1] = 1;	pnIndices[2] = 2;
		pnIndices[3] = 0;	pnIndices[4] = 2;	pnIndices[5] = 3;

		// �ĸ�
		pnIndices[6] = 5;	pnIndices[7] = 4;	pnIndices[8] = 6;
		pnIndices[9] = 6;	pnIndices[10] = 4;	pnIndices[11] = 7;

		/** VS Input */
		pnIndices[12] = 4;	pnIndices[13] = 0;	pnIndices[14] = 7;
		pnIndices[15] = 7;	pnIndices[16] = 0;	pnIndices[17] = 3;

		// ������ ����
		pnIndices[18] = 1;	pnIndices[19] = 5;	pnIndices[20] = 2;
		pnIndices[21] = 2;	pnIndices[22] = 5;	pnIndices[23] = 6;

		// ����
		pnIndices[24] = 4;	pnIndices[25] = 5;	pnIndices[26] = 0;
		pnIndices[27] = 0;	pnIndices[28] = 5;	pnIndices[29] = 1;

		// �Ʒ���
		pnIndices[30] = 3;	pnIndices[31] = 2;	pnIndices[32] = 7;
		pnIndices[33] = 7;	pnIndices[34] = 2;	pnIndices[35] = 6;

		pIndexBuffer->Unlock();
	}
	// }

	return pIndexBuffer;
}
