#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

//! Example 11
class Example_11 : public CDirect3DApplication
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
	Example_11(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_11(void);

private:			// private �Լ�

	//! ���� ���۸� �����Ѵ�
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);

	//! �ε��� ���۸� �����Ѵ�
	LPDIRECT3DINDEXBUFFER9 createIndexBuffer(void);

private:			// private ����

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer = nullptr;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer = nullptr;
};
