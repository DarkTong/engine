#include "GZJShader.h"

namespace GZJ_ENGINE {
	void GZJShader::CheckCompliceErrors(ShaderID id, ShaderType type)
	{
		int success = 0;
		char infoLog[1024];
		if (type != PROGRAM_SHADER){
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if(!success){
				glGetShaderInfoLog(id, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" 
					<< infoLog << "\n " 
					<< "-- --------------------------------------------------- -- " 
					<< std::endl;
			}
		}
		else {
			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if(!success){ 
				glGetShaderInfoLog(id, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_LINKING_ERROR of type: " << type << "\n"
					<< infoLog << "\n "
					<< "-- --------------------------------------------------- -- "
					<< std::endl;
			}
		}
	}
	void GZJShader::Init()
	{
	}
	GZJShader::GZJShader(GZJShaderManagerPtr mgrPtr, ShaderID id)
		:_mgr(mgrPtr), _id(id)
	{
		Init();
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
}
