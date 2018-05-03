#pragma once

#include <tinyxml\tinyxml.h>
#include <cstdlib>

#include "GZJRequire.h"
#include "GZJShaderManager.h"
#include "GZJTransform.h"
#include "GZJModel.h"
#include "GZJMove.h"

namespace GZJ_ENGINE 
{
	class GZJEntity
	{		
	public:
		// 模型
		GZJModelPtr model;

		// transform
		GZJTransform transform;

		// shader
		GZJShaderPtr shader;

		// component
		// move
		GZJMovePtr move;

	public:
		// 对外接口
		// 渲染
		void Draw(GZJShaderPtr shader=nullptr);

		// 解析xml数据
		void ParseData(TiXmlElement* ele);

	private:
		// 对内接口

		/** 解析transform数据
		*/
		void DoParseTransformData(TiXmlElement* ele);

		/** 解析Transfomr中的Vector3数据
		*/
		Vector3 ParseTransVector3(TiXmlElement * ele);

		Vector3 ParseVector3(TiXmlElement * ele);

		/** 解析Model数据
		*/
		void DoParseModelData(TiXmlElement * ele);

		/** 解析shader数据
		*/
		void DoParseShaderData(TiXmlElement * ele);

		/** 解析组件数据
		*/
		void DoParseComponentData(TiXmlElement * ele);
	};
}

