#pragma once

#include "GZJRequire.h"
#include "GZJResource.h"
#include "GZJShader.h"

namespace GZJ_ENGINE {

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

	typedef std::vector<Vertex> Vertices;
	typedef std::vector<unsigned int> Indices;
	typedef std::vector<String> Textures;


	class GZJMesh : public GZJResource {
	private:
		// ��̬ȫ������
		static const int MAX_MATERIAL = 1;
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
		
		GZJMesh(GZJResourceManager* manager, const String& name, ResourceHandle handle);
		
		~GZJMesh();
		
		/** ��ʼ��Mesh�����������
		@param ��������
		@param ��������
		@param ��ͼ����
		*/
		void Prepare(Vertices ver, Indices ind, Textures tex);
		
		/** ��Ⱦ
		@param ��Ⱦ����
		*/
		void Draw(GZJShaderPtr shader);

		ResourceType GetResType();

	private:
		// ���ڽӿ�

		/** ���ض������ݵ��ڴ�
		*/
		void DoLoad();

		/** ж�ض�������
		*/
		void DoUnLoad();
	};
}

#include "GZJResourceManager.h"
#include "GZJTextureManager.h"
