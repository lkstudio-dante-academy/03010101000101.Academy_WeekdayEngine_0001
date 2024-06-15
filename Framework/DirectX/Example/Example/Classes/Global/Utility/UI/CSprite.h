#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CUIObject.h"

//! ��������Ʈ
class CSprite : public CUIObject
{
public:			// getter

	//! ũ�⸦ ��ȯ�Ѵ�
	virtual SIZE getSize(void) override;

public:			// public �Լ�

	//! �ʱ�ȭ
	virtual void init(void) override;

	//! UI �� �׸���
	virtual void doDrawUI(void) override;

public:			// ������, �Ҹ���

	//! ������
	CSprite(const std::string& a_rFilepath);

private:			// private ����

	SIZE m_stTextureSize;
	std::string m_oFilepath = "";

	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;
};
