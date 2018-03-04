#include "GZJResourceGroupManager.h"

namespace GZJ_ENGINE {
	GZJResourceGroupManagerPtr GZJResourceGroupManager::_instance = nullptr;
	GZJResourceGroupManager::GZJResourceGroupManager() {

	}

	GZJResourceManagerPtr GZJResourceGroupManager::GetResManagerByType(ResourceType type)
	{
		auto it = _resMgrMap.find(type);
		assert(it != _resMgrMap.end());

		return it->second;
	}

}
