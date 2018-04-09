#ifndef __GZJ_TEXTURE_MANAGER_
#define __GZJ_TEXTURE_MANAGER_

#include "GZJRequire.h"
#include "GZJResourceManager.h"
#include "GZJTexture.h"

namespace GZJ_ENGINE {
	class GZJTextureManager :public GZJResourceManager
	{
		/* 单例
		*/
	private:
		static GZJTextureManagerPtr _instance;
	public:
		static GZJTextureManagerPtr GetInstance()
		{
			if (_instance == nullptr)
				_instance = MakeShared<GZJTextureManager>();
			return _instance;
		}

	public:
		// 构造、析构
		GZJTextureManager();

		~GZJTextureManager();

	public:
		// 继承
		void StartUp();

		void ShutDown();

	private:
		// 不使用

		/** 准备所有资源
		*/
		void PrepareAll();

		/** 加载所有资源
		*/
		void LoadAll();

		/** 卸载所有资源
		*/
		void UnLoadAll();

	private:
		// 继承

		GZJResource* createImp(const String &name);
	};
}

#endif // !__GZJ_TEXTURE_MANAGER_
