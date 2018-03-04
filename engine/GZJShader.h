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
		/** ������ɫ������·��
		*/
		String _vertexPath;
		/** Ƭ����ɫ������·��
		*/
		String _fragmentPath;
		/** ��ɫ��������
		*/
		GZJShaderManagerPtr _mgr;
	private:
		/** ����shader����
		*/
		void Init();
	public:
		/** �����뼰���ӵĴ���
		@param ����id
		@param ��������
		*/
		void CheckCompliceErrors(ShaderID id, ShaderType type);

		// GZJShader(GZJShaderManagerPtr mgrPtr);

		/** ���캯��2
		@param ��ɫ��������
		@param ������ɫ��·��
		@param Ƭ����ɫ��·��
		*/
		GZJShader(GZJShaderManagerPtr mgrPtr, ShaderID id);
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
	};

}
