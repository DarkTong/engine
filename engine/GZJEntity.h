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
		// 模型
		GZJModelPtr model;

		// transform
		GZJTransform transform;

	public:
		// 对外接口
		// 渲染
		void Draw(GZJShaderPtr shader);

		// 解析xml数据
		void ParseData(TiXmlElement* ele);

	};
}

