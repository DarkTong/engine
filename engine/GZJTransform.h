#ifndef __GZJ_TRANSFORM__
#define __GZJ_TRANSFORM__

#include "GZJRequire.h"

namespace GZJ_ENGINE {
	enum TransformData {
		Position,
		Rotation,
		Scale,
		//EulerAngles,
		//LocalPosition,
		//LocalRotation,
		//LocalScale,
		//LocalEulerAngles,
		Up,
		Front,
		Right,

		LocalUp,
		LocalFront,
		LocalRight,

		LocalToWorld,
		WorldToLocal,

		// 功能性参数
		LookAtMatrix,
	};

    class GZJTransform{
	public:
		/** (0,0,0)
		*/
		static const Vector3 ZERO;
		/** (1,1,1)
		*/
		static const Vector3 ONE;
		/** (0,0,1)
		*/
		static const Vector3 FRONT;
		/** (1,0,0)
		*/
		static const Vector3 RIGHT;
		/** (0,1,0)
		*/
		static const Vector3 UP;

    private:
        /** 世界坐标
        */
        Vector3 _position;
        Vector3 _rotation;
        Vector3 _scale;
        Vector3 _eulerAngles;

        /** 本地坐标
        */
        Vector3 _localPosition;
        Vector3 _localRotation;
        Vector3 _localScale;
        Vector3 _localEulerAngles;

        /** 方向
        */
        Vector3 _up;         // y
        Vector3 _front;      // z
        Vector3 _right;       // x

		/** 世界方向
		*/
		Vector3 _localUp;
		Vector3 _localFront;
		Vector3 _localRight;

        Vector4x4 LocalToWorldMatrix; //(0,0,0)->(x,y,z)
        Vector4x4 WordlToLocalMatrix;

    public:
        /** 构造函数
        */
        GZJTransform();
        /** 构造函数
         * param : 世界坐标
         * param : 每轴旋转度数
         * param : 缩放
        */
        GZJTransform(Vector3 position, Vector3 rotation, Vector3 scale);

        /** 设置属性方法
         * param : 属性名
         * param : 属性值
        */
        void SetVector3(TransformData param, Vector3 data);

        /** 获取属性方法
         * param : 属性名
        */
		Vector3 GetVector3(TransformData param);

		/** 获取矩阵
		*/
		Vector4x4 GetMatrix(TransformData param);

    private:
		/** 缩放操作
		*/
		void DoScale(Vector3 scale);
		/** 旋转操作
		*/
		void DoRotate(Vector3 rotate);
		/** 唯一操作
		*/
		void DoTranslate(Vector3 translate);
        /** 每当数据改变时都执行Update
        */
        void Update();

    };
}

#endif // __GZJ_TRANSFORM__
