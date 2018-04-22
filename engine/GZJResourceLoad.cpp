#include "GZJResourceLoad.h"

namespace GZJ_ENGINE {
	//const int GZJResourceLoad::NUMBER_OF_RES_TYPE = 3;

	GZJResourceLoadPtr GZJResourceLoad::_instance = nullptr;

	GZJResourceLoadPtr GZJResourceLoad::GetInstance()
	{
		if (_instance == nullptr)
			_instance = MakeShared<GZJResourceLoad>();
		return _instance;
	}

	GZJResourceLoad::GZJResourceLoad()
	{
		if (_instance != nullptr)
		{
			cout << "GZJResourceLoadPtr Can't Create twice!!" << endl;
			assert(false);
		}

		for (int i = 0; i < NUMBER_OF_RES_TYPE; ++i)
		{
			_threadState[i] = ResLoadState_Close;
		}

	}

	GZJResourceLoad::~GZJResourceLoad()
	{
		for (int i = 0; i < NUMBER_OF_RES_TYPE; ++i)
			if (_threadGroup[i].joinable())
			{
				_threadState[i] = ResLoadState_Close;
				_threadGroup[i].join();
			}
	}

	void GZJResourceLoad::StartUp()
	{
		for (int i = 0; i < NUMBER_OF_RES_TYPE; ++i)
		{
			_threadState[i] = ResLoadState_Free;
		}

		_threadGroup[Texture] = std::thread(&GZJResourceLoad::DoLoadTextureRes, this);
		_threadGroup[Mesh] = std::thread(&GZJResourceLoad::DoLoadMeshRes, this);
		_threadGroup[Model] = std::thread(&GZJResourceLoad::DoLoadModelRes, this);
	}

	void GZJResourceLoad::ShutDown()
	{
		for (int i = 0; i < NUMBER_OF_RES_TYPE; ++i)
			if (_threadGroup[i].joinable())
			{
				_threadState[i] = ResLoadState_Close;
				_threadGroup[i].detach();
				_threadFlag[i].notify_one();
			}
	}

	void GZJResourceLoad::DoLoadTextureRes()
	{
		const ResourceType type = Texture;
		while (_threadState[type] != ResLoadState_Close)
		{
			std::unique_lock<std::mutex> lk(_threadMutex[type]);
			_threadFlag[type].wait(lk,
				[this] {return !_resQueue[Texture].empty(); });

			if (_threadState[type] == ResLoadState_Close)
				break;

			GZJResourcePtr texturePtr = _resQueue[type].front();
			_resQueue[type].pop();

			texturePtr->SyncLoad();
		}
	}

	void GZJResourceLoad::DoLoadMeshRes()
	{
		const ResourceType type = Mesh;
		while (_threadState[type] != ResLoadState_Close)
		{
			std::unique_lock<std::mutex> lk(_threadMutex[type]);
			_threadFlag[type].wait(lk,
				[this] {return !_resQueue[Mesh].empty(); });

			if (_threadState[type] == ResLoadState_Close)
				break;

			GZJResourcePtr meshPtr = _resQueue[type].front();
			_resQueue[type].pop();

			meshPtr->SyncLoad();
		}
	}

	void GZJResourceLoad::DoLoadModelRes()
	{
		const ResourceType type = Model;
		while (_threadState[type] != ResLoadState_Close)
		{
			std::unique_lock<std::mutex> lk(_threadMutex[type]);
			_threadFlag[type].wait(lk,
				[this] {return !_resQueue[Model].empty(); });

			if (_threadState[type] == ResLoadState_Close)
				break;

			GZJResourcePtr modelPtr = _resQueue[type].front();
			_resQueue[type].pop();

			modelPtr->SyncLoad();
		}
	}

	void GZJResourceLoad::AddRes(GZJResourcePtr resPtr, ResourceType type)
	{
		if (Texture == type
			|| Mesh == type
			|| Model == type)
		{
			std::lock_guard<std::mutex> lk(_threadMutex[type]);
			_resQueue[type].push(resPtr);
			_threadFlag[type].notify_one();
		}
		else
		{
			cout << "Can't contain this resource!!!" << endl;
		}
	}

}