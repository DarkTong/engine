#include "GZJEntity.h"

namespace GZJ_ENGINE
{
	void GZJEntity::Draw(GZJShaderPtr shader)
	{
		shader->Use();
		shader->SetMatrix(Shader_LocalToWorld,
			transform.GetMatrix(LocalToWorld));
		model->Draw(shader);
	}

	void GZJEntity::ParseData(TiXmlElement * ele)
	{
	}
	
}

