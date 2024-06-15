#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

class CObject;

/*
�ؽ�ó��?
:
�ؽ�ó�� �׷��� ī�忡�� ���Ǵ� ���ҽ� (�ڿ�) �� �ǹ��Ѵ�
(��, �ؽ�ó�� ��� ������ �����Ͱ� �����Ǵ��Ŀ� ���� �ؽ�ó�� ��Ī�ϴ�
�� �ٸ���)

���̷�Ʈ 3D 9 �������� �ؽ�ó�� ����ϴ� ���
:
���̷�Ʈ 3D 9 �������� �ؽ�ó�� LPDIRECT3DTEXTURE9 ���� �����ϴ� ���� �����ϴ�
����, �ؽ�ó�� ȭ��� ����ϱ� ���ؼ��� ���� ������ UV ��ǥ ������ ���ԵǾ�
�־�� �Ѵ�

UV ��ǥ��?
:
0 ~ 1 �� ������ ���ϴ� 2 ������ ��ǥ�� ���̷�Ʈ 3D �� ��ǥ��ʹ� �޸�
�»���� �������� �Ѵ� (��, UV ��ǥ�� ������ ���� �ؽ�ó�� ��ü �Ǵ� �Ϻθ�
����ϴ� ���� �����ϴ�)
*/
//! Example 16
class Example_16 : public CDirect3DApplication
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
	Example_16(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_16(void);

private:			// private �Լ�

	//! ���� ���۸� �����Ѵ�
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);

	//! �ε��� ���۸� �����Ѵ�
	LPDIRECT3DINDEXBUFFER9 createIndexBuffer(void);

private:			// private ����

	POINT m_stPrevMousePosition;
	CObject* m_pObject = nullptr;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer = nullptr;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer = nullptr;
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;
};
