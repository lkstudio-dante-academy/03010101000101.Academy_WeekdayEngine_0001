#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

//! ���� �޽�
class CStaticMesh : public CRenderObject
{
public:

	//! �Ű�����
	struct STParameters
	{
		std::string m_oMeshFilepath;
		std::string m_oEffectFilepath;
	};

public:			// public �Լ�

	//! �ʱ�ȭ
	virtual void init(void) override;

	//! ���� �ʱ�ȭ
	virtual void lateInit(void) override;

	//! ��ü�� �׸���
	virtual void doDrawObject(void) override;

	//! ��ü�� �׷��� ���
	virtual void postDrawObject(void) override;

	//! �׸��ڸ� �׸���
	virtual void doDrawShadow(void) override;

public:			// ������

	//! ������
	CStaticMesh(const STParameters& a_rstParameters);

private:			// private �Լ�

	//! ���� �޽ø� �׸���
	void drawStaticMesh(const D3DXMATRIXA16& a_rstMatrix, bool a_bIsDrawingShadow = false);

private:			// private ����

	LPD3DXEFFECT m_pEffect = nullptr;

	STParameters m_stParameters;
	STStaticMesh m_stStaticMesh;
};
