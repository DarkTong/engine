#ifndef __GZJ_EVENT_SYSTEM_
#define __GZJ_EVENT_SYSTEM_

#include "GZJRequire.h"
#include "GZJEventConstant.h"
#include "GZJEvent.h"

namespace GZJ_ENGINE {

	typedef Map<EventConstant, GZJEvent> EventMap;

	class GZJEventSystem {
		/** 单例
		*/
	private:
		static GZJEventSystemPtr _instance;
	public:
		inline static GZJEventSystemPtr GetInstance()
		{
			if (_instance == nullptr)
				_instance = std::make_shared<GZJEventSystem>();

			return _instance;
		}

	public:
		// 构造、析构
		GZJEventSystem() {};
		~GZJEventSystem() {};

	private:
		EventMap events;

	public:
		// 管理器接口

		/** 启动
		*/
		void StartUp();

		/** 运行
		*/
		void Update();

		/** 关闭
		*/
		void ShutDown();

		/** 销毁
		*/
		void Finalze();

	public:
		// 功能性对外接口

		/** 派发事件
		*/
		void Fire(EventConstant eventId, const GZJEventParamObj& param);

		/** 绑定事件
		*/
		void Bind(TargetID targetId, EventConstant eventId, NormalDelegate func);

		/** 解绑事件
		*/
		void UnBind(TargetID targetId, EventConstant eventId);
	};
}

#endif // !__GZJ_EVENT_SYSTEM_
