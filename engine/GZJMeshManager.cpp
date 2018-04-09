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

