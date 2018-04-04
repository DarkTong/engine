#ifndef __GZJ_MOVE_
#define __GZJ_MOVE_

#include "GZJRequire.h"
#include "GZJEventSystem.h"
#include "GZJTransform.h"


namespace GZJ_ENGINE {
	enum MoveData {
		MOVE_FRONT,
		MOVE_BACK,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_YAW,
		MOVE_PITCH,
		MOVE_ROLL,

	};

	/** �ƶ����
	*/
	class GZJMove {
	private:

		/** �󶨵��¼��б�
		*/
		std::vector<EventConstant> eventHandles;

		/** Ҫ���Ƶ�����Transform
		*/
		GZJTransform *transform;

	public:
		GZJMove(GZJTransform* transform, float speed=0.1f) 
			:transform(transform), speed(speed) {}

		~GZJMove() {
			UnBindEvent();
		};
		
	public:
		/** �ƶ��ٶ� m/s
		*/
		float speed;

	public:
		/** ���¼�
		*/
		void BindEvent();

		/** ����¼�
		*/
		void UnBindEvent();

		/** �ı�����
		*/
		void SetVector3(const MoveData& param);

	private:
		// �¼�����
		void Handle_Press_KeyBoard(const GZJEventParamObj& param);

		void Handle_Press_Mouse(const GZJEventParamObj& param);
	};
}

#endif // !__GZJ_MOVE
