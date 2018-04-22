#include "GZJTime.h"

namespace GZJ_ENGINE {
	GZJTimePtr GZJTime::_instance = nullptr;

	GZJTime::GZJTime() {
		assert(_instance == nullptr);
		now_time = 0;
		Update();
	}

	DWORD GZJTime::GetTickCount()
	{
		return ::GetTickCount();
	}

	void GZJTime::Update()
	{
		frame_time = GetTickCount() - now_time;
		now_time = GetTickCount();
	}


}

