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
	//场景ID
	typedef unsigned int SceneID;

	class GZJScene
	{
	private:
		/** 配置父路径
		*/
		const static String CONFIG_PATH_PRE;

		/** 场景id
		*/
		SceneID _id;

		/**  场景实体
		*/
		//Map<String, GZJEntityPtr> entityMap;
		std::vector<GZJEntityPtr> entityArr;

		/** 场景光照实体
		*/
		Map<LightID, GZJLightPtr> lightMap;

		/** 渲染场景的shader
		*/
		Map<ShaderID, GZJShaderPtr> shaderMap;

		/** 配置文件路径
		*/
		String configPath;

		/** shader管理器
		*/
		GZJShaderManagerPtr shaderMgr;

		/** model管理器
		*/
		GZJModelManagerPtr modelMgr;

		/** 窗口
		*/
		GZJWindowPtr win;

		/** 主摄像机
		*/
		GZJCamera mainCamera;

		/** 是否开启shadow
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
		// 解析
		/** 解析数据操作
		*/
		void DoParseConfig(TiXmlElement * ele);

		/** 解析光照数据
		*/
		void DoParseLightData(TiXmlElement * ele);

		/** 解析实体数据
		*/
		void DoParseEntityData(TiXmlElement * ele);

		/** 解析主摄像机数据
		*/
		void DoParseMainCameraData(TiXmlElement * ele);
		
		/** 解析shadow数据
		*/
		void DoParseShadowData(TiXmlElement * ele);

	private:

		void DoLoad();

		void DoUnLoad();

		/** 构建深度帧缓存
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

