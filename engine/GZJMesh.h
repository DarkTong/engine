#ifndef __GZJ_MESH__
#define __GZJ_MESH__

#include "GZJRequire.h"
#include "GZJResource.h"
#include "GZJResourceManager.h"
#include "GZJTextureManager.h"
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
		/** 加载定点数据到内存
		*/
		void Load();
		/** 卸载定点数据
		*/
		void Unload();
		
		/** 渲染
		@param 渲染程序
		*/
		void Draw(GZJShaderPtr shader);

	};
}
#endif // __GZJ_MESH__
