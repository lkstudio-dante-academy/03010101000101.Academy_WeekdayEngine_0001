#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! ���� ��ü
class CObject : public IUpdateable
{
public:			// �������̽� ����

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// getter, setter

	//! ��ġ�� ��ȯ�Ѵ�
	virtual D3DXVECTOR3 getPosition(void);

	//! ô���� ��ȯ�Ѵ�
	virtual D3DXVECTOR3 getScale(void);

	//! X �� ������ ��ȯ�Ѵ�
	virtual D3DXVECTOR3 getRightDirection(void);

	//! Y �� ������ ��ȯ�Ѵ�
	virtual D3DXVECTOR3 getUpDirection(void);

	//! Z �� ������ ��ȯ�Ѵ�
	virtual D3DXVECTOR3 getForwardDirection(void);

	//! ���� ����� ��ȯ�Ѵ�
	virtual D3DXMATRIXA16 getWorldMatrix(void);

	//! ���� ���� ����� ��ȯ�Ѵ�
	virtual D3DXMATRIXA16 getFinalWorldMatrix(void);

	//! �θ� ��ü�� ��ȯ�Ѵ�
	virtual CObject* getParentObject(void);

	//! �ڽ� ��ü ����Ʈ�� ��ȯ�Ѵ�
	virtual std::vector<CObject*> getChildObjectList(void);

	//! ��ġ�� �����Ѵ�
	virtual void setPosition(const D3DXVECTOR3& a_rstPosition);

	//! ô���� �����Ѵ�
	virtual void setScale(const D3DXVECTOR3& a_rstScale);

	//! ȸ���� �����Ѵ�
	virtual void setRotation(const D3DXVECTOR3& a_rstRotation);

	//! ������ ����� �����Ѵ�
	virtual void setOffsetMatrix(const D3DXMATRIXA16& a_rstOffsetMatrix);

	//! �߰� ���� ����� �����Ѵ�
	virtual void setExtraWorldMatrix(const D3DXMATRIXA16& a_rstExtraWorldMatrix);

	//! �θ� ��ü�� �����Ѵ�
	virtual void setParentObject(CObject* a_pParentObject);

public:			// public �Լ�

	//! �ʱ�ȭ
	virtual void init(void);

	//! ���� �ʱ�ȭ
	virtual void lateInit(void);

	//! �ڽ� ��ü�� �߰��Ѵ�
	virtual void addChildObject(CObject* a_pChildObject);

	//! �ڽ� ��ü�� �����Ѵ�
	virtual void removeChildObject(CObject* a_pChildObject);

	//! X ������ �̵��Ѵ�
	virtual void moveByXAxis(float a_fOffset, bool a_bIsLocal = true);

	//! Y ������ �̵��Ѵ�
	virtual void moveByYAxis(float a_fOffset, bool a_bIsLocal = true);

	//! Z ������ �̵��Ѵ�
	virtual void moveByZAxis(float a_fOffset, bool a_bIsLocal = true);

	//! X ������ ȸ���Ѵ�
	virtual void rotateByXAxis(float a_fAngle, bool a_bIsLocal = true);

	//! Y ������ ȸ���Ѵ�
	virtual void rotateByYAxis(float a_fAngle, bool a_bIsLocal = true);

	//! Z ������ ȸ���Ѵ�
	virtual void rotateByZAxis(float a_fAngle, bool a_bIsLocal = true);

	//! �ش� ��ġ�� ȸ���Ѵ�
	virtual void rotateByPosition(const D3DXVECTOR3& a_rstPosition, bool a_bIsSphere = true);

	//! �ش� �������� ȸ���Ѵ�
	virtual void rotateByDirection(const D3DXVECTOR3& a_rstDirection, bool a_bIsSphere = true);

	//! �ش� ��ķ� ȸ���Ѵ�
	virtual void rotateByMatrix(const D3DXMATRIXA16& a_rstMatrix);

	//! ���� ���¸� �����Ѵ�
	virtual void updateDirections(void);

public:			// ������, �Ҹ���

	//! ������
	CObject(void);

	//! �Ҹ���
	virtual ~CObject(void);

protected:			// protected ����

	CObject* m_pParentObject = nullptr;
	std::vector<CObject*> m_oChildObjectList;

	D3DXVECTOR3 m_stPosition;
	D3DXVECTOR3 m_stScale;

	D3DXVECTOR3 m_stRightDirection;
	D3DXVECTOR3 m_stUpDirection;
	D3DXVECTOR3 m_stForwardDirection;

	D3DXMATRIXA16 m_stWorldMatrix;
	D3DXMATRIXA16 m_stOffsetMatrix;
	D3DXMATRIXA16 m_stExtraWorldMatrix;
};
