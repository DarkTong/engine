#ifndef __GZJ_MODEL__
#define __GZJ_MODEL__

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GZJRequire.h"
#include "GZJResource.h"
#include "GZJResourceManager.h"
#include "GZJMeshManager.h"
#include "GZJMesh.h"

namespace GZJ_ENGINE{
    class GZJModel : public GZJResource{
    public:
		/** 资源类
		@param 管理当前资源的管理者
		@param 资源的相对路径
		*/
		GZJModel(GZJResourceManagerPtr manager, const String& name, ResourceHandle handle);

	private:
		/** mesh资源管理
		*/
		GZJMeshManager meshMgr;
	public:
		///** 准备资源来准备加载
		//*/
		//virtual void Prepare( ... ) = 0;

		/** 加载资源
		*/
		void Load();

		/** 卸载资源
		*/
		void Unload();

	private:
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
    };
}

#endif //__GZJ_MODEL__
