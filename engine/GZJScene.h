#pragma once

#include <tinyxml\tinyxml.h>

#include "GZJRequire.h"
#include "GZJTransform.h"
#include "GZJShaderManager.h"
#include "GZJModelManager.h"
#include "GZJLight.h"
#include "GZJParallelLight.h"
#include "GZJPointLight.h"
#include "GZJSpotLight.h"
#include "GZJEntity.h"
#include "GZJCamera.h"

namespace GZJ_ENGINE
{
	//����ID
	typedef unsigned int SceneID;

	class GZJScene
	{
	private:
		/** ���ø�·��
		*/
		const static String CONFIG_PATH_PRE;

		/** ����id
		*/
		SceneID _id;

		/**  ����ʵ��
		*/
		//Map<String, GZJEntityPtr> entityMap;
		std::vector<GZJEntityPtr> entityArr;

		/** ��������ʵ��
		*/
		Map<LightID, GZJLightPtr> lightMap;

		/** ��Ⱦ������shader
		*/
		Map<ShaderID, GZJShaderPtr> shaderMap;

		/** �����ļ�·��
		*/
		String configPath;

		/** shader������
		*/
		GZJShaderManagerPtr shaderMgr;

		/** model������
		*/
		GZJModelManagerPtr modelMgr;

		/** ����
		*/
		GZJWindowPtr win;

		/** �������
		*/
		GZJCamera mainCamera;

		/** �Ƿ���shadow
		*/
		bool isOpenShadow;

		// depth id
		unsigned int depthBuffer = 0;
		unsigned int depthTexture = 0;
		GZJShaderPtr depthShader;

	public:
		GZJScene(unsigned int id);
		
		~GZJScene();

	private:
		// ����
		/** �������ݲ���
		*/
		void DoParseConfig(TiXmlElement * ele);

		/** ������������
		*/
		void DoParseLightData(TiXmlElement * ele);

		/** ����ʵ������
		*/
		void DoParseEntityData(TiXmlElement * ele);

		/** ���������������
		*/
		void DoParseMainCameraData(TiXmlElement * ele);
		
		/** ����shadow����
		*/
		void DoParseShadowData(TiXmlElement * ele);

	private:

		void DoLoad();

		void DoUnLoad();

		/** �������֡����
		*/
		void BuildDepthMap();

	public:
		void ParseConfig();

		void Load();

		void UnLoad();

		void RenderToDepth();

		void RenderToNormal();

		void Render();
	};
}

