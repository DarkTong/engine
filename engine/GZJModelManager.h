#ifndef __GZJ_MODEL_MANAGER__
#define __GZJ_MODEL_MANAGER__

#include "GZJRequire.h"
#include "GZJModel.h"
#include "GZJMeshManager.h"

namespace GZJ_ENGINE {
	class GZJModelManager :public GZJResourceManager {

	public:
		GZJModelManager();
		
		~GZJModelManager();

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

	protected:
		// 对内接口
		GZJResource* createImp(const String& name);

	};
}

#endif // !__GZJ_MODEL_MANAGER__
