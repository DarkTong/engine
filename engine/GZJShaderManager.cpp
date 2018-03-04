#include "GZJShaderManager.h"

namespace GZJ_ENGINE {
	const String GZJShaderManager::rootPath = ENGINE_ROOT_PATH + "\\shader";
	bool GZJShaderManager::LOAD_ALL_SHADER_WHEN_CREATE = true;
	void GZJShaderManager::CheckCompliceErrors(ShaderID id, ShaderType type)
	{
		int success = 0;
		if (type != PROGRAM_SHADER) {
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(id, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
					<< infoLog << "\n "
					<< "-- --------------------------------------------------- -- "
					<< std::endl;
			}
		}
		else {
			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(id, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_LINKING_ERROR of type: " << type << "\n"
					<< infoLog << "\n "
					<< "-- --------------------------------------------------- -- "
					<< std::endl;
			}
		}
	}
	GZJShaderPtr GZJShaderManager::LoadShaderObj(const String & name)
	{
		auto it = _objMap.find(name);
		if (it != _objMap.end())
			return it->second;

		ShaderID it_1 = LoadShader(name, VERTEX_SHADER);
		ShaderID it_2 = LoadShader(name, FRAGMENT_SHADER);
		ShaderID id = glCreateProgram();
		glAttachShader(id, it_1);
		glAttachShader(id, it_2);
		glLinkProgram(id);

		CheckCompliceErrors(id, PROGRAM_SHADER);
		GZJShaderPtr _ptr = GZJShaderPtr(new GZJShader((GZJShaderManagerPtr)this, id));
		_objMap.insert(Pair<String, GZJShaderPtr>(name, _ptr));

		return _ptr;
	}
	ShaderID GZJShaderManager::LoadShader(const String & name, ShaderType type)
	{
		ShaderID id;
		assert(ReadSrc(name, type));
		ShaderSourceMap::iterator it;
		if (type == VERTEX_SHADER) {
			id = glCreateShader(GL_VERTEX_SHADER);
			it = _vertexSrcMap.find(name);
		}
		else if (type == VERTEX_SHADER) {
			id = glCreateShader(GL_FRAGMENT_SHADER);
			it = _fragmentSrcMap.find(name);
		}
		const char *a = it->second.c_str();
		glShaderSource(id, 1, &a, NULL);
		glCompileShader(id);
		
		CheckCompliceErrors(id, type);
		return id;
	}
	bool GZJShaderManager::ReadSrc(const String & name, ShaderType type)
	{
		// 1. 从文件路径中获取顶点/片段着色器
		// 保证ifstream对象可以抛出异常：
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// 打开文件
			String path="";
			if (type == VERTEX_SHADER)
				path = rootPath + name + ".vs";
			else if (type == FRAGMENT_SHADER)
				path = rootPath + name + ".fs";
			file.open(path);
			// 读取文件的缓冲内容到数据流中
			stream << file.rdbuf();
			// 关闭文件处理器
			file.close();
			// 转换数据流到string
			String code;
			stream >> code;
			if (type == VERTEX_SHADER)
				_vertexSrcMap.insert(Pair<String, String>(name, code));
			else if (type == FRAGMENT_SHADER)
				_fragmentSrcMap.insert(Pair<String, String>(name, code));
			stream.clear();

			return true;
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			return false;
		}
	}
	GZJShaderManager::GZJShaderManager(bool flag)
	{
		LOAD_ALL_SHADER_WHEN_CREATE = flag;

		// 获取所有文件名字
		ReadShaderName();

		if (LOAD_ALL_SHADER_WHEN_CREATE)
			LoadAll();
	}
	GZJShaderPtr GZJShaderManager::GetShaderObjByName(const String & name)
	{
		return LoadShaderObj(name);
	}
	void GZJShaderManager::LoadAll()
	{
		for (auto it = _nameSet.begin(); it != _nameSet.end(); ++it)
			LoadShaderObj(*it);
	}
	void GZJShaderManager::ReadShaderName()
	{
		std::vector<String> fileNames;
		GZJTools::GetAllFileName(fileNames, rootPath, JUST_FILE);
		size_t len;
		String str;
		for (auto it = fileNames.begin(); it != fileNames.end(); ++it) {
			len = it->length();
			str.assign(it->substr(len - 3));
			if (str == ".vs" || str == ".fs") {
				str.assign(it->substr(0, len - 3));
				_nameSet.insert(str);
			}
		}
		// debug
		std::cout << "size:" << _nameSet.size() << std::endl;
	}
}
