#include "GZJModelManager.h"

namespace GZJ_ENGINE {

	GZJModelManager::GZJModelManager()
	{
		_resRoot = ENGINE_SRC_ROOT_PATH + "\\model";
	}

	GZJModelManager::~GZJModelManager()
	{
	}

	void GZJModelManager::StartUp()
	{
		resMap.clear();
		resHandleMap.clear();

		PrepareAll();
	}

	void GZJModelManager::ShutDown()
	{
		UnLoadAll();
	}

	void GZJModelManager::PrepareAll()
	{
	}

	GZJResource * GZJModelManager::createImp(const String & name)
	{
		GZJResourceManager* tmp = static_cast<GZJResourceManager*>(this);
		return (new GZJModel(tmp, name, resHandle));
	}

}
