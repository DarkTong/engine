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

	/** 移动组件
	*/
	class GZJMove {
	private:
		/** 移动速度 m/s
		*/
		float speed;

	public:
		GZJMove(float speed=0.5f) :speed(speed) {}
		
	public:
		/** 改变数据
		*/
		//void SetVector3(MoveData param, const GZJTransform& transform)
	};
}

#endif // !__GZJ_MOVE
