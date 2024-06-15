#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

class CObject;

/*
������?
:
3 ���� �����󿡼� ī�޶��� ��ġ�� �ֽ��ϴ� ��ü�� ������� �Ѵ�
(��, ������ �׻� ī�޶� �ٷκ��� �־���Ѵ�)

������� ����
:
1. ��ü �����
2. Y �� �����

1-1. ��ü ������� Ư¡
:
��ü ������ ���带 �������� ī�޶��� ��ġ�� ���� ��ü�� ���� ���� ��� ��ȭ ��
����带 �ǹ��Ѵ� (��, ī�޶� �ٶ󺸴� �������� ��ü�� ȸ���ȴ�)

2-1. Y �� ������� Ư¡
:
Y �� ������ ī�޶� �ֽ��ϱ� ���� ��ü�� ���� ���� ��� ��ȭ�Ǵ� ��ü �����ʹ�
�޸� Y ���� �׻� ������ Y ��� ��ġ�� ����带 �ǹ��Ѵ�

���� ������?
:
3 ���� ��ü�� ���� ���� �� ���� ���� �̿��ؼ� ������ ������� ����ϴ� ����� �ǹ��Ѵ�
(��, ���� ����带 Ȱ���ϸ� ���� ���� ���� ������ ȥ���ϴ� ���� �����ϴ�)
*/
//! Example 22
class Example_22 : public CDirect3DApplication
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
	Example_22(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_22(void);

private:			// private �Լ�

	//! ���� ���۸� �����Ѵ�
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);

	//! �ε��� ���۸� �����Ѵ�
	LPDIRECT3DINDEXBUFFER9 createIndexBuffer(void);

private:			// private ����

	float m_fOpacity = 0.0f;
	LPD3DXEFFECT m_pEffect = nullptr;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer = nullptr;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer = nullptr;
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;

	CObject* m_pObject = nullptr;
};
