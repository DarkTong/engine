#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GZJRequire.h"
#include "GZJTransform.h"
#include "GZJResourceManager.h"
#include "GZJMeshManager.h"
#include "GZJTextureManager.h"
#include "GZJShader.h"

namespace GZJ_ENGINE{
    class GZJModel : public GZJResource{
    public:
		/** ��Դ��
		@param ����ǰ��Դ�Ĺ�����
		@param ��Դ�����·��
		*/
		GZJModel(GZJResourceManager* manager, const String& name, ResourceHandle handle);

	private:

		/** ��Դ·��
		*/
		String _direction;

		/** mesh��Դ����
		*/
		GZJMeshManager meshMgr;

		/** shader
		*/
		GZJShaderPtr shader;

		/** ��¼ĳ�������Ƿ��ȡ��
		*/
		std::map<ShaderData, bool> dataRec;

		/** ��������shader������
		*/
		std::map<unsigned int, float> dataVec1;
		std::map<unsigned int, Vector2> dataVec2;
		std::map<unsigned int, Vector3> dataVec3;
		std::map<unsigned int, Vector4x4> dataMat4;

	public:

		/** λ����Ϣ
		*/
		GZJTransform transform;

	public:
		///** ׼����Դ��׼������
		//*/
		//virtual void Prepare( ... ) = 0;

		/** ��Ⱦ
		 * param : ��ɫ��
		*/
		void Draw();

		/** ����������Ⱦ��shader
		 * param : shader
		*/
		void SetShader(GZJShaderPtr shader);

		/** ����Shader�ĸ�������
		*/
		void SetShaderData();

	private:
		/** ������Դ
		*/
		void DoLoad();

		/** ж����Դ
		*/
		void DoUnLoad();

		/** ����assimp�Ľڵ���Ϣ
		@param assimp�ڵ�
		@param assimp����
		*/
		void ProcessNode(aiNode *node, const aiScene *scene);

		/** ����assimp��������Ϣ
		@param assimp����
		@param assimp����
		*/
		void ProcessMesh(aiMesh *mesh, const aiScene *scene);

	public:
		/* ���������Shader���ݽӿ�
		*/
		void SetVec1(ShaderData shaderData, const float& vec1);
		void SetVec2(ShaderData shaderData, const Vector2& vec2);
		void SetVec3(ShaderData shaderData, const Vector3& vec3);
		void SetMat4(ShaderData shaderData, const Vector4x4& mat4);

		/** ��ȡ��Դ����
		*/
		ResourceType GetResType();

	private:
		///** �������shaderData����
		//*/
		//void DoTransform(Vector4x4 mat4);


	private:
		// ���ߺ���
		Textures LoadMaterialTextures(aiMaterial* material, aiTextureType ai_type, TextureType type);

    };
}

#include "GZJModelManager.h"

