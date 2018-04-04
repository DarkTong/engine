#ifndef __GZJ_CAMERA_
#define __GZJ_CAMERA_

#include "GZJRequire.h"
#include "GZJTransform.h"
#include "GZJMove.h"

namespace GZJ_ENGINE {
	struct CameraParam {
		static const String Position;
		static const String Rotation;
	};

	class GZJCamera {
	private:
		/** 观察空间矩阵
		*/
		Vector4x4 viewMatrix;

	public:
		// 组件

		/** 位置参数（不能直接设置）
		*/
		GZJTransform transform;

		/** 移动组件
		*/
		GZJMovePtr moveCmp;

	public:
		/** 默认构造函数
		*/
		GZJCamera();
		
		/** 获取观察空间
		*/
		Vector4x4 LookAt();
		
		/** 设置摄像机参数
		*/
		void SetVector3(const String param, Vector3 data);

		/** 更新摄像机相关参数
		*/
		void Update();

		///** 绑定摄像机相关事件
		//*/
		//virtual void InitEvents();
	};
}

#endif // !__GZJ_CAMERA_
