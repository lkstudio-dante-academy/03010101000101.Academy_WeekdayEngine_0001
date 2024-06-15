#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

/*
�׷��� �������̶�?
:
3 ���� ��ü�� ���� ���� (R, G, B) �� ���� ������ �����ؼ� ȸ���� �������� ��ȭ ��
����� �ǹ��Ѵ�

�ؽ�ó Ÿ�ϸ��̶�?
:
3 ���� ��ü�� ������ �ؽ�ó�� ���� ��Ģ�� ���� �ݺ��Ǵ� �������� �ؽ�ó��
������ �׷��� ����� �ǹ��Ѵ�
*/
//! Example 20
class Example_20 : public CDirect3DApplication
{
public:

	//! ����
	struct STVertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_TEX1
		};

		D3DXVECTOR3 m_stPosition;
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
	Example_20(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_20(void);

private:			// private �Լ�

	//! ���� ���۸� �����Ѵ�
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);

	//! �ε��� ���۸� �����Ѵ�
	LPDIRECT3DINDEXBUFFER9 createIndexBuffer(void);

private:			// private ����

	float m_fTileSizeX = 0.0f;
	float m_fTileSizeY = 0.0f;

	bool m_bIsGrayscale = false;
	LPD3DXEFFECT m_pEffect = nullptr;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer = nullptr;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer = nullptr;
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;
};
