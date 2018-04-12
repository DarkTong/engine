#ifndef _GZJ_RESOURCE_
#define _GZJ_RESOURCE_

#include <mutex>

#include "GZJRequire.h"
#include "GZJResourceManager.h"
#include "GZJResourceLoad.h"

namespace GZJ_ENGINE {

	class GZJResource {
	public:
		/** 资源类
		@param 管理当前资源的管理者
		@param 资源的相对路径
		*/
		GZJResource(GZJResourceManager* manager, const String& name, ResourceHandle handle);
	protected:

		GZJResourceManager* _mgr;
		String _path;
		ResourceHandle _handle;
		String _name;
		ResState _state;

	private:
		/** 控制资源状态的锁
		*/
		mutable std::mutex mutexToState;

	public:
		/** 准备资源来准备加载
		*/
		void Prepare();

		/** 同步加载资源
		*/
		void SyncLoad();

		/** 异步加载资源
		*/
		void AsyncLoad();

		/** 卸载资源
		*/
		void UnLoad();

		/** 设置资源状态
		*/
		void SetState(ResState state);
		
		/** 获取资源状态
		*/
		ResState GetState() const;

		/** 获取资源类型
		*/
		virtual ResourceType GetResType() = 0;

	private:
		// 对内接口

		/** 加载资源
		*/
		void Load();

		/** 实行加载资源
		*/
		virtual void DoLoad() = 0;

		/** 实行卸载资源
		*/
		virtual void DoUnLoad() = 0;

	};
}
#endif // !_GZJ_RESOURCE_
