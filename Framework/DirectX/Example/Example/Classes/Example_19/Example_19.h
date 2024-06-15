#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

/*
����Ʈ �����ӿ�ũ��?
:
3 ���� ��ü�� �׸��� ���ؼ� ����Ǵ� �������� ���� ���� ���� ���·� �����Ͽ�
���� �� ���� �� �� �ִ� ����� �ǹ��Ѵ�

����Ʈ �����ӿ�ũ Ư¡
:
1. ����Ʈ �����ӿ�ũ�� �⺻������ ��ũ���̶�� �׷����� �������� ���� ���� �׷�ȭ
��Ű�� ���� �����ϴ� (��, �ϵ���� ��翡 ���� �������� ��ũ���� ���� �� �� �ִ�)

2. ����Ʈ �����ӿ�ũ�� 3 ���� ��ü�� �׸��� ���� ���� �ܰ踦 �н��� ���ؼ� �����ϴ�
���� �����ϴ� (��, �ϳ��� ��ü�� �׸��� ���� �۾��� �� �н��� �л� ��ų �� �ִ�)

3. ����Ʈ �����ӿ�ũ�� ����ϸ� ������ ��� ���̺� ���� �����ϰ� ���̴��� ��� ������
���� �����ϴ� ���� �����ϴ�

����Ʈ �����ӿ�ũ�� ���� ���� ������ ��ǥ���� ����
:
1. ���� ���̴� ����
2. �ȼ� ���̴� ����
3. ���� ���� ����

1-1 & 2-1. ����Ʈ �����ӿ�ũ�� ����ϸ� �����ϰ� ���� �� �ȼ� ���̴��� �����ϴ� ����
���� �� �Ӹ� �ƴ϶� ���̴� �ڵ带 �Ｎ���� �ۼ� �� ������ �ϴ� ���� �����ϴ�

3-1. ����Ʈ �����ӿ�ũ�� ����ϸ� ���� ���¸� �����ϰ� ������ �� ���� �Ӹ� �ƴ϶�
������ ���¸� �ٽ� �ǵ����� �ʾƵ� �ȴ� (��, ���������� ������ ���� ���´� �ٽ�
������ �������� �ǵ�������)
*/
//! Example 19
class Example_19 : public CDirect3DApplication
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
	Example_19(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_19(void);

private:			// private �Լ�

	//! ���� ���۸� �����Ѵ�
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);

	//! �ε��� ���۸� �����Ѵ�
	LPDIRECT3DINDEXBUFFER9 createIndexBuffer(void);

private:			// private ����

	LPD3DXEFFECT m_pEffect = nullptr;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer = nullptr;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer = nullptr;
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;
};
