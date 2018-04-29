#include "GZJLightManager.h"

namespace GZJ_ENGINE
{
	GZJLightManagerPtr GZJLightManager::_instance = nullptr;

	GZJLightManagerPtr GZJLightManager::GetInstance()
	{
		if (_instance == nullptr)
			_instance = MakeShared<GZJLightManager>();
		return _instance;
	}

	GZJLightManager::GZJLightManager()
	{
		_resRoot = ENGINE_SRC_ROOT_PATH + "\\light";
		selfDefindId = MIN_SELF_DEF_ID;
	}

	GZJLightManager::~GZJLightManager()
	{
	}

	void GZJLightManager::StartUp()
	{
		sceneLightsMap.clear();
	}

	void GZJLightManager::ShutDown()
	{
		sceneLightsMap.clear();
	}

	void GZJLightManager::AddLightToScene(const SceneID& sceneId,
		GZJLightPtr lightPtr)
	{
		auto it = sceneLightsMap.find(sceneId);
		if (it == sceneLightsMap.end())
		{
			sceneLightsMap[sceneId] = LightMap();
			it = sceneLightsMap.find(sceneId);
		}
		it->second[lightPtr->GetID()] = lightPtr;
	}

	const LightMap & GZJLightManager::GetSceneLightMap(const SceneID& sceneId)
	{
		auto it = sceneLightsMap.find(sceneId);
		if (it == sceneLightsMap.end())
		{
			LoadByScene(sceneId);
			it = sceneLightsMap.find(sceneId);
		}
		return it->second;
	}

	void GZJLightManager::RemoveLightToScene(const SceneID& sceneId,
		const LightID& id)
	{
		auto it = sceneLightsMap.find(sceneId);
		if (it != sceneLightsMap.end())
		{
			it->second.erase(id);
		}
	}

	void GZJLightManager::RemoveAllLightToScene(const SceneID& sceneId)
	{
		sceneLightsMap.erase(sceneId);
	}

	String GZJLightManager::GetResRoot()
	{
		return _resRoot;
	}

	void GZJLightManager::LoadByScene(const SceneID& sceneId)
	{
		String path = GetResRoot() + "\\" + std::to_string(sceneId) + ".xml";
		TiXmlDocument doc;

		if (!doc.LoadFile(path.c_str()))
		{
			cout << "read light file fail!!, path:" << path << endl;
			return;
		}

		TiXmlElement *lightEle = doc.RootElement()->FirstChildElement();
		for (; lightEle != nullptr; lightEle = lightEle->NextSiblingElement())
		{
			// 根据类型创建光照资源
			// 然后初始化资源
			String type = lightEle->Attribute("type");
			GZJLightPtr lightPtr;
			if (type == "ParallelLight")
			{
				lightPtr = std::static_pointer_cast<GZJLight>(
					MakeShared<GZJParallelLight>(this));
			}
			else if (type == "PointLight")
			{
				lightPtr = std::static_pointer_cast<GZJLight>(
					MakeShared<GZJPointLight>(this));
			}
			else if (type == "SpotLight")
			{
				lightPtr = std::static_pointer_cast<GZJLight>(
					MakeShared<GZJSpotLight>(this));
			}
			else
			{
				cout << "not contain this light type!!, type:" << type << endl;
				continue;
			}

			lightPtr->ParseLightData(lightEle);
		}

	}

}
