#include "GZJShader.h"

namespace GZJ_ENGINE {
	

	void GZJShader::Init()
	{
		dataMap.clear();
	}

	void GZJShader::CheckCompliceErrors(ShaderID id, ShaderType type)
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

	GZJShader::GZJShader(GZJResourceManager* manager, const String & name, ResourceHandle handle)
		:GZJResource(manager, name, handle)
	{
		Init();
	}

	String GZJShader::ReadSrc(const String & name, ShaderType type)
	{
		// 1. 从文件路径中获取顶点/片段着色器
		std::ifstream file;
		std::stringstream stream;
		String path;
		// 保证ifstream对象可以抛出异常：
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			if (type == ShaderType::VERTEX_SHADER)
				path = _path + ".vs";
			else if (type == ShaderType::FRAGMENT_SHADER)
				path = _path + ".fs";
			/*std::cout << "path:" << path << std::endl;*/
			// 打开文件
			file.open(path);
			// 读取文件的缓冲内容到数据流中
			stream.clear();
			stream.str("");
			stream << file.rdbuf();
			// 关闭文件处理器
			file.close();
			// 转换数据流到string
			String code = stream.str();

			return code;
		}
		catch (std::ifstream::failure e)
		{
			file.close();
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			return "";
		}
	}

	ShaderID GZJShader::LoadShader(const String & name, ShaderType type)
	{
		String src = ReadSrc(name, type);

		assert(!src.empty());
		ShaderID id;
		if (type == VERTEX_SHADER) {
			id = glCreateShader(GL_VERTEX_SHADER);
		}
		else if (type == FRAGMENT_SHADER) {
			id = glCreateShader(GL_FRAGMENT_SHADER);
		}
		const char *a = src.c_str();
		glShaderSource(id, 1, &a, NULL);
		glCompileShader(id);

		CheckCompliceErrors(id, type);

		return id;
	}

	void GZJShader::DoLoad()
	{
		ShaderID it_1 = LoadShader(_name, VERTEX_SHADER);
		ShaderID it_2 = LoadShader(_name, FRAGMENT_SHADER);
		ShaderID id = glCreateProgram();
		glAttachShader(id, it_1);
		glAttachShader(id, it_2);
		glLinkProgram(id);

		CheckCompliceErrors(id, PROGRAM_SHADER);

		glDeleteShader(it_1);
		glDeleteShader(it_2);

		_id = id;
	}

	void GZJShader::DoUnLoad()
	{
		dataMap.clear();
	}

	String GZJShader::GetName()
	{
		return _name;
	}

	ShaderID GZJShader::GetShaderID()
	{
		return _id;
	}

	void GZJShader::Use() const
	{
		glUseProgram(_id);
	}

	void GZJShader::SetBool(const String & name, bool value) const
	{
		glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
	}

	void GZJShader::SetInt(const String & name, int value) const
	{
		glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
	}

	void GZJShader::SetFloat(const String & name, float value) const
	{
		glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
	}

	void GZJShader::SetMatrix(ShaderData param, Vector4x4 data)
	{
		const unsigned none = -1;
		unsigned int loc = -1;
		switch (param)
		{
		case Shader_LocalToWorld:
			loc = glGetUniformLocation(_id, "local2world");
			break;
		case Shader_WorldToView:
			loc = glGetUniformLocation(_id, "world2view");
			break;
		case Shader_ViewToProjection:
			loc = glGetUniformLocation(_id, "view2projection");
			break;
		default:
			std::cout << "GZJShader SetMatrix 参数错误!!!" << std::endl;
			assert(false);
		}
		if (loc == none) return;
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(data));
	}

	ResourceType GZJShader::GetResType()
	{
		return Shader;
	}

}
