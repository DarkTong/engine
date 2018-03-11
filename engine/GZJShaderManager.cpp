#include "GZJShaderManager.h"

namespace GZJ_ENGINE {
	GZJShaderManagerPtr GZJShaderManager::_instance = nullptr;
	
	const String GZJShaderManager::rootPath = ENGINE_ROOT_PATH + "\\src\\shader";
	
	bool GZJShaderManager::LOAD_ALL_SHADER_WHEN_CREATE = true;

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
		// Çå¿Õshader¶ÔÏó
		GZJShaderPtr _ptr = nullptr;
		for (auto it = resMap.begin(); it != resMap.end(); ++it) {
			_ptr = std::dynamic_pointer_cast<GZJShader>(it->second);
			_ptr->DeleteProgram();
			_ptr.reset();
		}
		resMap.clear();
		_nameSet.clear();
	}

	void GZJShaderManager::PrepareAll()
	{
		GetAllShaderName();
		GZJResourcePtr _ptr;
		for (auto it = _nameSet.begin(); it != _nameSet.end(); ++it) {
			CreateRes(*it);
		}
	}
	
	GZJResource * GZJShaderManager::createImp(const String & name)
	{
		GZJResourceManagerPtr tmp = std::dynamic_pointer_cast<GZJResourceManager>(_instance);
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
			file_name = it->substr(0, pos - 1);
			if (file_ext == "vs" || file_ext == "fs") {
				_nameSet.insert(file_name);
			}
		}
		
		// debug
		std::cout << _nameSet.size() << std::endl;
	}
}
