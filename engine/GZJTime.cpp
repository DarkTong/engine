#include "GZJTime.h"
#include <iostream>

namespace GZJ_ENGINE {
	GZJTimePtr GZJTime::_instance = nullptr;

	GZJTime::GZJTime() {
		assert(_instance == nullptr);
		Update();
	}

	DWORD GZJTime::GetTickCount()
	{
		return ::GetTickCount();
	}

	void GZJTime::Update()
	{
		now_time = GetTickCount();
	}


}

