#pragma once

#define __GZJ_LIGHT_

#include <algorithm>

#include <tinyxml\tinyxml.h>

#include "GZJRequire.h"
#include "GZJTransform.h"
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
		// ͨ�ù�����
		LightData_Ambient,
		LightData_Diffuse,
		LightData_Specular,
		LightData_Intensity,
		LightData_Position,
		LightData_Near_Plane,
		LightData_Far_Plane,
		LightData_Ortho_Width,
		LightData_Perspective_Angle,
		// ���Դ����
		LightData_Param_K1,
		LightData_Param_K2,
		// �۹��Դ����
		LightData_Direction,
		LightData_InnerAngle,
		LightData_OutterAngle,
		//  ��ռ�
		LightData_LightSpace,
	};

	/** ��С����ǿ��
	*/
	const float MIN_LIGHT_INTENSITY = 0.0f;
	/** ������ǿ��
	*/
	const float MAX_LIGHT_INTENSITY = 1.0f;
	/** ��С������ɫ
	*/
	const Vector3 MIN_LIGHT_COLOR = Vector3(0.0f, 0.0f, 0.0f);
	/** ��������ɫ
	*/
	const Vector3 MAX_LIGHT_COLOR = Vector3(1.0f, 1.0f, 1.0f);

	class GZJLight
	{
	public:
		/** ��̬��־, ����û��ĳ����
		*/
		static String None;

	public:
		// '����1-1',ʹ��Ĭ�����ݵĹ��캯��,ί�� '����1-2'
		GZJLight(GZJLightManager* manager);

		// '����1-2',ʹ���ֶ��������ݵĹ��캯��
		GZJLight(GZJLightManager* manager,
			Vector3 position, Vector3 ambientLight,
			Vector3 diffuseLight, Vector3 specularLight, 
			float intensity);

		~GZJLight();
	protected:
		// ����
		/** ��ռ�
		*/
		Vector4x4 lightSpace;

		/** ������
		*/
		GZJLightManager* _mgr;

		/** ��ԴID
		*/
		LightID _id;

		/** ��Դ����
		*/
		LightType lightType;

		///** ��Դλ����Ϣ
		//*/
		//GZJTransform transform;
		/** ��Դģ��
		*/
		GZJModelPtr _model;

		/** ȫ�ֹ��շ���
		*/
		Vector3 ambientLight;

		/** ��������շ���
		*/
		Vector3 diffuseLight;

		/** �߹���շ���
		*/
		Vector3 specularLight;

		/** ����ǿ��
		*/
		float intensity;

		/** ��ƽ��
		*/
		float nearPlane;

		/** Զƽ��
		*/
		float farPlane;

	private:
		// ���߷���

		/** �����������ݾ������
		*/
		void DoParse(TiXmlElement * ele);

		/** ����ƽ�й���������
		*/
		void DoParseParallerLightData(TiXmlElement * ele);

		/** ���������������
		*/
		void DoParsePointLightData(TiXmlElement * ele);

		/** �����۹���������
		*/
		void DoParseSpotLightData(TiXmlElement * ele);

		/** ������Դ�������
		*/
		void DoParseLightData(TiXmlElement * ele);

		/** ����Model����
		*/
		void DoParseModelData(TiXmlElement * ele);

		/** ����Vector3����
		*/
		Vector3 ParseVector3(TiXmlElement * node);

	public:
		// ����ӿ�

		/** ����Vector3������
		*/
		virtual void SetVector3(LightData type, const Vector3& data);

		/** ����float����
		*/
		virtual void SetFloat(LightData type, const float& data);

		/** ��ȡVector3����
		*/
		virtual Vector3 GetVector3(LightData type);

		/** ��ȡfloat����
		*/
		virtual float GetFloat(LightData type);

		/** ��ȡ��������
		*/
		virtual Vector4x4 GetMatrix(LightData type);

		/** ��ȡ����Դ����
		*/
		LightType GetLightType();

		/** �����������ݽӿ�
		*/
		void ParseLightData(TiXmlElement * lightElement);

		/**��ȡ��ԴID
		*/
		LightID GetID();

		/** ��ȡģ��
		*/
		GZJModelPtr GetModel();

		/** ���ù������ݸ�shader
		*/
		void SetToShader(GZJShaderPtr shader);

		private:
			//  ���߷���
			void UpdateData();
	};
}

#include "GZJLightManager.h"
#include "GZJModel.h"

