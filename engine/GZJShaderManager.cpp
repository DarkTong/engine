#include "GZJShaderManager.h"

namespace GZJ_ENGINE {
	GZJShaderManagerPtr GZJShaderManager::_instance = nullptr;
	
	const String GZJShaderManager::rootPath = ENGINE_ROOT_PATH + "\\src\\shader";
	
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
		GZJShaderPtr _ptr(new GZJShader(id, name));
		_objMap.insert(Pair<String, GZJShaderPtr>(name, _ptr));

		glDeleteShader(it_1);
		glDeleteShader(it_2);

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
		else if (type == FRAGMENT_SHADER) {
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
		// 1. ���ļ�·���л�ȡ����/Ƭ����ɫ��
		std::ifstream file;
		std::stringstream stream;
		// ��֤ifstream��������׳��쳣��
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// ���ļ�
			String path="";
			if (type == VERTEX_SHADER)
				path = rootPath + "\\" + name + ".vs";
			else if (type == FRAGMENT_SHADER)
				path = rootPath + "\\" + name + ".fs";
			file.open(path);
			// ��ȡ�ļ��Ļ������ݵ���������
			stream.clear();
			stream.str("");
			stream << file.rdbuf();
			// �ر��ļ�������
			file.close();
			// ת����������string
			String code = stream.str();
			if (type == VERTEX_SHADER)
				_vertexSrcMap.insert(Pair<String, String>(name, code));
			else if (type == FRAGMENT_SHADER)
				_fragmentSrcMap.insert(Pair<String, String>(name, code));

			// debug
			// std::cout << code << std::endl;

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
		assert(_instance == nullptr);
		_instance = GZJShaderManagerPtr(this);

		LOAD_ALL_SHADER_WHEN_CREATE = flag;

		// ��ȡ�����ļ�����
		ReadShaderName();

		if (LOAD_ALL_SHADER_WHEN_CREATE)
			LoadAll();
	}
	
	//GZJShaderManager::~GZJShaderManager()
	//{
	//}
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
		std::cout << "path:" << rootPath << std::endl;
		std::vector<String> fileNames;
		std::cout << "fileNameSize:" << fileNames.size() << std::endl;
		GZJTools::GetAllFileName(fileNames, rootPath, JUST_FILE);
		size_t len;
		String str;
		for (auto it = fileNames.begin(); it != fileNames.end(); ++it) {
			len = it->length();
			str = it->substr(len - 3);
			if (str == ".vs" || str == ".fs") {
				str = it->substr(0, len - 3);
				_nameSet.insert(str);
			}
		}
		// debug
		std::cout << "size:" << _nameSet.size() << std::endl;
	}
}
