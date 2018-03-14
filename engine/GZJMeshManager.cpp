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
		// ����ʵ�־������Դ����
		// ����Mesh�Ĺ���
		GZJResourceManagerPtr tmp = std::static_pointer_cast<GZJResourceManager>(self);
		return (new GZJMesh(tmp, name, resHandle++));
	}

	void GZJMeshManager::StartUp()
	{
	}

	void GZJMeshManager::ShutDown()
	{
		UnLoadAll();
		self = nullptr;
	}

	void GZJMeshManager::PrepareAll()
	{
	}


}

