#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

class CStaticMesh;

//! Example 24
class Example_24 : public CDirect3DApplication
{
public:			// public �Լ�

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

	//! ȭ���� �׸���
	virtual void draw(void) override;

	//! ���ø����̼��� �ʱ�ȭ�Ѵ�
	virtual void initApplication(void) override;

public:			// ������

	//! ������
	Example_24(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_24(void);

private:			// private �Լ�

	//! ���� �޽ø� �����Ѵ�
	CStaticMesh* createStaticMesh(void);

private:			// private ����

	CStaticMesh* m_pStaticMesh = nullptr;
};
