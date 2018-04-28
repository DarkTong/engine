#pragma once

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
		/** 资源管理器
		*/
		GZJResourceManager* _mgr;
		/** 资源存储路径
		*/
		String _path;
		/** 资源句柄
		*/
		ResourceHandle _handle;
		/** 资源名字
		*/
		String _name;
		/** 资源状态
		*/
		ResState _state;
		/** 资源引用计数器
		*/
		unsigned int _count;

	public:
		// 友元
		friend class GZJResourceManager;

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

		/** 获取资源句柄
		*/
		ResourceHandle GetResHandle();

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

		/** 强制卸载资源
		* 不管是否有对象正在引用
		* 用于管理器关闭时调用
		*/
		void ForceUnLoad();
	};
}

