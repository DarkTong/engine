#include "GZJEventSystem.h"

namespace GZJ_ENGINE {
	GZJEventSystemPtr GZJEventSystem::_instance = nullptr;

	void GZJEventSystem::StartUp()
	{
		events.clear();
	}

	void GZJEventSystem::Update()
	{
	}

	void GZJEventSystem::ShutDown()
	{
		events.clear();
	}

	void GZJEventSystem::Finalze()
	{
		if (_instance and _instance.use_count() > 1)
		{
			cout << "GZJEventSystem的Instance还有地方被使用" << endl;
			assert(false);
		}
	}

	void GZJEventSystem::Fire(EventConstant eventId, const GZJEventParamObj& param)
	{
		auto it = events.find(eventId);
		
		if (it == events.end()) 
		{
			cout << "this eventId no bind any event!!! eventId:" << eventId << endl;
		}
		else
		{
			it->second.Fire(param);
		}
	}

	void GZJEventSystem::Bind(TargetID targetId, EventConstant eventId, NormalDelegate func)
	{
		auto it = events.find(eventId);

		if (it == events.end()) 
		{
			events.insert(Pair<EventConstant, GZJEvent>(eventId, GZJEvent(eventId)));
			it = events.find(eventId);
		}

		it->second.Bind(targetId, func);

	}

	void GZJEventSystem::UnBind(TargetID targetId, EventConstant eventId)
	{
		auto it = events.find(eventId);

		if (it == events.end())
		{
			cout << "this eventId not be bind any!!! eventId:" << eventId << endl;
		}
		else
		{
			it->second.UnBind(targetId);
		}
	}

}
