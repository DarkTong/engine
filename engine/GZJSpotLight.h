#ifndef __GZJ_SPOT_LIGHT_
#define __GZJ_SPOT_LIGHT_

#include "GZJLight.h"

namespace GZJ_ENGINE
{
	class GZJSpotLight :public GZJLight
	{
	public:
		GZJSpotLight(GZJLightManager* manager);

		~GZJSpotLight();

	private:
		// ����

		/** ��ָ��
		*/
		Vector3 direction;

		/** ���й��
		*/
		float innerAngle;

		/** ���й��
		*/
		float outterAngle;

		/** һ��ϵ��
		*/
		float param_k1;

		/** ����ϵ��
		*/
		float param_k2;

	public:

		void SetVector3(LightData type, const Vector3& data);

		void SetFloat(LightData type, const float& data);

		Vector3 GetVector3(LightData type);

		float GetFloat(LightData type);

		void DoParseLightData(TiXmlElement * ele);
	};
}

#endif // !__GZJ_SPOT_LIGHT_
