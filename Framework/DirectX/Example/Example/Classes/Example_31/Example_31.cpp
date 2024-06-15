#include "Example_31.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CStaticMesh.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CInputManager.h"

#define COLLISION_CHECK_TYPE_OBB			1
#define COLLISION_CHECK_TYPE_AABB			2
#define COLLISION_CHECK_TYPE_SPHERE			3

#define COLLISION_CHECK_TYPE			COLLISION_CHECK_TYPE_SPHERE

Example_31::Example_31(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_31::~Example_31(void)
{
	SAFE_DELETE(m_pStaticMeshA);
	SAFE_DELETE(m_pStaticMeshB);
}

void Example_31::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pStaticMeshA = this->createStaticMesh();
	m_pStaticMeshA->setPosition(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
	m_pStaticMeshA->setScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));

	m_pStaticMeshB = this->createStaticMesh();
	m_pStaticMeshB->setPosition(D3DXVECTOR3(10.0f, 0.0f, 0.0f));
	m_pStaticMeshB->setScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));

#if COLLISION_CHECK_TYPE == COLLISION_CHECK_TYPE_SPHERE
	m_pStaticMeshA->setDebugEnable(true, EDebugDrawType::SPHERE);
	m_pStaticMeshB->setDebugEnable(true, EDebugDrawType::SPHERE);
#else
	m_pStaticMeshA->setDebugEnable(true, EDebugDrawType::BOX);
	m_pStaticMeshB->setDebugEnable(true, EDebugDrawType::BOX);
#endif			// #if COLLISION_CHECK_TYPE == COLLISION_CHECK_TYPE_SPHERE
}

void Example_31::update(void)
{
	CDirect3DApplication::update();

	m_pStaticMeshA->update();
	m_pStaticMeshB->update();

	if(IS_KEY_DOWN(DIK_UP))
	{
		m_pStaticMeshA->moveByZAxis(10.0f * GET_DELTA_TIME(), false);
	}
	else if(IS_KEY_DOWN(DIK_DOWN))
	{
		m_pStaticMeshA->moveByZAxis(-10.0f * GET_DELTA_TIME(), false);
	}

	if(IS_KEY_DOWN(DIK_LEFT))
	{
		m_pStaticMeshA->moveByXAxis(-10.0f * GET_DELTA_TIME(), false);
	}
	else if(IS_KEY_DOWN(DIK_RIGHT))
	{
		m_pStaticMeshA->moveByXAxis(10.0f * GET_DELTA_TIME(), false);
	}

	if(IS_KEY_DOWN(DIK_Q))
	{
		m_pStaticMeshA->rotateByYAxis(-90.0f * GET_DELTA_TIME());
	}
	else if(IS_KEY_DOWN(DIK_E))
	{
		m_pStaticMeshA->rotateByYAxis(90.0f * GET_DELTA_TIME());
	}

#if COLLISION_CHECK_TYPE == COLLISION_CHECK_TYPE_OBB || COLLISION_CHECK_TYPE == COLLISION_CHECK_TYPE_AABB
	auto stObjectBoundingBoxA = m_pStaticMeshA->getObjectBoundingBox();
	auto stObjectBoundingBoxB = m_pStaticMeshB->getObjectBoundingBox();

#if COLLISION_CHECK_TYPE == COLLISION_CHECK_TYPE_OBB
	if(IsIntersectObjectBox(stObjectBoundingBoxA, stObjectBoundingBoxB))
	{
		printf("�浹\n");
	}
#else
	auto stBoundingBoxA = ObjectBoxToBox(stObjectBoundingBoxA);
	auto stBoundingBoxB = ObjectBoxToBox(stObjectBoundingBoxB);

	if(IsIntersectBox(stBoundingBoxA, stBoundingBoxB))
	{
		printf("�浹\n");
	}
#endif			// #if COLLISION_CHECK_TYPE == COLLISION_CHECK_TYPE_OBB
#else
	auto stBoundingSphereA = m_pStaticMeshA->getFinalBoundingSphere();
	auto stBoundingSphereB = m_pStaticMeshB->getFinalBoundingSphere();

	if(IsIntersectSphere(stBoundingSphereA, stBoundingSphereB))
	{
		printf("�浹\n");
	}
#endif			// #if COLLISION_CHECK_TYPE == COLLISION_CHECK_TYPE_OBB || COLLISION_CHECK_TYPE == COLLISION_CHECK_TYPE_AABB
}

void Example_31::draw(void)
{
	CDirect3DApplication::draw();

	m_pStaticMeshA->draw();
	m_pStaticMeshB->draw();
}

CStaticMesh* Example_31::createStaticMesh(void)
{
	CStaticMesh::STParameters stParameters = {
		"Resources/Meshes/GunShip/GunShip.x",
		"Resources/Effects/Example_24.fx"
	};

	return CreateObject<CStaticMesh>(stParameters);
}
