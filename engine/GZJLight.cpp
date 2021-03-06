#include "GZJLight.h"

namespace GZJ_ENGINE 
{
	String GZJLight::None = "None";

	GZJLight::GZJLight()
		:GZJLight(GZJTransform::ZERO, 
			Vector3(0.1f, 0.1f, 0.1f), Vector3(0.8f, 0.8f, 0.8f), 
			GZJTransform::ONE, 1.0f)
	{
	}

	GZJLight::GZJLight( 
		Vector3 position, Vector3 ambientLight, Vector3 diffuseLight, 
		Vector3 specularLight, float intensity)
		:ambientLight(ambientLight), 
		diffuseLight(diffuseLight), specularLight(specularLight), 
		intensity(intensity)
	{
		_entity = MakeShared<GZJEntity>();
		SetVector3(LightData_Position, position);
	}

	GZJLight::~GZJLight()
	{
	}

	void GZJLight::DoParse(TiXmlElement * ele)
	{
		_id = std::stoi(ele->FirstChildElement("id")->GetText());
		_entity->ParseData(ele->FirstChildElement("entity"));
		DoParseLightData(ele->FirstChildElement("light_param"));
	}

	void GZJLight::DoParseParallerLightData(TiXmlElement * ele)
	{
		SetFloat(LightData_Ortho_Width, atof(ele->
			FirstChildElement("ortho_width")->Attribute("value")));
	}

	void GZJLight::DoParsePointLightData(TiXmlElement * ele)
	{
		SetFloat(LightData_Perspective_Angle, atof(ele->
			FirstChildElement("perspective_angle")->Attribute("value")));

		SetFloat(LightData_Param_K1, (float)atof(ele->
			FirstChildElement("param_k1")->Attribute("value")));

		SetFloat(LightData_Param_K2,(float)atof(ele->
			FirstChildElement("param_k2")->Attribute("value")));
	}

	void GZJLight::DoParseSpotLightData(TiXmlElement * ele)
	{
		SetFloat(LightData_Perspective_Angle, atof(ele->
			FirstChildElement("perspective_angle")->Attribute("value")));

		SetFloat(LightData_InnerAngle, (float)atof(ele->
			FirstChildElement("inner_angle")->Attribute("value")));

		SetFloat(LightData_OutterAngle, (float)atof(ele->
			FirstChildElement("outter_angle")->Attribute("value")));

		SetFloat(LightData_Param_K1, (float)atof(ele->
			FirstChildElement("param_k1")->Attribute("value")));

		SetFloat(LightData_Param_K2, (float)atof(ele->
			FirstChildElement("param_k2")->Attribute("value")));
	}

	void GZJLight::DoParseLightData(TiXmlElement * ele)
	{
		switch (lightType)
		{
		case GZJ_ENGINE::Light_ParallelLight:
			DoParseParallerLightData(ele);
			break;
		case GZJ_ENGINE::Light_PointLight:
			DoParsePointLightData(ele);
			break;
		case GZJ_ENGINE::Light_SpotLight:
			DoParseSpotLightData(ele);
			break;
		default:
			throw "light type error!!, id:" + std::to_string(_id) +
				" type:" + std::to_string(lightType);
			return;
		}

		// set light data
		//SetVector3(LightData_Ambient, ParseVector3(ele->FirstChildElement("ambient")));
		//SetVector3(LightData_Diffuse, ParseVector3(ele->FirstChildElement("diffuse")));
		//SetVector3(LightData_Specular, ParseVector3(ele->FirstChildElement("specular")));
		SetVector3(LightData_Color, ParseVector3(ele->FirstChildElement("color")));
		SetFloat(LightData_Intensity, (float)atof(ele->FirstChildElement("intensity")
			->Attribute("value")));
		SetFloat(LightData_Near_Plane, (float)atof(
			ele->FirstChildElement("near_plane")->Attribute("value")));
		SetFloat(LightData_Far_Plane, (float)atof(
			ele->FirstChildElement("far_plane")->Attribute("value")));
	}

	Vector3 GZJLight::ParseVector3(TiXmlElement * node)
	{
		return Vector3(atof(node->Attribute("x")),
			atof(node->Attribute("y")),
			atof(node->Attribute("z")));
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
			_entity->transform.SetVector3(Position, data);
			break;
		case LightData_Color:
			color = data;
			GZJTools::clamp(color, MIN_LIGHT_COLOR, MAX_LIGHT_COLOR);
			break;
		default:
			throw None;
		}
	}

	void GZJLight::SetFloat(LightData type, const float& data)
	{
		switch (type)
		{
		case LightData_Intensity:
			intensity = data;
			break;
		case LightData_Near_Plane:
			nearPlane = data;
			break;
		case LightData_Far_Plane:
			farPlane = data;
			break;
		default:
			throw None;
		};
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
			return _entity->transform.GetVector3(Position);
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
		case LightData_Near_Plane:
			return nearPlane;
		case LightData_Far_Plane:
			return farPlane;
		default:
			throw None;
		}
	}

	Vector4x4 GZJLight::GetMatrix(LightData type)
	{
		switch (type)
		{
		case LightData_LightSpace:
			return lightSpace;
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
			DoParse(lightElement);
		}
		catch(const char* error_msg)
		{
			cout << "GZJLight: " << error_msg << endl;
		}

		UpdateData();
	}

	LightID GZJLight::GetID()
	{
		return _id;
	}

	GZJEntityPtr GZJLight::GetEntity()
	{
		return _entity;
	}

	void GZJLight::SetToShader(GZJShaderPtr shader)
	{
		shader->Use();
		// 设置深度纹理，只有有光照才有阴影的。
		shader->SetInt(Shader_Shadow_Texture, 0);
		//shader->SetVector3(ShaderData::Light_Ambient, ambientLight);
		//shader->SetVector3(ShaderData::Light_Diffuse, diffuseLight);
		//shader->SetVector3(ShaderData::Light_Specular, specularLight);
		shader->SetInt(ShaderData::Light_Type, (int)lightType);
		shader->SetVector3(ShaderData::Light_Color, color);
		shader->SetFloat(ShaderData::Light_Intensity, intensity);
		shader->SetFloat(ShaderData::Light_Far_Plane, farPlane);
		shader->SetFloat(ShaderData::Light_Near_Plane, nearPlane);

		shader->SetVector3(ShaderData::Light_Position, 
			_entity->transform.GetVector3(Position));

		shader->SetMatrix(ShaderData::Shader_Light_Space, lightSpace);

		LightType type = GetLightType();

		if (type == LightType::Light_ParallelLight)
		{
			shader->SetVector3(ShaderData::Light_Direction,
				GetVector3(LightData_Direction));

		}
		else if (type == LightType::Light_PointLight)
		{
			shader->SetFloat(ShaderData::Light_Param_K1,
				GetFloat(LightData_Param_K1));
			shader->SetFloat(ShaderData::Light_Param_K2,
				GetFloat(LightData_Param_K2));

		}
		else if (type == LightType::Light_SpotLight)
		{
			shader->SetVector3(ShaderData::Light_Direction,
				GetVector3(LightData_Direction));
			shader->SetFloat(ShaderData::Light_Inner_Angle,
				GetFloat(LightData_InnerAngle));
			shader->SetFloat(ShaderData::Light_Outter_Angle,
				GetFloat(LightData_OutterAngle));

		}
	}

	void GZJLight::UpdateData()
	{
		LightType type = GetLightType();

		Vector2 size = GZJWindow::GetInstance()->GetSize();
		Vector4x4 lookAt = _entity->transform.GetMatrix(LookAtMatrix);

		if (type == LightType::Light_ParallelLight)
		{
			float ortho_width = GetFloat(LightData_Ortho_Width);
			float width = ortho_width / 2;
			float height = size.y / size.x * width;
			Vector4x4 ortho_projection = glm::ortho(-width, width, height, -height, nearPlane, farPlane);
			lightSpace = ortho_projection * lookAt;
		}
		else if (type == LightType::Light_PointLight)
		{
			Vector4x4 persp_projection = glm::perspective(
				glm::radians(GetFloat(LightData_Perspective_Angle)),
				size.x / size.y, nearPlane, farPlane);
			lightSpace = persp_projection * lookAt;
		}
		else if (type == LightType::Light_SpotLight)
		{
			Vector4x4 persp_projection = glm::perspective(
				glm::radians(GetFloat(LightData_Perspective_Angle)),
				size.x / size.y, nearPlane, farPlane);
			lightSpace = persp_projection * lookAt;
		}
	}

}