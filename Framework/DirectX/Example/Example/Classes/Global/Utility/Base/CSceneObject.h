#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IRenderable.h"
#include "CObject.h"

//! �� ��ü
class CSceneObject : public CObject,
	public IRenderable
{
public:			// �������̽� ����

	//! ȭ���� �׸���
	virtual void draw(void) final override;

	//! UI ȭ���� �׸���
	virtual void drawUI(void) final override;
};
