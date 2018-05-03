#ifndef _GZJ_SHADER_
#define _GZJ_SHADER_

#include "GZJRequire.h"
#include "GZJResource.h"

namespace GZJ_ENGINE {
	typedef unsigned int ShaderID;

	enum ShaderType {
		PROGRAM_SHADER = 0x01,
		VERTEX_SHADER = 0x02,
		FRAGMENT_SHADER = 0x04,
		GEOMETRY_SHADER = 0x08,
	};

	enum ShaderData {
		TexCoords,
		Shader_IsOpenShadow,
		Shader_Ambient_Color,

		// �������
		Mate_DiffuseTexture,
		Mate_DiffuseColor,
		Mate_SpecularTexture,
		Mate_SpecularColor,
		Mate_BumpTexture,
		Mate_Shininess,			// ����ϵ��
		Mate_Flag_DiffuseTextureUse,	//�Ƿ�ʹ��������������ͼ
		Mate_Flag_SpecularTextureUse,
		Mate_Flag_NormalTextureUse,

		// �������
		Light_Ambient,
		Light_Diffuse,
		Light_Specular,
		Light_Color,
		Light_Intensity,
		Light_Position,
		Light_Direction,
		Light_Param_K1,			// һ��������ϵ��
		Light_Param_K2,			// ����������ϵ��
		Light_Inner_Angle,		// ���й��
		Light_Outter_Angle,		// ���й��
		Light_Near_Plane,
		Light_Far_Plane,
		Light_Ortho_Width,
		Light_Perspective_Angle,

		// �۲���
		View_ViewPosition,

		// shadow
		Shader_Shadow_Texture,

		// �������
		Shader_LocalToWorld,
		Shader_WorldToView,
		Shader_ViewToProjection,
		Shader_Light_Space,

		// ��
		Shader_None,
	};

	/** ShaderData���ַ�����ʾ
	*/
	const std::vector<String> ShaderDataStr = {
		"texcoord",
		"is_open_shadow",
		"ambient_color",

		// �������
		"mesh_mate.diffuse_texture",
		"mesh_mate.diffuse_color",
		"mesh_mate.specular_texture",
		"mesh_mate.specular_color",
		"mesh_mate.shininess"
		"mesh_mate.diffuse_tex_use",
		"mesh_mate.specular_tex_use",
		"mesh_mate.normal_tex_use",

		// �������
		"light.ambient",
		"light.diffuse",
		"light.specular",
		"light.color",
		"light.intensity",
		"light_transform.position",
		"light_transform.direction",
		"light.param_k1",
		"light.param_k2",
		"light.inner_angle",
		"light.outter_angle",

		// �۲���
		"view_position",

		// shadow
		"shadow_texture",

		// �������
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
		/** ����ID
		*/
		ShaderID _id;

		/** ��ɫ������
		*/
		ShaderDataMap dataMap;

		/** ʹ�õ�shader���ͼ���
		*/
		unsigned int shaderTypeSet;
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

		/** ������Դ
		*/
		void DoLoad();

		/** ж����Դ
		*/
		void DoUnLoad();

		/** ����shander�ӳ���
		*/
		void BuildSubShader(ShaderType type);

	public:

		/** ��ȡ��ɫ������
		*/
		String GetName();

		/** ��ȡ��ɫ��ID
		*/
		ShaderID GetShaderID();

		/** ��ɫ��ʹ��
		*/
		void Use() const;

		/** ������ɫ����Ĳ���ֵ
		@param ������
		@param �޸�ֵ
		*/
		void SetBool(const ShaderData& type, bool value) const;

		/** ������ɫ���������ֵ
		@param ������
		@param �޸�ֵ
		*/
		void SetInt(const ShaderData& type, int value) const;

		/** ������ɫ����ĸ���ֵ
		@param ������
		@param �޸�ֵ
		*/
		void SetFloat(const ShaderData& type, float value) const;

		/** ������ɫ��Vector3����
		@param ������
		@param ֵ
		*/
		void SetVector2(const ShaderData& type, Vector2 value) const;

		/** ������ɫ��Vector3����
		@param ������
		@param ֵ
		*/
		void SetVector3(const ShaderData& type, Vector3 value) const;

		/** ������صľ�������
		*/
		void SetMatrix(ShaderData param, Vector4x4 data);

		/** ������ɫ��ʹ�����ͼ��ϵ�Ԫ��
		*/
		void SetUseShaderSet(ShaderType type, int flag);


		ResourceType GetResType();
	};
}

#endif // _GZJ_SHADER_
