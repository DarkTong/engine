#ifndef __GZJ_MESH__
#define __GZJ_MESH__

#include "GZJRequire.h"
#include "GZJResource.h"
#include "GZJResourceManager.h"
#include "GZJShader.h"

namespace GZJ_ENGINE {
	/** ��Ⱦ�ĵ�Ԫ������߱�һ����Ⱦ�����Ķ���
	*/
	enum TextureType {
		DIFFUSE,
		SPECULAR,
	};

	struct Vertex {
		/** ����
		*/
		Vector3 position;
		/** ������
		*/
		Vector3 normal;
		/** ��ͼ
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
		/** ���еĶ�����Ϣ
		*/
		Vertices vertices;
		/** ���е�������Ϣ
		*/
		Indices indices;
		/** ���е���ͼ
		*/
		Textures textures;
	public:
		
		GZJMesh(GZJResourceManagerPtr manager, const String& name, ResourceHandle handle);
		/** ��ʼ��Mesh�����������
		@param ��������
		@param ��������
		@param ��ͼ����
		*/
		void Prepare(Vertices ver, Indices ind, Textures tex);
		/** ���ض������ݵ��ڴ�
		*/
		void Load();
		/** ж�ض�������
		*/
		void Unload();
		
		/** ��Ⱦ
		@param ��Ⱦ����
		*/
		void Draw(GZJShaderPtr shader);

	};
}
#endif // __GZJ_MESH__
