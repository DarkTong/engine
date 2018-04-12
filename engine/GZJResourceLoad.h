#ifndef __GZJ_RESOURCE_LOAD_
#define __GZJ_RESOURCE_LOAD_

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

#include "GZJRequire.h"

#include "GZJResource.h"

namespace GZJ_ENGINE{

	enum ResLoadState
	{
		ResLoadState_Open,
		ResLoadState_Close,
		ResLoadState_Free,
		ResLoadState_Busy,
	};

	class GZJResourceLoad
	{
		/** 单例
		*/
	public:
		static GZJResourceLoadPtr _instance;

		static GZJResourceLoadPtr GetInstance();
		
		GZJResourceLoad();

		~GZJResourceLoad();

	private:
		/** 待加载资源种类数
		*/
		const static int NUMBER_OF_RES_TYPE = 3;

		/** 待加载的资源队列
		*/
		std::queue<GZJResourcePtr> _resQueue[NUMBER_OF_RES_TYPE];
		
		/** 记录线程数据
		*/
		std::thread _threadGroup[NUMBER_OF_RES_TYPE];

		/** 记录当前线程状态
		*/
		ResLoadState _threadState[NUMBER_OF_RES_TYPE];

		/** 对应的队列的锁
		*/
		std::mutex _threadMutex[NUMBER_OF_RES_TYPE];

		/**对应线程的条件变量
		*/
		std::condition_variable _threadFlag[NUMBER_OF_RES_TYPE];

	public:
		// 对外接口

		void StartUp();

		void ShutDown();

		/** 添加待加载资源
		*/
		void AddRes(GZJResourcePtr resPtr, ResourceType type);

	public:
		// 对应的资源处理函数
		
		void DoLoadTextureRes();

		void DoLoadMeshRes();

		void DoLoadModelRes();

	};
}

#endif // !__GZJ_RESOURCE_LOAD_
