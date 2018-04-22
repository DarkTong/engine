#pragma once

#include "GZJRequire.h"
#include "GZJLight.h"

namespace GZJ_ENGINE
{
	// 临时，场景ID
	typedef unsigned int SceneID;

	/** 光源集合
	*/
	typedef Map<LightID, GZJLightPtr> LightMap;
	/** 场景光源集合
	*/
	typedef std::map<SceneID, LightMap> SceneLightsMap;

	class GZJLightManager
	{
		/** 单例
		*/
	private:
		static GZJLightManagerPtr _instance;
	public:
		static GZJLightManagerPtr GetInstance();

		/** 构造析构
		*/
	public:
		GZJLightManager();
		~GZJLightManager();

	private:
		// 属性

		String _resRoot;



		/** 按场景记录光源
		*/
		SceneLightsMap sceneLightsMap;

		/** 光源的总集合
		*/
		LightMap lightMap;

		/** 自定义光源的随机ID
			(咱不用)
		*/
		LightID selfDefindId;
		static const LightID MIN_SELF_DEF_ID = 10000;
		static const LightID MAX_SELF_DEF_ID = 20000;

	public:
		// 对外接口

		void StartUp();

		void ShutDown();

		/** 向场景添加光源
		*/
		void AddLightToScene(const SceneID& sceneId,
			GZJLightPtr lightPtr);

		/** 获取光源信息
		*/
		const LightMap& GetSceneLightMap(const SceneID& sceneId);

		/** 移除场景光照资源
		*/
		void RemoveLightToScene(const SceneID& sceneId,
			const LightID& id);

		/** 移除场景所有关照资源
		*/
		void RemoveAllLightToScene(const SceneID& sceneId);

		String GetResRoot();

		///** 创建光照资源
		//@param 场景id，1为全局
		//*/
		//GZJLightPtr CreateRes(const LightType& type, TiXmlElement *ele
		//	, const SceneID& sceneId = 1);

	private:
		// 隐藏起来的接口

		/** 根据场景读取光照资源文件
		*/
		void LoadByScene(const SceneID& sceneId);

		///** 创建资源的具体操作
		//*/
		//GZJLightPtr createImp(const LightType& type);

	};
}

#include "GZJParallelLight.h"
#include "GZJPointLight.h"
#include "GZJSpotLight.h"

