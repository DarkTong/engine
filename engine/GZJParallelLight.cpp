#include "GZJParallelLight.h"

namespace GZJ_ENGINE
{
	GZJParallelLight::GZJParallelLight(GZJLightManager * manager)
		:GZJLight(manager)
	{
	}

	GZJParallelLight::~GZJParallelLight()
	{
	}

	void GZJParallelLight::SetVector3(LightData type, const Vector3 & data)
	{
		try
		{
			GZJLight::SetVector3(type, data);
		}
		catch (const String & flag)
		{
			throw "error";
		}
	}

	void GZJParallelLight::SetFloat(LightData type, const float & data)
	{
		try
		{
			GZJLight::SetFloat(type, data);
		}
		catch (const String & flag)
		{
			if (flag == GZJLight::None)
			{
				switch (type)
				{
				case LightData_Ortho_Width:
					orthoWidth = data;
					break;
				default:
					cout << "LightData Error!!, type:" << type << endl;
				}
			}
			else
				throw flag;
		}
	}

	Vector3 GZJParallelLight::GetVector3(LightData type)
	{
		try
		{
			return GZJLight::GetVector3(type);
		}
		catch (const String & flag)
		{
			if (flag == GZJLight::None)
			{
				switch (type)
				{
				case LightData_Direction:
					return glm::normalize(GetEntity()->transform.GetVector3(Front));;
				default:
					throw "error";
				}
			}
			else
				throw "error";
		}
	}

	float GZJParallelLight::GetFloat(LightData type)
	{
		try
		{
			return GZJLight::GetFloat(type);
		}
		catch (const String & flag)
		{
			if (flag == GZJLight::None)
			{
				switch (type)
				{
				case LightData_Ortho_Width:
					return orthoWidth;
				default:
					cout << "LightData Error!!, type:" << type << endl;
				}
			}
			else
				throw flag;
		}
	}

}
