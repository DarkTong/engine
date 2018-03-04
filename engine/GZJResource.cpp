#include "GZJResource.h"

namespace GZJ_ENGINE {
	GZJResource::GZJResource(GZJResourceManagerPtr manager, const String& path
		, const String& name, ResourceHandle handle)
		:_mgr(manager), _path(path), _name(name), _handle(handle)
	{
		_state = ResState::UNPREPARE;
	}

}

