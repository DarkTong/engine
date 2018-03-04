#include "GZJRequire.h"
#include "GZJResourceManager.h"

namespace GZJ_ENGINE {
	enum ResourceType {
		TEXTURE,
		MESH,
	};

	typedef Map<ResourceType, GZJResourceManagerPtr> ResGroupMgr;
	typedef Map<ResourceType, String> ResLoacationMap;

	class GZJResourceGroupManager {
	public:
		static GZJResourceGroupManagerPtr _instance;
		static GZJResourceGroupManagerPtr GetInstance() {
			if (_instance == nullptr)
				_instance = static_cast<GZJResourceGroupManagerPtr>(new GZJResourceGroupManager());
			return _instance;
		}
	private:
		GZJResourceGroupManager();

	private:
		/** ���������Դ
		*/
		ResGroupMgr _resMgrMap;
		/** ��¼������Դ�����·��
		*/
		ResLoacationMap _resLocationMap;

	public:
		/** ��ȡ��Դ������
		*/
		GZJResourceManagerPtr GetResManagerByType(ResourceType type);

	};

}
