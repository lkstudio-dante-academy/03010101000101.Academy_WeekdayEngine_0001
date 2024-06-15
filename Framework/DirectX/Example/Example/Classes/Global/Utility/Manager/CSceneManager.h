#pragma once

#include "../../Define/KGlobalDefine.h"

class CSceneObject;

//! �� ������
class CSceneManager
{
public:			// getter, setter

	//! �� ��ü�� ��ȯ�Ѵ�
	CSceneObject* getSceneObject(void);

	//! �� ��ü�� �����Ѵ�
	void setSceneObject(CSceneObject* a_pSceneObject);

public:			// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CSceneManager);

private:			// �Ҹ���

	//! �Ҹ���
	virtual ~CSceneManager(void);

private:			// private ����

	CSceneObject* m_pSceneObject = nullptr;
};
