#include "GZJSpotLight.h"

namespace GZJ_ENGINE
{
	GZJSpotLight::GZJSpotLight(GZJLightManager * manager)
		:GZJLight(manager)
	{
	}

	GZJSpotLight::~GZJSpotLight()
	{
	}

	void GZJSpotLight::SetVector3(LightData type, const Vector3 & data)
	{
		try
		{
			GZJLight::SetVector3(type, data);
		}
		catch(const String& flag)
		{
			throw "error";
		}
	}

	void GZJSpotLight::SetFloat(LightData type, const float & data)
	{
		try
		{
			GZJLight::SetFloat(type, data);
		}
		catch (const String& flag)
		{
			if (flag == GZJLight::None)
			{
				switch (type)
				{
				case LightData_InnerAngle:
					innerAngle = glm::cos(glm::radians(data));
					break;
				case LightData_OutterAngle:
					outterAngle = glm::cos(glm::radians(data));
					break;
				case LightData_Param_K1:
					param_k1 = data;
					break;
				case LightData_Param_K2:
					param_k2 = data;
					break;
				case LightData_Perspective_Angle:
					prespectiveAngle = data;
					break;
				}
			}
		}
	}

	Vector3 GZJSpotLight::GetVector3(LightData type)
	{
		try
		{
			return GZJLight::GetVector3(type);
		}
		catch (const String& flag)
		{
			if (flag == GZJLight::None)
			{
				switch (type)
				{
				case LightData_Direction:
					return glm::normalize(GetEntity()->transform.GetVector3(Front));
					break;
				default:
					throw "error";
				}
			}
			else
				throw "error";
		}
	}

	float GZJSpotLight::GetFloat(LightData type)
	{
		try
		{
			return GZJLight::GetFloat(type);
		}
		catch (const String& flag)
		{
			if (flag == GZJLight::None)
			{
				switch (type)
				{
				case LightData_InnerAngle:
					return innerAngle;
				case LightData_OutterAngle:
					return outterAngle;
				case LightData_Param_K1:
					return param_k1;
				case LightData_Param_K2:
					return param_k2;
				case LightData_Perspective_Angle:
					return prespectiveAngle;
				default:
					throw "error";
				}
			}
			else
				throw "error";
		}
	}

}

