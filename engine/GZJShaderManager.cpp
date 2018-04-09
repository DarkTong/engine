#include "GZJShaderManager.h"

namespace GZJ_ENGINE {
	GZJShaderManagerPtr GZJShaderManager::_instance = nullptr;
	
	bool GZJShaderManager::LOAD_ALL_SHADER_WHEN_CREATE = true;

	GZJShaderManager::GZJShaderManager()
	{
		assert(_instance == nullptr);

		_resRoot = ENGINE_SRC_ROOT_PATH + "\\shader";
	}

	void GZJShaderManager::StartUp()
	{
		resMap.clear();
		_nameSet.clear();

		PrepareAll();

		//if (LOAD_ALL_SHADER_WHEN_CREATE)
		LoadAll();
	}

	void GZJShaderManager::ShutDown()
	{
		UnLoadAll();
		_nameSet.clear();
	}

	void GZJShaderManager::PrepareAll()
	{
		GetAllShaderName();
		GZJResourcePtr _ptr;
		for (auto it = _nameSet.begin(); it != _nameSet.end(); ++it) {
			CreateRes(*it);
			resMap[*it]->Prepare();
		}
	}
	
	GZJResource * GZJShaderManager::createImp(const String & name)
	{
		GZJResourceManager* tmp = static_cast<GZJResourceManager*>(this);
		return (new GZJShader(tmp, name, resHandle++));
	}

	void GZJShaderManager::GetAllShaderName()
	{
		FileNames fileNames;
		String file_name, file_ext;
		size_t pos;
		GZJTools::GetAllFileName(fileNames, _resRoot, JUST_FILE);
		for (FileNames::iterator it = fileNames.begin(); it != fileNames.end(); ++it) {
			pos = it->find_last_of(".");
			file_ext = it->substr(pos + 1);
			file_name = it->substr(0, pos);
			if (file_ext == "vs" || file_ext == "fs") {
				_nameSet.insert(file_name);
			}
		}
		
		// debug
		std::cout << "nameSet Size:" << _nameSet.size() << std::endl;
	}
}
