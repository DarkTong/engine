#ifndef __GZJ_MOVE_
#define __GZJ_MOVE_

#include "GZJRequire.h"
#include "GZJEventSystem.h"
#include "GZJTime.h"
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

	/** 移动组件
	*/
	class GZJMove {
	private:

		/** 绑定的事件列表
		*/
		std::vector<EventConstant> eventHandles;

		/** 要控制的物体Transform
		*/
		GZJTransform *transform;

		/** 按键记录
		*/
		Map<int, bool> keyIsPress;

		/** 鼠标按键记录
		*/
		Map<int, bool> cursorIsPress;

	public:
		GZJMove(GZJTransform* transform, float moveSpeed = 0.1f
			, float yawSpeed = 0.1f
			, float pitchSpeed = 0.1f)
			:transform(transform), moveSpeed(moveSpeed) 
			, yawSpeed(yawSpeed), pitchSpeed(pitchSpeed) {}

		~GZJMove() {
			UnBindEvent();
		};

	private:

		/** 记录鼠标位置
		*/
		float xPos, yPos;

		/** 光标相对上次位置的偏移
		*/
		float xOffset, yOffset;

	public:
		/** 移动速度 m/s
		*/
		float moveSpeed;

		/** yaw速度
		*/
		float yawSpeed;

		/** pitch速度
		*/
		float pitchSpeed;

	public:
		/** 绑定事件
		*/
		void BindEvent();

		/** 解绑事件
		*/
		void UnBindEvent();

		/** 改变数据
		*/
		void SetVector3(const MoveData& param);

		/** 每逻辑帧更新
		*/
		void LogicUpdate(const GZJEventParamObj& param);

	private:
		// 功能

		/** 更新transform
		*/
		void UpdateTransform();

		/** 更新Cursor
		*/
		void UpdateCursor();
	private:
		// 事件函数
		void Handle_Press_KeyBoard(const GZJEventParamObj& param);

		void Handle_Press_Mouse(const GZJEventParamObj& param);
	};
}

#endif // !__GZJ_MOVE
