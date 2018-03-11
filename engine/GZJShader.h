#ifndef _GZJ_SHADER_
#define _GZJ_SHADER_
#include "GZJRequire.h"
#include "GZJResource.h"

namespace GZJ_ENGINE {
	typedef unsigned int ShaderID;

	enum ShaderType {
		PROGRAM_SHADER,
		VERTEX_SHADER,
		FRAGMENT_SHADER,
	};

	class GZJShader :public GZJResource{

	public:
		// GZJShader(GZJShaderManagerPtr mgrPtr);
		GZJShader(GZJResourceManagerPtr manager, const String & name
			, ResourceHandle handle);

	private:
		/** ����ID
		*/
		ShaderID _id;

		/** ��ɫ������
		*/
		String _name;

	private:
		/** ����shader����
		*/
		void Init();

		/** ����Ƿ�������
		*/
		void CheckCompliceErrors(ShaderID id, ShaderType type);

		/** ������Ϣ��
		*/
		char infoLog[1024];

		/** ��ȡshader��Դ��
		@param shader������
		@param shader������
		@return shaderԴ��
		*/
		String ReadSrc(const String& name, ShaderType type);

		/** ���ض�Ӧ��shader
		@param shader������
		@param shader������
		*/
		ShaderID LoadShader(const String& name, ShaderType type);

	public:
		/** ������Դ
		*/
		void Load();

		/** ж����Դ
		*/
		void Unload();

		/** ��ȡ��ɫ������
		*/
		String GetName();

		/** ��ɫ��ʹ��
		*/
		void Use() const;

		/** ������ɫ����Ĳ���ֵ
		@param ������
		@param �޸�ֵ
		*/
		void SetBool(const String& name, bool value) const;

		/** ������ɫ���������ֵ
		@param ������
		@param �޸�ֵ
		*/
		void SetInt(const String& name, int value) const;

		/** ������ɫ����ĸ���ֵ
		@param ������
		@param �޸�ֵ
		*/
		void SetFloat(const String& name, float value) const;

		void DeleteProgram() {
			glDeleteProgram(_id);
		}
	};

}

#endif // _GZJ_SHADER_
