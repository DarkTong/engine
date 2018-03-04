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
		/** 管理各种资源
		*/
		ResGroupMgr _resMgrMap;
		/** 记录各种资源的相对路径
		*/
		ResLoacationMap _resLocationMap;

	public:
		/** 获取资源管理器
		*/
		GZJResourceManagerPtr GetResManagerByType(ResourceType type);

	};

}
