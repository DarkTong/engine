#include "GZJMeshManager.h"

namespace GZJ_ENGINE {
	GZJMeshManager::GZJMeshManager()
	{
		_resRoot = ENGINE_ROOT_PATH + "\\mesh";
	}

	GZJMeshManager::~GZJMeshManager(){
		
	}

	GZJResource* GZJMeshManager::createImp(const String& name) {
		// todo
		// 用于实现具体的资源创建
		// 调用Mesh的构造
		GZJResourceManager* tmp = static_cast<GZJResourceManager*>(this);
		return (new GZJMesh(tmp, name, resHandle++));
	}

	void GZJMeshManager::StartUp()
	{
	}

	void GZJMeshManager::ShutDown()
	{
		UnLoadAll();
	}

	void GZJMeshManager::PrepareAll()
	{
	}

	void GZJMeshManager::DrawAll(GZJShaderPtr shader)
	{
		for (auto it = resMap.begin(); it != resMap.end(); ++it)
		{
			auto itt = std::dynamic_pointer_cast<GZJMesh>(it->second);
			itt->Draw(shader);
		}
	}


}

