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

		/** 透视角
		*/
		float projectionAngle;

	public:
		/** 默认构造函数
		*/
		GZJCamera();
		
		/** 获取观察空间
		*/
		Vector4x4 LookAt();
		
		/** 获取投影空间
		*/
		Vector4x4 Projection();
		/** 近,远平面
		*/
		float nearPlane;
		float farPlane;
		
		/** 设置摄像机参数
		*/
		void SetVector3(const String param, Vector3 data);

		/** 更新摄像机相关参数
		*/
		void Update();

		///** 绑定摄像机相关事件
		//*/
		//virtual void InitEvents();

	public:
		// 解析

		/** 解析配置数据
		*/
		void ParseData(TiXmlElement * ele);

		/** 解析projection数据
		*/
		void DoParseProjectionData(TiXmlElement * ele);
	};
}

#endif // !__GZJ_CAMERA_
