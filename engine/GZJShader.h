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
		/** 程序ID
		*/
		ShaderID _id;
		/** 着色器名字
		*/
		String _name;
		/** 着色器管理器
		*/
		//GZJShaderManagerPtr _mgr;
	private:
		/** 构造shader程序
		*/
		void Init();
	public:
		// GZJShader(GZJShaderManagerPtr mgrPtr);

		/** 构造函数2
		@param 着色器管理器
		@param 定点着色器路径
		@param 片段着色器路径
		*/
		GZJShader(ShaderID id, const String& name);
		/** 获取着色器名字
		*/
		String GetName();
		/** 着色器使用
		*/
		void Use() const;
		/** 设置着色器里的布尔值
		@param 变量名
		@param 修改值
		*/
		void SetBool(const String& name, bool value) const;
		/** 设置着色器里的整形值
		@param 变量名
		@param 修改值
		*/
		void SetInt(const String& name, int value) const;
		/** 设置着色器里的浮点值
		@param 变量名
		@param 修改值
		*/
		void SetFloat(const String& name, float value) const;

		void DeleteProgram() {
			glDeleteProgram(_id);
		}
	};

}
