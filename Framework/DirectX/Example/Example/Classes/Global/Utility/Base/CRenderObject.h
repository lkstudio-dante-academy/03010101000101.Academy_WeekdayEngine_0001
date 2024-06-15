#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IRenderable.h"
#include "CObject.h"

class CDebugDraw;

//! ���� ��ü
class CRenderObject : public CObject,
	public IRenderable
{
public:			// �������̽� ����

	//! ȭ���� �׸���
	virtual void draw(void) final override;

public:			// getter, setter

	//! ��� ���� ����� ��ȯ�Ѵ�
	virtual D3DXMATRIXA16 getBoundingWorldMatrix(void);

	//! ��� ������ ��ȯ�Ѵ�
	virtual STBoundingBox getBoundingBox(void);

	//! ��ü ��� ������ ��ȯ�Ѵ�
	virtual STObjectBoundingBox getObjectBoundingBox(void);

	//! ��� ���� ��ȯ�Ѵ�
	virtual STBoundingSphere getBoundingSphere(void);

	//! ���� ��� ������ ��ȯ�Ѵ�
	virtual STBoundingBox getFinalBoundingBox(void);

	//! ���� ��� ���� ��ȯ�Ѵ�
	virtual STBoundingSphere getFinalBoundingSphere(void);

	//! �׸��� ���θ� �����Ѵ�
	virtual void setVisible(bool a_bIsVisible);

	//! ����� ���θ� �����Ѵ�
	virtual void setDebugEnable(bool a_bIsDebugEnable, EDebugDrawType a_eDebugDrawType = EDebugDrawType::SPHERE);

	//! �׸��� ���θ� �����Ѵ�
	virtual void setShadowEnable(bool a_bIsShadowEnable, EShadowType a_eShadowType = EShadowType::PROJECTION);

	//! �׸��� ������ �����Ѵ�
	virtual void setShadowMaterial(const D3DMATERIAL9& a_rstShadowMaterial);

	//! �׸��� ����� �����Ѵ�
	virtual void setShadowMatrix(const D3DXMATRIXA16& a_rstShadowMatrix);

	//! ��� ������ �����Ѵ�
	virtual void setBoundingBox(const STBoundingBox& a_rstBoundingBox);

	//! ��� ���� �����Ѵ�
	virtual void setBoundingSphere(const STBoundingSphere& a_rstBoundingSphere);

public:			// ������, �Ҹ���

	//! ������
	CRenderObject(void);

	//! �Ҹ���
	virtual ~CRenderObject(void);

protected:			// protected �Լ�

	//! ��ü�� �׸� ���
	virtual void preDrawObject(void);

	//! ��ü�� �׸���
	virtual void doDrawObject(void);

	//! ��ü�� �׷��� ���
	virtual void postDrawObject(void);

	//! �׸��ڸ� �׸� ���
	virtual void preDrawShadow(void);

	//! �׸��ڸ� �׸���
	virtual void doDrawShadow(void);

	//! �׸��ڸ� �׷��� ���
	virtual void postDrawShadow(void);

	//! �׸��� �޽ø� �����Ѵ�
	virtual LPD3DXMESH createShadowMesh(void);

protected:			// protected ����

	bool m_bIsVisible = false;
	bool m_bIsDebugEnable = false;
	bool m_bIsShadowEnable = false;

	STBoundingBox m_stBoundingBox;
	STBoundingSphere m_stBoundingSphere;

	CDebugDraw* m_pDebugDraw = nullptr;

	LPD3DXMESH m_pShadowMesh = nullptr;
	EShadowType m_eShadowType = EShadowType::NONE;
	D3DMATERIAL9 m_stShadowMaterial;
	D3DXMATRIXA16 m_stShadowMatrix;
};
