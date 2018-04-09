#include "GZJTextureManager.h"

namespace GZJ_ENGINE {
	GZJTextureManagerPtr GZJTextureManager::_instance = nullptr;

	GZJTextureManager::GZJTextureManager()
	{
		assert(_instance == nullptr);
	}

	GZJTextureManager::~GZJTextureManager()
	{
	}

	void GZJTextureManager::StartUp()
	{
		resMap.clear();
		resHandleMap.clear();
		resHandle = 0;

		_resRoot = ENGINE_SRC_ROOT_PATH + "\\texture";
	}

	void GZJTextureManager::ShutDown()
	{
		resMap.clear();
		resHandleMap.clear();
		resHandle = 1;
	}

	void GZJTextureManager::PrepareAll()
	{
		// 外部不调用这个函数
		cout << ("Can't use this funciotn in Texture Manager!") << endl;
		return;
	}

	void GZJTextureManager::LoadAll()
	{
		// 外部不调用次方法
		cout << ("Can't use this funciotn in Texture Manager!") << endl;
		return;
	}

	void GZJTextureManager::UnLoadAll()
	{
		cout << ("Can't use this funciotn in Texture Manager!") << endl;
		return;
	}

	GZJResource* GZJTextureManager::createImp(const String & name)
	{
		GZJResourceManager* mgr = static_cast<GZJResourceManager*>(this);
		return (new GZJTexture(mgr, name, resHandle++));
	}

}
