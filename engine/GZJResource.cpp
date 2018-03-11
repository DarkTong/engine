#include "GZJResource.h"

namespace GZJ_ENGINE {
	GZJResource::GZJResource(GZJResourceManagerPtr manager, const String& name, ResourceHandle handle)
		:_mgr(manager), _name(name), _handle(handle)
	{
		_state	= ResState::UNPREPARE;
		_path = manager->GetResRoot() + "\\" + name;
	}

	void GZJResource::SetState(ResState state)
	{
		_state = state;
	}

}

