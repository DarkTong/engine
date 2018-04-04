#include "GZJEvent.h"

namespace GZJ_ENGINE {
	GZJEvent::GZJEvent(EventConstant id):eventId(id)
	{
		objFuncs.clear();
		noObjFuncs.clear();
	}

	void GZJEvent::Fire(const GZJEventParamObj& param)
	{
		for (auto it = objFuncs.begin(); it != objFuncs.end(); ++it)
			it->second(param);

		// 临时，不处理
		//for (auto it = noObjFuncs.begin(); it != noObjFuncs.end(); ++it)
		//	(*it)(param);
	}

	void GZJEvent::Bind(TargetID targetId, NormalDelegate func)
	{
		auto it = objFuncs.find(targetId);

		if (it != objFuncs.end()) 
		{
			String s1 = " EventId:" + std::to_string(eventId);
			String s2 = " TargetId:" + std::to_string(targetId);
			cout << "This Obj has Bind this Event!!!" << s1 << s2 << endl;
		}
		else
		{
			objFuncs.insert(Pair<TargetID, NormalDelegate>(
				targetId, func));
		}
	}

	void GZJEvent::UnBind(TargetID targetId)
	{
		auto it = objFuncs.find(targetId);

		if (it == objFuncs.end())
		{
			String s1 = " EventId:" + std::to_string(eventId);
			String s2 = " TargetId:" + std::to_string(targetId);
			cout << "This Obj has UnBind this Event!!!" << s1 << s2 << endl;
		}
		else
		{
			objFuncs.erase(targetId);
		}
	}

	void GZJEvent::UnBindAll()
	{
		objFuncs.clear();
		noObjFuncs.clear();
	}

	void GZJEvent::Finalize()
	{
		UnBindAll();
	}

}
