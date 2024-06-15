#include "Example_30.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CSkinnedMesh.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"

#define PICKING_TYPE_BOUNDING_BOX				1
#define PICKING_TYPE_BOUNDING_SPHERE			2

#define PICKING_TYPE			PICKING_TYPE_BOUNDING_BOX

Example_30::Example_30(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_30::~Example_30(void)
{
	SAFE_DELETE(m_pRenderObject);
}

void Example_30::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pRenderObject = CreateObject<CRenderObject>();
	m_pRenderObject->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pSkinnedMesh = this->createSkinnedMesh();
	m_pSkinnedMesh->setScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	m_pSkinnedMesh->setRotation(D3DXVECTOR3(0.0f, 90.0f, 0.0f));

	m_pRenderObject->addChildObject(m_pSkinnedMesh);

#if PICKING_TYPE == PICKING_TYPE_BOUNDING_BOX
	m_pSkinnedMesh->setDebugEnable(true, EDebugDrawType::BOX);
#else
	m_pSkinnedMesh->setDebugEnable(true, EDebugDrawType::SPHERE);
#endif			// #if PICKING_TYPE == PICKING_TYPE_BOUNDING_BOX

	auto oAnimationNameList = m_pSkinnedMesh->getAnimationNameList();
	m_pSkinnedMesh->playAnimation(oAnimationNameList[0], true);
}

void Example_30::update(void)
{
	CDirect3DApplication::update();
	m_pRenderObject->update();

	if(IS_KEY_DOWN(DIK_UP))
	{
		m_pRenderObject->moveByYAxis(10.0f * GET_DELTA_TIME(), false);
	}
	else if(IS_KEY_DOWN(DIK_DOWN))
	{
		m_pRenderObject->moveByYAxis(-10.0f * GET_DELTA_TIME(), false);
	}

	if(IS_KEY_DOWN(DIK_LEFT))
	{
		m_pRenderObject->moveByXAxis(-10.0f * GET_DELTA_TIME(), false);
	}
	else if(IS_KEY_DOWN(DIK_RIGHT))
	{
		m_pRenderObject->moveByXAxis(10.0f * GET_DELTA_TIME(), false);
	}

	if(IS_KEY_DOWN(DIK_Q))
	{
		m_pRenderObject->rotateByZAxis(90.0f * GET_DELTA_TIME(), false);
	}
	else if(IS_KEY_DOWN(DIK_E))
	{
		m_pRenderObject->rotateByZAxis(-90.0f * GET_DELTA_TIME(), false);
	}

	if(IS_MOUSE_BUTTON_PRESSED(EMouseButton::LEFT))
	{
		auto stRay = CreateRay(GET_MOUSE_POSITION());

#if PICKING_TYPE == PICKING_TYPE_BOUNDING_BOX
		auto stObjectBoundingBox = m_pSkinnedMesh->getObjectBoundingBox();
		auto stBoundingBox = ObjectBoxToBox(stObjectBoundingBox);

		if(IsIntersectRayBox(stBoundingBox, stRay))
		{
			printf("�浹\n");
		}
#else
		auto stBoundingSphere = m_pSkinnedMesh->getFinalBoundingSphere();

		if(IsIntersectRaySphere(stBoundingSphere, stRay))
		{
			printf("�浹\n");
		}
#endif
	}
}

void Example_30::draw(void)
{
	CDirect3DApplication::draw();
	m_pRenderObject->draw();
}

CSkinnedMesh* Example_30::createSkinnedMesh(void)
{
	CSkinnedMesh::STParameters stParameters = {
		"Resources/Meshes/WitchApprentice/WitchApprentice.x",
		"Resources/Effects/Example_29.fx",
		"Dummy_root"
	};

	return CreateObject<CSkinnedMesh>(stParameters);
}
