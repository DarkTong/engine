#ifndef __GZJ_MESH__
#define __GZJ_MESH__

#include "GZJRequire.h"
#include "GZJResource.h"
#include "GZJResourceManager.h"
#include "GZJShader.h"

namespace GZJ_ENGINE {
	/** 渲染的单元组件，具备一次渲染基本的东西
	*/
	enum TextureType {
		DIFFUSE,
		SPECULAR,
	};

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

	struct Texture {
		unsigned int textureID;

	};

	typedef std::vector<Vertex> Vertices;
	typedef std::vector<unsigned int> Indices;
	typedef std::vector<Texture> Textures;


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
		
		GZJMesh(GZJResourceManagerPtr manager, const String& name, ResourceHandle handle);
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
