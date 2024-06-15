#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

class CStaticMesh;

//! Example 31
class Example_31 : public CDirect3DApplication
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
	Example_31(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_31(void);

private:			// private �Լ�

	//! ���� �޽ø� �����Ѵ�
	CStaticMesh* createStaticMesh(void);

private:			// private ����

	CStaticMesh* m_pStaticMeshA = nullptr;
	CStaticMesh* m_pStaticMeshB = nullptr;
};
