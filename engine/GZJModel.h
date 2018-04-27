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
		/** 资源类
		@param 管理当前资源的管理者
		@param 资源的相对路径
		*/
		GZJModel(GZJResourceManager* manager, const String& name, ResourceHandle handle);

	private:

		/** 资源路径
		*/
		String _direction;

		/** mesh资源
		*/
		std::vector<GZJMeshPtr> meshs;

	public:
		///** 准备资源来准备加载
		//*/
		//virtual void Prepare( ... ) = 0;

		/** 渲染
		 * param : 着色器
		*/
		void Draw(const GZJShaderPtr& shader);

	private:
		/** 加载资源
		*/
		void DoLoad();

		/** 卸载资源
		*/
		void DoUnLoad();

		/** 处理assimp的节点信息
		@param assimp节点
		@param assimp场景
		*/
		void ProcessNode(aiNode *node, const aiScene *scene);

		/** 处理assimp的网格信息
		@param assimp网格
		@param assimp场景
		*/
		void ProcessMesh(aiMesh *mesh, const aiScene *scene);

	public:
		/** 获取资源类型
		*/
		ResourceType GetResType();

	private:
		// 工具函数
		Textures LoadMaterialTextures(aiMaterial* material, aiTextureType ai_type, TextureType type);

    };
}

#include "GZJModelManager.h"

