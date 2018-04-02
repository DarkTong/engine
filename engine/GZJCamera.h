#ifndef __GZJ_CAMERA_
#define __GZJ_CAMERA_

#include "GZJRequire.h"
#include "GZJTransform.h"

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
		/** λ�ò���������ֱ�����ã�
		*/
		GZJTransform transform;
	public:
		/** Ĭ�Ϲ��캯��
		*/
		GZJCamera();
		
		/** ��ȡ�۲�ռ�
		*/
		Vector4x4 LookAt();
		
		/** �������������
		*/
		void SetVector3(const String param, Vector3 data);

		/** �����������ز���
		*/
		void Update();
	};
}

#endif // !__GZJ_CAMERA_
