#include "GZJLight.h"

namespace GZJ_ENGINE 
{
	String GZJLight::None = "None";

	GZJLight::GZJLight(GZJLightManager * manager)
		:GZJLight(manager, GZJTransform::ZERO, 
			Vector3(0.1f, 0.1f, 0.1f), Vector3(0.8f, 0.8f, 0.8f), 
			GZJTransform::ONE, 1.0f)
	{
	}

	GZJLight::GZJLight(GZJLightManager * manager, 
		Vector3 position, Vector3 ambientLight, Vector3 diffuseLight, 
		Vector3 specularLight, float intensity)
		:_mgr(manager), ambientLight(ambientLight), 
		diffuseLight(diffuseLight), specularLight(specularLight), 
		intensity(intensity)
	{
		_model = std::static_pointer_cast<GZJModel>(
			GZJModelManager::GetInstance()->CreateRes("cube1"));
		SetVector3(LightData_Position, position);
	}

	GZJLight::~GZJLight()
	{
	}

	void GZJLight::DoParseLightData(TiXmlElement * ele)
	{
		_id = std::stoi(ele->Attribute("id"));
		
		const String typeStr = ele->Attribute("type");
		if (typeStr == "ParallelLight")
		{
			lightType = Light_ParallelLight;
		}
		else if (typeStr == "PointLight")
		{
			lightType = Light_PointLight;
		}
		else if (typeStr == "SpotLight")
		{
			lightType = Light_SpotLight;
		}
		else
		{
			cout << "light type error!!, id:" << _id << " type:" << typeStr << endl;
			return;
		}

		auto func = [this](TiXmlElement * node) 
		{
			return Vector3(atof(node->Attribute("x")),
				atof(node->Attribute("y")),
				atof(node->Attribute("z")));
		};
		// load model
		String modelName = ele->FirstChildElement("model")
			->Attribute("name");
		_model = std::static_pointer_cast<GZJModel>(
			GZJModelManager::GetInstance()->CreateRes(modelName));
		_model->SyncLoad();
		
		// set transform
		_model->transform.SetVector3(Position, func(ele->FirstChildElement("position")));
		_model->transform.SetVector3(Rotation, func(ele->FirstChildElement("rotation")));
		_model->transform.SetVector3(Scale, func(ele->FirstChildElement("scale")));

		// set light data
		SetVector3(LightData_Ambient, func(ele->FirstChildElement("ambient")));
		SetVector3(LightData_Diffuse, func(ele->FirstChildElement("diffuse")));
		SetVector3(LightData_Specular, func(ele->FirstChildElement("specular")));
		SetFloat(LightData_Intensity, (float)atof(ele->FirstChildElement("intensity")
			->Attribute("value")));
	}

	void GZJLight::SetVector3(LightData type, const Vector3& data)
	{
		switch (type)
		{
		case LightData_Ambient:
			ambientLight = data;
			GZJTools::clamp(ambientLight, MIN_LIGHT_COLOR, MAX_LIGHT_COLOR);
			break;
		case LightData_Diffuse:
			diffuseLight = data;
			GZJTools::clamp(diffuseLight, MIN_LIGHT_COLOR, MAX_LIGHT_COLOR);
			break;
		case LightData_Specular:
			specularLight = data;
			GZJTools::clamp(specularLight, MIN_LIGHT_COLOR, MAX_LIGHT_COLOR);
			break;
		case LightData_Position:
			_model->transform.SetVector3(Position, data);
			break;
		default:
			throw None;
		}
	}

	void GZJLight::SetFloat(LightData type, const float& data)
	{
		if (type == LightData_Intensity)
		{
			intensity = data;
			//GZJTools::clamp(intensity, MIN_LIGHT_INTENSITY, MAX_LIGHT_INTENSITY);
		}
		else
		{
			throw None;
		}
	}

	Vector3 GZJLight::GetVector3(LightData type)
	{
		switch (type)
		{
		case LightData_Ambient:
			return ambientLight;
		case LightData_Diffuse:
			return diffuseLight;
		case LightData_Specular:
			return specularLight;
		case LightData_Position:
			return _model->transform.GetVector3(Position);
		default:
			throw None;
		}
	}

	float GZJLight::GetFloat(LightData type)
	{
		switch (type)
		{
		case LightData_Intensity:
			return intensity;
		default:
			throw None;
		}
	}

	LightType GZJLight::GetLightType()
	{
		return lightType;
	}

	void GZJLight::ParseLightData(TiXmlElement * lightElement)
	{
		try
		{
			DoParseLightData(lightElement);
		}
		catch(const char* error_msg)
		{
			cout << "GZJLight: " << error_msg << endl;
		}
	}

	LightID GZJLight::GetID()
	{
		return _id;
	}

	GZJModelPtr GZJLight::GetModel()
	{
		return _model;
	}

}