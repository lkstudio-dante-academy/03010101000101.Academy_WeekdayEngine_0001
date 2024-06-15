#include "CRenderObject.h"
#include "../../Function/GlobalFunction.h"
#include "../Debug/CDebugDraw.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CResourceManager.h"

CRenderObject::CRenderObject(void)
	:
	m_bIsVisible(true)
{
	ZeroMemory(&m_stBoundingBox, sizeof(m_stBoundingBox));
	ZeroMemory(&m_stBoundingSphere, sizeof(m_stBoundingSphere));

	ZeroMemory(&m_stShadowMaterial, sizeof(m_stShadowMaterial));
	m_stShadowMaterial.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

	D3DXMatrixIdentity(&m_stShadowMatrix);
}

CRenderObject::~CRenderObject(void)
{
	// Do Nothing
}

void CRenderObject::draw(void)
{
	if(m_bIsVisible)
	{
		this->preDrawObject();
		this->doDrawObject();
		this->postDrawObject();

		if(m_bIsShadowEnable)
		{
			this->preDrawShadow();
			this->doDrawShadow();
			this->postDrawShadow();
		}

		// �ڽ� ��ü�� �׸���
		for(auto pChildObject : m_oChildObjectList)
		{
			auto pRenderObject = dynamic_cast<CRenderObject*>(pChildObject);

			if(pRenderObject != nullptr)
			{
				pRenderObject->draw();
			}
		}
	}
}

D3DXMATRIXA16 CRenderObject::getBoundingWorldMatrix(void)
{
	return this->getFinalWorldMatrix();
}

STBoundingBox CRenderObject::getBoundingBox(void)
{
	return m_stBoundingBox;
}

STObjectBoundingBox CRenderObject::getObjectBoundingBox(void)
{
	auto stBoundingBox = this->getFinalBoundingBox();
	auto stWorldMatrix = this->getBoundingWorldMatrix();

	STObjectBoundingBox stObjectBoundingBox;
	ZeroMemory(&stObjectBoundingBox, sizeof(stObjectBoundingBox));

	/** VS Input */�� �����Ѵ�
	// {
	D3DXVECTOR3 stRightDirection;
	D3DXVECTOR3 stUpDirection;
	D3DXVECTOR3 stForwardDirection;

	CopyMemory(&stRightDirection, &stWorldMatrix(0, 0), sizeof(stRightDirection));
	CopyMemory(&stUpDirection, &stWorldMatrix(1, 0), sizeof(stUpDirection));
	CopyMemory(&stForwardDirection, &stWorldMatrix(2, 0), sizeof(stForwardDirection));

	D3DXVec3Normalize(&stObjectBoundingBox.m_astDirections[(int)EDirection::RIGHT], &stRightDirection);
	D3DXVec3Normalize(&stObjectBoundingBox.m_astDirections[(int)EDirection::UP], &stUpDirection);
	D3DXVec3Normalize(&stObjectBoundingBox.m_astDirections[(int)EDirection::FORWARD], &stForwardDirection);
	// }

	for(int i = 0; i < NUM_DIRECTIONS; ++i)
	{
		auto stAxis = stObjectBoundingBox.m_astDirections[i];
		auto stHalfDirection = (stBoundingBox.m_stMaxPosition - stBoundingBox.m_stMinPosition) / 2.0f;

		stObjectBoundingBox.m_afHelfLengths[i] = fabsf(D3DXVec3Dot(&stAxis, &stHalfDirection));
	}

	auto stCenterPosition = (stBoundingBox.m_stMinPosition + stBoundingBox.m_stMaxPosition) / 2.0f;
	stObjectBoundingBox.m_stCenterPosition = stCenterPosition;

	return stObjectBoundingBox;
}

STBoundingSphere CRenderObject::getBoundingSphere(void)
{
	return m_stBoundingSphere;
}

STBoundingBox CRenderObject::getFinalBoundingBox(void)
{
	auto stWorldMatrix = this->getBoundingWorldMatrix();

	auto stBoundingBox = m_stBoundingBox;
	D3DXVec3TransformCoord(&stBoundingBox.m_stMinPosition, &m_stBoundingBox.m_stMinPosition, &stWorldMatrix);
	D3DXVec3TransformCoord(&stBoundingBox.m_stMaxPosition, &m_stBoundingBox.m_stMaxPosition, &stWorldMatrix);

	return stBoundingBox;
}

STBoundingSphere CRenderObject::getFinalBoundingSphere(void)
{
	auto stWorldMatrix = this->getBoundingWorldMatrix();

	auto stBoundingSphere = m_stBoundingSphere;
	D3DXVec3TransformCoord(&stBoundingSphere.m_stCenterPosition, &m_stBoundingSphere.m_stCenterPosition, &stWorldMatrix);

	stBoundingSphere.m_fRadius *= max(max(stWorldMatrix(0, 0), stWorldMatrix(1, 1)),
		max(stWorldMatrix(1, 1), stWorldMatrix(2, 2)));

	return stBoundingSphere;
}

void CRenderObject::setVisible(bool a_bIsVisible)
{
	m_bIsVisible = a_bIsVisible;
}

void CRenderObject::setDebugEnable(bool a_bIsDebugEnable, EDebugDrawType a_eDebugDrawType)
{
	if(m_bIsDebugEnable != a_bIsDebugEnable)
	{
		m_bIsDebugEnable = a_bIsDebugEnable;

		if(!a_bIsDebugEnable)
		{
			this->removeChildObject(m_pDebugDraw);
		}
		else
		{
			m_pDebugDraw = CreateObject<CDebugDraw>(this, a_eDebugDrawType);
			m_pDebugDraw->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			this->addChildObject(m_pDebugDraw);
		}
	}
}

void CRenderObject::setShadowEnable(bool a_bIsShadowEnable, EShadowType a_eShadowType)
{
	if(m_bIsShadowEnable != a_bIsShadowEnable)
	{
		m_bIsShadowEnable = a_bIsShadowEnable;

		if(!a_bIsShadowEnable)
		{
			SAFE_RELEASE(m_pShadowMesh);
		}
		else
		{
			m_eShadowType = a_eShadowType;
			m_pShadowMesh = this->createShadowMesh();
		}
	}
}

void CRenderObject::setShadowMaterial(const D3DMATERIAL9& a_rstShadowMaterial)
{
	m_stShadowMaterial = a_rstShadowMaterial;
}

void CRenderObject::setShadowMatrix(const D3DXMATRIXA16& a_rstShadowMatrix)
{
	m_stShadowMatrix = a_rstShadowMatrix;
}

void CRenderObject::setBoundingBox(const STBoundingBox& a_rstBoundingBox)
{
	m_stBoundingBox = a_rstBoundingBox;
}

void CRenderObject::setBoundingSphere(const STBoundingSphere& a_rstBoundingSphere)
{
	m_stBoundingSphere = a_rstBoundingSphere;
}

void CRenderObject::preDrawObject(void)
{
	// Do Nothing
}

void CRenderObject::doDrawObject(void)
{
	// Do Nothing
}

void CRenderObject::postDrawObject(void)
{
	// Do Nothing
}

void CRenderObject::preDrawShadow(void)
{
	// ���ٽ� ���¸� �����Ѵ�
	GET_DEVICE()->SetRenderState(D3DRS_STENCILENABLE, true);
	GET_DEVICE()->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	GET_DEVICE()->SetRenderState(D3DRS_STENCILREF, 0);
	GET_DEVICE()->SetRenderState(D3DRS_STENCILMASK, UINT_MAX);
	GET_DEVICE()->SetRenderState(D3DRS_STENCILWRITEMASK, UINT_MAX);
	GET_DEVICE()->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	GET_DEVICE()->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	GET_DEVICE()->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

	/** VS Input */� ���¸� �����Ѵ�
	GET_DEVICE()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	GET_DEVICE()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GET_DEVICE()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void CRenderObject::doDrawShadow(void)
{
	// Do Nothing
}

void CRenderObject::postDrawShadow(void)
{
	// ���ٽ�, ���� ����带 ��Ȱ��ȭ�Ѵ�
	GET_DEVICE()->SetRenderState(D3DRS_STENCILENABLE, false);
	GET_DEVICE()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

LPD3DXMESH CRenderObject::createShadowMesh(void)
{
	auto pMesh = GET_MESH(NAME_DEFAULT_SHADOW_MESH);

	if(pMesh == nullptr)
	{
		LPD3DXBUFFER pAdjacency = nullptr;

		// �޽ø� �����Ѵ�
		D3DXCreateSphere(GET_DEVICE(),
			0.5f,
			10,
			10,
			&pMesh,
			&pAdjacency);

		/** VS Input */�� ����Ѵ�
		D3DXComputeNormals(pMesh, (DWORD*)(pAdjacency->GetBufferPointer()));

		SAFE_RELEASE(pAdjacency);
		GET_RESOURCE_MANAGER()->addMeshForKey(NAME_DEFAULT_SHADOW_MESH, pMesh);
	}

	return pMesh;
}
