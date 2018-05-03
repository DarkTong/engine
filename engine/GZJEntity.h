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
		// ģ��
		GZJModelPtr model;

		// transform
		GZJTransform transform;

		// shader
		GZJShaderPtr shader;

		// component
		// move
		GZJMovePtr move;

	public:
		// ����ӿ�
		// ��Ⱦ
		void Draw(GZJShaderPtr shader=nullptr);

		// ����xml����
		void ParseData(TiXmlElement* ele);

	private:
		// ���ڽӿ�

		/** ����transform����
		*/
		void DoParseTransformData(TiXmlElement* ele);

		/** ����Transfomr�е�Vector3����
		*/
		Vector3 ParseTransVector3(TiXmlElement * ele);

		Vector3 ParseVector3(TiXmlElement * ele);

		/** ����Model����
		*/
		void DoParseModelData(TiXmlElement * ele);

		/** ����shader����
		*/
		void DoParseShaderData(TiXmlElement * ele);

		/** �����������
		*/
		void DoParseComponentData(TiXmlElement * ele);
	};
}

