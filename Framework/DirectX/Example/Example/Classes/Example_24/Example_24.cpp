#include "Example_24.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CStaticMesh.h"
#include "../Global/Utility/Manager/CDeviceManager.h"

Example_24::Example_24(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_24::~Example_24(void)
{
	SAFE_DELETE(m_pStaticMesh);
}

void Example_24::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pStaticMesh = this->createStaticMesh();
	m_pStaticMesh->setScale(D3DXVECTOR3(0.15f, 0.15f, 0.15f));
}

void Example_24::update(void)
{
	CDirect3DApplication::update();
	m_pStaticMesh->update();
}

void Example_24::draw(void)
{
	CDirect3DApplication::draw();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);

	m_pStaticMesh->draw();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
}

CStaticMesh* Example_24::createStaticMesh(void)
{
	CStaticMesh::STParameters stParameters = {
		"Resources/Meshes/Elementalist/Elementalist.x",
		"Resources/Effects/Example_24.fx"
	};

	return CreateObject<CStaticMesh>(stParameters);
}
