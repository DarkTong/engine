#ifndef __GZJ_POINT_LIGHT_
#define __GZJ_POINT_LIGHT_

#include "GZJLight.h"

namespace GZJ_ENGINE
{
	class GZJPointLight :public GZJLight
	{
	public:
		GZJPointLight();

		~GZJPointLight();

	private:
		// ����

		/** һ��ϵ��
		*/
		float param_k1;
		
		/** ����ϵ��
		*/
		float param_k2;

		/** ��͸��ͶӰ�Ƕ�
		*/
		float prespectiveAngle;

	public:

		void SetVector3(LightData type, const Vector3& data);

		void SetFloat(LightData type, const float& data);

		Vector3 GetVector3(LightData type);

		float GetFloat(LightData type);

	};
}

#endif // !__GZJ_POINT_LIGHT_
