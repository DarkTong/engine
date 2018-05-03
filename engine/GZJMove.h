#ifndef __GZJ_MOVE_
#define __GZJ_MOVE_

#include <tinyxml\tinyxml.h>

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

		/** ������¼
		*/
		Map<int, bool> keyIsPress;

		/** ��갴����¼
		*/
		Map<int, bool> cursorIsPress;

	public:
		GZJMove(GZJTransform* transform, float moveSpeed = 0.1f
			, float yawSpeed = 0.1f, float pitchSpeed = 0.1f);

		~GZJMove();

	private:

		/** ��¼���λ��
		*/
		float xPos, yPos;

		/** �������ϴ�λ�õ�ƫ��
		*/
		float xOffset, yOffset;

	public:
		/** �ƶ��ٶ� m/s
		*/
		float moveSpeed;

		/** yaw�ٶ�
		*/
		float yawSpeed;

		/** pitch�ٶ�
		*/
		float pitchSpeed;

		/** �Զ��ƶ�
		*/
		bool autoRowYaw, autoRowPitch;

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

		/** ÿ�߼�֡����
		*/
		void LogicUpdate(const GZJEventParamObj& param);

	public:

		/**  ������������
		*/
		void ParseData(TiXmlElement * ele);

	private:
		// ����

		void DoParseData(TiXmlElement * ele);

		/** ����transform
		*/
		void UpdateTransform();

		/** �Զ��ƶ�����ת
		*/
		void AutoTransform();

		/** ����Cursor
		*/
		void UpdateCursor();

		/** ��������
		*/
		void UpdateData(const MoveData& param, float offset = 1.0f);
	private:
		// �¼�����
		void Handle_Press_KeyBoard(const GZJEventParamObj& param);

		void Handle_Press_Mouse(const GZJEventParamObj& param);
	};
}

#endif // !__GZJ_MOVE
