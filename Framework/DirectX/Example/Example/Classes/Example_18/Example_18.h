#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

/*
���̴���?
:
������ ������������ ���� �ܰ� �߿� Ư�� �ܰ踦 Ŀ�����ϰ� �����ϴ� �����
���̴���� �Ѵ� (��, ������ ������������ �ܰ� �� ��� �ܰ踦 �����ϴ��Ŀ� ����
���̴��� ��Ī�� �ٸ���)

1. ���̴��� ����
:
���̴��� ������ ������������ Ư�� �ܰ踦 Ŀ�����ϰ� �����ϴ� ����� ���������ν�
������ 3 ���� �׷��� �����ӿ�ũ�� ���ϰ� �ִ� ������ ��� (�Ѱ�) �� ��� �� ��
�����ο� ���α׷��� ȯ���� �����Ѵ�

����, ���̴��� ���� ������ �̷л����θ� �����ߴ� ���� ��� �׷��� �������
������ �����ϴ� ���� �����ϴ� (Ex. �븻 ����, Specular ����, �׸��� ���� ���)

��������� ���̴��� ������ ���� �׷��� ȿ���� ������ �Ϳ� �ִ�

2. ���̴��� ����
:
���̴��� ����Ѵٴ� ���� ������ 3 ���� �׷��� �����ӿ�ũ�� ����������
ó�����־��� ������ ���������� ������ �ؾߵǱ� ������ ��Ȯ�� ���� ������ ����
���� ��� ��ġ �ʴ� ����� ��� �� �� �ۿ� ����

���̴��� ����ϱ� ���ؼ� �ʿ��� ����?
:
HLSL (High Level Shader Language) �� ���� �� ���̴��� �����ϴ� ��ɿ�
�ش��ϴ� ��ɾ �ۼ������ν� ���̴��� ����ϴ� ���� �����ϴ�

HLSL �� ���̷�Ʈ 3D ���� �����ϴ� ���̴��� �����ϱ����� ����̴�
(��, HLSL �� ���̷�Ʈ 3D ������ ����� �����ϸ� �ٸ� 3 ���� �׷��� �����ӿ�ũ����
���̴��� ����ϱ� ���ؼ��� �ش� �����ӿ�ũ���� �����ϴ� ���̴� �� ����ؾ��Ѵ�)

���̷�Ʈ 3D 9 �������� �����ϴ� ���̴��� ����
1. ���� ���̴�
2. �ȼ� ���̴�

1-1. ���� ���̴���?
:
3 ���� �� ��ü�� �����ϴ� ������ ������ 2 ���� �� �����ϱ� ���� ������ ��ġ��
�����ϴ� ����� �����ϴ� ���̴��̴� (��, ���� ���̴����� ����� ������ ��ġ��
����Ʈ ���꿡 ���ؼ� ���������� ȭ��� ��µȴ�)

2-1. �ȼ� ���̴���?
:
ȭ��� ��µǴ� �������� �ȼ��� ������ �����ϴ� ����� �����ϴ� ���̴��̴�
(��, �ȼ� ���̴����� ��µǴ� ������ ������ ���� Ÿ�ٿ� ��µȴ�)

���� ���� ���̴��� ���� ������ ������������ Ư�� �ܰ踦 Ŀ�����ϰ� ����Ǵ�
������ ������������ ���α׷��Ӻ� (Programmable) ������ �����������̶�� �Ѵ�

�ݴ�� ���̴��� ������� ���� ������ ����� �����ϴ� ������ ������������
���� (Fixed) ������ �����������̶�� �Ѵ�
*/
//! Example 18
class Example_18 : public CDirect3DApplication
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
	Example_18(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_18(void);

private:			// private �Լ�

	//! ���� ���۸� �����Ѵ�
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);

	//! �ε��� ���۸� �����Ѵ�
	LPDIRECT3DINDEXBUFFER9 createIndexBuffer(void);

	//! ���� ���̴��� �����Ѵ�
	LPDIRECT3DVERTEXSHADER9 createVertexShader(LPD3DXCONSTANTTABLE* a_pOutVariableTable);

	//! �ȼ� ���̴��� �����Ѵ�
	LPDIRECT3DPIXELSHADER9 createPixelShader(LPD3DXCONSTANTTABLE* a_pOutVariableTable);

private:			// private ����

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer = nullptr;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer = nullptr;
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;

	LPDIRECT3DVERTEXSHADER9 m_pVertexShader = nullptr;
	LPDIRECT3DPIXELSHADER9 m_pPixelShader = nullptr;

	LPD3DXCONSTANTTABLE m_pVertexVariable = nullptr;
	LPD3DXCONSTANTTABLE m_pPixelVariable = nullptr;
};
