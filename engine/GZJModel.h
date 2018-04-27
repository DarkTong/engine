#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GZJRequire.h"
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

		/** mesh��Դ
		*/
		std::vector<GZJMeshPtr> meshs;

	public:
		///** ׼����Դ��׼������
		//*/
		//virtual void Prepare( ... ) = 0;

		/** ��Ⱦ
		 * param : ��ɫ��
		*/
		void Draw(const GZJShaderPtr& shader);

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
		/** ��ȡ��Դ����
		*/
		ResourceType GetResType();

	private:
		// ���ߺ���
		Textures LoadMaterialTextures(aiMaterial* material, aiTextureType ai_type, TextureType type);

    };
}

#include "GZJModelManager.h"

