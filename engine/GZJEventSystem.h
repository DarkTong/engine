#ifndef __GZJ_EVENT_SYSTEM_
#define __GZJ_EVENT_SYSTEM_

#include "GZJRequire.h"
#include "GZJEventConstant.h"
#include "GZJEvent.h"

namespace GZJ_ENGINE {

	typedef Map<EventConstant, GZJEvent> EventMap;

	class GZJEventSystem {
		/** ����
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
		// ���졢����
		GZJEventSystem() {};
		~GZJEventSystem() {};

	private:
		EventMap events;

	public:
		// �������ӿ�

		/** ����
		*/
		void StartUp();

		/** ����
		*/
		void Update();

		/** �ر�
		*/
		void ShutDown();

		/** ����
		*/
		void Finalze();

	public:
		// �����Զ���ӿ�

		/** �ɷ��¼�
		*/
		void Fire(EventConstant eventId, const GZJEventParamObj& param);

		/** ���¼�
		*/
		void Bind(TargetID targetId, EventConstant eventId, NormalDelegate func);

		/** ����¼�
		*/
		void UnBind(TargetID targetId, EventConstant eventId);
	};
}

#endif // !__GZJ_EVENT_SYSTEM_
