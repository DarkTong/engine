#include "GZJPointLight.h"

namespace GZJ_ENGINE
{
	GZJPointLight::GZJPointLight(GZJLightManager * manager)
		:GZJLight(manager)
	{
	}

	GZJPointLight::~GZJPointLight()
	{
	}

	void GZJPointLight::SetVector3(LightData type, const Vector3 & data)
	{
		try
		{
			GZJLight::SetVector3(type, data);
		}
		catch (const String& flag)
		{
			if (flag == GZJLight::None)
			{
				cout << "LightData Error!!, type:" << type << endl;
			}
		}
	}

	void GZJPointLight::SetFloat(LightData type, const float & data)
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
				case LightData_Param_K1:
					param_k1 = data;
					break;
				case LightData_Param_K2:
					param_k2 = data;
					break;
				case LightData_Perspective_Angle:
					prespectiveAngle = data;
					break;
				default:
					cout << "LightData Error!!, type:" << type << endl;
				}
			}
		}
	}

	Vector3 GZJPointLight::GetVector3(LightData type)
	{
		try
		{
			return GZJLight::GetVector3(type);
		}
		catch (const String& flag)
		{
			throw "error";
		}
	}

	float GZJPointLight::GetFloat(LightData type)
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
				case LightData_Param_K1:
					return param_k1;
				case LightData_Param_K2:
					return param_k2;
				case LightData_Perspective_Angle:
					return prespectiveAngle;
				default:
					cout << "LightData Error!!, type:" << type << endl;
				}
			}
			else
				throw "error";
		}

	}

}

