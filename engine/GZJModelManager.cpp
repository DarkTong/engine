#include "GZJModelManager.h"

namespace GZJ_ENGINE {
	GZJModelManagerPtr GZJModelManager::_instance = nullptr;
	GZJModelManagerPtr GZJModelManager::GetInstance()
	{
		if (_instance == nullptr)
			_instance = MakeShared<GZJModelManager>();
		return _instance;
	}
	GZJModelManager::GZJModelManager()
	{
		if (_instance != nullptr)
		{
			cout << "Can't create GZJModelManager twice!!!" << endl;
			assert(false);
		}
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
