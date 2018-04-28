#include "GZJResource.h"

namespace GZJ_ENGINE {
	GZJResource::GZJResource(GZJResourceManager* manager, const String& name, ResourceHandle handle)
		:_mgr(manager), _name(name), _handle(handle)
	{
		_state	= ResState::UNPREPARE;
		_path = manager->GetResRoot() + "\\" + name;
		_count = 0;
	}

	void GZJResource::Prepare()
	{
		_state = ResState::UNLOAD;
	}

	void GZJResource::SyncLoad()
	{
		Load();
	}

	void GZJResource::AsyncLoad()
	{
		ResState state = GetState();
		GZJResourceLoad::GetInstance()
			->AddRes(_mgr->FindResByName(_name), GetResType());
	}

	ResourceHandle GZJResource::GetResHandle()
	{
		return _handle;
	}

	void GZJResource::Load()
	{
		_count++;
		ResState state = GetState();
		if (state == UNLOAD)
		{
			SetState(LOADING);
			try {
				DoLoad();
				SetState(LOADED);
			}
			catch (const char *error) {
				cout << error << endl;
				SetState(UNLOAD);
			}
		}
		else
		{
			cout << "This Resource is not UnLoad!!, state:" << _state << " path:" << _path << endl;
		}
	}

	void GZJResource::ForceUnLoad()
	{
		if (GetState() == ResState::LOADED)
		{
			DoUnLoad();
			_count = 0;
			SetState(UNLOAD);
		}
	}

	void GZJResource::UnLoad()
	{
		_count--;
		if (_count == 0)
			ForceUnLoad();
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

