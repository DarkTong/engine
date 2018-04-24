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

	void GZJShader::SetBool(const ShaderData& type, bool value) const
	{
		//glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
	}

	void GZJShader::SetInt(const ShaderData& type, int value) const
	{
		int loc = GL_INVALID_INDEX;
		//glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
		switch (type)
		{
		case Mate_DiffuseTexture:
			loc = glGetUniformLocation(_id, "mesh_mate.diffuse_texture");
			break;
		case Mate_SpecularTexture:
			loc = glGetUniformLocation(_id, "mesh_mate.specular_texture");
			break;
		case Mate_Shininess:
			loc = glGetUniformLocation(_id, "mesh_mate.shininess");
			break;
		case Shader_Shadow_Texture:
			loc = glGetUniformLocation(_id, "shadow_texture");
			break;
		}

		if (GL_INVALID_INDEX != loc)
		{
			glUniform1i(loc, value);
		}

		
	}

	void GZJShader::SetFloat(const ShaderData& type, float value) const
	{
		//glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
		int loc = GL_INVALID_INDEX;
		switch (type)
		{
		case Light_Intensity:
			loc = glGetUniformLocation(_id, "light.intensity");
			break;
		case Light_Param_K1:
			loc = glGetUniformLocation(_id, "light.param_k1");
			break;
		case Light_Param_K2:
			loc = glGetUniformLocation(_id, "light.param_k2");
			break;
		case Light_Inner_Angle:
			loc = glGetUniformLocation(_id, "light.inner_angle");
			break;
		case Light_Outter_Angle:
			loc = glGetUniformLocation(_id, "light.outter_angle");
			break;
		case Light_Near_Plane:
			loc = glGetUniformLocation(_id, "light.near_plane");
			break;
		case Light_Far_Plane:
			loc = glGetUniformLocation(_id, "light.far_plane");
			break;
		}

		if (GL_INVALID_INDEX != loc)
		{
			glUniform1f(loc, value);
		}

	}

	void GZJShader::SetVector2(const ShaderData & type, Vector2 value) const
	{
		int loc = GL_INVALID_INDEX;
		
		if (GL_INVALID_INDEX != loc)
		{
			glUniform2f(loc, value.x, value.y);
		}
	}

	void GZJShader::SetVector3(const ShaderData& type, Vector3 value) const
	{
		/*glUniform3f(glGetUniformLocation(_id, name.c_str()), 
			value.x, value.y, value.z);*/
		int loc = GL_INVALID_INDEX;

		switch (type)
		{
		case Light_Ambient:
			loc = glGetUniformLocation(_id, "light.ambient");
			break;
		case Light_Diffuse:
			loc = glGetUniformLocation(_id, "light.diffuse");
			break;
		case Light_Specular:
			loc = glGetUniformLocation(_id, "light.specular");
			break;
		case Light_Position:
			loc = glGetUniformLocation(_id, "light.position");
			break;
		case Light_Direction:
			loc = glGetUniformLocation(_id, "light.direction");
			break;
		case View_ViewPosition:
			loc = glGetUniformLocation(_id, "view_position");
			break;
		}

		if (GL_INVALID_INDEX != loc)
		{
			glUniform3f(loc, value.x, value.y, value.z);
		}

		
	}

	void GZJShader::SetMatrix(ShaderData param, Vector4x4 data)
	{
		unsigned int loc = GL_INVALID_INDEX;
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
		case Shader_Light_Space:
			loc = glGetUniformLocation(_id, "light_space");
			break;
		}
		if (GL_INVALID_INDEX != loc)
		{
			glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(data));
		}
	}

	ResourceType GZJShader::GetResType()
	{
		return Shader;
	}

}
