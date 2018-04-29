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
		TexCoords,
		Shader_IsOpenShadow,

		// 材质相关
		Mate_DiffuseTexture,
		Mate_SpecularTexture,
		Mate_Shininess,			// 反光系数

		// 光照相关
		Light_Ambient,
		Light_Diffuse,
		Light_Specular,
		Light_Intensity,
		Light_Position,
		Light_Direction,
		Light_Param_K1,			// 一次项距离的系数
		Light_Param_K2,			// 二次项距离的系数
		Light_Inner_Angle,		// 内切光角
		Light_Outter_Angle,		// 外切光角
		Light_Near_Plane,
		Light_Far_Plane,
		Light_Ortho_Width,
		Light_Perspective_Angle,

		// 观察者
		View_ViewPosition,

		// shadow
		Shader_Shadow_Texture,

		// 坐标相关
		Shader_LocalToWorld,
		Shader_WorldToView,
		Shader_ViewToProjection,
		Shader_Light_Space,

		// 空
		Shader_None,
	};

	/** ShaderData的字符串表示
	*/
	const std::vector<String> ShaderDataStr = {
		"texcoord",
		"is_open_shadow",

		// 材质相关
		"mesh_mate.diffuse_texture",
		"mesh_mate.specular_texture",
		"mesh_mate.shininess"

		// 光照相关
		"light.ambient",
		"light.diffuse",
		"light.specular",
		"light.intensity",
		"light.position",
		"light.direction",
		"light.param_k1",
		"light.param_k2",
		"light.inner_angle",
		"light.outter_angle",

		// 观察者
		"view_position",

		// shadow
		"shadow_texture",

		// 坐标相关
		"local2world",
		"world2view",
		"view2projection",
		"light_space"
	};

	typedef std::map<String, unsigned int> ShaderDataMap;

	class GZJShader :public GZJResource{

	public:
		// GZJShader(GZJShaderManagerPtr mgrPtr);
		GZJShader(GZJResourceManager* manager, const String & name
			, ResourceHandle handle);

	private:
		/** 程序ID
		*/
		ShaderID _id;

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

		/** 加载资源
		*/
		void DoLoad();

		/** 卸载资源
		*/
		void DoUnLoad();

	public:

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
		void SetBool(const ShaderData& type, bool value) const;

		/** 设置着色器里的整形值
		@param 变量名
		@param 修改值
		*/
		void SetInt(const ShaderData& type, int value) const;

		/** 设置着色器里的浮点值
		@param 变量名
		@param 修改值
		*/
		void SetFloat(const ShaderData& type, float value) const;

		/** 设置着色器Vector3数据
		@param 变量名
		@param 值
		*/
		void SetVector2(const ShaderData& type, Vector2 value) const;

		/** 设置着色器Vector3数据
		@param 变量名
		@param 值
		*/
		void SetVector3(const ShaderData& type, Vector3 value) const;

		/** 设置相关的矩阵数据
		*/
		void SetMatrix(ShaderData param, Vector4x4 data);

		ResourceType GetResType();
	};
}

#endif // _GZJ_SHADER_
