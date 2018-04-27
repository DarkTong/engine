#pragma once

#include <tinyxml\tinyxml.h>

#include "GZJRequire.h"
#include "GZJShader.h"
#include "GZJTransform.h"
#include "GZJModel.h"

namespace GZJ_ENGINE 
{
	class GZJEntity
	{		
	public:
		// ģ��
		GZJModelPtr model;

		// transform
		GZJTransform transform;

	public:
		// ����ӿ�
		// ��Ⱦ
		void Draw(GZJShaderPtr shader);

		// ����xml����
		void ParseData(TiXmlElement* ele);

	};
}

