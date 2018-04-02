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

	enum ShaderData {
		Transform,
		TexCoord,
		DiffuseTexCoord1,
		SpecularTexCoord1,
		AmbientLight,
		AmbientStrong,
		DiffuseLight,
		DiffuseStrong,
		SpecularLight,
		SpecularStrong,

		// 坐标相关
		Shader_LocalToWorld,
		Shader_WorldToView,
		Shader_ViewToProjection,
	};

	/** ShaderData的字符串表示
	*/
	const std::vector<String> ShaderDataStr = {
		"transform",

		"texcoord",
		"diffuseTexCoord1",
		"specularTexCoord1",

		"ambientLight",
		"ambientStrong",

		"diffuseLight",
		"diffuseStrong",

		"specularLight",
		"specularStrong",
	};

	typedef std::map<String, unsigned int> ShaderDataMap;

	class GZJShader :public GZJResource{

	public:
		// GZJShader(GZJShaderManagerPtr mgrPtr);
		GZJShader(GZJResourceManagerPtr manager, const String & name
			, ResourceHandle handle);

	private:
		/** 程序ID
		*/
		ShaderID _id;

		/** 着色器名字
		*/
		String _name;

		/** 着色器数据
		*/
		ShaderDataMap dataMap;
	private:
		/** 构造shader程序
		*/
		void Init();

		/** 检查是否编译错误
		*/
		void CheckCompliceErrors(ShaderID id, ShaderType type);

		/** 错误信息池
		*/
		char infoLog[1024];

		/** 获取shader的源码
		@param shader的名字
		@param shader的类型
		@return shader源码
		*/
		String ReadSrc(const String& name, ShaderType type);

		/** 加载对应的shader
		@param shader的名字
		@param shader的类型
		*/
		ShaderID LoadShader(const String& name, ShaderType type);

	public:
		/** 加载资源
		*/
		void Load();

		/** 卸载资源
		*/
		void Unload();

		/** 获取着色器名字
		*/
		String GetName();

		/** 获取着色器ID
		*/
		ShaderID GetShaderID();

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

		/** 设置相关的矩阵数据
		*/
		void SetMatrix(ShaderData param, Vector4x4 data);
	};

}

#endif // _GZJ_SHADER_
