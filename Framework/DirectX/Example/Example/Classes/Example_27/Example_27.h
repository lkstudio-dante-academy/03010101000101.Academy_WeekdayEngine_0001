#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

class CSkybox;

//! Example 27
class Example_27 : public CDirect3DApplication
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
	Example_27(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

private:			// private �Լ�

	//! ��ī�� �ڽ��� �����Ѵ�
	CSkybox* createSkybox(void);
};
