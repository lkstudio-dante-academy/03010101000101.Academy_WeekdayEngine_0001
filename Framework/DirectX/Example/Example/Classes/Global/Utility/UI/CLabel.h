#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CUIObject.h"

//! �� ��ü
class CLabel : public CUIObject
{
public:			// getter, setter

	//! ũ�⸦ ��ȯ�Ѵ�
	virtual SIZE getSize(void) override;

	//! ���ڿ��� �����Ѵ�
	void setString(const std::string& a_rString);

public:			// public �Լ�

	//! �ʱ�ȭ
	virtual void init(void) override;

	//! UI �� �׸���
	virtual void doDrawUI(void) override;

public:			// ������

	//! ������
	CLabel(const std::string& a_rString, int a_nFontSize);

	//! �Ҹ���
	virtual ~CLabel(void);

private:			// private ����

	int m_nFontSize = 0;
	std::string m_oString;

	LPD3DXFONT m_pFont = nullptr;
};
