#include "../Define/KGlobalDefine.h"
#include "GlobalFunction.h"

template<typename T, typename ...ARGS>
T* CreateObject(ARGS && ...args)
{
	auto pObject = new T(args...);
	pObject->init();
	pObject->lateInit();

	return pObject;
}

template<typename T, typename ...ARGS>
T* CreateInstance(ARGS && ...args)
{
	return new T(args...);
}
