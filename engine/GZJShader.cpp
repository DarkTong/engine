#include "GZJShader.h"

namespace GZJ_ENGINE {
	void GZJShader::Init()
	{
	}
	GZJShader::GZJShader(ShaderID id, const String& name)
		: _id(id), _name(name)
	{
		Init();
	}
	String GZJShader::GetName()
	{
		return _name;
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
