#include "GZJShader.h"

namespace GZJ_ENGINE {
	

	void GZJShader::Init()
	{
		shaderTypeSet |= VERTEX_SHADER;
		shaderTypeSet |= FRAGMENT_SHADER;
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
		// 1. ���ļ�·���л�ȡ����/Ƭ����ɫ��
		std::ifstream file;
		std::stringstream stream;
		String path;
		// ��֤ifstream��������׳��쳣��
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			if (type == ShaderType::VERTEX_SHADER)
				path = _path + ".vs";
			else if (type == ShaderType::FRAGMENT_SHADER)
				path = _path + ".fs";
			else if (type == ShaderType::GEOMETRY_SHADER)
				path = _path + ".gs";
			/*std::cout << "path:" << path << std::endl;*/
			// ���ļ�
			file.open(path);
			// ��ȡ�ļ��Ļ������ݵ���������
			stream.clear();
			stream.str("");
			stream << file.rdbuf();
			// �ر��ļ�������
			file.close();
			// ת����������string
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
		ShaderID id = GL_NONE;
		switch (type)
		{
		case VERTEX_SHADER:
			id = glCreateShader(GL_VERTEX_SHADER);
			break;
		case FRAGMENT_SHADER:
			id = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		case GEOMETRY_SHADER:
			id = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		}
		
		const char *a = src.c_str();
		glShaderSource(id, 1, &a, NULL);
		glCompileShader(id);

		CheckCompliceErrors(id, type);

		return id;
	}

	void GZJShader::DoLoad()
	{
		_id = glCreateProgram();
		BuildSubShader(VERTEX_SHADER);
		BuildSubShader(GEOMETRY_SHADER);
		BuildSubShader(FRAGMENT_SHADER);
		glLinkProgram(_id);

		CheckCompliceErrors(_id, PROGRAM_SHADER);

	}

	void GZJShader::DoUnLoad()
	{
		dataMap.clear();
	}

	void GZJShader::BuildSubShader(ShaderType type)
	{
		if (shaderTypeSet & type)
		{
			ShaderID it = LoadShader(_name, type);
			glAttachShader(_id, it);
			glDeleteShader(it);
		}
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
		int loc = GL_INVALID_INDEX;
		switch (type)
		{
		case Mate_Flag_DiffuseTextureUse:
			loc = glGetUniformLocation(_id, "mesh_mate.diffuse_tex_use");
			break;
		case Mate_Flag_SpecularTextureUse:
			loc = glGetUniformLocation(_id, "mesh_mate.specular_tex_use");
			break;
		case Mate_Flag_NormalTextureUse:
			loc = glGetUniformLocation(_id, "mesh_mate.normal_tex_use");
			break;
		case Shader_IsOpenShadow:
			loc = glGetUniformLocation(_id, "is_open_shadow");
			break;
		}
		if (loc != GL_INVALID_INDEX)
			Use();
			glUniform1i(loc, value);
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
		case Mate_BumpTexture:
			loc = glGetUniformLocation(_id, "mesh_mate.normal_texture");
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
			Use();
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
			Use();
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
		case Light_Color:
			loc = glGetUniformLocation(_id, "light.color");
			break;
		case Light_Position:
			loc = glGetUniformLocation(_id, "light_transform.position");
			break;
		case Light_Direction:
			loc = glGetUniformLocation(_id, "light_transform.direction");
			break;
		case View_ViewPosition:
			loc = glGetUniformLocation(_id, "view_position");
			break;
		case Mate_DiffuseColor:
			loc = glGetUniformLocation(_id, "mesh_mate.diffuse_color");
			break;
		case Mate_SpecularColor:
			loc = glGetUniformLocation(_id, "mesh_mate.specular_color");
			break;
		case Shader_Ambient_Color:
			loc = glGetUniformLocation(_id, "ambient_color");
			break;
		}

		if (GL_INVALID_INDEX != loc)
		{
			Use();
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
			Use();
			glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(data));
		}
	}

	void GZJShader::SetUseShaderSet(ShaderType type, int flag)
	{
		shaderTypeSet |= type;
		if (!flag)
			shaderTypeSet -= type;
	}

	ResourceType GZJShader::GetResType()
	{
		return Shader;
	}

}
