#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

class CObject;

//! Example 14
class Example_14 : public CDirect3DApplication
{
public:

	//! ����
	struct STVertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
		};

		D3DXVECTOR3 m_stPosition;
		D3DCOLOR m_nColor;
	};

public:			// public �Լ�

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

	//! ȭ���� �׸���
	virtual void draw(void) override;

	//! ���ø����̼��� �ʱ�ȭ�Ѵ�
	virtual void initApplication(void) override;

public:			// ������

	//! ������
	Example_14(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_14(void);

private:			// private �Լ�

	//! ���� ���۸� �����Ѵ�
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);

	//! �ε��� ���۸� �����Ѵ�
	LPDIRECT3DINDEXBUFFER9 createIndexBuffer(void);

private:			// private ����

	float m_fRoll = 0.0f;
	float m_fPitch = 0.0f;
	float m_fPitchVelocity = 0.0f;

	CObject* m_pObject = nullptr;
	CObject* m_pChildObject = nullptr;
	CObject* m_pGrandChildObject = nullptr;

	CObject* m_pBodyObject = nullptr;
	CObject* m_pHeadObject = nullptr;

	CObject* m_pLeftArmObject = nullptr;
	CObject* m_pRightArmObject = nullptr;

	CObject* m_pLeftLegObject = nullptr;
	CObject* m_pRightLegObject = nullptr;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer = nullptr;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer = nullptr;
};
