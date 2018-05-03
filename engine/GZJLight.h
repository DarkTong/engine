#pragma once

#define __GZJ_LIGHT_

#include <algorithm>

#include <tinyxml\tinyxml.h>

#include "GZJRequire.h"
#include "GZJTools.h"
#include "GZJWindow.h"

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
		LightData_Color,
		LightData_Intensity,
		LightData_Position,
		LightData_Near_Plane,
		LightData_Far_Plane,
		LightData_Ortho_Width,
		LightData_Perspective_Angle,
		// 点光源数据
		LightData_Param_K1,
		LightData_Param_K2,
		// 聚光光源数据
		LightData_Direction,
		LightData_InnerAngle,
		LightData_OutterAngle,
		//  光空间
		LightData_LightSpace,
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
		GZJLight();

		// '构造1-2',使用手动设置数据的构造函数
		GZJLight(
			Vector3 position, Vector3 ambientLight,
			Vector3 diffuseLight, Vector3 specularLight, 
			float intensity);

		~GZJLight();
	protected:
		// 属性
		/** 光空间
		*/
		Vector4x4 lightSpace;

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
		GZJEntityPtr _entity;

		/** 全局光照分量
		*/
		Vector3 ambientLight;

		/** 漫放射光照分量
		*/
		Vector3 diffuseLight;

		/** 高光光照分量
		*/
		Vector3 specularLight;

		/** 光的颜色
		*/
		Vector3 color;

		/** 光照强度
		*/
		float intensity;

		/** 近平面
		*/
		float nearPlane;

		/** 远平面
		*/
		float farPlane;

	private:
		// 工具方法

		/** 解析光照数据具体操作
		*/
		void DoParse(TiXmlElement * ele);

		/** 解析平行光特有数据
		*/
		void DoParseParallerLightData(TiXmlElement * ele);

		/** 解析点光特有数据
		*/
		void DoParsePointLightData(TiXmlElement * ele);

		/** 解析聚光特有数据
		*/
		void DoParseSpotLightData(TiXmlElement * ele);

		/** 解析光源相关数据
		*/
		void DoParseLightData(TiXmlElement * ele);

		/** 解析Vector3数据
		*/
		Vector3 ParseVector3(TiXmlElement * node);

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

		/** 获取矩阵数据
		*/
		virtual Vector4x4 GetMatrix(LightData type);

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
		GZJEntityPtr GetEntity();

		/** 设置光照数据给shader
		*/
		void SetToShader(GZJShaderPtr shader);

		private:
			//  工具方法
			void UpdateData();
	};
}

#include "GZJEntity.h"

