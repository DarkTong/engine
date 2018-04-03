#ifndef __GZJ_EVENT_
#define __GZJ_EVENT_

#include "GZJRequire.h"
#include "GZJEventConstant.h"
#include "GZJEventParamObj.h"

namespace GZJ_ENGINE {


	typedef unsigned long long TargetID;

	class GZJEvent {
	private:
		/** �¼�ID
		*/
		EventConstant eventId;

		/** ����ί��
		*/
		std::map<TargetID, NormalDelegate> objFuncs;

		/** �޶���ί�У���̬����ͨ����
		*/
		std::set<NormalDelegate> noObjFuncs;

	public:
		GZJEvent(EventConstant id);

	public:
		// ����ӿ�

		/** ִ���¼�
		*/
		void Fire(GZJEventParamObj param);

		/** ��ί��,�ж���
		*/
		void Bind(TargetID targetId, NormalDelegate func);

		/** ���ί��,�ж���
		*/
		void UnBind(TargetID targetId);

		/** �������ί��
		*/
		void UnBindAll();

		/** ����
		*/
		void Finalize();
	};
}

#endif // !__Event_
