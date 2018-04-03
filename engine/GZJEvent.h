#ifndef __GZJ_EVENT_
#define __GZJ_EVENT_

#include "GZJRequire.h"
#include "GZJEventConstant.h"
#include "GZJEventParamObj.h"

namespace GZJ_ENGINE {


	typedef unsigned long long TargetID;

	class GZJEvent {
	private:
		/** 事件ID
		*/
		EventConstant eventId;

		/** 对象委托
		*/
		std::map<TargetID, NormalDelegate> objFuncs;

		/** 无对象委托，静态，普通函数
		*/
		std::set<NormalDelegate> noObjFuncs;

	public:
		GZJEvent(EventConstant id);

	public:
		// 对外接口

		/** 执行事件
		*/
		void Fire(GZJEventParamObj param);

		/** 绑定委托,有对象
		*/
		void Bind(TargetID targetId, NormalDelegate func);

		/** 解绑委托,有对象
		*/
		void UnBind(TargetID targetId);

		/** 解绑所有委托
		*/
		void UnBindAll();

		/** 销毁
		*/
		void Finalize();
	};
}

#endif // !__Event_
