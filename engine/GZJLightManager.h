#pragma once

#include "GZJRequire.h"
#include "GZJLight.h"

namespace GZJ_ENGINE
{
	// ��ʱ������ID
	typedef unsigned int SceneID;

	/** ��Դ����
	*/
	typedef Map<LightID, GZJLightPtr> LightMap;
	/** ������Դ����
	*/
	typedef std::map<SceneID, LightMap> SceneLightsMap;

	class GZJLightManager
	{
		/** ����
		*/
	private:
		static GZJLightManagerPtr _instance;
	public:
		static GZJLightManagerPtr GetInstance();

		/** ��������
		*/
	public:
		GZJLightManager();
		~GZJLightManager();

	private:
		// ����

		String _resRoot;



		/** ��������¼��Դ
		*/
		SceneLightsMap sceneLightsMap;

		/** ��Դ���ܼ���
		*/
		LightMap lightMap;

		/** �Զ����Դ�����ID
			(�۲���)
		*/
		LightID selfDefindId;
		static const LightID MIN_SELF_DEF_ID = 10000;
		static const LightID MAX_SELF_DEF_ID = 20000;

	public:
		// ����ӿ�

		void StartUp();

		void ShutDown();

		/** �򳡾���ӹ�Դ
		*/
		void AddLightToScene(const SceneID& sceneId,
			GZJLightPtr lightPtr);

		/** ��ȡ��Դ��Ϣ
		*/
		const LightMap& GetSceneLightMap(const SceneID& sceneId);

		/** �Ƴ�����������Դ
		*/
		void RemoveLightToScene(const SceneID& sceneId,
			const LightID& id);

		/** �Ƴ��������й�����Դ
		*/
		void RemoveAllLightToScene(const SceneID& sceneId);

		String GetResRoot();

		///** ����������Դ
		//@param ����id��1Ϊȫ��
		//*/
		//GZJLightPtr CreateRes(const LightType& type, TiXmlElement *ele
		//	, const SceneID& sceneId = 1);

	private:
		// ���������Ľӿ�

		/** ���ݳ�����ȡ������Դ�ļ�
		*/
		void LoadByScene(const SceneID& sceneId);

		///** ������Դ�ľ������
		//*/
		//GZJLightPtr createImp(const LightType& type);

	};
}

#include "GZJParallelLight.h"
#include "GZJPointLight.h"
#include "GZJSpotLight.h"

