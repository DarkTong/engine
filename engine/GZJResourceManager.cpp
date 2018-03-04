#include "GZJResourceManager.h"

namespace GZJ_ENGINE {
	GZJResourceManager::GZJResourceManager(const String& resRoot)
	:_resRoot(resRoot){}
	GZJResourcePtr GZJResourceManager::CreateRes(const String & name, const String & path)
	{
		GZJResourcePtr resPtr = createImp(name, path);

		return resPtr;
	}
	GZJResourcePtr GZJResourceManager::FindResByName(const String & name)
	{
		GZJResourcePtr resPtr = resMap[name];
		return resPtr;
	}
	void GZJResourceManager::LoadAll()
	{
		for (auto it = resMap.begin(); it != resMap.end(); ++it)
			it->second->load();
	}
	void GZJResourceManager::LoadByName(const String & name)
	{
		auto it = resMap.find(name);
		if(it != resMap.end())
			it->second->load();
	}
	void GZJResourceManager::UnLoadAll()
	{
		for (auto it = resMap.begin(); it != resMap.end(); ++it)
			it->second->unload();
	}
	void GZJResourceManager::UnLoadByName(const String & name)
	{
		auto it = resMap.find(name);
		if (it != resMap.end())
			it->second->unload();
	}
}

