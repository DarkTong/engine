#include "GZJResourceManager.h"

namespace GZJ_ENGINE {
	GZJResourceManager::GZJResourceManager(){}
	GZJResourceManager::~GZJResourceManager()
	{
	}
	GZJResourcePtr GZJResourceManager::CreateRes(const String & name)
	{
		GZJResourcePtr l_resPtr = GZJResourcePtr(createImp(name));
		resMap.insert(Pair<String, GZJResourcePtr>(name, l_resPtr));
		resHandleMap.insert(Pair<ResourceHandle, GZJResourcePtr>(resHandle, l_resPtr));
		resHandle++;

		return l_resPtr;
	}
	GZJResourcePtr GZJResourceManager::FindResByName(const String & name)
	{
		GZJResourcePtr resPtr = resMap[name];
		if (resPtr == nullptr) {
			resPtr = CreateRes(name);
			resMap.insert(Pair<String, GZJResourcePtr>(name, resPtr));
		}
		return resPtr;
	}
	void GZJResourceManager::LoadAll()
	{
		for (auto it = resMap.begin(); it != resMap.end(); ++it)
			it->second->Load();
	}
	void GZJResourceManager::LoadByName(const String & name)
	{
		auto it = resMap.find(name);
		if(it != resMap.end())
			it->second->Load();
		else
			std::cout << ("WRONG:not include resource :") << name << std::endl;
	}
	void GZJResourceManager::UnLoadAll()
	{
		for (auto it = resMap.begin(); it != resMap.end(); ++it)
		{
			std::cout << it->first << std::endl;
			if(resMap[it->first] != nullptr)
				it->second->Unload();
			else
				std::cout << "error shader unloadAll nullptr" << std::endl;
		}
		resMap.clear();
	}
	void GZJResourceManager::UnLoadByName(const String & name)
	{
		auto it = resMap.find(name);
		if (it != resMap.end())
			it->second->Unload();
		else
			std::cout << ("WRONG:not include resource :") << name << std::endl;

	}
	String GZJResourceManager::GetResRoot()
	{
		return _resRoot;
	}
}

