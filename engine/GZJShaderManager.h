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
		/** 存放shader源码的路径
		*/
		const static String rootPath;
		/** 是否启动便加载所有shader
		*/
		static bool LOAD_ALL_SHADER_WHEN_CREATE;
	private:
		/** 记录所有的shader名
		*/
		ShaderNameSet _nameSet;
		/** 顶点着色器源码管理
		*/
		ShaderSourceMap _vertexSrcMap;
		/** 片段着色器源码管理
		*/
		ShaderSourceMap _fragmentSrcMap;
		/** 链接后的着色器程序管理，保留
		*/
		ShaderObjMap _objMap;
		/** 错误信息
		*/
		char infoLog[1024];

		/** 用于处理文件数据的数据流
		*/
		//std::stringstream stream;
		/** 用于打开文件的文件
		*/
		//std::ifstream file;

	public:
		GZJShaderManager(bool flag = true);
		//~GZJShaderManager();
		/** 通过名字查找着色器对象
		@param 着色器名字
		*/
		GZJShaderPtr GetShaderObjByName(const String& name);

	private:
		/** 检查是否编译错误
		*/
		void CheckCompliceErrors(ShaderID id, ShaderType type);
		/** 添加构造好的着色器对象
		*/
		GZJShaderPtr LoadShaderObj(const String& name);
		/** 添加对应的资源
		*/
		ShaderID LoadShader(const String& name, ShaderType type);
		/** 加载源码
		*/
		bool ReadSrc(const String& name, ShaderType type);
		/** 加载所有shader
		*/
		void LoadAll();
		/** 获取所有shader的名字
		*/
		void ReadShaderName();

	public:
		void DeleteMe() {
			// 清空shader对象
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
