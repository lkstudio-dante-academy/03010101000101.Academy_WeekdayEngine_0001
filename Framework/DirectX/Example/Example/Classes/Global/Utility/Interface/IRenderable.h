#pragma once

#include "../../Define/KGlobalDefine.h"

//! �׸��� �������̽�
class IRenderable
{
public:			// �������̽�

	//! ȭ���� �׸���
	virtual void draw(void) = 0;

	//! UI ȭ���� �׸���
	virtual void drawUI(void) { }
};
