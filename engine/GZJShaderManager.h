#ifndef _GZJ_SHADER_MANAGER_
#define _GZJ_SHADER_MANAGER_

#include "GZJRequire.h"
#include "GZJShader.h"
#include "GZJTools.h"

namespace GZJ_ENGINE {

	typedef Map<String, String> ShaderSourceMap;
	//typedef Map<String, GZJShaderPtr> ShaderObjMap;
	typedef Set<String> ShaderNameSet;

	class GZJShaderManager :public GZJResourceManager{
	public:
		static GZJShaderManagerPtr _instance;
		static GZJShaderManagerPtr GetInstance() {
			if (_instance == nullptr)
				new GZJShaderManager();
			return _instance;
		}
		/** ���shaderԴ���·��
		*/
		const static String rootPath;
		/** �Ƿ��������������shader
		*/
		static bool LOAD_ALL_SHADER_WHEN_CREATE;
	private:
		/** ��¼���е�shader��
		*/
		ShaderNameSet _nameSet;

	public:
		GZJShaderManager() { 
			assert(_instance == nullptr);

			_instance = std::dynamic_pointer_cast<GZJShaderManager>(self);

			_resRoot = ENGINE_ROOT_PATH + "\\src\\shader";
		};
		~GZJShaderManager() {};

	public:
		/** ����������
		*/
		void StartUp();
		/** �رտ�����
		*/
		void ShutDown();

		/** ׼��������Դ
		*/
		void PrepareAll();

	protected:
		/** ������Դ����
		*/
		GZJResource* createImp(const String& name);

	private:
		/** ��ȡ����shader������
		*/
		void GetAllShaderName();
	};
}

#endif // !_GZJ_SHADER_MANAGER_
