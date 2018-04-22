#ifndef __GZJ_POINT_LIGHT_
#define __GZJ_POINT_LIGHT_

#include "GZJLight.h"

namespace GZJ_ENGINE
{
	class GZJPointLight :public GZJLight
	{
	public:
		GZJPointLight(GZJLightManager* manager);

		~GZJPointLight();

	private:
		// 属性

		/** 一阶系数
		*/
		float param_k1;
		
		/** 二阶系数
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

#endif // !__GZJ_POINT_LIGHT_
