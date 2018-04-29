#ifndef __GZJ_CAMERA_
#define __GZJ_CAMERA_

#include "GZJRequire.h"
#include "GZJTools.h"
#include "GZJTransform.h"
#include "GZJMove.h"
#include "GZJWindow.h"

namespace GZJ_ENGINE {
	struct CameraParam {
		static const String Position;
		static const String Rotation;
	};

	class GZJCamera {
	private:
		/** �۲�ռ����
		*/
		Vector4x4 viewMatrix;

	public:
		// ���

		/** λ�ò���������ֱ�����ã�
		*/
		GZJTransform transform;

		/** �ƶ����
		*/
		GZJMovePtr moveCmp;

		/** ͸�ӽ�
		*/
		float projectionAngle;

	public:
		/** Ĭ�Ϲ��캯��
		*/
		GZJCamera();
		
		/** ��ȡ�۲�ռ�
		*/
		Vector4x4 LookAt();
		
		/** ��ȡͶӰ�ռ�
		*/
		Vector4x4 Projection();
		/** ��,Զƽ��
		*/
		float nearPlane;
		float farPlane;
		
		/** �������������
		*/
		void SetVector3(const String param, Vector3 data);

		/** �����������ز���
		*/
		void Update();

		///** �����������¼�
		//*/
		//virtual void InitEvents();

	public:
		// ����

		/** ������������
		*/
		void ParseData(TiXmlElement * ele);

		/** ����projection����
		*/
		void DoParseProjectionData(TiXmlElement * ele);
	};
}

#endif // !__GZJ_CAMERA_
