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
			throw "error";
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
					return glm::normalize(_model->transform.GetVector3(Front));;
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
			throw "error";
		}
	}

	void GZJParallelLight::DoParseLightData(TiXmlElement * ele)
	{
		// 先获取父类光数据
		GZJLight::DoParseLightData(ele);

		auto func = [](TiXmlElement * node) {
			return Vector3(atof(node->Attribute("x")),
				atof(node->Attribute("y")),
				atof(node->Attribute("z")));
		};
	}

}
