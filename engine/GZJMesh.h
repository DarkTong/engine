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
	typedef std::vector<GZJTexturePtr> Textures;


	class GZJMesh{
	private:
		// 静态全局数据
		static const int MAX_MATERIAL = 1;
	private:
		// GPU句柄
		unsigned int VAO, VBO, EBO;
	public:
		/** 所有的定点信息
		*/
		Vertices vertices;
		/** 所有的索引信息
		*/
		Indices indices;
		/** 所有的贴图
		*/
		Textures textures;

		/** 各项材质颜色
		*/
		Vector3 diffuseColor;
		Vector3 specularColor;
	public:
		
		GZJMesh();
		
		~GZJMesh();
		
		/** 渲染
		@param 渲染程序
		*/
		void Draw(GZJShaderPtr shader);

		/** 是否已经在GPU中申请内存了
		*/
		bool IsLoginGPU();

		/** 加载定点数据到内存
		*/
		void LoginGPU();

		/** 卸载定点数据
		*/
		void LogoutGPU();
	};
}

#include "GZJResourceManager.h"
#include "GZJTextureManager.h"
