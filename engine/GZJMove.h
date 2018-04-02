#ifndef __GZJ_MOVE_
#define __GZJ_MOVE_

#include "GZJRequire.h"
#include "GZJTransform.h"


namespace GZJ_ENGINE {
	enum MoveData {
		FRONT,
		LEFT,
		UP,
		YAW,
		PITCH,
		ROLL,

	};

	/** �ƶ����
	*/
	class GZJMove {
	private:
		/** �ƶ��ٶ� m/s
		*/
		float speed;

	public:
		GZJMove(float speed=0.5f) :speed(speed) {}
		
	public:
		/** �ı�����
		*/
		//void SetVector3(MoveData param, const GZJTransform& transform)
	};
}

#endif // !__GZJ_MOVE
