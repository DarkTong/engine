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

		// �����Բ���
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
        /** ��������
        */
        Vector3 _position;
        Vector3 _rotation;
        Vector3 _scale;
        Vector3 _eulerAngles;

        /** ��������
        */
        Vector3 _localPosition;
        Vector3 _localRotation;
        Vector3 _localScale;
        Vector3 _localEulerAngles;

        /** ����
        */
        Vector3 _up;         // y
        Vector3 _front;      // z
        Vector3 _right;       // x

		/** ���緽��
		*/
		Vector3 _localUp;
		Vector3 _localFront;
		Vector3 _localRight;

        Vector4x4 LocalToWorldMatrix; //(0,0,0)->(x,y,z)
        Vector4x4 WordlToLocalMatrix;

    public:
        /** ���캯��
        */
        GZJTransform();
        /** ���캯��
         * param : ��������
         * param : ÿ����ת����
         * param : ����
        */
        GZJTransform(Vector3 position, Vector3 rotation, Vector3 scale);

        /** �������Է���
         * param : ������
         * param : ����ֵ
        */
        void SetVector3(TransformData param, Vector3 data);

        /** ��ȡ���Է���
         * param : ������
        */
		Vector3 GetVector3(TransformData param);

		/** ��ȡ����
		*/
		Vector4x4 GetMatrix(TransformData param);

    private:
		/** ���Ų���
		*/
		void DoScale(Vector3 scale);
		/** ��ת����
		*/
		void DoRotate(Vector3 rotate);
		/** Ψһ����
		*/
		void DoTranslate(Vector3 translate);
        /** ÿ�����ݸı�ʱ��ִ��Update
        */
        void Update();

    };
}

#endif // __GZJ_TRANSFORM__
