#include "GZJMeshManager.h"

namespace GZJ_ENGINE {
	GZJMeshManagerPtr GZJMeshManager::_instance = nullptr;

	GZJMeshManager::GZJMeshManager()
	{
		GZJResourceManager::_resRoot = ENGINE_ROOT_PATH + "\\mesh";
	}

	GZJMeshManager::~GZJMeshManager(){}

	GZJResource* GZJMeshManager::createImp(const String& name) {
		// todo
		// 用于实现具体的资源创建
		// 调用Mesh的构造
		GZJResourceManagerPtr tmp = std::static_pointer_cast<GZJResourceManager>(_instance);
		return (new GZJMesh(tmp, name, resHandle++));
	}

	void GZJMeshManager::StartUp()
	{
	}

	void GZJMeshManager::ShutDown()
	{
	}

	void GZJMeshManager::PrepareAll()
	{
	}


}

