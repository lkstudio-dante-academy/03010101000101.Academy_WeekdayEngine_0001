#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

/*
�� ���̵��̶�?
:
���� ���⿡ ���� �߻��ϴ� ������ �ܰ踦 Ư�� ������ ���ȭ ���Ѽ� ��ȭ��
���� ȿ���� ����ϴ� �׷��� ����� �ǹ��Ѵ�

UV �ִϸ��̼��̶�?
:
UV ��ǥ�� ��ȭ���Ѽ� Ư���� ȿ���� �����ϴ� �ִϸ��̼� ����� �ǹ��Ѵ�
(��, ���������� UV ��ǥ�� �ؽ�ó ��巹�� ��带 Ȱ���ؼ� ȿ���� �����Ѵ�)
*/
//! Example 21
class Example_21 : public CDirect3DApplication
{
public:

	//! ����
	struct STVertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
		};

		D3DXVECTOR3 m_stPosition;
		D3DXVECTOR3 m_stNormal;
		D3DXVECTOR2 m_stUV;
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
	Example_21(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_21(void);

private:			// private �Լ�

	//! ���� ���۸� �����Ѵ�
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);

	//! �ε��� ���۸� �����Ѵ�
	LPDIRECT3DINDEXBUFFER9 createIndexBuffer(void);

private:			// private ����

	float m_fOffset = 0.0f;

	bool m_bIsToonShading = false;
	LPD3DXEFFECT m_pEffect = nullptr;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer = nullptr;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer = nullptr;
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;
};
