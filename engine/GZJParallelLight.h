#ifndef __GZJ_PARALLEL_LIGHT_
#define __GZJ_PARALLEL_LIGHT_

#include "GZJLight.h"

namespace GZJ_ENGINE {
	class GZJParallelLight :public GZJLight
	{
	public:
		GZJParallelLight(GZJLightManager* manager);

		~GZJParallelLight();

	private:
		// ����
		/** ��ָ��
		*/
		Vector3 direction;

		/** �����ռ���
		*/
		float orthoWidth;

	public:

		void SetVector3(LightData type, const Vector3& data);

		void SetFloat(LightData type, const float& data);

		Vector3 GetVector3(LightData type);

		float GetFloat(LightData type);
	};
}

#endif // !__GZJ_PARALLEL_LIGHT_
