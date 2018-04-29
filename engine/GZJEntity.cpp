#include "GZJEntity.h"

namespace GZJ_ENGINE
{
	void GZJEntity::Draw(GZJShaderPtr shader)
	{
		GZJShaderPtr useShader = this->shader;
		if (shader != nullptr)
			useShader = shader;

		useShader->Use();
		useShader->SetMatrix(Shader_LocalToWorld,
			transform.GetMatrix(LocalToWorld));
		model->Draw(useShader);
	}

	void GZJEntity::ParseData(TiXmlElement * ele)
	{
		DoParseTransformData(ele->FirstChildElement("transform"));
		DoParseModelData(ele->FirstChildElement("model"));
		DoParseShaderData(ele->FirstChildElement("shader"));
	}

	void GZJEntity::DoParseTransformData(TiXmlElement * ele)
	{
		// set transform
		transform.SetVector3(Position, ParseTransVector3(ele->FirstChildElement("position")));
		transform.SetVector3(Rotation, ParseTransVector3(ele->FirstChildElement("rotation")));
		transform.SetVector3(Scale, ParseTransVector3(ele->FirstChildElement("scale")));
	}

	Vector3 GZJEntity::ParseTransVector3(TiXmlElement * ele)
	{
		const char * _auto = ele->Attribute("auto");
		if (_auto && String(_auto) == "true")
		{
			Vector3 min_v = ParseVector3(ele->FirstChildElement("min"));
			Vector3 max_v = ParseVector3(ele->FirstChildElement("max"));
			// ·¶Î§Ëæ»úÊý
			auto func = [](float _min, float _max) {
				float tmp = (_max - _min) / RAND_MAX * rand();
				return tmp + _min;
			};
			return Vector3(func(min_v.x, max_v.x),
				func(min_v.y, max_v.y),
				func(min_v.z, max_v.z));
		}
		else
			return ParseVector3(ele);

	}

	Vector3 GZJEntity::ParseVector3(TiXmlElement * ele)
	{
		return Vector3(atof(ele->Attribute("x")),
			atof(ele->Attribute("y")),
			atof(ele->Attribute("z")));
	}
	
	void GZJEntity::DoParseModelData(TiXmlElement * ele)
	{
		// load model
		String modelName = ele->FirstChildElement("name")
			->GetText();
		model = std::static_pointer_cast<GZJModel>(
			GZJModelManager::GetInstance()->FindResByName(modelName));
	}
	
	void GZJEntity::DoParseShaderData(TiXmlElement * ele)
	{
		String shaderName = ele->FirstChildElement("name")->GetText();
		shader = std::static_pointer_cast<GZJShader>(
			GZJShaderManager::GetInstance()->FindResByName(shaderName));
	}

}

