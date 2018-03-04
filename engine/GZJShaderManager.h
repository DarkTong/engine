#include "GZJRequire.h"
#include "GZJShader.h"
#include "GZJTools.h"

namespace GZJ_ENGINE {

	typedef Map<String, String> ShaderSourceMap;
	typedef Map<String, ShaderID> ShaderVertexMap;
	typedef Map<String, ShaderID> ShaderFragmentMap;
	typedef Map<String, GZJShaderPtr> ShaderObjMap;
	typedef Set<String> ShaderNameSet;

	class GZJShaderManager {
	public:
		static GZJShaderManagerPtr _instance;
		static GZJShaderManagerPtr GetInstance() {
			if (_instance == nullptr)
				_instance = static_cast<GZJShaderManagerPtr>(new GZJShaderManager());
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
		/** ������ɫ��Դ�����
		*/
		ShaderSourceMap _vertexSrcMap;
		/** Ƭ����ɫ��Դ�����
		*/
		ShaderSourceMap _fragmentSrcMap;
		/** ���Ӻ����ɫ�������������
		*/
		ShaderObjMap _objMap;
		/** ������Ϣ
		*/
		char infoLog[1024];

		/** ���ڴ����ļ����ݵ�������
		*/
		//std::stringstream stream;
		/** ���ڴ��ļ����ļ�
		*/
		//std::ifstream file;

	public:
		GZJShaderManager(bool flag = true);
		//~GZJShaderManager();
		/** ͨ�����ֲ�����ɫ������
		@param ��ɫ������
		*/
		GZJShaderPtr GetShaderObjByName(const String& name);

	private:
		/** ����Ƿ�������
		*/
		void CheckCompliceErrors(ShaderID id, ShaderType type);
		/** ��ӹ���õ���ɫ������
		*/
		GZJShaderPtr LoadShaderObj(const String& name);
		/** ��Ӷ�Ӧ����Դ
		*/
		ShaderID LoadShader(const String& name, ShaderType type);
		/** ����Դ��
		*/
		bool ReadSrc(const String& name, ShaderType type);
		/** ��������shader
		*/
		void LoadAll();
		/** ��ȡ����shader������
		*/
		void ReadShaderName();

	public:
		void DeleteMe() {
			// ���shader����
			for (auto it = _objMap.begin(); it != _objMap.end(); ++it) {
				//it->second->DeleteProgram();
				it->second.reset();
			}
			_objMap.clear();
			_fragmentSrcMap.clear();
			_vertexSrcMap.clear();
			_nameSet.clear();
		}
	};
}
