#pragma once

#define __GZJ_LIGHT_

#include <algorithm>

#include <tinyxml\tinyxml.h>

#include "GZJRequire.h"
#include "GZJTransform.h"
#include "GZJTools.h"

namespace GZJ_ENGINE
{
	typedef unsigned int LightID;

	enum LightType
	{
		Light_ParallelLight,
		Light_PointLight,
		Light_SpotLight,
	};

	enum LightData
	{
		// 通用光数据
		LightData_Ambient,
		LightData_Diffuse,
		LightData_Specular,
		LightData_Intensity,
		LightData_Position,
		// 点光源数据
		LightData_Param_K1,
		LightData_Param_K2,
		// 聚光光源数据
		LightData_Direction,
		LightData_InnerAngle,
		LightData_OutterAngle,
	};

	/** 最小光照强度
	*/
	const float MIN_LIGHT_INTENSITY = 0.0f;
	/** 最大光照强度
	*/
	const float MAX_LIGHT_INTENSITY = 1.0f;
	/** 最小光照颜色
	*/
	const Vector3 MIN_LIGHT_COLOR = Vector3(0.0f, 0.0f, 0.0f);
	/** 最大光照颜色
	*/
	const Vector3 MAX_LIGHT_COLOR = Vector3(1.0f, 1.0f, 1.0f);

	class GZJLight
	{
	public:
		/** 静态标志, 代表没有某属性
		*/
		static String None;

	public:
		// '构造1-1',使用默认数据的构造函数,委托 '构造1-2'
		GZJLight(GZJLightManager* manager);

		// '构造1-2',使用手动设置数据的构造函数
		GZJLight(GZJLightManager* manager,
			Vector3 position, Vector3 ambientLight,
			Vector3 diffuseLight, Vector3 specularLight, 
			float intensity);

		~GZJLight();
	protected:
		// 属性

		/** 管理器
		*/
		GZJLightManager* _mgr;

		/** 光源ID
		*/
		LightID _id;

		/** 光源类型
		*/
		LightType lightType;

		///** 光源位置信息
		//*/
		//GZJTransform transform;
		/** 光源模型
		*/
		GZJModelPtr _model;

		/** 全局光照分量
		*/
		Vector3 ambientLight;

		/** 漫放射光照分量
		*/
		Vector3 diffuseLight;

		/** 高光光照分量
		*/
		Vector3 specularLight;

		/** 光照强度
		*/
		float intensity;
	protected:
		// 对内接口

		/** 解析光照数据具体操作
		*/
		virtual void DoParseLightData(TiXmlElement * ele);

	public:
		// 对外接口

		/** 设置Vector3的属性
		*/
		virtual void SetVector3(LightData type, const Vector3& data);

		/** 设置float属性
		*/
		virtual void SetFloat(LightData type, const float& data);

		/** 获取Vector3属性
		*/
		virtual Vector3 GetVector3(LightData type);

		/** 获取float属性
		*/
		virtual float GetFloat(LightData type);

		/** 获取光资源类型
		*/
		LightType GetLightType();

		/** 解析光照数据接口
		*/
		void ParseLightData(TiXmlElement * lightElement);

		/**获取光源ID
		*/
		LightID GetID();

		/** 获取模型
		*/
		GZJModelPtr GetModel();

	};
}

#include "GZJLightManager.h"
#include "GZJModel.h"

