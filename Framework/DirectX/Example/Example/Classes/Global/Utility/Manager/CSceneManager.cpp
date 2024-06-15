#include "CSceneManager.h"
#include "CScheduleManager.h"
#include "../Base/CSceneObject.h"

CSceneManager::~CSceneManager(void)
{
	SAFE_DELETE(m_pSceneObject);
}

CSceneObject* CSceneManager::getSceneObject(void)
{
	return m_pSceneObject;
}

void CSceneManager::setSceneObject(CSceneObject* a_pSceneObject)
{
	m_pSceneObject = a_pSceneObject;
}
