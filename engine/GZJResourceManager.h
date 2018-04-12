#ifndef __GZJ_RESOURCE_MANAGER__
#define __GZJ_RESOURCE_MANAGER__

#include "GZJRequire.h"
#include "GZJResource.h"

namespace GZJ_ENGINE {

	typedef HashMap<String, GZJResourcePtr> ResourceMap;
	typedef Map<ResourceHandle, GZJResourcePtr> ResourceHandleMap;
	typedef ResourceMap::iterator ResourceMapIterator;

	class GZJResourceManager {
	public:
		GZJResourceManager();
		~GZJResourceManager();
	protected:
		// /** 管理自身的智能指针
		// */
		// GZJResourceManagerPtr self;
		/** 根据资源名存储资源
		*/
		ResourceMap resMap;
		/** 根据资源句柄加载资源
		*/
		ResourceHandleMap resHandleMap;
		/** 当前未分配的资源句柄
		*/
		ResourceHandle resHandle;
		/** 当前管理的资源的根路径
		*/
		String _resRoot;
	public:
		/** 开启管理器
		*/
		virtual void StartUp() = 0;

		/** 关闭管理器
		*/
		virtual void ShutDown() = 0;

		/** 创建资源
		@param 资源名字
		@param 资源相对路径
		*/
		GZJResourcePtr CreateRes(const String& name);

		/** 按名字查找资源
		@param 资源的名字
		@return 没有返回nullptr
		*/
		GZJResourcePtr FindResByName(const String& name);

		/** 准备所有资源
		*/
		virtual void PrepareAll() = 0;

		/** 加载所有资源
		*/
		virtual void LoadAll(bool isAsyncLoad=false);

		/** 加载对应名字的资源
		*/
		virtual void LoadByName(const String& name);

		/** 卸载所有资源
		*/
		virtual void UnLoadAll();

		/** 卸载对应名字的资源
		*/
		virtual void UnLoadByName(const String& name);

		/** 判断资源是否已经被加载
		*/
		bool IsLoad(const String& name);

		/** 获取资源路径
		@param 资源路径
		*/
		String GetResRoot();

		/** 获取下一个资源句柄
		*/
		ResourceHandle GetNextHandle();

		// /** 获取自身的智能指针
		// */
		// GZJResourceManagerPtr GetSelf() const;

	protected:
		// 对内接口
		virtual GZJResource* createImp(const String& name) = 0;

	};
}
#endif // !__GZJ_RESOURCE_MANAGER__
