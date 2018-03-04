#include "GZJRequire.h"

namespace GZJ_ENGINE {
	typedef unsigned int ShaderID;

	enum ShaderType {
		PROGRAM_SHADER,
		VERTEX_SHADER,
		FRAGMENT_SHADER,
	};

	class GZJShader {
	private:
		/** ����ID
		*/
		ShaderID _id;
		/** ��ɫ������
		*/
		String _name;
		/** ��ɫ��������
		*/
		//GZJShaderManagerPtr _mgr;
	private:
		/** ����shader����
		*/
		void Init();
	public:
		// GZJShader(GZJShaderManagerPtr mgrPtr);

		/** ���캯��2
		@param ��ɫ��������
		@param ������ɫ��·��
		@param Ƭ����ɫ��·��
		*/
		GZJShader(ShaderID id, const String& name);
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
