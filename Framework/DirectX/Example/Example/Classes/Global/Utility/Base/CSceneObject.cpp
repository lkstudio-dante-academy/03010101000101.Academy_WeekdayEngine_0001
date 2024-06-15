#include "CSceneObject.h"
#include "CRenderObject.h"
#include "CUIObject.h"

void CSceneObject::draw(void)
{
	for(auto pChildObject : m_oChildObjectList)
	{
		auto pRenderObject = dynamic_cast<CRenderObject*>(pChildObject);

		if(pRenderObject != nullptr)
		{
			pRenderObject->draw();
		}
	}
}

void CSceneObject::drawUI(void)
{
	for(auto pChildObject : m_oChildObjectList)
	{
		auto pRenderObject = dynamic_cast<CUIObject*>(pChildObject);

		if(pRenderObject != nullptr)
		{
			pRenderObject->drawUI();
		}
	}
}
