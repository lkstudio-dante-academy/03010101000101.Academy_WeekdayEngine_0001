#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

class CLabel;
class CButton;
class CSprite;

//! Example 17
class Example_17 : public CDirect3DApplication
{
public:			// public �Լ�

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

	//! UI ȭ���� �׸���
	virtual void drawUI(void) override;

	//! ���ø����̼��� �ʱ�ȭ�Ѵ�
	virtual void initApplication(void) override;

public:			// ������

	//! ������
	Example_17(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_17(void);

private:			// private �Լ�

	//! ��ư�� Ŭ������ ���
	void onClickButton(CButton* a_pSender);

private:			// private ����

	CLabel* m_pLabel = nullptr;
	CButton* m_pButton = nullptr;
	CSprite* m_pSprite = nullptr;
};
