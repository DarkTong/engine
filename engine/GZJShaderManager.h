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

	public:
		GZJShaderManager() { 
			assert(_instance == nullptr);

			_instance = std::dynamic_pointer_cast<GZJShaderManager>(self);

			_resRoot = ENGINE_ROOT_PATH + "\\src\\shader";
		};
		~GZJShaderManager() {};

	public:
		/** 启动控制器
		*/
		void StartUp();
		/** 关闭控制器
		*/
		void ShutDown();

		/** 准备所有资源
		*/
		void PrepareAll();

	protected:
		/** 创建资源对象
		*/
		GZJResource* createImp(const String& name);

	private:
		/** 获取所有shader的名字
		*/
		void GetAllShaderName();
	};
}

#endif // !_GZJ_SHADER_MANAGER_
