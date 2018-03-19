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
#include "GZJShader.h"

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

		/** shader
		*/
		GZJShaderPtr shader;

		/** 记录某种数据是否获取了
		*/
		std::map<ShaderData, bool> dataRec;

		/** 各种用于shader的数据
		*/
		std::map<unsigned int, float> dataVec1;
		std::map<unsigned int, Vector2> dataVec2;
		std::map<unsigned int, Vector3> dataVec3;
		std::map<unsigned int, Vector4x4> dataMat4;


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

		/** 渲染
		 * param : 着色器
		*/
		void Draw();

		/** 设置用于渲染的shader
		 * param : shader
		*/
		void SetShader(GZJShaderPtr shader);

		/** 配置Shader的各项属性
		*/
		void SetShaderData();

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

		/** prepare
		*/

	public:
		/* 对外的设置Shader数据接口
		*/
		void SetVec1(ShaderData shaderData, Vector3 vec1);
		void SetVec2(ShaderData shaderData, Vector3 vec2);
		void SetVec3(ShaderData shaderData, Vector3 vec3);
		void SetMat4(ShaderData shaderData, Vector4x4 mat4);

	private:
		/** 处理各种shaderData函数
		*/
		void DoTransform(Vector4x4 mat4);
    };
}

#endif //__GZJ_MODEL__
