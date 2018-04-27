#include "GZJResource.h"

namespace GZJ_ENGINE {
	GZJResource::GZJResource(GZJResourceManager* manager, const String& name, ResourceHandle handle)
		:_mgr(manager), _name(name), _handle(handle)
	{
		_state	= ResState::UNPREPARE;
		_path = manager->GetResRoot() + "\\" + name;
	}

	void GZJResource::Prepare()
	{
		_state = ResState::UNLOAD;
	}

	void GZJResource::SyncLoad()
	{
		ResState state = GetState();
		if (state == UNLOAD)
		{
			SetState(LOADING);
			Load();
		}
		else
		{
			cout << "This Resource is not UnLoad!!, state:" << _state << " path:" << _path << endl;
		}
	}

	void GZJResource::AsyncLoad()
	{
		ResState state = GetState();
		if (state == UNLOAD)
		{
			GZJResourceLoad::GetInstance()
				->AddRes(_mgr->FindResByName(_name), GetResType());
		}
		else
		{
			cout << "This Resource is not UnLoad!!, path:" << _path << endl;
		}
	}

	ResourceHandle GZJResource::GetResHandle()
	{
		return _handle;
	}

	void GZJResource::Load()
	{
		try {
			DoLoad();
			SetState(LOADED);
		}
		catch(const char *error){
			cout << error << endl;
		}
	}

	void GZJResource::UnLoad()
	{
		if (GetState() == ResState::LOADED)
		{
			DoUnLoad();
			SetState(UNLOAD);
		}
	}

	void GZJResource::SetState(ResState state)
	{
		//std::lock_guard<std::mutex> lk(mutexToState);
		_state = state;
	}

	ResState GZJResource::GetState() const
	{
		//std::lock_guard<std::mutex> lk(mutexToState);
		return _state;
	}

}

