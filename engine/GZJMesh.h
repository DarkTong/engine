#pragma once

#include "GZJRequire.h"
#include "GZJResource.h"
#include "GZJShader.h"

namespace GZJ_ENGINE {

	struct Vertex {
		/** 定点
		*/
		Vector3 position;
		/** 法线量
		*/
		Vector3 normal;
		/** 贴图
		*/
		Vector2 texCoords;

	};

	typedef std::vector<Vertex> Vertices;
	typedef std::vector<unsigned int> Indices;
	typedef std::vector<String> Textures;


	class GZJMesh : public GZJResource {
	private:
		// 静态全局数据
		static const int MAX_MATERIAL = 1;
	private:

		unsigned int VAO, VBO, EBO;
		/** 所有的定点信息
		*/
		Vertices vertices;
		/** 所有的索引信息
		*/
		Indices indices;
		/** 所有的贴图
		*/
		Textures textures;
	public:
		
		GZJMesh(GZJResourceManager* manager, const String& name, ResourceHandle handle);
		
		~GZJMesh();
		
		/** 初始化Mesh，并获得数据
		@param 定点数据
		@param 索引数据
		@param 贴图数据
		*/
		void Prepare(Vertices ver, Indices ind, Textures tex);
		
		/** 渲染
		@param 渲染程序
		*/
		void Draw(GZJShaderPtr shader);

		ResourceType GetResType();

	private:
		// 对内接口

		/** 加载定点数据到内存
		*/
		void DoLoad();

		/** 卸载定点数据
		*/
		void DoUnLoad();
	};
}

#include "GZJResourceManager.h"
#include "GZJTextureManager.h"
