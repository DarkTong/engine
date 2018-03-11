#ifndef _GZJ_MESH_MANAGER_
#define _GZJ_MESH_MANAGER_

#include "GZJRequire.h"
#include "GZJResourceManager.h"
#include "GZJMesh.h"

namespace GZJ_ENGINE {
	class GZJMeshManager :public GZJResourceManager 
	{
	public:
		static GZJMeshManagerPtr _instance;
		static GZJMeshManagerPtr GetInstance() {
			if (_instance == nullptr)
				_instance = GZJMeshManagerPtr(new GZJMeshManager());
			return _instance;
		}
	private:
		GZJResource * createImp(const String& name);

	public:
		GZJMeshManager();

		~GZJMeshManager();

	public:
		/** 开启管理器
		*/
		void StartUp();

		/** 关闭管理器
		*/
		void ShutDown();

		/** 准备所有资源
		*/
		void PrepareAll();
	};
}

#endif // !_GZJ_MESH_MANAGER_
