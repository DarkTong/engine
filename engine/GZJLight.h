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
		// ͨ�ù�����
		LightData_Ambient,
		LightData_Diffuse,
		LightData_Specular,
		LightData_Intensity,
		LightData_Position,
		// ���Դ����
		LightData_Param_K1,
		LightData_Param_K2,
		// �۹��Դ����
		LightData_Direction,
		LightData_InnerAngle,
		LightData_OutterAngle,
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
	protected:
		// ���ڽӿ�

		/** �����������ݾ������
		*/
		virtual void DoParseLightData(TiXmlElement * ele);

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

	};
}

#include "GZJLightManager.h"
#include "GZJModel.h"

