#include "GZJResourceManager.h"

namespace GZJ_ENGINE {
	GZJResourceManager::GZJResourceManager(){
		resHandle = 1;
	}
	GZJResourceManager::~GZJResourceManager()
	{
	}
	GZJResourcePtr GZJResourceManager::CreateRes(const String & name)
	{
		GZJResourcePtr l_resPtr = GZJResourcePtr(createImp(name));
		resMap[name] = l_resPtr;
		resHandleMap[resHandle] = l_resPtr;
		resHandle++;

		return l_resPtr;
	}
	GZJResourcePtr GZJResourceManager::FindResByName(const String & name)
	{
		GZJResourcePtr resPtr = resMap[name];
		if (resPtr == nullptr) {
			resPtr = CreateRes(name);
		}
		return resPtr;
	}
	GZJResourcePtr GZJResourceManager::FindResByHandle(const ResourceHandle & handle)
	{
		if (handle > 0 and handle < resHandle)
		{
			return resHandleMap[handle];
		}
		return nullptr;
	}
	void GZJResourceManager::LoadAll(bool isAsyncLoad)
	{
		if(isAsyncLoad)
			for (auto it = resMap.begin(); it != resMap.end(); ++it)
				it->second->AsyncLoad();
		else
			for (auto it = resMap.begin(); it != resMap.end(); ++it)
				it->second->SyncLoad();
	}
	void GZJResourceManager::LoadByName(const String & name)
	{
		auto it = resMap.find(name);
		if(it != resMap.end())
			it->second->SyncLoad();
		else
			std::cout << ("WRONG:not include resource :") << name << std::endl;
	}
	void GZJResourceManager::UnLoadAll()
	{
		for (auto it = resMap.begin(); it != resMap.end(); ++it)
		{
			std::cout << it->first << std::endl;
			if(resMap[it->first] != nullptr)
				it->second->UnLoad();
			else
				std::cout << "error resource unloadAll nullptr" << std::endl;
		}
		resMap.clear();
		resHandleMap.clear();
	}
	void GZJResourceManager::UnLoadByName(const String & name)
	{
		auto it = resMap.find(name);
		if (it != resMap.end())
			it->second->UnLoad();
		else
			std::cout << ("WRONG:not include resource :") << name << std::endl;

	}
	bool GZJResourceManager::IsLoad(const String& name)
	{
		auto it = resMap.find(name);
		return it != resMap.end();
	}
	String GZJResourceManager::GetResRoot()
	{
		return _resRoot;
	}
	ResourceHandle GZJResourceManager::GetNextHandle()
	{
		return resHandle;
	}
	//GZJResourceManagerPtr GZJResourceManager::GetSelf() const
	//{
	//	return self;
	//}
}

